/*!
* \file direct_share_service_helper_interface.h
* \brief Direct share service helper Interface.
* 
*/
#ifndef _DIRECT_SHARE_SERVICE_HELPER_INTERFACE_H_
#define _DIRECT_SHARE_SERVICE_HELPER_INTERFACE_H_
#include "zoom_sdk_def.h"
/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/*
typedef enum DirectShareStatusType_Enum
{
	DirectShare_Unknown = 0,
	DirectShare_In_SIP_Call,
	//DirectShare_Called_Too_Frequency, //move it to return value as SDKERR_TOO_FREQUENT_CALL
	DirectShare_Start_Connecting,
	DirectShare_UltraSound_Detect_Failed,
	DirectShare_Need_MeetingID_Or_ParingCode,	
	DirectShare_AccountID_Not_Same,
	DirectShare_NetWork_Error,
	DirectShare_Target_Version_Old,
	DirectShare_Direct_Share_Start,
	DirectShare_Direct_Share_Stop,
}DirectShareStatusType;
*/
typedef enum DirectShareStatusStatus_Enum
{
	DirectShare_Unknown = 0,  // no use currently. Just for initialization
	DirectShare_Connecting,  //trying to start direct share, just waiting
	DirectShare_In_Direct_Share_Mode, //in diret share mode
	DirectShare_Ended,  //diret share is ended
	DirectShare_Need_MeetingID_Or_PairingCode, // need the user to set a meeting id/paring code
	DirectShare_NetWork_Error, // network error. Try again later
	DirectShare_Other_Error,   //other error. mainly happened in SIP call mode	
}DirectShareStatus;


class IDirectShareViaMeetingIDOrPairingCodeHandler
{
public:
	virtual ~IDirectShareViaMeetingIDOrPairingCodeHandler(){};
	virtual SDKError TryWithMeetingNumber(UINT64 meetingNumber) = 0;
	virtual SDKError TryWithPairingCode(const wchar_t* pairingCode) = 0;
	virtual SDKError Cancel() = 0;
};

/// \brief Direct share helper Callback Event
///
class IDirectShareServiceHelperEvent
{
public:
	/// \brief Direct share status update login notification
	/// \param [in, out] Specifies the status of direct share.
	///If the value of direct_share_action is DirectShare_Need_MeetingID_Or_ParingCode, the user must set the value of the _paring_code or _meeting_number to start share.
	virtual void OnDirectShareStatusUpdate(DirectShareStatus status, IDirectShareViaMeetingIDOrPairingCodeHandler* handler) = 0;

};

/// \brief Direct share helper Interface
///
class IDirectShareServiceHelper
{
public:

	/// \brief Direct share helper callback event
	/// \param pEvent A pointer to an IDirectShareServiceHelperEvent* that receives direct share service event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IDirectShareServiceHelperEvent* pEvent) = 0;

	virtual SDKError CanStartDirectShare()= 0;

	virtual bool	 IsDirectShareInProgress() = 0;
	/// \brief Start direct share.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \remarks Only login user can call this API.
	virtual SDKError StartDirectShare() = 0;

	// \brief Stop direct share.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \remarks Only login user can call this API.
	virtual SDKError StopDirectShare() = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif