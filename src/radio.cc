// SPDX-License-Identifier: Apache-2.0
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <android/log.h>

#include <climits>
#include <cstdio>
#include <mutex>

#include <aidl/android/hardware/radio/RadioAccessFamily.h>

#include "gen/config_base.h"
#include "gen/data_base.h"
#include "gen/messaging_base.h"
#include "gen/modem_base.h"
#include "gen/network_base.h"
#include "gen/sim_base.h"
#include "gen/voice_base.h"
#include "qmi_glue.h"

#define LOG_TAG "qrild"
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

namespace radio = ::aidl::android::hardware::radio;
namespace config = radio::config;
namespace modem = radio::modem;
namespace network = radio::network;
namespace sim = radio::sim;

using radio::RadioIndicationType;
using radio::RadioTechnology;

static std::string mncString(int mcc, int mnc) {
    static const int three[] = {302, 310, 311, 312, 313, 314, 315, 316, 334, 338, 342, 344,
                                346, 348, 354, 356, 358, 360, 365, 376, 405, 708, 722, 732};
    char buf[8];
    bool wide = mnc >= 100;
    for (int m : three) wide |= m == mcc;
    snprintf(buf, sizeof(buf), wide ? "%03d" : "%02d", mnc);
    return buf;
}

static std::string mccString(int mcc) {
    char buf[8];
    snprintf(buf, sizeof(buf), "%03d", mcc);
    return buf;
}

static network::SignalStrength makeSignal(const glue_signal& s) {
    network::SignalStrength ss;
    ALOGI("signal: lte %d rssi %d rsrq %d rsrp %d snr %d, wcdma %d %d, gsm %d %d", s.lte_valid,
          s.lte_rssi, s.lte_rsrq, s.lte_rsrp, s.lte_snr, s.wcdma_valid, s.wcdma_rssi, s.gsm_valid,
          s.gsm_rssi);
    ss.gsm = {INT_MAX, INT_MAX, INT_MAX};
    ss.cdma = {INT_MAX, INT_MAX};
    ss.evdo = {INT_MAX, INT_MAX, INT_MAX};
    ss.lte = {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX};
    ss.tdscdma = {INT_MAX, INT_MAX, INT_MAX};
    ss.wcdma = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};
    ss.nr.ssRsrp = ss.nr.ssRsrq = ss.nr.ssSinr = INT_MAX;
    ss.nr.csiRsrp = ss.nr.csiRsrq = ss.nr.csiSinr = INT_MAX;
    ss.nr.csiCqiTableIndex = ss.nr.timingAdvance = INT_MAX;

    if (s.lte_valid) {
        int asu = (s.lte_rssi + 113) / 2;
        ss.lte.signalStrength = asu < 0 ? 0 : (asu > 31 ? 31 : asu);
        ss.lte.rsrp = -s.lte_rsrp;
        ss.lte.rsrq = -s.lte_rsrq;
        ss.lte.rssnr = s.lte_snr;
    }
    if (s.wcdma_valid) {
        int asu = (s.wcdma_rssi + 113) / 2;
        ss.wcdma.signalStrength = asu < 0 ? 0 : (asu > 31 ? 31 : asu);
        ss.wcdma.bitErrorRate = 99;
    }
    if (s.gsm_valid) {
        int asu = (s.gsm_rssi + 113) / 2;
        ss.gsm.signalStrength = asu < 0 ? 0 : (asu > 31 ? 31 : asu);
        ss.gsm.bitErrorRate = 99;
    }
    return ss;
}

