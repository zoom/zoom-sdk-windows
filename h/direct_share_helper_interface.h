/*!
* \file direct_share_helper_interface.h
* \brief Direct Sharing Service Interface.
* 
*/
#ifndef _DIRECT_SHARE_SERVICE_HELPER_INTERFACE_H_
#define _DIRECT_SHARE_SERVICE_HELPER_INTERFACE_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/*! \enum DirectShareStatusStatus_Enum
    \brief Direct sharing status.
    Here are more detailed structural descriptions.
*/
typedef enum DirectShareStatusStatus_Enum
{
	DirectShare_Unknown = 0,///<Only for initialization.
	DirectShare_Connecting,///<Waiting for enabling the direct sharing.
	DirectShare_In_Direct_Share_Mode,///<In direct sharing mode.
	DirectShare_Ended,///<End the direct sharing.
	DirectShare_Need_MeetingID_Or_PairingCode,///<Re-enter the meeting ID/paring code.
	DirectShare_NetWork_Error,///<Network error. Please try again later.
	DirectShare_Other_Error,///<Other errors. Mainly occur in SIP call mode.
	DirectShare_WrongMeetingID_Or_SharingKey,///<Wrong meeting id or sharing key.
}DirectShareStatus;

/// \brief Direct sharing by meeting ID or pairing code helper interface.
///
class IDirectShareViaMeetingIDOrPairingCodeHandler
{
public:
	virtual ~IDirectShareViaMeetingIDOrPairingCodeHandler(){};
	
	/// \brief Try to match with the specified meeting number.
	/// \param meetingNumber Specifies the meeting number.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError TryWithMeetingNumber(UINT64 meetingNumber) = 0;
	
	/// \brief Try to match with the pairing code.
	/// \param pairingCode Specifies the pairing code.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.	
	virtual SDKError TryWithPairingCode(const wchar_t* pairingCode) = 0;
	
	/// \brief Delete the present direct sharing.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Cancel() = 0;
};

/// \brief Direct sharing helper callback event.
///
class IDirectShareServiceHelperEvent
{
public:
	/// \brief The callback event will be triggered if the status of direct sharing changes.
	/// \param status Specifies the status of direct sharing. For more details, see \link DirectShareStatus \endlink enum.
	/// \param handler A pointer to the IDirectShareViaMeetingIDOrPairingCodeHandler. It is only valid when the value of status is DirectShare_Need_MeetingID_Or_PairingCode.
	///The SDK user must set the value of the _paring_code or _meeting_number via the functions of IDirectShareViaMeetingIDOrPairingCodeHandler to start direct sharing. For more details, see \link IDirectShareViaMeetingIDOrPairingCodeHandler \endlink.
	virtual void OnDirectShareStatusUpdate(DirectShareStatus status, IDirectShareViaMeetingIDOrPairingCodeHandler* handler) = 0;

};

/// \brief Direct sharing helper Interface.
///
class IDirectShareServiceHelper
{
public:

	/// \brief Direct sharing helper callback event handler.
	/// \param pEvent A pointer to the IDirectShareServiceHelperEvent that receives the direct sharing service event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IDirectShareServiceHelperEvent* pEvent) = 0;

	/// \brief Determine if it is able to start the direct sharing.
	/// \return If it is enabled to start the direct sharing, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanStartDirectShare()= 0;
	
	/// \brief Determine if direct sharing is in progress.
	/// \return TRUE indicates that the direct sharing is in progress.
	virtual bool	 IsDirectShareInProgress() = 0;
	
	/// \brief Start direct sharing.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks This API can only be called by the logged in user.
	virtual SDKError StartDirectShare() = 0;

	/// \brief Stop direct sharing.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks This API can only be called by the logged in user.
	virtual SDKError StopDirectShare() = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif