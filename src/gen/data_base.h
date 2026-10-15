// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <aidl/android/hardware/radio/data/BnRadioData.h>
#include <aidl/android/hardware/radio/data/IRadioDataResponse.h>
#include <aidl/android/hardware/radio/data/IRadioDataIndication.h>
#include "response_info.h"

class RadioDataBase : public ::aidl::android::hardware::radio::data::BnRadioData {
  protected:
    std::shared_ptr<::aidl::android::hardware::radio::data::IRadioDataResponse> mResp;
    std::shared_ptr<::aidl::android::hardware::radio::data::IRadioDataIndication> mInd;
    virtual void onResponseFunctionsSet() {}

  public:
    ::ndk::ScopedAStatus allocatePduSessionId(int32_t in_serial) override {
        if (mResp) mResp->allocatePduSessionIdResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus cancelHandover(int32_t in_serial, int32_t in_callId) override {
        if (mResp) mResp->cancelHandoverResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus deactivateDataCall(int32_t in_serial, int32_t in_cid, ::aidl::android::hardware::radio::data::DataRequestReason in_reason) override {
        if (mResp) mResp->deactivateDataCallResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getDataCallList(int32_t in_serial) override {
        if (mResp) mResp->getDataCallListResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getSlicingConfig(int32_t in_serial) override {
        if (mResp) mResp->getSlicingConfigResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus releasePduSessionId(int32_t in_serial, int32_t in_id) override {
        if (mResp) mResp->releasePduSessionIdResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus responseAcknowledgement() override {
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setDataAllowed(int32_t in_serial, bool in_allow) override {
        if (mResp) mResp->setDataAllowedResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setDataProfile(int32_t in_serial, const std::vector<::aidl::android::hardware::radio::data::DataProfileInfo>& in_profiles) override {
        if (mResp) mResp->setDataProfileResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setDataThrottling(int32_t in_serial, ::aidl::android::hardware::radio::data::DataThrottlingAction in_dataThrottlingAction, int64_t in_completionDurationMillis) override {
        if (mResp) mResp->setDataThrottlingResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setInitialAttachApn(int32_t in_serial, const std::optional<::aidl::android::hardware::radio::data::DataProfileInfo>& in_dataProfileInfo) override {
        if (mResp) mResp->setInitialAttachApnResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr<::aidl::android::hardware::radio::data::IRadioDataResponse>& in_radioDataResponse, const std::shared_ptr<::aidl::android::hardware::radio::data::IRadioDataIndication>& in_radioDataIndication) override {
        mResp = in_radioDataResponse;
        mInd = in_radioDataIndication;
        onResponseFunctionsSet();
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setupDataCall(int32_t in_serial, ::aidl::android::hardware::radio::AccessNetwork in_accessNetwork, const ::aidl::android::hardware::radio::data::DataProfileInfo& in_dataProfileInfo, bool in_roamingAllowed, ::aidl::android::hardware::radio::data::DataRequestReason in_reason, const std::vector<::aidl::android::hardware::radio::data::LinkAddress>& in_addresses, const std::vector<std::string>& in_dnses, int32_t in_pduSessionId, const std::optional<::aidl::android::hardware::radio::data::SliceInfo>& in_sliceInfo, bool in_matchAllRuleAllowed) override {
        if (mResp) mResp->setupDataCallResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus startHandover(int32_t in_serial, int32_t in_callId) override {
        if (mResp) mResp->startHandoverResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus startKeepalive(int32_t in_serial, const ::aidl::android::hardware::radio::data::KeepaliveRequest& in_keepalive) override {
        if (mResp) mResp->startKeepaliveResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus stopKeepalive(int32_t in_serial, int32_t in_sessionHandle) override {
        if (mResp) mResp->stopKeepaliveResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setUserDataEnabled(int32_t in_serial, bool in_enabled) override {
        if (mResp) mResp->setUserDataEnabledResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setUserDataRoamingEnabled(int32_t in_serial, bool in_enabled) override {
        if (mResp) mResp->setUserDataRoamingEnabledResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus notifyImsDataNetwork(int32_t in_serial, const ::aidl::android::hardware::radio::data::ImsDataNetworkInfo& in_info) override {
        if (mResp) mResp->notifyImsDataNetworkResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
};
