#ifndef __QMI_UIM_H__
#define __QMI_UIM_H__

#include <stdint.h>
#include <stdbool.h>

#include "libqrtr.h"

extern struct qmi_elem_info uim_get_card_status_resp_ei[];
extern struct qmi_elem_info uim_change_provisioning_session_req_ei[];
extern struct qmi_elem_info uim_change_provisioning_session_resp_ei[];
extern struct qmi_elem_info uim_icc_open_logical_channel_req_ei[];
extern struct qmi_elem_info uim_icc_open_logical_channel_resp_ei[];
extern struct qmi_elem_info uim_get_slot_status_req_ei[];
extern struct qmi_elem_info uim_get_slot_status_resp_ei[];
extern struct qmi_elem_info uim_get_slot_status_ind_ei[];
extern struct qmi_elem_info uim_read_transparent_req_ei[];
extern struct qmi_elem_info uim_read_transparent_resp_ei[];
extern struct qmi_elem_info uim_read_record_req_ei[];
extern struct qmi_elem_info uim_read_record_resp_ei[];
extern struct qmi_elem_info uim_get_file_attrs_req_ei[];
extern struct qmi_elem_info uim_get_file_attrs_resp_ei[];
extern struct qmi_elem_info uim_refresh_ei[];

#define QMI_UIM_GET_CARD_STATUS 47
#define QMI_UIM_CHANGE_PROVISIONING_SESSION 56
#define QMI_UIM_GET_SLOT_STATUS 71
#define QMI_UIM_SLOT_STATUS_IND 72
#define QMI_UIM_SESSION_TYPE_PRIMARY_GW_PROVISIONING 0

enum QmiUimCardState {
	QMI_UIM_CARD_STATE_ABSENT = 0,
	QMI_UIM_CARD_STATE_PRESENT = 1,
	QMI_UIM_CARD_STATE_ERROR = 2,
};

enum QmiUimPhysicalCardState {
	QMI_UIM_PHYSICAL_CARD_STATE_UNKNOWN = 0,
	QMI_UIM_PHYSICAL_CARD_STATE_ABSENT = 1,
	QMI_UIM_PHYSICAL_CARD_STATE_PRESENT = 2,
};

enum QmiUimCardApplicationState {
	QMI_UIM_CARD_APPLICATION_STATE_UNKNOWN = 0,
	QMI_UIM_CARD_APPLICATION_STATE_DETECTED = 1,
	QMI_UIM_CARD_APPLICATION_STATE_PIN1_OR_UPIN_PIN_REQUIRED = 2,
	QMI_UIM_CARD_APPLICATION_STATE_PUK1_OR_UPIN_PUK_REQUIRED = 3,
	QMI_UIM_CARD_APPLICATION_STATE_CHECK_PERSONALIZATION_STATE = 4,
	QMI_UIM_CARD_APPLICATION_STATE_PIN1_BLOCKED = 5,
	QMI_UIM_CARD_APPLICATION_STATE_ILLEGAL = 6,
	QMI_UIM_CARD_APPLICATION_STATE_READY = 7,
};

enum QmiUimFileType {
	QMI_UIM_FILE_TYPE_TRANSPARENT = 0,
	QMI_UIM_FILE_TYPE_CYCLIC = 1,
	QMI_UIM_FILE_TYPE_LINEAR_FIXED = 2,
	QMI_UIM_FILE_TYPE_DEDICATED_FILE = 3,
	QMI_UIM_FILE_TYPE_MASTER_FILE = 4,
};


struct uim_card_status_cards_applications {
	uint8_t type;
	uint8_t state;
	uint8_t personalization_state;
	uint8_t personalization_feature;
	uint8_t personalization_retries;
	uint8_t personalization_unblock_retries;
	uint8_t application_identifier_value_len;
	uint8_t application_identifier_value[16];
	uint8_t upin_replaces_pin1;
	uint8_t pin1_state;
	uint8_t pin1_retries;
	uint8_t puk1_retries;
	uint8_t pin2_state;
	uint8_t pin2_retries;
	uint8_t puk2_retries;
};

struct uim_card_status_cards {
	uint8_t card_state;
	uint8_t upin_state;
	uint8_t upin_retries;
	uint8_t upuk_retries;
	uint8_t error_code;
	uint8_t applications_len;
	struct uim_card_status_cards_applications applications[2];
};

struct uim_card_status {
	uint16_t index_gw_primary;
	uint16_t index_1x_primary;
	uint16_t index_gw_secondary;
	uint16_t index_1x_secondary;
	uint8_t cards_len;
	struct uim_card_status_cards cards[2];
};

struct uim_provisioning_session_change {
	uint8_t session_type;
	uint8_t activate;
};

struct uim_provisioning_session_application {
	uint8_t slot;
	uint8_t application_identifier_value_len;
	uint8_t application_identifier_value[16];
};

struct uim_physical_slot_state {
	uint32_t card_state;
	uint32_t slot_state;
	uint8_t logical_slot;
	uint8_t iccid_len;
	uint8_t iccid[128];
};

struct uim_physical_slot_info_slots {
	uint32_t card_protocol;
	uint8_t valid_applications;
	uint8_t atr_value_len;
	uint8_t atr_value[32];
	uint8_t is_euicc;
};

struct uim_physical_slot_info {
	uint8_t slots_len;
	struct uim_physical_slot_info_slots slots[128];
};

struct uim_session_t {
	uint8_t type;
	uint8_t aid_len;
	uint8_t aid[128];
};

struct uim_file_t {
	uint16_t file_id;
	uint8_t path_len;
	uint8_t path[128];
};

struct uim_read_info_t {
	uint16_t offset;
	uint16_t len;
};

struct uim_card_res_t {
	uint8_t sw1;
	uint8_t sw2;
};

struct uim_file_attrs_t {
	uint16_t file_size;
	uint16_t file_id;
	uint8_t file_type;
	uint16_t record_size;
	uint16_t record_count;
	uint8_t read_sec_attr_logic;
	uint16_t read_sec_attrs;
	uint8_t write_sec_attr_logic;
	uint16_t write_sec_attrs;
	uint8_t inc_sec_attr_logic;
	uint16_t inc_sec_attrs;
	uint8_t deactivate_sec_attr_logic;
	uint16_t deactivate_sec_attrs;
	uint8_t activate_sec_attr_logic;
	uint16_t activate_sec_attrs;
	uint16_t raw_data_len;
	uint8_t raw_data[128];
};

struct uim_refresh_ev_t_files {
	uint16_t id;
	uint8_t path_len;
	uint8_t path[128];
};

struct uim_refresh_ev_t {
	uint8_t stage;
	uint8_t mode;
	uint8_t session_type;
	uint8_t aid_len;
	uint8_t aid[16];
	uint16_t files_len;
	struct uim_refresh_ev_t_files files[128];
};

struct uim_get_card_status_resp { // 0x002f
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 result;  // 0x02
	bool status_valid;
	struct uim_card_status status;  // 0x10
};

struct uim_change_provisioning_session_req { // 0x0038
	struct qmi_message_header hdr;
	bool session_change_valid;
	struct uim_provisioning_session_change session_change;  // 0x01
	bool application_information_valid;
	struct uim_provisioning_session_application application_information;  // 0x10
};

struct uim_change_provisioning_session_resp { // 0x0038
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 result;  // 0x02
};

struct uim_icc_open_logical_channel_req { // 0x0042
	struct qmi_message_header hdr;
	uint8_t slot;  // 0x01
	bool application_id_valid;
	uint32_t application_id_len;
	uint8_t application_id[32];  // 0x10
	bool fileControlInfo_valid;
	uint8_t fileControlInfo;  // 0x11
};

struct uim_icc_open_logical_channel_resp { // 0x0042
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 result;  // 0x02
	bool channel_id_valid;
	uint8_t channel_id;  // 0x10
	bool card_result_valid;
	uint16_t card_result;  // 0x11
	bool select_response_valid;
	uint32_t select_response_len;
	uint8_t select_response[255];  // 0x12
};

struct uim_get_slot_status_req { // 0x0047
	struct qmi_message_header hdr;
};

struct uim_get_slot_status_resp { // 0x0047
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 result;  // 0x02
	bool slot_state_valid;
	uint32_t slot_state_len;
	struct uim_physical_slot_state slot_state[8];  // 0x10
	bool slot_info_valid;
	struct uim_physical_slot_info slot_info;  // 0x11
	bool eid_info_valid;
	uint32_t eid_info_len;
	uint8_t eid_info[32];  // 0x12
};

struct uim_get_slot_status_ind { // 0x0048
	struct qmi_message_header hdr;
	uint32_t slot_state_len;
	struct uim_physical_slot_state slot_state[8];  // 0x10
	bool slot_info_valid;
	struct uim_physical_slot_info slot_info;  // 0x11
	bool eid_info_valid;
	uint32_t eid_info_len;
	uint8_t eid_info[32];  // 0x12
};

struct uim_read_transparent_req { // 0x0020
	struct qmi_message_header hdr;
	struct uim_session_t session;  // 0x01
	struct uim_file_t file;  // 0x02
	struct uim_read_info_t read_info;  // 0x03
	bool resp_in_ind_valid;
	uint32_t resp_in_ind;  // 0x10
	bool encrypt_data_valid;
	uint8_t encrypt_data;  // 0x11
};

struct uim_read_transparent_resp { // 0x0020
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 res;  // 0x02
	bool card_res_valid;
	struct uim_card_res_t card_res;  // 0x10
	bool read_result_valid;
	uint32_t read_result_len;
	uint8_t read_result[64];  // 0x11
	bool resp_in_ind_valid;
	uint32_t resp_in_ind;  // 0x12
	bool encrypted_valid;
	uint8_t encrypted;  // 0x13
};

struct uim_read_record_req { // 0x0021
	struct qmi_message_header hdr;
	struct uim_session_t session;  // 0x01
	struct uim_file_t file;  // 0x02
	struct uim_read_info_t read_info;  // 0x03
	bool last_record_valid;
	uint16_t last_record;  // 0x10
	bool resp_in_ind_valid;
	uint32_t resp_in_ind;  // 0x11
};

struct uim_read_record_resp { // 0x0021
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 res;  // 0x02
	bool card_res_valid;
	struct uim_card_res_t card_res;  // 0x10
	bool read_result_valid;
	uint32_t read_result_len;
	uint8_t read_result[64];  // 0x11
	bool additional_read_result_valid;
	uint32_t additional_read_result_len;
	uint8_t additional_read_result[2];  // 0x12
	bool resp_in_ind_valid;
	uint32_t resp_in_ind;  // 0x13
};

struct uim_get_file_attrs_req { // 0x0024
	struct qmi_message_header hdr;
	struct uim_session_t session;  // 0x01
	struct uim_file_t file;  // 0x02
	bool resp_in_ind_valid;
	uint32_t resp_in_ind;  // 0x11
};

struct uim_get_file_attrs_resp { // 0x0024
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 res;  // 0x02
	bool card_res_valid;
	struct uim_card_res_t card_res;  // 0x10
	bool file_attrs_valid;
	struct uim_file_attrs_t file_attrs;  // 0x11
	bool resp_in_ind_valid;
	uint32_t resp_in_ind;  // 0x12
};

struct uim_refresh { // 0x0033
	struct qmi_message_header hdr;
	struct uim_refresh_ev_t event;  // 0x10
};

#define UIM_GET_CARD_STATUS_RESP_NEW ({ \
	struct uim_get_card_status_resp *ptr = malloc(sizeof(struct uim_get_card_status_resp)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x002f; \
	ptr->hdr.ei = uim_get_card_status_resp_ei; \
	ptr->hdr.service = 0x0b; \
	ptr->hdr.name = "get_card_status_resp"; ptr; })
#define UIM_GET_CARD_STATUS_RESP_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x002f, 0 },\
	.ei = uim_get_card_status_resp_ei, \
	.service = 0x0b, .name = "get_card_status_resp" } }
#define UIM_CHANGE_PROVISIONING_SESSION_REQ_NEW ({ \
	struct uim_change_provisioning_session_req *ptr = malloc(sizeof(struct uim_change_provisioning_session_req)); \
	ptr->hdr.qmi_header.type = 0; \
	ptr->hdr.qmi_header.msg_id = 0x0038; \
	ptr->hdr.ei = uim_change_provisioning_session_req_ei; \
	ptr->hdr.service = 0x0b; \
	ptr->hdr.name = "change_provisioning_session_req"; ptr; })
#define UIM_CHANGE_PROVISIONING_SESSION_REQ_INITIALIZER { .hdr = { .qmi_header = { 0, 0, 0x0038, 0 },\
	.ei = uim_change_provisioning_session_req_ei, \
	.service = 0x0b, .name = "change_provisioning_session_req" } }
#define UIM_CHANGE_PROVISIONING_SESSION_RESP_NEW ({ \
	struct uim_change_provisioning_session_resp *ptr = malloc(sizeof(struct uim_change_provisioning_session_resp)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x0038; \
	ptr->hdr.ei = uim_change_provisioning_session_resp_ei; \
	ptr->hdr.service = 0x0b; \
	ptr->hdr.name = "change_provisioning_session_resp"; ptr; })
#define UIM_CHANGE_PROVISIONING_SESSION_RESP_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x0038, 0 },\
	.ei = uim_change_provisioning_session_resp_ei, \
	.service = 0x0b, .name = "change_provisioning_session_resp" } }
#define UIM_ICC_OPEN_LOGICAL_CHANNEL_REQ_NEW ({ \
	struct uim_icc_open_logical_channel_req *ptr = malloc(sizeof(struct uim_icc_open_logical_channel_req)); \
	ptr->hdr.qmi_header.type = 0; \
	ptr->hdr.qmi_header.msg_id = 0x0042; \
	ptr->hdr.ei = uim_icc_open_logical_channel_req_ei; \
	ptr->hdr.service = 0x0b; \
	ptr->hdr.name = "icc_open_logical_channel_req"; ptr; })
#define UIM_ICC_OPEN_LOGICAL_CHANNEL_REQ_INITIALIZER { .hdr = { .qmi_header = { 0, 0, 0x0042, 0 },\
	.ei = uim_icc_open_logical_channel_req_ei, \
	.service = 0x0b, .name = "icc_open_logical_channel_req" } }
#define UIM_ICC_OPEN_LOGICAL_CHANNEL_RESP_NEW ({ \
	struct uim_icc_open_logical_channel_resp *ptr = malloc(sizeof(struct uim_icc_open_logical_channel_resp)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x0042; \
	ptr->hdr.ei = uim_icc_open_logical_channel_resp_ei; \
	ptr->hdr.service = 0x0b; \
	ptr->hdr.name = "icc_open_logical_channel_resp"; ptr; })
#define UIM_ICC_OPEN_LOGICAL_CHANNEL_RESP_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x0042, 0 },\
	.ei = uim_icc_open_logical_channel_resp_ei, \
	.service = 0x0b, .name = "icc_open_logical_channel_resp" } }
#define UIM_GET_SLOT_STATUS_REQ_NEW ({ \
	struct uim_get_slot_status_req *ptr = malloc(sizeof(struct uim_get_slot_status_req)); \
	ptr->hdr.qmi_header.type = 0; \
	ptr->hdr.qmi_header.msg_id = 0x0047; \
	ptr->hdr.ei = uim_get_slot_status_req_ei; \
	ptr->hdr.service = 0x0b; \
	ptr->hdr.name = "get_slot_status_req"; ptr; })
#define UIM_GET_SLOT_STATUS_REQ_INITIALIZER { .hdr = { .qmi_header = { 0, 0, 0x0047, 0 },\
	.ei = uim_get_slot_status_req_ei, \
	.service = 0x0b, .name = "get_slot_status_req" } }
#define UIM_GET_SLOT_STATUS_RESP_NEW ({ \
	struct uim_get_slot_status_resp *ptr = malloc(sizeof(struct uim_get_slot_status_resp)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x0047; \
	ptr->hdr.ei = uim_get_slot_status_resp_ei; \
	ptr->hdr.service = 0x0b; \
	ptr->hdr.name = "get_slot_status_resp"; ptr; })
#define UIM_GET_SLOT_STATUS_RESP_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x0047, 0 },\
	.ei = uim_get_slot_status_resp_ei, \
	.service = 0x0b, .name = "get_slot_status_resp" } }
#define UIM_GET_SLOT_STATUS_IND_NEW ({ \
	struct uim_get_slot_status_ind *ptr = malloc(sizeof(struct uim_get_slot_status_ind)); \
	ptr->hdr.qmi_header.type = 4; \
	ptr->hdr.qmi_header.msg_id = 0x0048; \
	ptr->hdr.ei = uim_get_slot_status_ind_ei; \
	ptr->hdr.service = 0x0b; \
	ptr->hdr.name = "get_slot_status_ind"; ptr; })
#define UIM_GET_SLOT_STATUS_IND_INITIALIZER { .hdr = { .qmi_header = { 4, 0, 0x0048, 0 },\
	.ei = uim_get_slot_status_ind_ei, \
	.service = 0x0b, .name = "get_slot_status_ind" } }
#define UIM_READ_TRANSPARENT_REQ_NEW ({ \
	struct uim_read_transparent_req *ptr = malloc(sizeof(struct uim_read_transparent_req)); \
	ptr->hdr.qmi_header.type = 0; \
	ptr->hdr.qmi_header.msg_id = 0x0020; \
	ptr->hdr.ei = uim_read_transparent_req_ei; \
	ptr->hdr.service = 0x0b; \
	ptr->hdr.name = "read_transparent_req"; ptr; })
#define UIM_READ_TRANSPARENT_REQ_INITIALIZER { .hdr = { .qmi_header = { 0, 0, 0x0020, 0 },\
	.ei = uim_read_transparent_req_ei, \
	.service = 0x0b, .name = "read_transparent_req" } }
#define UIM_READ_TRANSPARENT_RESP_NEW ({ \
	struct uim_read_transparent_resp *ptr = malloc(sizeof(struct uim_read_transparent_resp)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x0020; \
	ptr->hdr.ei = uim_read_transparent_resp_ei; \
	ptr->hdr.service = 0x0b; \
	ptr->hdr.name = "read_transparent_resp"; ptr; })
#define UIM_READ_TRANSPARENT_RESP_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x0020, 0 },\
	.ei = uim_read_transparent_resp_ei, \
	.service = 0x0b, .name = "read_transparent_resp" } }
#define UIM_READ_RECORD_REQ_NEW ({ \
	struct uim_read_record_req *ptr = malloc(sizeof(struct uim_read_record_req)); \
	ptr->hdr.qmi_header.type = 0; \
	ptr->hdr.qmi_header.msg_id = 0x0021; \
	ptr->hdr.ei = uim_read_record_req_ei; \
	ptr->hdr.service = 0x0b; \
	ptr->hdr.name = "read_record_req"; ptr; })
#define UIM_READ_RECORD_REQ_INITIALIZER { .hdr = { .qmi_header = { 0, 0, 0x0021, 0 },\
	.ei = uim_read_record_req_ei, \
	.service = 0x0b, .name = "read_record_req" } }
#define UIM_READ_RECORD_RESP_NEW ({ \
	struct uim_read_record_resp *ptr = malloc(sizeof(struct uim_read_record_resp)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x0021; \
	ptr->hdr.ei = uim_read_record_resp_ei; \
	ptr->hdr.service = 0x0b; \
	ptr->hdr.name = "read_record_resp"; ptr; })
#define UIM_READ_RECORD_RESP_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x0021, 0 },\
	.ei = uim_read_record_resp_ei, \
	.service = 0x0b, .name = "read_record_resp" } }
#define UIM_GET_FILE_ATTRS_REQ_NEW ({ \
	struct uim_get_file_attrs_req *ptr = malloc(sizeof(struct uim_get_file_attrs_req)); \
	ptr->hdr.qmi_header.type = 0; \
	ptr->hdr.qmi_header.msg_id = 0x0024; \
	ptr->hdr.ei = uim_get_file_attrs_req_ei; \
	ptr->hdr.service = 0x0b; \
	ptr->hdr.name = "get_file_attrs_req"; ptr; })
#define UIM_GET_FILE_ATTRS_REQ_INITIALIZER { .hdr = { .qmi_header = { 0, 0, 0x0024, 0 },\
	.ei = uim_get_file_attrs_req_ei, \
	.service = 0x0b, .name = "get_file_attrs_req" } }
#define UIM_GET_FILE_ATTRS_RESP_NEW ({ \
	struct uim_get_file_attrs_resp *ptr = malloc(sizeof(struct uim_get_file_attrs_resp)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x0024; \
	ptr->hdr.ei = uim_get_file_attrs_resp_ei; \
	ptr->hdr.service = 0x0b; \
	ptr->hdr.name = "get_file_attrs_resp"; ptr; })
#define UIM_GET_FILE_ATTRS_RESP_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x0024, 0 },\
	.ei = uim_get_file_attrs_resp_ei, \
	.service = 0x0b, .name = "get_file_attrs_resp" } }
#define UIM_REFRESH_NEW ({ \
	struct uim_refresh *ptr = malloc(sizeof(struct uim_refresh)); \
	ptr->hdr.qmi_header.type = 4; \
	ptr->hdr.qmi_header.msg_id = 0x0033; \
	ptr->hdr.ei = uim_refresh_ei; \
	ptr->hdr.service = 0x0b; \
	ptr->hdr.name = "refresh"; ptr; })
#define UIM_REFRESH_INITIALIZER { .hdr = { .qmi_header = { 4, 0, 0x0033, 0 },\
	.ei = uim_refresh_ei, \
	.service = 0x0b, .name = "refresh" } }

#endif
