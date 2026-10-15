// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <aidl/android/hardware/radio/messaging/BnRadioMessaging.h>
#include <aidl/android/hardware/radio/messaging/IRadioMessagingResponse.h>
#include <aidl/android/hardware/radio/messaging/IRadioMessagingIndication.h>
#include "response_info.h"

class RadioMessagingBase : public ::aidl::android::hardware::radio::messaging::BnRadioMessaging {
  protected:
    std::shared_ptr<::aidl::android::hardware::radio::messaging::IRadioMessagingResponse> mResp;
    std::shared_ptr<::aidl::android::hardware::radio::messaging::IRadioMessagingIndication> mInd;
    virtual void onResponseFunctionsSet() {}

  public:
    ::ndk::ScopedAStatus acknowledgeIncomingGsmSmsWithPdu(int32_t in_serial, bool in_success, const std::string& in_ackPdu) override {
        if (mResp) mResp->acknowledgeIncomingGsmSmsWithPduResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus acknowledgeLastIncomingCdmaSms(int32_t in_serial, const ::aidl::android::hardware::radio::messaging::CdmaSmsAck& in_smsAck) override {
        if (mResp) mResp->acknowledgeLastIncomingCdmaSmsResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus acknowledgeLastIncomingGsmSms(int32_t in_serial, bool in_success, ::aidl::android::hardware::radio::messaging::SmsAcknowledgeFailCause in_cause) override {
        if (mResp) mResp->acknowledgeLastIncomingGsmSmsResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus deleteSmsOnRuim(int32_t in_serial, int32_t in_index) override {
        if (mResp) mResp->deleteSmsOnRuimResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus deleteSmsOnSim(int32_t in_serial, int32_t in_index) override {
        if (mResp) mResp->deleteSmsOnSimResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getCdmaBroadcastConfig(int32_t in_serial) override {
        if (mResp) mResp->getCdmaBroadcastConfigResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getGsmBroadcastConfig(int32_t in_serial) override {
        if (mResp) mResp->getGsmBroadcastConfigResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getSmscAddress(int32_t in_serial) override {
        if (mResp) mResp->getSmscAddressResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus reportSmsMemoryStatus(int32_t in_serial, bool in_available) override {
        if (mResp) mResp->reportSmsMemoryStatusResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus responseAcknowledgement() override {
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus sendCdmaSms(int32_t in_serial, const ::aidl::android::hardware::radio::messaging::CdmaSmsMessage& in_sms) override {
        if (mResp) mResp->sendCdmaSmsResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus sendCdmaSmsExpectMore(int32_t in_serial, const ::aidl::android::hardware::radio::messaging::CdmaSmsMessage& in_sms) override {
        if (mResp) mResp->sendCdmaSmsExpectMoreResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus sendImsSms(int32_t in_serial, const ::aidl::android::hardware::radio::messaging::ImsSmsMessage& in_message) override {
        if (mResp) mResp->sendImsSmsResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus sendSms(int32_t in_serial, const ::aidl::android::hardware::radio::messaging::GsmSmsMessage& in_message) override {
        if (mResp) mResp->sendSmsResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus sendSmsExpectMore(int32_t in_serial, const ::aidl::android::hardware::radio::messaging::GsmSmsMessage& in_message) override {
        if (mResp) mResp->sendSmsExpectMoreResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setCdmaBroadcastActivation(int32_t in_serial, bool in_activate) override {
        if (mResp) mResp->setCdmaBroadcastActivationResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setCdmaBroadcastConfig(int32_t in_serial, const std::vector<::aidl::android::hardware::radio::messaging::CdmaBroadcastSmsConfigInfo>& in_configInfo) override {
        if (mResp) mResp->setCdmaBroadcastConfigResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setGsmBroadcastActivation(int32_t in_serial, bool in_activate) override {
        if (mResp) mResp->setGsmBroadcastActivationResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setGsmBroadcastConfig(int32_t in_serial, const std::vector<::aidl::android::hardware::radio::messaging::GsmBroadcastSmsConfigInfo>& in_configInfo) override {
        if (mResp) mResp->setGsmBroadcastConfigResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr<::aidl::android::hardware::radio::messaging::IRadioMessagingResponse>& in_radioMessagingResponse, const std::shared_ptr<::aidl::android::hardware::radio::messaging::IRadioMessagingIndication>& in_radioMessagingIndication) override {
        mResp = in_radioMessagingResponse;
        mInd = in_radioMessagingIndication;
        onResponseFunctionsSet();
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setSmscAddress(int32_t in_serial, const std::string& in_smsc) override {
        if (mResp) mResp->setSmscAddressResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus writeSmsToRuim(int32_t in_serial, const ::aidl::android::hardware::radio::messaging::CdmaSmsWriteArgs& in_cdmaSms) override {
        if (mResp) mResp->writeSmsToRuimResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus writeSmsToSim(int32_t in_serial, const ::aidl::android::hardware::radio::messaging::SmsWriteArgs& in_smsWriteArgs) override {
        if (mResp) mResp->writeSmsToSimResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
};
