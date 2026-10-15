// SPDX-License-Identifier: Apache-2.0
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libqril.h"
#include "qmi_dms.h"
#include "qmi_nas.h"
#include "qmi_uim.h"
#include "qmi_wms.h"

#include "qmi_glue.h"

static struct glue_callbacks callbacks;
static uint32_t sms_transaction_id;
static bool sms_needs_ack;

static void handle_wms_event(struct qmi_header *hdr, size_t len)
{
	struct wms_event_report_ind *ind = WMS_EVENT_REPORT_IND_NEW;
	int rc;

	rc = qmi_decode_message2(hdr, len, ind);
	if (rc < 0 || !ind->transfer_route_valid) {
		log_error("WMS event report without a transferred message (%d)", rc);
		free(ind);
		return;
	}

	sms_transaction_id = ind->transfer_route.transaction_id;
	sms_needs_ack = ind->transfer_route.ack_indicator == 0;
	log_info("New SMS: %u bytes, transaction %u, ack %d", ind->transfer_route.data_len,
		 sms_transaction_id, sms_needs_ack);
	if (callbacks.new_sms)
		callbacks.new_sms(ind->transfer_route.data, ind->transfer_route.data_len);
	free(ind);
}

static void copy_str(char *dst, int len, const char *src, uint32_t src_len)
{
	uint32_t n = src_len < (uint32_t)(len - 1) ? src_len : (uint32_t)(len - 1);

	memcpy(dst, src, n);
	dst[n] = '\0';
}

static void on_indication(void *data, enum qmi_service service, struct qmi_header *hdr,
			  size_t len)
{
	if (service == QMI_SERVICE_NAS) {
		if (hdr->msg_id == QMI_NAS_SERVING_SYSTEM_REPORT && callbacks.serving_changed)
			callbacks.serving_changed();
		else if (hdr->msg_id == QMI_NAS_SIGNAL_INFO_REPORT && callbacks.signal_changed)
			callbacks.signal_changed();
	} else if (service == QMI_SERVICE_WMS) {
		if (hdr->msg_id == QMI_WMS_EVENT_REPORT)
			handle_wms_event(hdr, len);
	} else if (service == QMI_SERVICE_UIM) {
		if (callbacks.sim_changed)
			callbacks.sim_changed();
	}
}

static struct libqril_events events = {
	.on_qmi_indication = on_indication,
};

static int register_nas_indications(void)
{
	struct nas_register_indications_req *req = NAS_REGISTER_INDICATIONS_REQ_NEW;
	int rc;

	memset((char *)req + sizeof(req->hdr), 0, sizeof(*req) - sizeof(req->hdr));
	req->serving_system_events = true;
	req->signal_info = true;
	req->current_plmn_name = true;
	req->subscription_info = true;
	req->network_time = true;

	rc = libqril_send_message_ack_sync(&req->hdr);
	free(req);
	return rc;
}

static int setup_sms(void)
{
	struct wms_set_routes_req *routes = WMS_SET_ROUTES_REQ_NEW;
	struct wms_set_event_report_req *ev = WMS_SET_EVENT_REPORT_REQ_NEW;
	int rc, i;

	memset((char *)routes + sizeof(routes->hdr), 0, sizeof(*routes) - sizeof(routes->hdr));
	routes->routes_len = 5;
	for (i = 0; i < 5; i++) {
		routes->routes[i].message_type = 0;
		routes->routes[i].message_class = i;
		routes->routes[i].storage = QMI_WMS_STORAGE_TYPE_NONE;
		routes->routes[i].receipt_action = QMI_WMS_RECEIPT_ACTION_TRANSFER_ONLY;
	}
	routes->transfer_status_report_valid = true;
	routes->transfer_status_report = 1;
	rc = libqril_send_message_ack_sync(&routes->hdr);
	if (rc)
		log_error("Failed to set SMS routes: %d", rc);
	free(routes);

	memset((char *)ev + sizeof(ev->hdr), 0, sizeof(*ev) - sizeof(ev->hdr));
	ev->new_mt_message_indicator_valid = true;
	ev->new_mt_message_indicator = 1;
	rc = libqril_send_message_ack_sync(&ev->hdr);
	if (rc)
		log_error("Failed to enable SMS event reports: %d", rc);
	free(ev);
	return rc;
}

