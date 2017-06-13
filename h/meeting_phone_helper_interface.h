/*!
* \file meeting_phone_helper_interface.h
* \brief Meeting Service Interface
* 
*/
#ifndef _MEETING_PHONE_HELPER_INTERFACE_H_
#define _MEETING_PHONE_HELPER_INTERFACE_H_
#include "zoom_sdk_def.h"

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
class IMeetingPhoneSupportCountryInfo
{
public:
	virtual const wchar_t* GetCountryID() = 0;
	virtual const wchar_t* GetCountryName() = 0;
	virtual const wchar_t* GetCountryCode() = 0;
};

enum PhoneStatus
{
	PhoneStatus_None,
	PhoneStatus_Calling,
	PhoneStatus_Ringing,
	PhoneStatus_Accepted,
	PhoneStatus_Success,
	PhoneStatus_Failed,
	PhoneStatus_Canceling,
	PhoneStatus_Canceled,
	PhoneStatus_Cancel_Failed,
	PhoneStatus_Timeout,
};
enum PhoneFailedReason
{
	PhoneFailedReason_None,
	PhoneFailedReason_Busy,
	PhoneFailedReason_Not_Available,
	PhoneFailedReason_User_Hangup,
	PhoneFailedReason_Other_Fail,
	PhoneFailedReason_No_Answer,
	PhoneFailedReason_Block_No_Host,
	PhoneFailedReason_Block_High_Rate,
	PhoneFailedReason_Block_Too_Frequent,
};
class IMeetingPhoneHelperEvent
{
public:
	/// \brief Invite callout user to the meeting status changed callback
	/// \param status status value.
	/// \param reason if status is PhoneStatus_Failed, reason is the one of the PhoneFailedReason.
	virtual void onInviteCallOutUserStatus(PhoneStatus status, PhoneFailedReason reason) = 0;
	
	/// \brief Invite callme user to the meeting status changed callback
	/// \param status status value.
	/// \param reason if status is PhoneStatus_Failed, reason is the one of the PhoneFailedReason.
	virtual void onCallMeStatus(PhoneStatus status, PhoneFailedReason reason) = 0;
};
/// \brief Meeting phone Helper Interface
///
class IMeetingPhoneHelper
{
public:
	/// \brief Set meeting phone helper callback event
	/// \param pEvent A pointer to a IMeetingPhoneHelperEvent* that receives phone event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingPhoneHelperEvent* pEvent) = 0;

	/// \brief support phone feature or not for current meeting
	/// \return support or not.
	virtual bool IsSupportPhoneFeature() = 0;

	/// \brief Determines the supported country for phone feature
	/// \return the list of the supported country.
	virtual IList<IMeetingPhoneSupportCountryInfo* >* GetSupportCountryInfo() = 0;

	/// \brief invite the user to the meeting by phone
	/// \param countryCode country code, one of the list of the supported country.
	/// \param phoneNumber which phone number invited
	/// \param name the name display in the meeting
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError InviteCallOutUser(const wchar_t* countryCode, const wchar_t* phoneNumber, const wchar_t* name) = 0;

	/// \brief cancel in progress callout invite.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError CancelCallOut() = 0;

	/// \brief get the status of the in progress callout invite.
	/// \return the return value is current callout status.To get extended error information, refer to PhoneStatus enum
	virtual PhoneStatus GetInviteCalloutUserStatus() = 0;

	/// \brief call me to the meeting by phone
	/// \param countryCode country code, one of the list of the supported country.
	/// \param phoneNumber which phone number invited
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError CallMe(const wchar_t* countryCode, const wchar_t* phoneNumber) = 0;

	/// \brief cancel callme or leave phone
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Hangup() = 0;

	/// \brief get the status of the in progress callme.
	/// \return the return value is current callme status.To get extended error information, refer to PhoneStatus enum
	virtual PhoneStatus GetCallMeStatus() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif