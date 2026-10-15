#ifndef __QMI_WMS_H__
#define __QMI_WMS_H__

#include <stdint.h>
#include <stdbool.h>

#include "libqrtr.h"

extern struct qmi_elem_info wms_set_event_report_req_ei[];
extern struct qmi_elem_info wms_set_event_report_resp_ei[];
extern struct qmi_elem_info wms_event_report_ind_ei[];
extern struct qmi_elem_info wms_set_routes_req_ei[];
extern struct qmi_elem_info wms_set_routes_resp_ei[];
extern struct qmi_elem_info wms_raw_send_req_ei[];
extern struct qmi_elem_info wms_raw_send_resp_ei[];
extern struct qmi_elem_info wms_send_ack_req_ei[];
extern struct qmi_elem_info wms_send_ack_resp_ei[];
extern struct qmi_elem_info wms_get_smsc_address_resp_ei[];

#define QMI_WMS_SET_EVENT_REPORT 1
#define QMI_WMS_EVENT_REPORT 1
#define QMI_WMS_RAW_SEND 32
#define QMI_WMS_SET_ROUTES 50
#define QMI_WMS_GET_SMSC_ADDRESS 52
#define QMI_WMS_SEND_ACK 55
#define QMI_WMS_MESSAGE_FORMAT_GSM_WCDMA_POINT_TO_POINT 6
#define QMI_WMS_MESSAGE_PROTOCOL_WCDMA 1
#define QMI_WMS_RECEIPT_ACTION_TRANSFER_ONLY 2
#define QMI_WMS_STORAGE_TYPE_NONE 255

struct wms_mt_message {
	uint8_t storage_type;
	uint32_t storage_index;
};

struct wms_transfer_route_mt_message {
	uint8_t ack_indicator;
	uint32_t transaction_id;
	uint8_t format;
	uint16_t data_len;
	uint8_t data[256];
};

struct wms_route {
	uint8_t message_type;
	uint8_t message_class;
	uint8_t storage;
	uint8_t receipt_action;
};

struct wms_raw_message {
	uint8_t format;
	uint16_t data_len;
	uint8_t data[256];
};

struct wms_ack_information {
	uint32_t transaction_id;
	uint8_t message_protocol;
	uint8_t success;
};

struct wms_smsc_address {
	uint8_t type[3];
	uint8_t address_len;
	uint8_t address[32];
};

struct wms_set_event_report_req { // 0x0001
	struct qmi_message_header hdr;
	bool new_mt_message_indicator_valid;
	uint8_t new_mt_message_indicator;  // 0x10
};

struct wms_set_event_report_resp { // 0x0001
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 res;  // 0x02
};

struct wms_event_report_ind { // 0x0001
	struct qmi_message_header hdr;
	bool mt_valid;
	struct wms_mt_message mt;  // 0x10
	bool transfer_route_valid;
	struct wms_transfer_route_mt_message transfer_route;  // 0x11
	bool message_mode_valid;
	uint8_t message_mode;  // 0x12
};

struct wms_set_routes_req { // 0x0032
	struct qmi_message_header hdr;
	uint32_t routes_len;
	struct wms_route routes[8];  // 0x01
	bool transfer_status_report_valid;
	uint8_t transfer_status_report;  // 0x10
};

struct wms_set_routes_resp { // 0x0032
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 res;  // 0x02
};

struct wms_raw_send_req { // 0x0020
	struct qmi_message_header hdr;
	struct wms_raw_message msg;  // 0x01
};

struct wms_raw_send_resp { // 0x0020
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 res;  // 0x02
	bool message_id_valid;
	uint16_t message_id;  // 0x01
	bool cause_code_valid;
	uint16_t cause_code;  // 0x10
	bool error_class_valid;
	uint8_t error_class;  // 0x11
};

struct wms_send_ack_req { // 0x0037
	struct qmi_message_header hdr;
	struct wms_ack_information information;  // 0x01
	bool failure_cause_valid;
	uint8_t failure_cause;  // 0x10
};

struct wms_send_ack_resp { // 0x0037
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 res;  // 0x02
};

struct wms_get_smsc_address_resp { // 0x0034
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 res;  // 0x02
	bool smsc_valid;
	struct wms_smsc_address smsc;  // 0x01
};

#define WMS_SET_EVENT_REPORT_REQ_NEW ({ \
	struct wms_set_event_report_req *ptr = malloc(sizeof(struct wms_set_event_report_req)); \
	ptr->hdr.qmi_header.type = 0; \
	ptr->hdr.qmi_header.msg_id = 0x0001; \
	ptr->hdr.ei = wms_set_event_report_req_ei; \
	ptr->hdr.service = 0x05; \
	ptr->hdr.name = "set_event_report_req"; ptr; })
#define WMS_SET_EVENT_REPORT_REQ_INITIALIZER { .hdr = { .qmi_header = { 0, 0, 0x0001, 0 },\
	.ei = wms_set_event_report_req_ei, \
	.service = 0x05, .name = "set_event_report_req" } }
#define WMS_SET_EVENT_REPORT_RESP_NEW ({ \
	struct wms_set_event_report_resp *ptr = malloc(sizeof(struct wms_set_event_report_resp)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x0001; \
	ptr->hdr.ei = wms_set_event_report_resp_ei; \
	ptr->hdr.service = 0x05; \
	ptr->hdr.name = "set_event_report_resp"; ptr; })
#define WMS_SET_EVENT_REPORT_RESP_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x0001, 0 },\
	.ei = wms_set_event_report_resp_ei, \
	.service = 0x05, .name = "set_event_report_resp" } }
#define WMS_EVENT_REPORT_IND_NEW ({ \
	struct wms_event_report_ind *ptr = malloc(sizeof(struct wms_event_report_ind)); \
	ptr->hdr.qmi_header.type = 4; \
	ptr->hdr.qmi_header.msg_id = 0x0001; \
	ptr->hdr.ei = wms_event_report_ind_ei; \
	ptr->hdr.service = 0x05; \
	ptr->hdr.name = "event_report_ind"; ptr; })
#define WMS_EVENT_REPORT_IND_INITIALIZER { .hdr = { .qmi_header = { 4, 0, 0x0001, 0 },\
	.ei = wms_event_report_ind_ei, \
	.service = 0x05, .name = "event_report_ind" } }
#define WMS_SET_ROUTES_REQ_NEW ({ \
	struct wms_set_routes_req *ptr = malloc(sizeof(struct wms_set_routes_req)); \
	ptr->hdr.qmi_header.type = 0; \
	ptr->hdr.qmi_header.msg_id = 0x0032; \
	ptr->hdr.ei = wms_set_routes_req_ei; \
	ptr->hdr.service = 0x05; \
	ptr->hdr.name = "set_routes_req"; ptr; })
#define WMS_SET_ROUTES_REQ_INITIALIZER { .hdr = { .qmi_header = { 0, 0, 0x0032, 0 },\
	.ei = wms_set_routes_req_ei, \
	.service = 0x05, .name = "set_routes_req" } }
#define WMS_SET_ROUTES_RESP_NEW ({ \
	struct wms_set_routes_resp *ptr = malloc(sizeof(struct wms_set_routes_resp)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x0032; \
	ptr->hdr.ei = wms_set_routes_resp_ei; \
	ptr->hdr.service = 0x05; \
	ptr->hdr.name = "set_routes_resp"; ptr; })
#define WMS_SET_ROUTES_RESP_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x0032, 0 },\
	.ei = wms_set_routes_resp_ei, \
	.service = 0x05, .name = "set_routes_resp" } }
#define WMS_RAW_SEND_REQ_NEW ({ \
	struct wms_raw_send_req *ptr = malloc(sizeof(struct wms_raw_send_req)); \
	ptr->hdr.qmi_header.type = 0; \
	ptr->hdr.qmi_header.msg_id = 0x0020; \
	ptr->hdr.ei = wms_raw_send_req_ei; \
	ptr->hdr.service = 0x05; \
	ptr->hdr.name = "raw_send_req"; ptr; })
#define WMS_RAW_SEND_REQ_INITIALIZER { .hdr = { .qmi_header = { 0, 0, 0x0020, 0 },\
	.ei = wms_raw_send_req_ei, \
	.service = 0x05, .name = "raw_send_req" } }
#define WMS_RAW_SEND_RESP_NEW ({ \
	struct wms_raw_send_resp *ptr = malloc(sizeof(struct wms_raw_send_resp)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x0020; \
	ptr->hdr.ei = wms_raw_send_resp_ei; \
	ptr->hdr.service = 0x05; \
	ptr->hdr.name = "raw_send_resp"; ptr; })
#define WMS_RAW_SEND_RESP_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x0020, 0 },\
	.ei = wms_raw_send_resp_ei, \
	.service = 0x05, .name = "raw_send_resp" } }
#define WMS_SEND_ACK_REQ_NEW ({ \
	struct wms_send_ack_req *ptr = malloc(sizeof(struct wms_send_ack_req)); \
	ptr->hdr.qmi_header.type = 0; \
	ptr->hdr.qmi_header.msg_id = 0x0037; \
	ptr->hdr.ei = wms_send_ack_req_ei; \
	ptr->hdr.service = 0x05; \
	ptr->hdr.name = "send_ack_req"; ptr; })
#define WMS_SEND_ACK_REQ_INITIALIZER { .hdr = { .qmi_header = { 0, 0, 0x0037, 0 },\
	.ei = wms_send_ack_req_ei, \
	.service = 0x05, .name = "send_ack_req" } }
#define WMS_SEND_ACK_RESP_NEW ({ \
	struct wms_send_ack_resp *ptr = malloc(sizeof(struct wms_send_ack_resp)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x0037; \
	ptr->hdr.ei = wms_send_ack_resp_ei; \
	ptr->hdr.service = 0x05; \
	ptr->hdr.name = "send_ack_resp"; ptr; })
#define WMS_SEND_ACK_RESP_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x0037, 0 },\
	.ei = wms_send_ack_resp_ei, \
	.service = 0x05, .name = "send_ack_resp" } }
#define WMS_GET_SMSC_ADDRESS_RESP_NEW ({ \
	struct wms_get_smsc_address_resp *ptr = malloc(sizeof(struct wms_get_smsc_address_resp)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x0034; \
	ptr->hdr.ei = wms_get_smsc_address_resp_ei; \
	ptr->hdr.service = 0x05; \
	ptr->hdr.name = "get_smsc_address_resp"; ptr; })
#define WMS_GET_SMSC_ADDRESS_RESP_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x0034, 0 },\
	.ei = wms_get_smsc_address_resp_ei, \
	.service = 0x05, .name = "get_smsc_address_resp" } }

#endif