int glue_init(const struct glue_callbacks *cb)
{
	int rc;

	callbacks = *cb;
	libqril_init();
	libqril_wait_for_service_discovery();
	libqril_register_event_handlers(&events, NULL);

	rc = glue_set_online(true);
	if (rc)
		log_error("Failed to bring the modem online: %d", rc);

	rc = glue_set_mode_pref_lte();
	if (rc)
		log_error("Failed to set the mode preference: %d", rc);

	rc = register_nas_indications();
	if (rc)
		log_error("Failed to register NAS indications: %d", rc);

	setup_sms();

	return 0;
}

int glue_set_online(bool online)
{
	struct dms_set_operating_mode_req *req = DMS_SET_OPERATING_MODE_REQ_NEW;
	int rc;

	req->mode = online ? 0 : 1;
	rc = libqril_send_message_ack_sync(&req->hdr);
	free(req);
	return rc;
}

int glue_get_online(bool *online)
{
	struct dms_get_operating_mode_resp *resp = DMS_GET_OPERATING_MODE_RESP_NEW;
	int rc;

	rc = libqril_send_basic_request_sync(QMI_SERVICE_DMS, QMI_DMS_GET_OPERATING_MODE,
					     &resp->hdr);
	if (!rc)
		*online = resp->mode == 0;
	free(resp);
	return rc;
}

int glue_set_mode_pref_lte(void)
{
	struct nas_set_system_prefs *req = NAS_SET_SYSTEM_PREFS_NEW;
	int rc;

	memset((char *)req + sizeof(req->hdr), 0, sizeof(*req) - sizeof(req->hdr));
	req->mode_preference_valid = true;
	req->mode_preference = 0x04 | 0x08 | 0x10;
	rc = libqril_send_message_ack_sync(&req->hdr);
	free(req);
	return rc;
}

int glue_get_ids(char *imei, char *imeisv, int len)
{
	struct dms_get_ids_resp *resp = DMS_GET_IDS_RESP_NEW;
	int rc;

	rc = libqril_send_basic_request_sync(QMI_SERVICE_DMS, QMI_DMS_GET_IDS, &resp->hdr);
	if (!rc) {
		copy_str(imei, len, resp->imei, resp->imei_len);
		copy_str(imeisv, len, resp->imei_ver, resp->imei_ver_len);
	}
	free(resp);
	return rc;
}

int glue_get_revision(char *rev, int len)
{
	struct dms_get_revision_resp *resp = DMS_GET_REVISION_RESP_NEW;
	int rc;

	rc = libqril_send_basic_request_sync(QMI_SERVICE_DMS, QMI_DMS_GET_REVISION, &resp->hdr);
	if (!rc)
		copy_str(rev, len, resp->revision, resp->revision_len);
	free(resp);
	return rc;
}

int glue_get_imsi(char *imsi, int len)
{
	struct dms_uim_get_imsi *resp = DMS_UIM_GET_IMSI_NEW;
	int rc;

	rc = libqril_send_basic_request_sync(QMI_SERVICE_DMS, QMI_DMS_UIM_GET_IMSI, &resp->hdr);
	if (!rc)
		copy_str(imsi, len, resp->imsi, resp->imsi_len);
	free(resp);
	return rc;
}

int glue_get_iccid(char *iccid, int len)
{
	static const char digits[] = "0123456789";
	struct uim_read_transparent_req *req = UIM_READ_TRANSPARENT_REQ_NEW;
	struct uim_read_transparent_resp *resp = UIM_READ_TRANSPARENT_RESP_NEW;
	int rc, i, n = 0;

	iccid[0] = '\0';
	memset((char *)req + sizeof(req->hdr), 0, sizeof(*req) - sizeof(req->hdr));
	req->session.type = 6;
	req->file.file_id = 0x2fe2;
	req->file.path_len = 2;
	req->file.path[0] = 0x00;
	req->file.path[1] = 0x3f;

	rc = libqril_send_message_sync(&req->hdr, &resp->hdr);
	if (!rc && resp->read_result_valid) {
		for (i = 0; i < (int)resp->read_result_len && n < len - 2; i++) {
			uint8_t lo = resp->read_result[i] & 0xf, hi = resp->read_result[i] >> 4;

			if (lo < 10)
				iccid[n++] = digits[lo];
			if (hi < 10)
				iccid[n++] = digits[hi];
		}
		iccid[n] = '\0';
	}
	free(req);
	free(resp);
	return rc;
}

