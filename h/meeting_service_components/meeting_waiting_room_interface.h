/*!
* \file meeting_waiting_room_interface.h
* \brief WaitingRoom of Meeting Service Interface
* 
*/
#ifndef _MEETING_WaitingRoom_INTERFACE_H_
#define _MEETING_WaitingRoom_INTERFACE_H_
#include "..\zoom_sdk_def.h"

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Meeting Waiting Room Callback Event
///
class IMeetingWaitingRoomEvent
{
public:
	/// \brief User join waiting room notify callback
	/// \param userID ID of the user join waiting room.
	virtual void onWatingRoomUserJoin(unsigned int userID) = 0;

	/// \brief User left waiting room notify callback
	/// \param userID ID of the user left waiting room.
	virtual void onWatingRoomUserLeft(unsigned int userID) = 0;

};
/// \brief Meeting waiting room controller interface
///
class IMeetingWaitingRoomController
{
public:
	/// \brief Set meeting waiting room callback event
	/// \param pEvent A pointer to a IMeetingWaitingRoomEvent* that receives waiting room event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingWaitingRoomEvent* pEvent) = 0;

	/// \brief Current meeting support waiting room or not.
	/// \return true, support waiting room.
	virtual bool IsSupportWaitingRoom() = 0;

	/// \brief Get the flag of put attendee in waiting room on entry for the current meeting.
	/// \return true, enabled.
	virtual bool IsWaitingRoomOnEntryFlagOn() = 0;

	/// \brief Enable the flag of put attendee in waiting room on entry for the current meeting.
	/// \param bEnable enable waiting room or not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableWaitingRoomOnEntry(bool bEnable) = 0;

	/// \brief Get meeting participants list in the waiting room
	/// \return the return value is current meeting all waiting room participants list.if not in meeting, return NULL.
	virtual IList<unsigned int >* GetWaitingRoomLst() = 0;

	/// \brief Get waiting room user information via user id
	/// \param userId Specifies which the user's information to get.
	/// \return If the function succeeds, the return value is user information interface.
	///If the function fails, the return value is NULL.
	virtual IUserInfo* GetWaitingRoomUserInfoByID(unsigned int userid) = 0;

	/// \brief Admit user to the meeting
	/// \param userId Specifies which the user to admitted.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError AdmitToMeeting(unsigned int userid) = 0;

	/// \brief Put user into the waiting room
	/// \param userId Specifies which the user to put in.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError PutInWaitingRoom(unsigned int userid) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif