#ifndef __QMI_DMS_H__
#define __QMI_DMS_H__

#include <stdint.h>
#include <stdbool.h>

#include "libqrtr.h"

extern struct qmi_elem_info dms_get_revision_req_ei[];
extern struct qmi_elem_info dms_get_revision_resp_ei[];
extern struct qmi_elem_info dms_get_ids_req_ei[];
extern struct qmi_elem_info dms_get_ids_resp_ei[];
extern struct qmi_elem_info dms_get_operating_mode_req_ei[];
extern struct qmi_elem_info dms_get_operating_mode_resp_ei[];
extern struct qmi_elem_info dms_set_operating_mode_req_ei[];
extern struct qmi_elem_info dms_set_operating_mode_resp_ei[];
extern struct qmi_elem_info dms_get_msisdn_ei[];
extern struct qmi_elem_info dms_uim_get_imsi_ei[];
extern struct qmi_elem_info dms_uim_get_iccid_ei[];

#define QMI_DMS_GET_REVISION 35
#define QMI_DMS_GET_MSISDN 36
#define QMI_DMS_GET_IDS 37
#define QMI_DMS_GET_OPERATING_MODE 45
#define QMI_DMS_SET_OPERATING_MODE 46
#define QMI_DMS_UIM_GET_ICCID 60
#define QMI_DMS_UIM_GET_IMSI 67

enum QmiDmsOperatingMode {
	QMI_DMS_OPERATING_MODE_ONLINE = 0,
	QMI_DMS_OPERATING_MODE_LOW_POWER = 1,
	QMI_DMS_OPERATING_MODE_FACTORY_TEST = 2,
	QMI_DMS_OPERATING_MODE_OFFLINE = 3,
	QMI_DMS_OPERATING_MODE_RESET = 4,
	QMI_DMS_OPERATING_MODE_SHUTTING_DOWN = 5,
	QMI_DMS_OPERATING_MODE_PERSISTENT_LOW_POWER = 6,
	QMI_DMS_OPERATING_MODE_MODE_ONLY_LOW_POWER = 7,
	QMI_DMS_OPERATING_MODE_UNKNOWN = 255,
};


struct dms_get_revision_req { // 0x0023
	struct qmi_message_header hdr;
};

struct dms_get_revision_resp { // 0x0023
	struct qmi_message_header hdr;
	uint32_t revision_len;
	char revision[256]; // 0x01
};

struct dms_get_ids_req { // 0x0025
	struct qmi_message_header hdr;
};

struct dms_get_ids_resp { // 0x0025
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 res;  // 0x02
	uint32_t esn_len;
	char esn[256]; // 0x10
	uint32_t imei_len;
	char imei[256]; // 0x11
	uint32_t meid_len;
	char meid[256]; // 0x12
	uint32_t imei_ver_len;
	char imei_ver[256]; // 0x13
};

struct dms_get_operating_mode_req { // 0x002d
	struct qmi_message_header hdr;
};

struct dms_get_operating_mode_resp { // 0x002d
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 res;  // 0x02
	uint8_t mode;  // 0x01
	bool offline_reason_valid;
	uint16_t offline_reason;  // 0x10
	uint8_t hardware_restricted;  // 0x11
};

struct dms_set_operating_mode_req { // 0x002e
	struct qmi_message_header hdr;
	uint8_t mode;  // 0x01
};

struct dms_set_operating_mode_resp { // 0x002e
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 res;  // 0x02
};

struct dms_get_msisdn { // 0x0024
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 res;  // 0x02
	uint32_t msisdn_len;
	char msisdn[256]; // 0x01
	uint32_t imsi_len;
	char imsi[256]; // 0x11
};

struct dms_uim_get_imsi { // 0x0043
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 res;  // 0x02
	uint32_t imsi_len;
	char imsi[256]; // 0x01
};

struct dms_uim_get_iccid { // 0x003c
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 res;  // 0x02
	uint32_t iccid_len;
	char iccid[256]; // 0x01
};

#define DMS_GET_REVISION_REQ_NEW ({ \
	struct dms_get_revision_req *ptr = malloc(sizeof(struct dms_get_revision_req)); \
	ptr->hdr.qmi_header.type = 0; \
	ptr->hdr.qmi_header.msg_id = 0x0023; \
	ptr->hdr.ei = dms_get_revision_req_ei; \
	ptr->hdr.service = 0x02; \
	ptr->hdr.name = "get_revision_req"; ptr; })
#define DMS_GET_REVISION_REQ_INITIALIZER { .hdr = { .qmi_header = { 0, 0, 0x0023, 0 },\
	.ei = dms_get_revision_req_ei, \
	.service = 0x02, .name = "get_revision_req" } }
#define DMS_GET_REVISION_RESP_NEW ({ \
	struct dms_get_revision_resp *ptr = malloc(sizeof(struct dms_get_revision_resp)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x0023; \
	ptr->hdr.ei = dms_get_revision_resp_ei; \
	ptr->hdr.service = 0x02; \
	ptr->hdr.name = "get_revision_resp"; ptr; })
#define DMS_GET_REVISION_RESP_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x0023, 0 },\
	.ei = dms_get_revision_resp_ei, \
	.service = 0x02, .name = "get_revision_resp" } }
#define DMS_GET_IDS_REQ_NEW ({ \
	struct dms_get_ids_req *ptr = malloc(sizeof(struct dms_get_ids_req)); \
	ptr->hdr.qmi_header.type = 0; \
	ptr->hdr.qmi_header.msg_id = 0x0025; \
	ptr->hdr.ei = dms_get_ids_req_ei; \
	ptr->hdr.service = 0x02; \
	ptr->hdr.name = "get_ids_req"; ptr; })
#define DMS_GET_IDS_REQ_INITIALIZER { .hdr = { .qmi_header = { 0, 0, 0x0025, 0 },\
	.ei = dms_get_ids_req_ei, \
	.service = 0x02, .name = "get_ids_req" } }
#define DMS_GET_IDS_RESP_NEW ({ \
	struct dms_get_ids_resp *ptr = malloc(sizeof(struct dms_get_ids_resp)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x0025; \
	ptr->hdr.ei = dms_get_ids_resp_ei; \
	ptr->hdr.service = 0x02; \
	ptr->hdr.name = "get_ids_resp"; ptr; })
#define DMS_GET_IDS_RESP_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x0025, 0 },\
	.ei = dms_get_ids_resp_ei, \
	.service = 0x02, .name = "get_ids_resp" } }
#define DMS_GET_OPERATING_MODE_REQ_NEW ({ \
	struct dms_get_operating_mode_req *ptr = malloc(sizeof(struct dms_get_operating_mode_req)); \
	ptr->hdr.qmi_header.type = 0; \
	ptr->hdr.qmi_header.msg_id = 0x002d; \
	ptr->hdr.ei = dms_get_operating_mode_req_ei; \
	ptr->hdr.service = 0x02; \
	ptr->hdr.name = "get_operating_mode_req"; ptr; })
#define DMS_GET_OPERATING_MODE_REQ_INITIALIZER { .hdr = { .qmi_header = { 0, 0, 0x002d, 0 },\
	.ei = dms_get_operating_mode_req_ei, \
	.service = 0x02, .name = "get_operating_mode_req" } }
#define DMS_GET_OPERATING_MODE_RESP_NEW ({ \
	struct dms_get_operating_mode_resp *ptr = malloc(sizeof(struct dms_get_operating_mode_resp)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x002d; \
	ptr->hdr.ei = dms_get_operating_mode_resp_ei; \
	ptr->hdr.service = 0x02; \
	ptr->hdr.name = "get_operating_mode_resp"; ptr; })
#define DMS_GET_OPERATING_MODE_RESP_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x002d, 0 },\
	.ei = dms_get_operating_mode_resp_ei, \
	.service = 0x02, .name = "get_operating_mode_resp" } }
#define DMS_SET_OPERATING_MODE_REQ_NEW ({ \
	struct dms_set_operating_mode_req *ptr = malloc(sizeof(struct dms_set_operating_mode_req)); \
	ptr->hdr.qmi_header.type = 0; \
	ptr->hdr.qmi_header.msg_id = 0x002e; \
	ptr->hdr.ei = dms_set_operating_mode_req_ei; \
	ptr->hdr.service = 0x02; \
	ptr->hdr.name = "set_operating_mode_req"; ptr; })
#define DMS_SET_OPERATING_MODE_REQ_INITIALIZER { .hdr = { .qmi_header = { 0, 0, 0x002e, 0 },\
	.ei = dms_set_operating_mode_req_ei, \
	.service = 0x02, .name = "set_operating_mode_req" } }
#define DMS_SET_OPERATING_MODE_RESP_NEW ({ \
	struct dms_set_operating_mode_resp *ptr = malloc(sizeof(struct dms_set_operating_mode_resp)); \
	ptr->hdr.qmi_header.type = 0; \
	ptr->hdr.qmi_header.msg_id = 0x002e; \
	ptr->hdr.ei = dms_set_operating_mode_resp_ei; \
	ptr->hdr.service = 0x02; \
	ptr->hdr.name = "set_operating_mode_resp"; ptr; })
#define DMS_SET_OPERATING_MODE_RESP_INITIALIZER { .hdr = { .qmi_header = { 0, 0, 0x002e, 0 },\
	.ei = dms_set_operating_mode_resp_ei, \
	.service = 0x02, .name = "set_operating_mode_resp" } }
#define DMS_GET_MSISDN_NEW ({ \
	struct dms_get_msisdn *ptr = malloc(sizeof(struct dms_get_msisdn)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x0024; \
	ptr->hdr.ei = dms_get_msisdn_ei; \
	ptr->hdr.service = 0x02; \
	ptr->hdr.name = "get_msisdn"; ptr; })
#define DMS_GET_MSISDN_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x0024, 0 },\
	.ei = dms_get_msisdn_ei, \
	.service = 0x02, .name = "get_msisdn" } }
#define DMS_UIM_GET_IMSI_NEW ({ \
	struct dms_uim_get_imsi *ptr = malloc(sizeof(struct dms_uim_get_imsi)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x0043; \
	ptr->hdr.ei = dms_uim_get_imsi_ei; \
	ptr->hdr.service = 0x02; \
	ptr->hdr.name = "uim_get_imsi"; ptr; })
#define DMS_UIM_GET_IMSI_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x0043, 0 },\
	.ei = dms_uim_get_imsi_ei, \
	.service = 0x02, .name = "uim_get_imsi" } }
#define DMS_UIM_GET_ICCID_NEW ({ \
	struct dms_uim_get_iccid *ptr = malloc(sizeof(struct dms_uim_get_iccid)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x003c; \
	ptr->hdr.ei = dms_uim_get_iccid_ei; \
	ptr->hdr.service = 0x02; \
	ptr->hdr.name = "uim_get_iccid"; ptr; })
#define DMS_UIM_GET_ICCID_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x003c, 0 },\
	.ei = dms_uim_get_iccid_ei, \
	.service = 0x02, .name = "uim_get_iccid" } }

#endif