int glue_get_msisdn(char *msisdn, int len)
{
	struct dms_get_msisdn *resp = DMS_GET_MSISDN_NEW;
	int rc;

	rc = libqril_send_basic_request_sync(QMI_SERVICE_DMS, QMI_DMS_GET_MSISDN, &resp->hdr);
	if (!rc)
		copy_str(msisdn, len, resp->msisdn, resp->msisdn_len);
	free(resp);
	return rc;
}

int glue_get_signal(struct glue_signal *s)
{
	struct nas_get_signal_info *resp = NAS_GET_SIGNAL_INFO_NEW;
	int rc;

	memset(s, 0, sizeof(*s));
	rc = libqril_send_basic_request_sync(QMI_SERVICE_NAS, QMI_NAS_GET_SIGNAL_INFO, &resp->hdr);
	if (!rc) {
		s->gsm_valid = resp->gsm_valid;
		s->gsm_rssi = resp->gsm;
		s->wcdma_valid = resp->wcdma_valid;
		s->wcdma_rssi = resp->wcdma.rssi;
		s->wcdma_ecio = resp->wcdma.ecio;
		s->lte_valid = resp->lte_valid;
		s->lte_rssi = resp->lte.rssi;
		s->lte_rsrq = resp->lte.rsrq;
		s->lte_rsrp = resp->lte.rsrp;
		s->lte_snr = resp->lte.snr;
	}
	free(resp);
	return rc;
}

int glue_get_serving(struct glue_serving *s)
{
	struct nas_serving_system_resp *resp = NAS_SERVING_SYSTEM_RESP_NEW;
	int rc;

	memset(s, 0, sizeof(*s));
	rc = libqril_send_basic_request_sync(QMI_SERVICE_NAS, QMI_NAS_SERVING_SYSTEM_REPORT,
					     &resp->hdr);
	if (!rc) {
		if (resp->system_valid) {
			s->reg_state = resp->system.registration_state;
			s->cs_attached = resp->system.cs_attach_state;
			s->ps_attached = resp->system.ps_attach_state;
			s->rat = resp->system.radio_interfaces_len ? resp->system.radio_interfaces[0]
								   : GLUE_RAT_NONE;
		}
		s->plmn_valid = resp->plmn_valid;
		if (resp->plmn_valid) {
			s->mcc = resp->plmn.mcc;
			s->mnc = resp->plmn.mnc;
			copy_str(s->description, sizeof(s->description), resp->plmn.description,
				 resp->plmn.description_len);
			if (!s->description[0]) {
				char short_name[65];

				glue_get_plmn_name(s->mcc, s->mnc, s->description, short_name,
						   sizeof(s->description));
			}
		}
		s->lac_valid = resp->lac_valid;
		s->lac = resp->lac;
		s->cid_valid = resp->cid_valid;
		s->cid = resp->cid;
	}
	free(resp);
	return rc;
}

int glue_get_card(struct glue_card *c)
{
	struct uim_get_card_status_resp *resp = UIM_GET_CARD_STATUS_RESP_NEW;
	struct uim_card_status_cards *card;
	struct uim_card_status_cards_applications *app;
	int rc, i;

	memset(c, 0, sizeof(*c));
	rc = libqril_send_basic_request_sync(QMI_SERVICE_UIM, QMI_UIM_GET_CARD_STATUS, &resp->hdr);
	if (rc || !resp->status_valid || !resp->status.cards_len) {
		free(resp);
		return rc ? rc : -ENODEV;
	}

	card = &resp->status.cards[0];
	c->card_state = card->card_state;
	c->present = card->card_state == 1;
	c->upin_state = card->upin_state;
	if (card->applications_len) {
		app = &card->applications[0];
		c->app_type = app->type;
		c->app_state = app->state;
		c->perso_state = app->personalization_state;
		c->pin1_state = app->pin1_state;
		c->pin2_state = app->pin2_state;
		c->upin_replaces_pin1 = app->upin_replaces_pin1;
		for (i = 0; i < app->application_identifier_value_len && i < 16; i++)
			sprintf(c->aid + 2 * i, "%02x", app->application_identifier_value[i]);
	}
	free(resp);
	return 0;
}

static void decode_name(char *dst, int len, uint8_t enc, const uint8_t *src, uint8_t src_len)
{
	int i, n = 0;

	if (enc == 1) {
		for (i = 0; i + 1 < src_len && n < len - 1; i += 2)
			dst[n++] = src[i + 1] ? '?' : (char)src[i];
	} else {
		for (i = 0; i < src_len && n < len - 1; i++)
			dst[n++] = (char)src[i];
	}
	dst[n] = '\0';
}

