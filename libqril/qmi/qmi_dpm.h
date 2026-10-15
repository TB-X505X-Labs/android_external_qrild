#ifndef __QMI_DPM_H__
#define __QMI_DPM_H__

#include <stdint.h>
#include <stdbool.h>

#include "libqrtr.h"

extern struct qmi_elem_info dpm_open_port_req_ei[];
extern struct qmi_elem_info dpm_open_port_resp_ei[];

#define QMI_DPM_SERVICE 47
#define QMI_DPM_OPEN_PORT 32

struct dpm_control_port {
	uint32_t ep_type;
	uint32_t iface_id;
	uint32_t consumer_pipe_num;
	uint32_t producer_pipe_num;
};

struct dpm_open_port_req { // 0x0020
	struct qmi_message_header hdr;
	bool port_list_valid;
	uint32_t port_list_len;
	struct dpm_control_port port_list[1];  // 0x11
};

struct dpm_open_port_resp { // 0x0020
	struct qmi_message_header hdr;
	struct qmi_response_type_v01 res;  // 0x02
};

#define DPM_OPEN_PORT_REQ_NEW ({ \
	struct dpm_open_port_req *ptr = malloc(sizeof(struct dpm_open_port_req)); \
	ptr->hdr.qmi_header.type = 0; \
	ptr->hdr.qmi_header.msg_id = 0x0020; \
	ptr->hdr.ei = dpm_open_port_req_ei; \
	ptr->hdr.service = 0x2f; \
	ptr->hdr.name = "open_port_req"; ptr; })
#define DPM_OPEN_PORT_REQ_INITIALIZER { .hdr = { .qmi_header = { 0, 0, 0x0020, 0 },\
	.ei = dpm_open_port_req_ei, \
	.service = 0x2f, .name = "open_port_req" } }
#define DPM_OPEN_PORT_RESP_NEW ({ \
	struct dpm_open_port_resp *ptr = malloc(sizeof(struct dpm_open_port_resp)); \
	ptr->hdr.qmi_header.type = 2; \
	ptr->hdr.qmi_header.msg_id = 0x0020; \
	ptr->hdr.ei = dpm_open_port_resp_ei; \
	ptr->hdr.service = 0x2f; \
	ptr->hdr.name = "open_port_resp"; ptr; })
#define DPM_OPEN_PORT_RESP_INITIALIZER { .hdr = { .qmi_header = { 2, 0, 0x0020, 0 },\
	.ei = dpm_open_port_resp_ei, \
	.service = 0x2f, .name = "open_port_resp" } }

#endif