static network::RegStateResult makeRegState(const glue_serving& s) {
    network::RegStateResult r;
    ALOGI("serving: reg %d rat %d plmn %d %d-%d '%s' lac %d cid %d", s.reg_state, s.rat,
          s.plmn_valid, s.mcc, s.mnc, s.description, s.lac, s.cid);
    switch (s.reg_state) {
        case 1: r.regState = network::RegState::REG_HOME; break;
        case 2: r.regState = network::RegState::NOT_REG_MT_SEARCHING_OP; break;
        case 3: r.regState = network::RegState::REG_DENIED; break;
        case 0: r.regState = network::RegState::NOT_REG_MT_NOT_SEARCHING_OP; break;
        default: r.regState = network::RegState::UNKNOWN; break;
    }

    switch (s.rat) {
        case GLUE_RAT_LTE: r.rat = RadioTechnology::LTE; break;
        case GLUE_RAT_UMTS: r.rat = RadioTechnology::UMTS; break;
        case GLUE_RAT_GSM: r.rat = RadioTechnology::EDGE; break;
        default: r.rat = RadioTechnology::UNKNOWN; break;
    }

    r.accessTechnologySpecificInfo =
            network::AccessTechnologySpecificInfo::make<network::AccessTechnologySpecificInfo::noinit>(true);

    if (s.reg_state != 1 || !s.plmn_valid) {
        r.cellIdentity = network::CellIdentity::make<network::CellIdentity::noinit>(true);
        return r;
    }

    std::string mcc = mccString(s.mcc), mnc = mncString(s.mcc, s.mnc);
    network::OperatorInfo op = {s.description, s.description, mcc + mnc, 0};
    r.registeredPlmn = mcc + mnc;

    if (s.rat == GLUE_RAT_LTE) {
        network::CellIdentityLte lte;
        lte.mcc = mcc;
        lte.mnc = mnc;
        lte.ci = s.cid_valid ? s.cid : INT_MAX;
        lte.pci = INT_MAX;
        lte.tac = s.lac_valid ? s.lac : INT_MAX;
        lte.earfcn = INT_MAX;
        lte.operatorNames = op;
        lte.bandwidth = INT_MAX;
        r.cellIdentity = network::CellIdentity::make<network::CellIdentity::lte>(lte);
    } else if (s.rat == GLUE_RAT_UMTS) {
        network::CellIdentityWcdma w;
        w.mcc = mcc;
        w.mnc = mnc;
        w.lac = s.lac_valid ? s.lac : INT_MAX;
        w.cid = s.cid_valid ? s.cid : INT_MAX;
        w.psc = INT_MAX;
        w.uarfcn = INT_MAX;
        w.operatorNames = op;
        r.cellIdentity = network::CellIdentity::make<network::CellIdentity::wcdma>(w);
    } else {
        network::CellIdentityGsm g;
        g.mcc = mcc;
        g.mnc = mnc;
        g.lac = s.lac_valid ? s.lac : INT_MAX;
        g.cid = s.cid_valid ? s.cid : INT_MAX;
        g.arfcn = INT_MAX;
        g.bsic = 0xff;
        g.operatorNames = op;
        r.cellIdentity = network::CellIdentity::make<network::CellIdentity::gsm>(g);
    }
    return r;
}

