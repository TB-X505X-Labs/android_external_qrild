// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <aidl/android/hardware/radio/config/BnRadioConfig.h>
#include <aidl/android/hardware/radio/config/IRadioConfigResponse.h>
#include <aidl/android/hardware/radio/config/IRadioConfigIndication.h>
#include "response_info.h"

class RadioConfigBase : public ::aidl::android::hardware::radio::config::BnRadioConfig {
  protected:
    std::shared_ptr<::aidl::android::hardware::radio::config::IRadioConfigResponse> mResp;
    std::shared_ptr<::aidl::android::hardware::radio::config::IRadioConfigIndication> mInd;
    virtual void onResponseFunctionsSet() {}

  public:
    ::ndk::ScopedAStatus getHalDeviceCapabilities(int32_t in_serial) override {
        if (mResp) mResp->getHalDeviceCapabilitiesResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getNumOfLiveModems(int32_t in_serial) override {
        if (mResp) mResp->getNumOfLiveModemsResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getPhoneCapability(int32_t in_serial) override {
        if (mResp) mResp->getPhoneCapabilityResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getSimSlotsStatus(int32_t in_serial) override {
        if (mResp) mResp->getSimSlotsStatusResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setNumOfLiveModems(int32_t in_serial, int8_t in_numOfLiveModems) override {
        if (mResp) mResp->setNumOfLiveModemsResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setPreferredDataModem(int32_t in_serial, int8_t in_modemId) override {
        if (mResp) mResp->setPreferredDataModemResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr<::aidl::android::hardware::radio::config::IRadioConfigResponse>& in_radioConfigResponse, const std::shared_ptr<::aidl::android::hardware::radio::config::IRadioConfigIndication>& in_radioConfigIndication) override {
        mResp = in_radioConfigResponse;
        mInd = in_radioConfigIndication;
        onResponseFunctionsSet();
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setSimSlotsMapping(int32_t in_serial, const std::vector<::aidl::android::hardware::radio::config::SlotPortMapping>& in_slotMap) override {
        if (mResp) mResp->setSimSlotsMappingResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getSimultaneousCallingSupport(int32_t in_serial) override {
        if (mResp) mResp->getSimultaneousCallingSupportResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getSimTypeInfo(int32_t in_serial) override {
        if (mResp) mResp->getSimTypeInfoResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setSimType(int32_t in_serial, const std::vector<::aidl::android::hardware::radio::config::SimType>& in_simTypes) override {
        if (mResp) mResp->setSimTypeResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus rebootModem(int32_t in_serial) override {
        if (mResp) mResp->rebootModemResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
};
