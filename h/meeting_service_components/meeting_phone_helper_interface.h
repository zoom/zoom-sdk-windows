/*!
* \file meeting_phone_helper_interface.h
* \brief Meeting Service Phone Interface.
* Valid for both ZOOM style and user custom interface mode.
*/
#ifndef _MEETING_PHONE_HELPER_INTERFACE_H_
#define _MEETING_PHONE_HELPER_INTERFACE_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Phone meeting support country information interface.
class IMeetingPhoneSupportCountryInfo
{
public:
	virtual ~IMeetingPhoneSupportCountryInfo(){}
	/// \brief Get the country ID of the current information. 
	/// \return The country ID.
	virtual const wchar_t* GetCountryID() = 0;
	/// \brief Get the country name of the current information.
	/// \return The country name.
	virtual const wchar_t* GetCountryName() = 0;
	/// \brief Get the country code of the current information.
	/// \return The country code.
	virtual const wchar_t* GetCountryCode() = 0;
};

/*! \enum CALLINNUMTYPE
    \brief Type of telephone call. 
    Here are more detailed structural descriptions.
*/
enum CALLINNUMTYPE
{
	CALLINNUMTYPE_NONE,///<For initialization.
	CALLINNUMTYPE_TOLL,///<Paid.
	CALLINNUMTYPE_TOLLFREE,///<Free.
};

/// \brief Call-in meeting Interface.
///
class IMeetingCallInPhoneNumberInfo
{
public:
	virtual ~IMeetingCallInPhoneNumberInfo(){}
	/// \brief Get the country ID of the current information.
	/// \return The country ID.	
	virtual const wchar_t* GetID() = 0;
	/// \brief Get the country code of the current information.
	/// \return The country code.	
	virtual const wchar_t* GetCode() = 0;
	/// \brief Get the country name of the current information.
	/// \return The country name.
	virtual const wchar_t* GetName() = 0;
	/// \brief Get the telephone number of the current information.
	/// \return The telephone number.
	virtual const wchar_t* GetNumber() = 0;
	/// \brief Get the display number of the current information. 
	/// \return The display number.
	virtual const wchar_t* GetDisplayNumber() = 0;
	/// \brief Get the call type of the current information.
	/// \return Call type. For more details, see \link CALLINNUMTYPE \endlink.
	virtual CALLINNUMTYPE  GetType() = 0;
};

/*! \enum PhoneStatus
    \brief Status of telephone.
    Here are more detailed structural descriptions.
*/
enum PhoneStatus
{
	PhoneStatus_None,///<No status.
	PhoneStatus_Calling,///<In process of calling out.
	PhoneStatus_Ringing,///<In process of ringing.
	PhoneStatus_Accepted,///<Accept the call.
	PhoneStatus_Success,///<Call successful.
	PhoneStatus_Failed,///<Call failed.
	PhoneStatus_Canceling,///<In process of canceling the response to the previous state.
	PhoneStatus_Canceled, ///<Cancel successfully.
	PhoneStatus_Cancel_Failed,///<Cancel fails.
	PhoneStatus_Timeout,///<Timeout.
};

/*! \enum PhoneFailedReason
    \brief The reason for the failure of the telephone call.
    Here are more detailed structural descriptions.
*/
enum PhoneFailedReason
{
	PhoneFailedReason_None,///<For initialization.
	PhoneFailedReason_Busy,///<The telephone service is busy.
	PhoneFailedReason_Not_Available,///<The telephone is out of the service.
	PhoneFailedReason_User_Hangup,///<The user hangs up.
	PhoneFailedReason_Other_Fail,///<Other reasons.
	PhoneFailedReason_No_Answer,///<The telephone does not reply.
	PhoneFailedReason_Block_No_Host,///<Disable the function of international call-out before the host joins the meeting.
	PhoneFailedReason_Block_High_Rate,///<The call-out is blocked by the system due to the high cost.
	PhoneFailedReason_Block_Too_Frequent,///<All the invitees invited by the call should press the button one(1) to join the meeting. In case that many invitees do not press the button that leads to time out, the call invitation for this meeting shall be banned.
};

/// \brief Meeting phone helper callback event.
class IMeetingPhoneHelperEvent
{
public:
	/// \brief Invite others by telephone call-out and send the response to the application according to the status of others.
	/// \param status The status of telephone. For more details, see \link PhoneStatus \endlink enum.
	/// \param reason The reason for the failure if the status value is PhoneStatus_Failed. For more details, see \link PhoneFailedReason \endlink enum.
	virtual void onInviteCallOutUserStatus(PhoneStatus status, PhoneFailedReason reason) = 0;
	
	/// \brief Invite others to join the meeting by CALL ME and give the response to the application according to the status. 
	/// \param status The status of telephone. For more details, see \link PhoneStatus \endlink enum.
	/// \param reason The reason for the failure if the status value is PhoneStatus_Failed. For more details, see \link PhoneFailedReason \endlink enum.
	virtual void onCallMeStatus(PhoneStatus status, PhoneFailedReason reason) = 0;
};
/// \brief Meeting phone helper interface.
///
class IMeetingPhoneHelper
{
public:
	/// \brief Set meeting phone helper callback event handler
	/// \param pEvent A pointer to the IMeetingPhoneHelperEvent that receives the phone event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IMeetingPhoneHelperEvent* pEvent) = 0;

	/// \brief Determine whether the meeting supports to join by the phone or not.
	/// \return TRUE indicates to support to join by phone. FALSE not.
	virtual bool IsSupportPhoneFeature() = 0;

	/// \brief Get the list of the country information where the meeting supports to join by telephone.
	/// \return List of the country information returns if the meeting supports to join by telephone. Otherwise NULL.
	virtual IList<IMeetingPhoneSupportCountryInfo* >* GetSupportCountryInfo() = 0;

	/// \brief Invite the specified user to join the meeting by call out.
	/// \param countryCode The country code of the specified user must be in the support list. 
	/// \param phoneNumber The phone number of specified user.
	/// \param name The screen name of the specified user in the meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError InviteCallOutUser(const wchar_t* countryCode, const wchar_t* phoneNumber, const wchar_t* name) = 0;

	/// \brief Cancel the invitation that is being called out by phone.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CancelCallOut() = 0;

	/// \brief Get the process of the invitation by call out.
	/// \return If the function succeeds, the return value is the current call-out process. To get extended error information, see \link PhoneStatus \endlink enum
	virtual PhoneStatus GetInviteCalloutUserStatus() = 0;

	/// \brief Use the CALL ME to invite the attendee who uses the specified number to join the meeting.
	/// \param countryCode The country code of the specified user must be in the support list.
	/// \param phoneNumber The specified phone number.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CallMe(const wchar_t* countryCode, const wchar_t* phoneNumber) = 0;

	/// \brief Cancel the current invitation by CALL ME.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Hangup() = 0;

	/// \brief Get the process of the invitation by CALL ME.
	/// \return If the function succeeds, the return value is the process of the invitation by CALL ME. 
	///Otherwise failed. To get extended error information, see \link PhoneStatus \endlink enum.
	virtual PhoneStatus GetCallMeStatus() = 0;

	/// \brief Get the list of call in numbers supported by meeting.
	/// \return If the function succeeds, the return value is the list of the call-in numbers. 
	///Otherwise failed. For more details, see \link IMeetingCallInPhoneNumberInfo \endlink.
	virtual IList<IMeetingCallInPhoneNumberInfo*>* GetCurrentMeetingCallinNumber() = 0;

	/// \brief Get the ID of participant who joins the meeting by calling in.
	/// \return If the function succeeds, the return value is the participant ID.
	virtual unsigned int GetCurrentMeetingCallinParticipantID() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif