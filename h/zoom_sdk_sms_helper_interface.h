#ifndef _ZOOM_SDK_SMS_HELPER_INTERFACE_H_
#define _ZOOM_SDK_SMS_HELPER_INTERFACE_H_
#include "zoom_sdk_platform.h"
class IZoomRetrieveSMSVerificationCodeHandler
{
public:
	virtual bool Retrieve(const zTCHAR* country_code, const zTCHAR* phone_number) = 0;
	virtual bool CancelAndLeaveMeeting() = 0;
	virtual ~IZoomRetrieveSMSVerificationCodeHandler(){}
};

class IZoomVerifySMSVerificationCodeHandler
{
public:
	virtual bool Verify(const zTCHAR* country_code, const zTCHAR* phone_number, const zTCHAR* verification_code) = 0;
	virtual bool CancelAndLeaveMeeting() = 0;
	virtual ~IZoomVerifySMSVerificationCodeHandler() {}
};

enum SMSVerificationCodeErr
{
	SMSVerificationCodeErr_Unknown,
	SMSVerificationCodeErr_Success,
	SMSVerificationCodeErr_Retrieve_SendSMSFailed,
	SMSVerificationCodeErr_Retrieve_InvalidPhoneNum,
	SMSVerificationCodeErr_Retrieve_PhoneNumAlreadyBound,
	SMSVerificationCodeErr_Retrieve_PhoneNumSendTooFrequent,
	SMSVerificationCodeErr_Verify_CodeIncorrect,
	SMSVerificationCodeErr_Verify_CodeExpired,
	SMSVerificationCodeErr_Verify_UnknownError,
};

class IZoomRealNameAuthCountryInfo
{
public:
	virtual const zTCHAR* GetCountryID() = 0;
	virtual const zTCHAR* GetCountryName() = 0;
	virtual const zTCHAR* GetCountryCode() = 0;
	virtual ~IZoomRealNameAuthCountryInfo() {}
};
class IZoomRealNameAuthMeetingEvent
{
public:
	virtual void onNeedRealNameAuthMeetingNotification(IVector<IZoomRealNameAuthCountryInfo* >* support_country_list, const zTCHAR* privacy_url, IZoomRetrieveSMSVerificationCodeHandler* handler) = 0;
	virtual void onRetrieveSMSVerificationCodeResultNotification(SMSVerificationCodeErr result, IZoomVerifySMSVerificationCodeHandler* handler) = 0;
	virtual void onVerifySMSVerificationCodeResultNotification(SMSVerificationCodeErr result) = 0;
	virtual ~IZoomRealNameAuthMeetingEvent() {}
};

class IZoomRealNameAuthMeetingHelper
{
public:
	virtual bool SetEvent(IZoomRealNameAuthMeetingEvent* event_) = 0;
	virtual bool EnableZoomAuthRealNameMeetingUIShown(bool enable) = 0;
	virtual bool SetDefaultCellPhoneInfo(const zTCHAR* country_code, const zTCHAR* phone_number) = 0;
	virtual IZoomRetrieveSMSVerificationCodeHandler* GetResendSMSVerificationCodeHandler() = 0;
	virtual IZoomVerifySMSVerificationCodeHandler* GetReVerifySMSVerificationCodeHandler() = 0;
	virtual IVector<IZoomRealNameAuthCountryInfo* >* GetSupportPhoneNumberCountryList() = 0;
	virtual ~IZoomRealNameAuthMeetingHelper() {}
};
#endif
