// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GLUE_RAT_NONE 0
#define GLUE_RAT_GSM 4
#define GLUE_RAT_UMTS 5
#define GLUE_RAT_LTE 8

struct glue_signal {
    bool gsm_valid;
    int gsm_rssi;
    bool wcdma_valid;
    int wcdma_rssi;
    int wcdma_ecio;
    bool lte_valid;
    int lte_rssi;
    int lte_rsrq;
    int lte_rsrp;
    int lte_snr;
};

struct glue_serving {
    int reg_state;
    int cs_attached;
    int ps_attached;
    int rat;
    bool plmn_valid;
    int mcc;
    int mnc;
    char description[65];
    bool lac_valid;
    int lac;
    bool cid_valid;
    int cid;
};

struct glue_card {
    bool present;
    int card_state;
    int upin_state;
    int app_type;
    int app_state;
    int perso_state;
    int pin1_state;
    int pin2_state;
    int upin_replaces_pin1;
    char aid[33];
};

struct glue_callbacks {
    void (*serving_changed)(void);
    void (*signal_changed)(void);
    void (*sim_changed)(void);
};

int glue_init(const struct glue_callbacks *cb);
int glue_set_online(bool online);
int glue_get_online(bool *online);
int glue_set_mode_pref_lte(void);
int glue_get_ids(char *imei, char *imeisv, int len);
int glue_get_revision(char *rev, int len);
int glue_get_imsi(char *imsi, int len);
int glue_get_msisdn(char *msisdn, int len);
int glue_get_signal(struct glue_signal *s);
int glue_get_serving(struct glue_serving *s);
int glue_get_card(struct glue_card *c);
int glue_get_plmn_name(int mcc, int mnc, char *long_name, char *short_name, int len);

#ifdef __cplusplus
}
#endif
