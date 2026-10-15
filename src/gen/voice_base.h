// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <aidl/android/hardware/radio/voice/BnRadioVoice.h>
#include <aidl/android/hardware/radio/voice/IRadioVoiceResponse.h>
#include <aidl/android/hardware/radio/voice/IRadioVoiceIndication.h>
#include "response_info.h"

class RadioVoiceBase : public ::aidl::android::hardware::radio::voice::BnRadioVoice {
  protected:
    std::shared_ptr<::aidl::android::hardware::radio::voice::IRadioVoiceResponse> mResp;
    std::shared_ptr<::aidl::android::hardware::radio::voice::IRadioVoiceIndication> mInd;
    virtual void onResponseFunctionsSet() {}

  public:
    ::ndk::ScopedAStatus acceptCall(int32_t in_serial) override {
        if (mResp) mResp->acceptCallResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus cancelPendingUssd(int32_t in_serial) override {
        if (mResp) mResp->cancelPendingUssdResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus conference(int32_t in_serial) override {
        if (mResp) mResp->conferenceResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus dial(int32_t in_serial, const ::aidl::android::hardware::radio::voice::Dial& in_dialInfo) override {
        if (mResp) mResp->dialResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus emergencyDial(int32_t in_serial, const ::aidl::android::hardware::radio::voice::Dial& in_dialInfo, int32_t in_categories, const std::vector<std::string>& in_urns, ::aidl::android::hardware::radio::voice::EmergencyCallRouting in_routing, bool in_hasKnownUserIntentEmergency, bool in_isTesting) override {
        if (mResp) mResp->emergencyDialResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus exitEmergencyCallbackMode(int32_t in_serial) override {
        if (mResp) mResp->exitEmergencyCallbackModeResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus explicitCallTransfer(int32_t in_serial) override {
        if (mResp) mResp->explicitCallTransferResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getCallForwardStatus(int32_t in_serial, const ::aidl::android::hardware::radio::voice::CallForwardInfo& in_callInfo) override {
        if (mResp) mResp->getCallForwardStatusResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getCallWaiting(int32_t in_serial, int32_t in_serviceClass) override {
        if (mResp) mResp->getCallWaitingResponse(notSupported(in_serial), {}, {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getClip(int32_t in_serial) override {
        if (mResp) mResp->getClipResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getClir(int32_t in_serial) override {
        if (mResp) mResp->getClirResponse(notSupported(in_serial), {}, {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getCurrentCalls(int32_t in_serial) override {
        if (mResp) mResp->getCurrentCallsResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getLastCallFailCause(int32_t in_serial) override {
        if (mResp) mResp->getLastCallFailCauseResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getMute(int32_t in_serial) override {
        if (mResp) mResp->getMuteResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getPreferredVoicePrivacy(int32_t in_serial) override {
        if (mResp) mResp->getPreferredVoicePrivacyResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getTtyMode(int32_t in_serial) override {
        if (mResp) mResp->getTtyModeResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus handleStkCallSetupRequestFromSim(int32_t in_serial, bool in_accept) override {
        if (mResp) mResp->handleStkCallSetupRequestFromSimResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus hangup(int32_t in_serial, int32_t in_gsmIndex) override {
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus hangupForegroundResumeBackground(int32_t in_serial) override {
        if (mResp) mResp->hangupForegroundResumeBackgroundResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus hangupWaitingOrBackground(int32_t in_serial) override {
        if (mResp) mResp->hangupWaitingOrBackgroundResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus isVoNrEnabled(int32_t in_serial) override {
        if (mResp) mResp->isVoNrEnabledResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus rejectCall(int32_t in_serial) override {
        if (mResp) mResp->rejectCallResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus responseAcknowledgement() override {
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus sendBurstDtmf(int32_t in_serial, const std::string& in_dtmf, int32_t in_on, int32_t in_off) override {
        if (mResp) mResp->sendBurstDtmfResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus sendCdmaFeatureCode(int32_t in_serial, const std::string& in_featureCode) override {
        if (mResp) mResp->sendCdmaFeatureCodeResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus sendDtmf(int32_t in_serial, const std::string& in_s) override {
        if (mResp) mResp->sendDtmfResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus sendUssd(int32_t in_serial, const std::string& in_ussd) override {
        if (mResp) mResp->sendUssdResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus separateConnection(int32_t in_serial, int32_t in_gsmIndex) override {
        if (mResp) mResp->separateConnectionResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setCallForward(int32_t in_serial, const ::aidl::android::hardware::radio::voice::CallForwardInfo& in_callInfo) override {
        if (mResp) mResp->setCallForwardResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setCallWaiting(int32_t in_serial, bool in_enable, int32_t in_serviceClass) override {
        if (mResp) mResp->setCallWaitingResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setClir(int32_t in_serial, int32_t in_status) override {
        if (mResp) mResp->setClirResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setMute(int32_t in_serial, bool in_enable) override {
        if (mResp) mResp->setMuteResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setPreferredVoicePrivacy(int32_t in_serial, bool in_enable) override {
        if (mResp) mResp->setPreferredVoicePrivacyResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr<::aidl::android::hardware::radio::voice::IRadioVoiceResponse>& in_radioVoiceResponse, const std::shared_ptr<::aidl::android::hardware::radio::voice::IRadioVoiceIndication>& in_radioVoiceIndication) override {
        mResp = in_radioVoiceResponse;
        mInd = in_radioVoiceIndication;
        onResponseFunctionsSet();
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setTtyMode(int32_t in_serial, ::aidl::android::hardware::radio::voice::TtyMode in_mode) override {
        if (mResp) mResp->setTtyModeResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setVoNrEnabled(int32_t in_serial, bool in_enable) override {
        if (mResp) mResp->setVoNrEnabledResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus startDtmf(int32_t in_serial, const std::string& in_s) override {
        if (mResp) mResp->startDtmfResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus stopDtmf(int32_t in_serial) override {
        if (mResp) mResp->stopDtmfResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus switchWaitingOrHoldingAndActive(int32_t in_serial) override {
        if (mResp) mResp->switchWaitingOrHoldingAndActiveResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
};