class RadioConfig : public RadioConfigBase {
  public:
    ::ndk::ScopedAStatus getHalDeviceCapabilities(int32_t in_serial) override {
        if (mResp) mResp->getHalDeviceCapabilitiesResponse(rspInfo(in_serial), false);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getNumOfLiveModems(int32_t in_serial) override {
        if (mResp) mResp->getNumOfLiveModemsResponse(rspInfo(in_serial), 1);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getPhoneCapability(int32_t in_serial) override {
        config::PhoneCapability cap;
        cap.maxActiveData = 1;
        cap.maxActiveInternetData = 1;
        cap.isInternetLingeringSupported = false;
        cap.logicalModemIds = {0};
        cap.maxActiveVoice = 1;
        if (mResp) mResp->getPhoneCapabilityResponse(rspInfo(in_serial), cap);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getSimSlotsStatus(int32_t in_serial) override {
        glue_card c;
        config::SimSlotStatus slot;
        config::SimPortInfo port;
        bool present = glue_get_card(&c) == 0 && c.present;
        slot.cardState = present ? sim::CardStatus::STATE_PRESENT : sim::CardStatus::STATE_ABSENT;
        char iccid[64] = "";
        if (present) glue_get_iccid(iccid, sizeof(iccid));
        port.iccId = iccid;
        port.logicalSlotId = 0;
        port.portActive = true;
        slot.portInfo = {port};
        if (mResp) mResp->getSimSlotsStatusResponse(rspInfo(in_serial), {slot});
        return ::ndk::ScopedAStatus::ok();
    }
};

class RadioModem : public RadioModemBase {
  protected:
    void onResponseFunctionsSet() override {
        bool online = false;
        glue_get_online(&online);
        mInd->rilConnected(RadioIndicationType::UNSOLICITED);
        mInd->radioStateChanged(RadioIndicationType::UNSOLICITED,
                                online ? modem::RadioState::ON : modem::RadioState::OFF);
    }

  public:
    ::ndk::ScopedAStatus enableModem(int32_t in_serial, bool in_on) override {
        if (mResp) mResp->enableModemResponse(rspInfo(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getBasebandVersion(int32_t in_serial) override {
        char rev[256] = "";
        int rc = glue_get_revision(rev, sizeof(rev));
        if (mResp)
            mResp->getBasebandVersionResponse(
                    rspInfo(in_serial, rc ? RadioError::MODEM_ERR : RadioError::NONE), rev);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getDeviceIdentity(int32_t in_serial) override {
        char imei[256] = "", svn[256] = "";
        int rc = glue_get_ids(imei, svn, sizeof(imei));
        if (mResp)
            mResp->getDeviceIdentityResponse(
                    rspInfo(in_serial, rc ? RadioError::MODEM_ERR : RadioError::NONE), imei, svn,
                    "", "");
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getImei(int32_t in_serial) override {
        char imei[256] = "", svn[256] = "";
        int rc = glue_get_ids(imei, svn, sizeof(imei));
        modem::ImeiInfo info;
        info.type = modem::ImeiInfo::ImeiType::PRIMARY;
        info.imei = imei;
        info.svn = svn;
        if (mResp)
            mResp->getImeiResponse(rspInfo(in_serial, rc ? RadioError::MODEM_ERR : RadioError::NONE),
                                   info);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getModemStackStatus(int32_t in_serial) override {
        if (mResp) mResp->getModemStackStatusResponse(rspInfo(in_serial), true);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getRadioCapability(int32_t in_serial) override {
        modem::RadioCapability rc;
        rc.session = 0;
        rc.phase = modem::RadioCapability::PHASE_CONFIGURED;
        rc.raf = static_cast<int32_t>(radio::RadioAccessFamily::GPRS) |
                 static_cast<int32_t>(radio::RadioAccessFamily::EDGE) |
                 static_cast<int32_t>(radio::RadioAccessFamily::UMTS) |
                 static_cast<int32_t>(radio::RadioAccessFamily::HSPA) |
                 static_cast<int32_t>(radio::RadioAccessFamily::LTE);
        rc.logicalModemUuid = "com.qrild.lm0";
        rc.status = modem::RadioCapability::STATUS_NONE;
        if (mResp) mResp->getRadioCapabilityResponse(rspInfo(in_serial), rc);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus requestShutdown(int32_t in_serial) override {
        glue_set_online(false);
        if (mResp) mResp->requestShutdownResponse(rspInfo(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus sendDeviceState(int32_t in_serial, modem::DeviceStateType in_deviceStateType,
                                         bool in_state) override {
        if (mResp) mResp->sendDeviceStateResponse(rspInfo(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setRadioPower(int32_t in_serial, bool in_powerOn, bool in_forEmergencyCall,
                                       bool in_preferredForEmergencyCall) override {
        int rc = glue_set_online(in_powerOn);
        ALOGI("setRadioPower(%d): %d", in_powerOn, rc);
        if (!rc && in_powerOn) glue_set_mode_pref_lte();
        if (mResp)
            mResp->setRadioPowerResponse(rspInfo(in_serial, rc ? RadioError::MODEM_ERR : RadioError::NONE));
        if (!rc && mInd)
            mInd->radioStateChanged(RadioIndicationType::UNSOLICITED,
                                    in_powerOn ? modem::RadioState::ON : modem::RadioState::OFF);
        return ::ndk::ScopedAStatus::ok();
    }
};

class RadioSim : public RadioSimBase {
  protected:
    void onResponseFunctionsSet() override { simChanged(); }

  public:
    void simChanged() {
        if (mInd) mInd->simStatusChanged(RadioIndicationType::UNSOLICITED);
    }
    ::ndk::ScopedAStatus areUiccApplicationsEnabled(int32_t in_serial) override {
        if (mResp) mResp->areUiccApplicationsEnabledResponse(rspInfo(in_serial), true);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getFacilityLockForApp(int32_t in_serial, const std::string& in_facility,
                                               const std::string& in_password,
                                               int32_t in_serviceClass,
                                               const std::string& in_appId) override {
        if (mResp) mResp->getFacilityLockForAppResponse(rspInfo(in_serial), 0);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getIccCardStatus(int32_t in_serial) override {
        glue_card c;
        sim::CardStatus cs;
        int rc = glue_get_card(&c);

        cs.cardState = (!rc && c.present) ? sim::CardStatus::STATE_PRESENT : sim::CardStatus::STATE_ABSENT;
        cs.universalPinState = static_cast<sim::PinState>(c.upin_state);
        cs.gsmUmtsSubscriptionAppIndex = -1;
        cs.cdmaSubscriptionAppIndex = -1;
        cs.imsSubscriptionAppIndex = -1;
        if (cs.cardState == sim::CardStatus::STATE_PRESENT) {
            char iccid[64] = "";
            glue_get_iccid(iccid, sizeof(iccid));
            cs.iccid = iccid;
            ALOGI("iccid %s", iccid);
        }
        cs.slotMap.physicalSlotId = 0;
        cs.slotMap.portId = 0;

        if (cs.cardState == sim::CardStatus::STATE_PRESENT && c.app_type) {
            sim::AppStatus app;
            app.appType = c.app_type <= 5 ? c.app_type : sim::AppStatus::APP_TYPE_UNKNOWN;
            switch (c.app_state) {
                case 1: app.appState = sim::AppStatus::APP_STATE_DETECTED; break;
                case 2: app.appState = sim::AppStatus::APP_STATE_PIN; break;
                case 3:
                case 5: app.appState = sim::AppStatus::APP_STATE_PUK; break;
                case 4: app.appState = sim::AppStatus::APP_STATE_SUBSCRIPTION_PERSO; break;
                case 7: app.appState = sim::AppStatus::APP_STATE_READY; break;
                default: app.appState = sim::AppStatus::APP_STATE_UNKNOWN; break;
            }
            app.persoSubstate = c.perso_state == 2 ? sim::PersoSubstate::READY
                                                   : static_cast<sim::PersoSubstate>(c.perso_state);
            app.aidPtr = c.aid;
            app.pin1Replaced = c.upin_replaces_pin1;
            app.pin1 = static_cast<sim::PinState>(c.pin1_state);
            app.pin2 = static_cast<sim::PinState>(c.pin2_state);
            cs.applications = {app};
            cs.gsmUmtsSubscriptionAppIndex = 0;
        }

        if (mResp) mResp->getIccCardStatusResponse(rspInfo(in_serial), cs);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getImsiForApp(int32_t in_serial, const std::string& in_aid) override {
        char imsi[256] = "";
        int rc = glue_get_imsi(imsi, sizeof(imsi));
        if (mResp)
            mResp->getImsiForAppResponse(
                    rspInfo(in_serial, rc ? RadioError::MODEM_ERR : RadioError::NONE), imsi);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus reportStkServiceIsRunning(int32_t in_serial) override {
        if (mResp) mResp->reportStkServiceIsRunningResponse(rspInfo(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
};

class RadioNetwork : public RadioNetworkBase {
    int32_t mAllowedTypes = 0;

  protected:
    void onResponseFunctionsSet() override {
        servingChanged();
        signalChanged();
    }

  public:
    void servingChanged() {
        if (mInd) mInd->networkStateChanged(RadioIndicationType::UNSOLICITED);
    }
    void signalChanged() {
        glue_signal s;
        if (mInd && glue_get_signal(&s) == 0)
            mInd->currentSignalStrength(RadioIndicationType::UNSOLICITED, makeSignal(s));
    }
    ::ndk::ScopedAStatus getAllowedNetworkTypesBitmap(int32_t in_serial) override {
        if (mResp) mResp->getAllowedNetworkTypesBitmapResponse(rspInfo(in_serial), mAllowedTypes);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setAllowedNetworkTypesBitmap(int32_t in_serial,
                                                      int32_t in_networkTypeBitmap) override {
        mAllowedTypes = in_networkTypeBitmap;
        if (mResp) mResp->setAllowedNetworkTypesBitmapResponse(rspInfo(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getCellInfoList(int32_t in_serial) override {
        if (mResp) mResp->getCellInfoListResponse(rspInfo(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getDataRegistrationState(int32_t in_serial) override {
        glue_serving s;
        int rc = glue_get_serving(&s);
        if (mResp)
            mResp->getDataRegistrationStateResponse(
                    rspInfo(in_serial, rc ? RadioError::MODEM_ERR : RadioError::NONE), makeRegState(s));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getVoiceRegistrationState(int32_t in_serial) override {
        glue_serving s;
        int rc = glue_get_serving(&s);
        if (mResp)
            mResp->getVoiceRegistrationStateResponse(
                    rspInfo(in_serial, rc ? RadioError::MODEM_ERR : RadioError::NONE), makeRegState(s));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getNetworkSelectionMode(int32_t in_serial) override {
        if (mResp) mResp->getNetworkSelectionModeResponse(rspInfo(in_serial), false);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getOperator(int32_t in_serial) override {
        glue_serving s;
        int rc = glue_get_serving(&s);
        std::string numeric;
        if (!rc && s.reg_state == 1 && s.plmn_valid)
            numeric = mccString(s.mcc) + mncString(s.mcc, s.mnc);
        else
            s.description[0] = '\0';
        if (mResp)
            mResp->getOperatorResponse(rspInfo(in_serial, rc ? RadioError::MODEM_ERR : RadioError::NONE),
                                       s.description, s.description, numeric);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getSignalStrength(int32_t in_serial) override {
        glue_signal s;
        int rc = glue_get_signal(&s);
        if (mResp)
            mResp->getSignalStrengthResponse(
                    rspInfo(in_serial, rc ? RadioError::MODEM_ERR : RadioError::NONE), makeSignal(s));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus isNrDualConnectivityEnabled(int32_t in_serial) override {
        if (mResp) mResp->isNrDualConnectivityEnabledResponse(rspInfo(in_serial), false);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setIndicationFilter(int32_t in_serial, int32_t in_indicationFilter) override {
        if (mResp) mResp->setIndicationFilterResponse(rspInfo(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setLinkCapacityReportingCriteria(
            int32_t in_serial, int32_t in_hysteresisMs, int32_t in_hysteresisDlKbps,
            int32_t in_hysteresisUlKbps, const std::vector<int32_t>& in_thresholdsDownlinkKbps,
            const std::vector<int32_t>& in_thresholdsUplinkKbps,
            radio::AccessNetwork in_accessNetwork) override {
        if (mResp) mResp->setLinkCapacityReportingCriteriaResponse(rspInfo(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setNetworkSelectionModeAutomatic(int32_t in_serial) override {
        if (mResp) mResp->setNetworkSelectionModeAutomaticResponse(rspInfo(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setSignalStrengthReportingCriteria(
            int32_t in_serial,
            const std::vector<network::SignalThresholdInfo>& in_signalThresholdInfos) override {
        if (mResp) mResp->setSignalStrengthReportingCriteriaResponse(rspInfo(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getUsageSetting(int32_t in_serial) override {
        if (mResp)
            mResp->getUsageSettingResponse(rspInfo(in_serial), network::UsageSetting::DATA_CENTRIC);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setUsageSetting(int32_t in_serial, network::UsageSetting in_usageSetting) override {
        if (mResp) mResp->setUsageSettingResponse(rspInfo(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
};

namespace messaging = radio::messaging;

static std::vector<uint8_t> hexToBytes(const std::string& hex) {
    std::vector<uint8_t> out;
    for (size_t i = 0; i + 1 < hex.size(); i += 2)
        out.push_back(static_cast<uint8_t>(std::stoi(hex.substr(i, 2), nullptr, 16)));
    return out;
}

class RadioMessaging : public RadioMessagingBase {
    ::ndk::ScopedAStatus doSend(int32_t serial, const messaging::GsmSmsMessage& m, bool more) {
        std::vector<uint8_t> raw = m.smscPdu.empty() ? std::vector<uint8_t>{0} : hexToBytes(m.smscPdu);
        std::vector<uint8_t> tpdu = hexToBytes(m.pdu);
        raw.insert(raw.end(), tpdu.begin(), tpdu.end());

        int ref = 0, cause = -1;
        int rc = glue_sms_send(raw.data(), raw.size(), &ref, &cause);
        messaging::SendSmsResult res;
        res.messageRef = ref;
        res.errorCode = rc ? cause : -1;
        RadioError err = RadioError::NONE;
        if (rc) err = rc < 0 ? RadioError::INTERNAL_ERR : RadioError::GENERIC_FAILURE;
        if (mResp) {
            if (more)
                mResp->sendSmsExpectMoreResponse(rspInfo(serial, err), res);
            else
                mResp->sendSmsResponse(rspInfo(serial, err), res);
        }
        return ::ndk::ScopedAStatus::ok();
    }

  public:
    void newSms(const uint8_t* pdu, int len) {
        if (mInd)
            mInd->newSms(RadioIndicationType::UNSOLICITED, std::vector<uint8_t>(pdu, pdu + len));
    }
    ::ndk::ScopedAStatus sendSms(int32_t in_serial, const messaging::GsmSmsMessage& in_message) override {
        return doSend(in_serial, in_message, false);
    }
    ::ndk::ScopedAStatus sendSmsExpectMore(int32_t in_serial,
                                           const messaging::GsmSmsMessage& in_message) override {
        return doSend(in_serial, in_message, true);
    }
    ::ndk::ScopedAStatus acknowledgeLastIncomingGsmSms(
            int32_t in_serial, bool in_success, messaging::SmsAcknowledgeFailCause in_cause) override {
        int rc = glue_sms_ack(in_success);
        if (mResp)
            mResp->acknowledgeLastIncomingGsmSmsResponse(
                    rspInfo(in_serial, rc ? RadioError::MODEM_ERR : RadioError::NONE));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getSmscAddress(int32_t in_serial) override {
        char smsc[64];
        int rc = glue_get_smsc(smsc, sizeof(smsc));
        if (mResp)
            mResp->getSmscAddressResponse(rspInfo(in_serial, rc ? RadioError::MODEM_ERR : RadioError::NONE),
                                          smsc);
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus reportSmsMemoryStatus(int32_t in_serial, bool in_available) override {
        if (mResp) mResp->reportSmsMemoryStatusResponse(rspInfo(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setGsmBroadcastActivation(int32_t in_serial, bool in_activate) override {
        if (mResp) mResp->setGsmBroadcastActivationResponse(rspInfo(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setGsmBroadcastConfig(
            int32_t in_serial, const std::vector<messaging::GsmBroadcastSmsConfigInfo>& in_configInfo) override {
        if (mResp) mResp->setGsmBroadcastConfigResponse(rspInfo(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
};

static std::shared_ptr<RadioSim> gSim;
static std::shared_ptr<RadioNetwork> gNetwork;
static std::shared_ptr<RadioMessaging> gMessaging;

static void onNewSms(const uint8_t* pdu, int len) {
    if (gMessaging) gMessaging->newSms(pdu, len);
}

static void onServing() {
    if (gNetwork) gNetwork->servingChanged();
}

static void onSignal() {
    if (gNetwork) gNetwork->signalChanged();
}

static void onSim() {
    if (gSim) gSim->simChanged();
}

template <typename T>
static void addService(const std::shared_ptr<T>& svc, const std::string& instance) {
    std::string name = std::string(T::descriptor) + "/" + instance;
    binder_status_t st = AServiceManager_addService(svc->asBinder().get(), name.c_str());
    ALOGI("register %s: %d", name.c_str(), st);
}

int main() {
    static const glue_callbacks cb = {onServing, onSignal, onSim, onNewSms};

    ABinderProcess_setThreadPoolMaxThreadCount(4);
    ALOGI("starting, waiting for the modem");
    glue_init(&cb);

    auto cfg = ndk::SharedRefBase::make<RadioConfig>();
    auto mdm = ndk::SharedRefBase::make<RadioModem>();
    gSim = ndk::SharedRefBase::make<RadioSim>();
    gNetwork = ndk::SharedRefBase::make<RadioNetwork>();
    auto data = ndk::SharedRefBase::make<RadioDataBase>();
    gMessaging = ndk::SharedRefBase::make<RadioMessaging>();
    auto voice = ndk::SharedRefBase::make<RadioVoiceBase>();

    addService(cfg, "default");
    addService(mdm, "slot1");
    addService(gSim, "slot1");
    addService(gNetwork, "slot1");
    addService(data, "slot1");
    addService(gMessaging, "slot1");
    addService(voice, "slot1");

    ABinderProcess_startThreadPool();
    ABinderProcess_joinThreadPool();
    return 0;
}
