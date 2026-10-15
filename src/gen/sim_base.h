// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <aidl/android/hardware/radio/sim/BnRadioSim.h>
#include <aidl/android/hardware/radio/sim/IRadioSimResponse.h>
#include <aidl/android/hardware/radio/sim/IRadioSimIndication.h>
#include "response_info.h"

class RadioSimBase : public ::aidl::android::hardware::radio::sim::BnRadioSim {
  protected:
    std::shared_ptr<::aidl::android::hardware::radio::sim::IRadioSimResponse> mResp;
    std::shared_ptr<::aidl::android::hardware::radio::sim::IRadioSimIndication> mInd;
    virtual void onResponseFunctionsSet() {}

  public:
    ::ndk::ScopedAStatus areUiccApplicationsEnabled(int32_t in_serial) override {
        if (mResp) mResp->areUiccApplicationsEnabledResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus changeIccPin2ForApp(int32_t in_serial, const std::string& in_oldPin2, const std::string& in_newPin2, const std::string& in_aid) override {
        if (mResp) mResp->changeIccPin2ForAppResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus changeIccPinForApp(int32_t in_serial, const std::string& in_oldPin, const std::string& in_newPin, const std::string& in_aid) override {
        if (mResp) mResp->changeIccPinForAppResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus enableUiccApplications(int32_t in_serial, bool in_enable) override {
        if (mResp) mResp->enableUiccApplicationsResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getAllowedCarriers(int32_t in_serial) override {
        if (mResp) mResp->getAllowedCarriersResponse(notSupported(in_serial), {}, {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getCdmaSubscription(int32_t in_serial) override {
        if (mResp) mResp->getCdmaSubscriptionResponse(notSupported(in_serial), {}, {}, {}, {}, {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getCdmaSubscriptionSource(int32_t in_serial) override {
        if (mResp) mResp->getCdmaSubscriptionSourceResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getFacilityLockForApp(int32_t in_serial, const std::string& in_facility, const std::string& in_password, int32_t in_serviceClass, const std::string& in_appId) override {
        if (mResp) mResp->getFacilityLockForAppResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getIccCardStatus(int32_t in_serial) override {
        if (mResp) mResp->getIccCardStatusResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getImsiForApp(int32_t in_serial, const std::string& in_aid) override {
        if (mResp) mResp->getImsiForAppResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getSimPhonebookCapacity(int32_t in_serial) override {
        if (mResp) mResp->getSimPhonebookCapacityResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getSimPhonebookRecords(int32_t in_serial) override {
        if (mResp) mResp->getSimPhonebookRecordsResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus iccCloseLogicalChannel(int32_t in_serial, int32_t in_channelId) override {
        if (mResp) mResp->iccCloseLogicalChannelResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus iccIoForApp(int32_t in_serial, const ::aidl::android::hardware::radio::sim::IccIo& in_iccIo) override {
        if (mResp) mResp->iccIoForAppResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus iccOpenLogicalChannel(int32_t in_serial, const std::string& in_aid, int32_t in_p2) override {
        if (mResp) mResp->iccOpenLogicalChannelResponse(notSupported(in_serial), {}, {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus iccTransmitApduBasicChannel(int32_t in_serial, const ::aidl::android::hardware::radio::sim::SimApdu& in_message) override {
        if (mResp) mResp->iccTransmitApduBasicChannelResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus iccTransmitApduLogicalChannel(int32_t in_serial, const ::aidl::android::hardware::radio::sim::SimApdu& in_message) override {
        if (mResp) mResp->iccTransmitApduLogicalChannelResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus reportStkServiceIsRunning(int32_t in_serial) override {
        if (mResp) mResp->reportStkServiceIsRunningResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus requestIccSimAuthentication(int32_t in_serial, int32_t in_authContext, const std::string& in_authData, const std::string& in_aid) override {
        if (mResp) mResp->requestIccSimAuthenticationResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus responseAcknowledgement() override {
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus sendEnvelope(int32_t in_serial, const std::string& in_contents) override {
        if (mResp) mResp->sendEnvelopeResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus sendEnvelopeWithStatus(int32_t in_serial, const std::string& in_contents) override {
        if (mResp) mResp->sendEnvelopeWithStatusResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus sendTerminalResponseToSim(int32_t in_serial, const std::string& in_contents) override {
        if (mResp) mResp->sendTerminalResponseToSimResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setAllowedCarriers(int32_t in_serial, const ::aidl::android::hardware::radio::sim::CarrierRestrictions& in_carriers, ::aidl::android::hardware::radio::sim::SimLockMultiSimPolicy in_multiSimPolicy) override {
        if (mResp) mResp->setAllowedCarriersResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setCarrierInfoForImsiEncryption(int32_t in_serial, const ::aidl::android::hardware::radio::sim::ImsiEncryptionInfo& in_imsiEncryptionInfo) override {
        if (mResp) mResp->setCarrierInfoForImsiEncryptionResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setCdmaSubscriptionSource(int32_t in_serial, ::aidl::android::hardware::radio::sim::CdmaSubscriptionSource in_cdmaSub) override {
        if (mResp) mResp->setCdmaSubscriptionSourceResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setFacilityLockForApp(int32_t in_serial, const std::string& in_facility, bool in_lockState, const std::string& in_password, int32_t in_serviceClass, const std::string& in_appId) override {
        if (mResp) mResp->setFacilityLockForAppResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr<::aidl::android::hardware::radio::sim::IRadioSimResponse>& in_radioSimResponse, const std::shared_ptr<::aidl::android::hardware::radio::sim::IRadioSimIndication>& in_radioSimIndication) override {
        mResp = in_radioSimResponse;
        mInd = in_radioSimIndication;
        onResponseFunctionsSet();
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setSimCardPower(int32_t in_serial, ::aidl::android::hardware::radio::sim::CardPowerState in_powerUp) override {
        if (mResp) mResp->setSimCardPowerResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setUiccSubscription(int32_t in_serial, const ::aidl::android::hardware::radio::sim::SelectUiccSub& in_uiccSub) override {
        if (mResp) mResp->setUiccSubscriptionResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus supplyIccPin2ForApp(int32_t in_serial, const std::string& in_pin2, const std::string& in_aid) override {
        if (mResp) mResp->supplyIccPin2ForAppResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus supplyIccPinForApp(int32_t in_serial, const std::string& in_pin, const std::string& in_aid) override {
        if (mResp) mResp->supplyIccPinForAppResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus supplyIccPuk2ForApp(int32_t in_serial, const std::string& in_puk2, const std::string& in_pin2, const std::string& in_aid) override {
        if (mResp) mResp->supplyIccPuk2ForAppResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus supplyIccPukForApp(int32_t in_serial, const std::string& in_puk, const std::string& in_pin, const std::string& in_aid) override {
        if (mResp) mResp->supplyIccPukForAppResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus supplySimDepersonalization(int32_t in_serial, ::aidl::android::hardware::radio::sim::PersoSubstate in_persoType, const std::string& in_controlKey) override {
        if (mResp) mResp->supplySimDepersonalizationResponse(notSupported(in_serial), {}, {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus updateSimPhonebookRecords(int32_t in_serial, const ::aidl::android::hardware::radio::sim::PhonebookRecordInfo& in_recordInfo) override {
        if (mResp) mResp->updateSimPhonebookRecordsResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus iccCloseLogicalChannelWithSessionInfo(int32_t in_serial, const ::aidl::android::hardware::radio::sim::SessionInfo& in_sessionInfo) override {
        if (mResp) mResp->iccCloseLogicalChannelWithSessionInfoResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
};