int glue_get_plmn_name(int mcc, int mnc, char *long_name, char *short_name, int len)
{
	static int cached_mcc = -1, cached_mnc = -1;
	static char cached_long[128], cached_short[128];
	struct nas_get_plmn_name_req *req;
	struct nas_get_plmn_name_resp *resp;
	int rc;

	if (mcc == cached_mcc && mnc == cached_mnc) {
		snprintf(long_name, len, "%s", cached_long);
		snprintf(short_name, len, "%s", cached_short);
		return 0;
	}

	req = NAS_GET_PLMN_NAME_REQ_NEW;
	resp = NAS_GET_PLMN_NAME_RESP_NEW;
	memset((char *)req + sizeof(req->hdr), 0, sizeof(*req) - sizeof(req->hdr));
	req->plmn.mcc = mcc;
	req->plmn.mnc = mnc;
	rc = libqril_send_message_sync(&req->hdr, &resp->hdr);
	if (!rc && resp->plmn_name_valid) {
		struct nas_eons_plmn_name *n = &resp->plmn_name;

		decode_name(cached_long, sizeof(cached_long), n->long_name_encoding, n->long_name,
			    n->long_name_len);
		decode_name(cached_short, sizeof(cached_short), n->short_name_encoding, n->short_name,
			    n->short_name_len);
		if (!cached_long[0])
			decode_name(cached_long, sizeof(cached_long), n->sp_name_encoding, n->sp_name,
				    n->sp_name_len);
		if (!cached_short[0])
			snprintf(cached_short, sizeof(cached_short), "%s", cached_long);
		cached_mcc = mcc;
		cached_mnc = mnc;
		log_info("PLMN %d-%d name '%s' / '%s'", mcc, mnc, cached_long, cached_short);
	} else if (!rc) {
		rc = -ENODATA;
	}
	snprintf(long_name, len, "%s", cached_mcc == mcc && cached_mnc == mnc ? cached_long : "");
	snprintf(short_name, len, "%s", cached_mcc == mcc && cached_mnc == mnc ? cached_short : "");
	free(req);
	free(resp);
	return rc;
}

int glue_sms_send(const uint8_t *pdu, int len, int *message_ref, int *cause)
{
	struct wms_raw_send_req *req = WMS_RAW_SEND_REQ_NEW;
	struct wms_raw_send_resp *resp = WMS_RAW_SEND_RESP_NEW;
	int rc;

	if (len > (int)sizeof(req->msg.data)) {
		free(req);
		free(resp);
		return -EINVAL;
	}

	memset((char *)req + sizeof(req->hdr), 0, sizeof(*req) - sizeof(req->hdr));
	req->msg.format = QMI_WMS_MESSAGE_FORMAT_GSM_WCDMA_POINT_TO_POINT;
	req->msg.data_len = len;
	memcpy(req->msg.data, pdu, len);

	rc = libqril_send_message_sync(&req->hdr, &resp->hdr);
	*message_ref = resp->message_id_valid ? resp->message_id : 0;
	*cause = resp->cause_code_valid ? resp->cause_code : -1;
	log_info("SMS send: rc %d ref %d cause %d", rc, *message_ref, *cause);
	free(req);
	free(resp);
	return rc;
}

int glue_sms_ack(bool success)
{
	struct wms_send_ack_req *req;
	int rc;

	if (!sms_needs_ack)
		return 0;

	req = WMS_SEND_ACK_REQ_NEW;
	memset((char *)req + sizeof(req->hdr), 0, sizeof(*req) - sizeof(req->hdr));
	req->information.transaction_id = sms_transaction_id;
	req->information.message_protocol = QMI_WMS_MESSAGE_PROTOCOL_WCDMA;
	req->information.success = success;
	if (!success) {
		req->failure_cause_valid = true;
		req->failure_cause = 0;
	}
	rc = libqril_send_message_ack_sync(&req->hdr);
	sms_needs_ack = false;
	free(req);
	return rc;
}

int glue_get_smsc(char *smsc, int len)
{
	struct wms_get_smsc_address_resp *resp = WMS_GET_SMSC_ADDRESS_RESP_NEW;
	int rc;

	smsc[0] = '\0';
	rc = libqril_send_basic_request_sync(QMI_SERVICE_WMS, QMI_WMS_GET_SMSC_ADDRESS, &resp->hdr);
	if (!rc && resp->smsc_valid)
		copy_str(smsc, len, (const char *)resp->smsc.address, resp->smsc.address_len);
	free(resp);
	return rc;
}
