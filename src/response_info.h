// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <aidl/android/hardware/radio/RadioError.h>
#include <aidl/android/hardware/radio/RadioResponseInfo.h>
#include <aidl/android/hardware/radio/RadioResponseInfoModem.h>

using ::aidl::android::hardware::radio::RadioError;
using ::aidl::android::hardware::radio::RadioResponseInfo;
using ::aidl::android::hardware::radio::RadioResponseInfoModem;
using ::aidl::android::hardware::radio::RadioResponseType;

inline RadioResponseInfo rspInfo(int32_t serial, RadioError err = RadioError::NONE) {
    return {RadioResponseType::SOLICITED, serial, err};
}

inline RadioResponseInfo notSupported(int32_t serial) {
    return rspInfo(serial, RadioError::REQUEST_NOT_SUPPORTED);
}

inline RadioResponseInfoModem modemNotSupported(int32_t serial) {
    RadioResponseInfoModem info;
    info.type = RadioResponseType::SOLICITED;
    info.serial = serial;
    info.error = RadioError::REQUEST_NOT_SUPPORTED;
    return info;
}
