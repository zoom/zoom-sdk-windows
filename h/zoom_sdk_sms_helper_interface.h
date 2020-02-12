#ifndef _ZOOM_SDK_SMS_HELPER_INTERFACE_H_
#define _ZOOM_SDK_SMS_HELPER_INTERFACE_H_
#include "zoom_sdk_platform.h"
/// \brief Retrieve SMS verification code handler interface.
class IZoomRetrieveSMSVerificationCodeHandler
{
public:
	/// \brief Retrieve the sms verification code. 
	/// \param country_code Specifies the country code.
	/// \param phone_number Specifies the phone number.
	/// \return If the function succeeds, the return value is TRUE.
	/// \remarks The handler will become invalid after calling this function successfully.
	virtual bool Retrieve(const zTCHAR* country_code, const zTCHAR* phone_number) = 0;
	
	/// \brief Ignore the prompt of retrieving the verification code and leave meeting.
	/// \return If the function succeeds, the return value is TRUE.
	/// \remarks The handler will become invalid and destroied after calling this function successfully.
	virtual bool CancelAndLeaveMeeting() = 0;
	virtual ~IZoomRetrieveSMSVerificationCodeHandler(){}
};

/// \brief Verify SMS verification code handler interface.
class IZoomVerifySMSVerificationCodeHandler
{
public:
	/// \brief Verify the sms verification code. 
	/// \param country_code Specifies the country code.
	/// \param phone_number Specifies the phone number.
	/// \param verification_code Specifies the verification code.
	/// \return If the function succeeds, the return value is TRUE.
	/// \remarks The handler will become invalid after calling this function successfully.
	virtual bool Verify(const zTCHAR* country_code, const zTCHAR* phone_number, const zTCHAR* verification_code) = 0;
	
	/// \brief Ignore the prompt of verifying the verification code and leave meeting.
	/// \return If the function succeeds, the return value is TRUE.
	/// \remarks The handler will become invalid and destroied after calling this function successfully.
	virtual bool CancelAndLeaveMeeting() = 0;
	virtual ~IZoomVerifySMSVerificationCodeHandler() {}
};

/*! \enum SMSVerificationCodeErr
    \brief SMS verification error types.
    Here are more detailed structural descriptions.
*/
enum SMSVerificationCodeErr
{
	SMSVerificationCodeErr_Unknown,///<For initialization.
	SMSVerificationCodeErr_Success,///<Success.
	SMSVerificationCodeErr_Retrieve_SendSMSFailed,///<Send SMS Failed.
	SMSVerificationCodeErr_Retrieve_InvalidPhoneNum,///<Invalid phone number.
	SMSVerificationCodeErr_Retrieve_PhoneNumAlreadyBound,///<The phone number is already bound.
	SMSVerificationCodeErr_Retrieve_PhoneNumSendTooFrequent,///<Send phone number too frequently.
	SMSVerificationCodeErr_Verify_CodeIncorrect,///<Verification code is incorrect.
	SMSVerificationCodeErr_Verify_CodeExpired,///<Verification code is expired.
	SMSVerificationCodeErr_Verify_UnknownError,///<Unknown error for verification.
};

/// \brief Interface of country information that supports real name auth.
class IZoomRealNameAuthCountryInfo
{
public:
    /// \brief Get the country ID of the current information. 
	/// \return The country ID.
	virtual const zTCHAR* GetCountryID() = 0;
	
	/// \brief Get the country name of the current information.
	/// \return The country name.
	virtual const zTCHAR* GetCountryName() = 0;
	
	/// \brief Get the country code of the current information.
	/// \return The country code.
	virtual const zTCHAR* GetCountryCode() = 0;
	virtual ~IZoomRealNameAuthCountryInfo() {}
};
/// \brief Real name auth meeting callback event.
class IZoomRealNameAuthMeetingEvent
{
public:
	/// \brief If real name auth is needed, this callback will be triggered.
	/// \param support_country_list The list of the supporting country information.
	/// \param privacy_url The privacy url.
	/// \param handler A pointer to the IZoomRetrieveSMSVerificationCodeHandler.
	///The SDK user can retrieve the verification code via the functions of IZoomRetrieveSMSVerificationCodeHandler. For more details, see \link IZoomRetrieveSMSVerificationCodeHandler \endlink.
	virtual void onNeedRealNameAuthMeetingNotification(IVector<IZoomRealNameAuthCountryInfo* >* support_country_list, const zTCHAR* privacy_url, IZoomRetrieveSMSVerificationCodeHandler* handler) = 0;
	
	/// \brief The callback event for retrieving SMS verification code.
	/// \param result Specifies the result of retrieve. For more details, see \link SMSVerificationCodeErr \endlink enum.
	/// \param handler A pointer to the IZoomVerifySMSVerificationCodeHandler. It is only valid when the value of result is SMSVerificationCodeErr_Success.
	///The SDK user can do the verification via the functions of IZoomVerifySMSVerificationCodeHandler. For more details, see \link IZoomVerifySMSVerificationCodeHandler \endlink.
	virtual void onRetrieveSMSVerificationCodeResultNotification(SMSVerificationCodeErr result, IZoomVerifySMSVerificationCodeHandler* handler) = 0;
	
	/// \brief The callback event for verification.
	/// \param result Specifies the result of verification.
	virtual void onVerifySMSVerificationCodeResultNotification(SMSVerificationCodeErr result) = 0;
	virtual ~IZoomRealNameAuthMeetingEvent() {}
};

/// \brief Real name auth meeting helper Interface.
class IZoomRealNameAuthMeetingHelper
{
public:
	/// \brief Set the real name auth meeting helper callback event handler.
	/// \param event_ A pointer to the IZoomRealNameAuthMeetingEvent. 
	/// \return If the function succeeds, the return value is TRUE.
	virtual bool SetEvent(IZoomRealNameAuthMeetingEvent* event_) = 0;
	
	/// \brief Set the visibility of the dialog box of auth real name when needed. Default value: TRUE.
	/// \param enable TRUE indicates to display the dialog box. Otherwise not.
	/// \return If the function succeeds, the return value is TRUE.
	virtual bool EnableZoomAuthRealNameMeetingUIShown(bool enable) = 0;
	
	/// \brief Set default cellphone information to let the user bypass the real name auth to start/join meeting directly.
	/// \param country_code Specifies the country code.
	/// \param phone_number Specifies the phone number. 
	/// \return If the function succeeds, the return value is TRUE.
	virtual bool SetDefaultCellPhoneInfo(const zTCHAR* country_code, const zTCHAR* phone_number) = 0;
	
	/// \brief Get retrieve SMS verification code handler interface.
	/// \return If the function succeeds, the return value is a pointer to IZoomRetrieveSMSVerificationCodeHandler. Otherwise returns NULL.
	virtual IZoomRetrieveSMSVerificationCodeHandler* GetResendSMSVerificationCodeHandler() = 0;
	
	/// \brief Get verify SMS verification code handler interface.
	/// \return If the function succeeds, the return value is a pointer to IZoomVerifySMSVerificationCodeHandler. Otherwise returns NULL.
	virtual IZoomVerifySMSVerificationCodeHandler* GetReVerifySMSVerificationCodeHandler() = 0;
	
	/// \brief Get the list of the country information where the meeting supports real name auth.
	/// \return List of the country information where the meeting supports real name auth.
	virtual IVector<IZoomRealNameAuthCountryInfo* >* GetSupportPhoneNumberCountryList() = 0;
	virtual ~IZoomRealNameAuthMeetingHelper() {}
};
#endif
