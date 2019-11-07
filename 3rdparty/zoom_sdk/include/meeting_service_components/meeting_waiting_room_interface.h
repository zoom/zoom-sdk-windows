/*!
* \file meeting_waiting_room_interface.h
* \brief Meeting Service Waiting Room Interface.
* Valid only for Zoom style user interface mode.
*/
#ifndef _MEETING_WaitingRoom_INTERFACE_H_
#define _MEETING_WaitingRoom_INTERFACE_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Meeting Waiting Room Callback Event.
///
class IMeetingWaitingRoomEvent
{
public:
	/// \brief Callback event of notification that user joins the waiting room.
	/// \param userID The ID of user who joins the waiting room. 
	virtual void onWatingRoomUserJoin(unsigned int userID) = 0;

	/// \brief Callback event of notification that user leaves the waiting room.
	/// \param userID The ID of user who leaves the waiting room.
	virtual void onWatingRoomUserLeft(unsigned int userID) = 0;

};
/// \brief Meeting waiting room controller interface.
///
class IMeetingWaitingRoomController
{
public:
	/// \brief Set meeting waiting room callback event handler.
	/// \param pEvent A pointer to the IMeetingWaitingRoomEvent that receives the waiting room event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IMeetingWaitingRoomEvent* pEvent) = 0;

	/// \brief Determine whether the current meeting supports the waiting room or not.
	/// \return True indicates to support.
	virtual bool IsSupportWaitingRoom() = 0;

	/// \brief Determine if the attendee is enabled to enter the waiting room when joining the meeting.
	/// \return True indicates to enable to enter.
	virtual bool IsWaitingRoomOnEntryFlagOn() = 0;

	/// \brief Set to enable the attendee to enter the waiting room when joining the meeting.
	/// \param bEnable True indicates to enable to enter. False not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableWaitingRoomOnEntry(bool bEnable) = 0;

	/// \brief Get the list of attendees who are in the waiting room.
	/// \return If the function succeeds, the return value is the list of attendees.
	///Otherwise failed, the return is NULL. 
	virtual IList<unsigned int >* GetWaitingRoomLst() = 0;

	/// \brief Get the attendee information in the waiting room via user ID.
	/// \param userid Specifies the user ID.
	/// \return If the function succeeds, the return value is a pointer to IUserInfo. 
	///Otherwise failed, the return is NULL. For more details, see \link IUserInfo \endlink.
	virtual IUserInfo* GetWaitingRoomUserInfoByID(unsigned int userid) = 0;

	/// \brief Permit the specified user to join the meeting.
	/// \param userid Specifies the user ID.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed, the return is NULL. For more details, see \link SDKError \endlink enum.
	virtual SDKError AdmitToMeeting(unsigned int userid) = 0;

	/// \brief Enable the specified user to enter the waiting room.
	/// \param userid Specifies the user ID.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError PutInWaitingRoom(unsigned int userid) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif