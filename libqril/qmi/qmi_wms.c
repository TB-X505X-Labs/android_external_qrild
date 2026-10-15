#include <errno.h>
#include <string.h>
#include "qmi_wms.h"

struct qmi_elem_info wms_mt_message_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wms_mt_message, storage_type),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct wms_mt_message, storage_index),
	},
	{}
};

struct qmi_elem_info wms_transfer_route_mt_message_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wms_transfer_route_mt_message, ack_indicator),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct wms_transfer_route_mt_message, transaction_id),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wms_transfer_route_mt_message, format),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct wms_transfer_route_mt_message, data_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 256,
		.array_type = VAR_LEN_ARRAY,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wms_transfer_route_mt_message, data),
	},
	{}
};

struct qmi_elem_info wms_route_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wms_route, message_type),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wms_route, message_class),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wms_route, storage),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wms_route, receipt_action),
	},
	{}
};

struct qmi_elem_info wms_raw_message_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wms_raw_message, format),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct wms_raw_message, data_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 256,
		.array_type = VAR_LEN_ARRAY,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wms_raw_message, data),
	},
	{}
};

struct qmi_elem_info wms_ack_information_ei[] = {
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct wms_ack_information, transaction_id),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wms_ack_information, message_protocol),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wms_ack_information, success),
	},
	{}
};

struct qmi_elem_info wms_smsc_address_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 3,
		.array_type = STATIC_ARRAY,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wms_smsc_address, type),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wms_smsc_address, address_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 32,
		.array_type = VAR_LEN_ARRAY,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct wms_smsc_address, address),
	},
	{}
};

struct qmi_elem_info wms_set_event_report_req_ei[] = {
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct wms_set_event_report_req, new_mt_message_indicator_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 16,
		.offset = offsetof(struct wms_set_event_report_req, new_mt_message_indicator),
	},
	{}
};

struct qmi_elem_info wms_set_event_report_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct wms_set_event_report_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{}
};

struct qmi_elem_info wms_event_report_ind_ei[] = {
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct wms_event_report_ind, mt_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct wms_mt_message),
		.tlv_type = 16,
		.offset = offsetof(struct wms_event_report_ind, mt),
		.ei_array = wms_mt_message_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct wms_event_report_ind, transfer_route_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct wms_transfer_route_mt_message),
		.tlv_type = 17,
		.offset = offsetof(struct wms_event_report_ind, transfer_route),
		.ei_array = wms_transfer_route_mt_message_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct wms_event_report_ind, message_mode_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 18,
		.offset = offsetof(struct wms_event_report_ind, message_mode),
	},
	{}
};

struct qmi_elem_info wms_set_routes_req_ei[] = {
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 1,
		.offset = offsetof(struct wms_set_routes_req, routes_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 8,
		.elem_size = sizeof(struct wms_route),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 1,
		.offset = offsetof(struct wms_set_routes_req, routes),
		.ei_array = wms_route_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct wms_set_routes_req, transfer_status_report_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 16,
		.offset = offsetof(struct wms_set_routes_req, transfer_status_report),
	},
	{}
};

struct qmi_elem_info wms_set_routes_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct wms_set_routes_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{}
};

struct qmi_elem_info wms_raw_send_req_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct wms_raw_message),
		.tlv_type = 1,
		.offset = offsetof(struct wms_raw_send_req, msg),
		.ei_array = wms_raw_message_ei,
	},
	{}
};

struct qmi_elem_info wms_raw_send_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct wms_raw_send_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 1,
		.offset = offsetof(struct wms_raw_send_resp, message_id_valid),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 1,
		.offset = offsetof(struct wms_raw_send_resp, message_id),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct wms_raw_send_resp, cause_code_valid),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 16,
		.offset = offsetof(struct wms_raw_send_resp, cause_code),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct wms_raw_send_resp, error_class_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 17,
		.offset = offsetof(struct wms_raw_send_resp, error_class),
	},
	{}
};

struct qmi_elem_info wms_send_ack_req_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct wms_ack_information),
		.tlv_type = 1,
		.offset = offsetof(struct wms_send_ack_req, information),
		.ei_array = wms_ack_information_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct wms_send_ack_req, failure_cause_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 16,
		.offset = offsetof(struct wms_send_ack_req, failure_cause),
	},
	{}
};

struct qmi_elem_info wms_send_ack_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct wms_send_ack_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{}
};

struct qmi_elem_info wms_get_smsc_address_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct wms_get_smsc_address_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 1,
		.offset = offsetof(struct wms_get_smsc_address_resp, smsc_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct wms_smsc_address),
		.tlv_type = 1,
		.offset = offsetof(struct wms_get_smsc_address_resp, smsc),
		.ei_array = wms_smsc_address_ei,
	},
	{}
};

