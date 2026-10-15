// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <aidl/android/hardware/radio/modem/BnRadioModem.h>
#include <aidl/android/hardware/radio/modem/IRadioModemResponse.h>
#include <aidl/android/hardware/radio/modem/IRadioModemIndication.h>
#include "response_info.h"

class RadioModemBase : public ::aidl::android::hardware::radio::modem::BnRadioModem {
  protected:
    std::shared_ptr<::aidl::android::hardware::radio::modem::IRadioModemResponse> mResp;
    std::shared_ptr<::aidl::android::hardware::radio::modem::IRadioModemIndication> mInd;
    virtual void onResponseFunctionsSet() {}

  public:
    ::ndk::ScopedAStatus enableModem(int32_t in_serial, bool in_on) override {
        if (mResp) mResp->enableModemResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getBasebandVersion(int32_t in_serial) override {
        if (mResp) mResp->getBasebandVersionResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getDeviceIdentity(int32_t in_serial) override {
        if (mResp) mResp->getDeviceIdentityResponse(notSupported(in_serial), {}, {}, {}, {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getHardwareConfig(int32_t in_serial) override {
        if (mResp) mResp->getHardwareConfigResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getModemActivityInfo(int32_t in_serial) override {
        if (mResp) mResp->getModemActivityInfoResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getModemStackStatus(int32_t in_serial) override {
        if (mResp) mResp->getModemStackStatusResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getRadioCapability(int32_t in_serial) override {
        if (mResp) mResp->getRadioCapabilityResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus nvReadItem(int32_t in_serial, ::aidl::android::hardware::radio::modem::NvItem in_itemId) override {
        if (mResp) mResp->nvReadItemResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus nvResetConfig(int32_t in_serial, ::aidl::android::hardware::radio::modem::ResetNvType in_resetType) override {
        if (mResp) mResp->nvResetConfigResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus nvWriteCdmaPrl(int32_t in_serial, const std::vector<uint8_t>& in_prl) override {
        if (mResp) mResp->nvWriteCdmaPrlResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus nvWriteItem(int32_t in_serial, const ::aidl::android::hardware::radio::modem::NvWriteItem& in_item) override {
        if (mResp) mResp->nvWriteItemResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus requestShutdown(int32_t in_serial) override {
        if (mResp) mResp->requestShutdownResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus responseAcknowledgement() override {
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus sendDeviceState(int32_t in_serial, ::aidl::android::hardware::radio::modem::DeviceStateType in_deviceStateType, bool in_state) override {
        if (mResp) mResp->sendDeviceStateResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setRadioCapability(int32_t in_serial, const ::aidl::android::hardware::radio::modem::RadioCapability& in_rc) override {
        if (mResp) mResp->setRadioCapabilityResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setRadioPower(int32_t in_serial, bool in_powerOn, bool in_forEmergencyCall, bool in_preferredForEmergencyCall) override {
        if (mResp) mResp->setRadioPowerResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr<::aidl::android::hardware::radio::modem::IRadioModemResponse>& in_radioModemResponse, const std::shared_ptr<::aidl::android::hardware::radio::modem::IRadioModemIndication>& in_radioModemIndication) override {
        mResp = in_radioModemResponse;
        mInd = in_radioModemIndication;
        onResponseFunctionsSet();
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getImei(int32_t in_serial) override {
        if (mResp) mResp->getImeiResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
};
