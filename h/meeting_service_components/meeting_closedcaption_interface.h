/*!
* \file meeting_claosecaptioin_interface.h
* \brief Meeting Service Closed Caption Interface. 
* \remarks Valid for both ZOOM style and user custom interface mode.
*/
#ifndef _MEETING_CLOSEDCAPTION_INTERFACE_H_
#define _MEETING_CLOSEDCAPTION_INTERFACE_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Closed Caption controller callback event.
///
class IClosedCaptionControllerEvent
{
public:
	/// \brief Callback event when the user is assigned to send Closed Caption messages.
	virtual void onAssignedToSendCC(bool bAssigned) = 0;
	/// \brief Callback event when the user receives Closed Caption messages.
	virtual void onClosedCaptionMsgReceived(const wchar_t* ccMsg, time_t time) = 0;
};

/// \brief Closed caption controller interface.
class IClosedCaptionController
{
public:
	/// Set the controller event of closed caption(CC).
	virtual SDKError SetEvent(IClosedCaptionControllerEvent* pEvent) = 0;
	/// Determine if the current meeting supports the CC feature.
	virtual bool IsMeetingSupportCC() = 0;
	/// Query if it is able to assign others to send CC.
	virtual bool CanAssignOthersToSendCC() = 0;
	/// Assign a user to send CC.
	/// Zero(0) means to assign the current user himself.
	virtual SDKError AssignCCPriviledge(unsigned int userid, bool bAssigned) = 0;
	/// Determine if the user can be assigned as a CC sender.
	virtual bool CanBeAssignedToSendCC(unsigned int userid) = 0;
	/// Query if the user can send CC.
	virtual bool CanSendClosedCaption() = 0;
	/// Send the CC message.
	virtual SDKError SendClosedCaption(const wchar_t* ccMsg) = 0;
	/// Determine if it is enabled to save CC.
	virtual bool IsSaveCCEnabled() = 0;
	/// History of saving CC.
	virtual SDKError SaveCCHistory() = 0;
	/// Get the path of saving CC.
	virtual const wchar_t* GetClosedCaptionHistorySavedPath() = 0;
	/// Get the CC URL used by the third party service.
	virtual const wchar_t* GetClosedCaptionUrlFor3rdParty() = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif