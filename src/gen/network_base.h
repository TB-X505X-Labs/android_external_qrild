// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <aidl/android/hardware/radio/network/BnRadioNetwork.h>
#include <aidl/android/hardware/radio/network/IRadioNetworkResponse.h>
#include <aidl/android/hardware/radio/network/IRadioNetworkIndication.h>
#include "response_info.h"

class RadioNetworkBase : public ::aidl::android::hardware::radio::network::BnRadioNetwork {
  protected:
    std::shared_ptr<::aidl::android::hardware::radio::network::IRadioNetworkResponse> mResp;
    std::shared_ptr<::aidl::android::hardware::radio::network::IRadioNetworkIndication> mInd;
    virtual void onResponseFunctionsSet() {}

  public:
    ::ndk::ScopedAStatus getAllowedNetworkTypesBitmap(int32_t in_serial) override {
        if (mResp) mResp->getAllowedNetworkTypesBitmapResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getAvailableBandModes(int32_t in_serial) override {
        if (mResp) mResp->getAvailableBandModesResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getAvailableNetworks(int32_t in_serial) override {
        if (mResp) mResp->getAvailableNetworksResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getBarringInfo(int32_t in_serial) override {
        if (mResp) mResp->getBarringInfoResponse(notSupported(in_serial), {}, {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getCdmaRoamingPreference(int32_t in_serial) override {
        if (mResp) mResp->getCdmaRoamingPreferenceResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getCellInfoList(int32_t in_serial) override {
        if (mResp) mResp->getCellInfoListResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getDataRegistrationState(int32_t in_serial) override {
        if (mResp) mResp->getDataRegistrationStateResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getImsRegistrationState(int32_t in_serial) override {
        if (mResp) mResp->getImsRegistrationStateResponse(notSupported(in_serial), {}, {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getNetworkSelectionMode(int32_t in_serial) override {
        if (mResp) mResp->getNetworkSelectionModeResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getOperator(int32_t in_serial) override {
        if (mResp) mResp->getOperatorResponse(notSupported(in_serial), {}, {}, {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getSignalStrength(int32_t in_serial) override {
        if (mResp) mResp->getSignalStrengthResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getSystemSelectionChannels(int32_t in_serial) override {
        if (mResp) mResp->getSystemSelectionChannelsResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getVoiceRadioTechnology(int32_t in_serial) override {
        if (mResp) mResp->getVoiceRadioTechnologyResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getVoiceRegistrationState(int32_t in_serial) override {
        if (mResp) mResp->getVoiceRegistrationStateResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus isNrDualConnectivityEnabled(int32_t in_serial) override {
        if (mResp) mResp->isNrDualConnectivityEnabledResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus responseAcknowledgement() override {
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setAllowedNetworkTypesBitmap(int32_t in_serial, int32_t in_networkTypeBitmap) override {
        if (mResp) mResp->setAllowedNetworkTypesBitmapResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setBandMode(int32_t in_serial, ::aidl::android::hardware::radio::network::RadioBandMode in_mode) override {
        if (mResp) mResp->setBandModeResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setBarringPassword(int32_t in_serial, const std::string& in_facility, const std::string& in_oldPassword, const std::string& in_newPassword) override {
        if (mResp) mResp->setBarringPasswordResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setCdmaRoamingPreference(int32_t in_serial, ::aidl::android::hardware::radio::network::CdmaRoamingType in_type) override {
        if (mResp) mResp->setCdmaRoamingPreferenceResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setCellInfoListRate(int32_t in_serial, int32_t in_rate) override {
        if (mResp) mResp->setCellInfoListRateResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setIndicationFilter(int32_t in_serial, int32_t in_indicationFilter) override {
        if (mResp) mResp->setIndicationFilterResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setLinkCapacityReportingCriteria(int32_t in_serial, int32_t in_hysteresisMs, int32_t in_hysteresisDlKbps, int32_t in_hysteresisUlKbps, const std::vector<int32_t>& in_thresholdsDownlinkKbps, const std::vector<int32_t>& in_thresholdsUplinkKbps, ::aidl::android::hardware::radio::AccessNetwork in_accessNetwork) override {
        if (mResp) mResp->setLinkCapacityReportingCriteriaResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setLocationUpdates(int32_t in_serial, bool in_enable) override {
        if (mResp) mResp->setLocationUpdatesResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setNetworkSelectionModeAutomatic(int32_t in_serial) override {
        if (mResp) mResp->setNetworkSelectionModeAutomaticResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setNetworkSelectionModeManual(int32_t in_serial, const std::string& in_operatorNumeric, ::aidl::android::hardware::radio::AccessNetwork in_ran) override {
        if (mResp) mResp->setNetworkSelectionModeManualResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setNrDualConnectivityState(int32_t in_serial, ::aidl::android::hardware::radio::network::NrDualConnectivityState in_nrDualConnectivityState) override {
        if (mResp) mResp->setNrDualConnectivityStateResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr<::aidl::android::hardware::radio::network::IRadioNetworkResponse>& in_radioNetworkResponse, const std::shared_ptr<::aidl::android::hardware::radio::network::IRadioNetworkIndication>& in_radioNetworkIndication) override {
        mResp = in_radioNetworkResponse;
        mInd = in_radioNetworkIndication;
        onResponseFunctionsSet();
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setSignalStrengthReportingCriteria(int32_t in_serial, const std::vector<::aidl::android::hardware::radio::network::SignalThresholdInfo>& in_signalThresholdInfos) override {
        if (mResp) mResp->setSignalStrengthReportingCriteriaResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setSuppServiceNotifications(int32_t in_serial, bool in_enable) override {
        if (mResp) mResp->setSuppServiceNotificationsResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setSystemSelectionChannels(int32_t in_serial, bool in_specifyChannels, const std::vector<::aidl::android::hardware::radio::network::RadioAccessSpecifier>& in_specifiers) override {
        if (mResp) mResp->setSystemSelectionChannelsResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus startNetworkScan(int32_t in_serial, const ::aidl::android::hardware::radio::network::NetworkScanRequest& in_request) override {
        if (mResp) mResp->startNetworkScanResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus stopNetworkScan(int32_t in_serial) override {
        if (mResp) mResp->stopNetworkScanResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus supplyNetworkDepersonalization(int32_t in_serial, const std::string& in_netPin) override {
        if (mResp) mResp->supplyNetworkDepersonalizationResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setUsageSetting(int32_t in_serial, ::aidl::android::hardware::radio::network::UsageSetting in_usageSetting) override {
        if (mResp) mResp->setUsageSettingResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getUsageSetting(int32_t in_serial) override {
        if (mResp) mResp->getUsageSettingResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setEmergencyMode(int32_t in_serial, ::aidl::android::hardware::radio::network::EmergencyMode in_emcModeType) override {
        if (mResp) mResp->setEmergencyModeResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus triggerEmergencyNetworkScan(int32_t in_serial, const ::aidl::android::hardware::radio::network::EmergencyNetworkScanTrigger& in_request) override {
        if (mResp) mResp->triggerEmergencyNetworkScanResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus cancelEmergencyNetworkScan(int32_t in_serial, bool in_resetScan) override {
        if (mResp) mResp->cancelEmergencyNetworkScanResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus exitEmergencyMode(int32_t in_serial) override {
        if (mResp) mResp->exitEmergencyModeResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setNullCipherAndIntegrityEnabled(int32_t in_serial, bool in_enabled) override {
        if (mResp) mResp->setNullCipherAndIntegrityEnabledResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus isNullCipherAndIntegrityEnabled(int32_t in_serial) override {
        if (mResp) mResp->isNullCipherAndIntegrityEnabledResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus isN1ModeEnabled(int32_t in_serial) override {
        if (mResp) mResp->isN1ModeEnabledResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setN1ModeEnabled(int32_t in_serial, bool in_enable) override {
        if (mResp) mResp->setN1ModeEnabledResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus isCellularIdentifierTransparencyEnabled(int32_t in_serial) override {
        if (mResp) mResp->isCellularIdentifierTransparencyEnabledResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setCellularIdentifierTransparencyEnabled(int32_t in_serial, bool in_enabled) override {
        if (mResp) mResp->setCellularIdentifierTransparencyEnabledResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setSecurityAlgorithmsUpdatedEnabled(int32_t in_serial, bool in_enable) override {
        if (mResp) mResp->setSecurityAlgorithmsUpdatedEnabledResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus isSecurityAlgorithmsUpdatedEnabled(int32_t in_serial) override {
        if (mResp) mResp->isSecurityAlgorithmsUpdatedEnabledResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setSatellitePlmn(int32_t in_serial, const std::vector<std::string>& in_carrierPlmnArray, const std::vector<std::string>& in_allSatellitePlmnArray) override {
        if (mResp) mResp->setSatellitePlmnResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setSatelliteEnabledForCarrier(int32_t in_serial, bool in_satelliteEnabled) override {
        if (mResp) mResp->setSatelliteEnabledForCarrierResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus isSatelliteEnabledForCarrier(int32_t in_serial) override {
        if (mResp) mResp->isSatelliteEnabledForCarrierResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus setSatelliteNetworkInfo(int32_t in_serial, const ::aidl::android::hardware::radio::network::SatelliteNetworkInfo& in_satelliteNetworkInfo) override {
        if (mResp) mResp->setSatelliteNetworkInfoResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus enablePrioritizedNetworkScan(int32_t in_serial, const ::aidl::android::hardware::radio::network::PrioritizedNetworkScanRequest& in_scanRequest) override {
        if (mResp) mResp->enablePrioritizedNetworkScanResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus disablePrioritizedNetworkScan(int32_t in_serial) override {
        if (mResp) mResp->disablePrioritizedNetworkScanResponse(notSupported(in_serial));
        return ::ndk::ScopedAStatus::ok();
    }
    ::ndk::ScopedAStatus getSupportedNetworkAlertCategories(int32_t in_serial) override {
        if (mResp) mResp->getSupportedNetworkAlertCategoriesResponse(notSupported(in_serial), {});
        return ::ndk::ScopedAStatus::ok();
    }
};
