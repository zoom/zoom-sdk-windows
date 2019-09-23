/*!
* \file meeting_breakout_rooms_interface.h
* \brief BreakoutRooms of Meeting Service Interface
* 
*/
#ifndef _MEETING_BreakoutRooms_INTERFACE_H_
#define _MEETING_BreakoutRooms_INTERFACE_H_
#include "..\zoom_sdk_def.h"

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
class IBreakoutRoomsInfo
{
public:
	virtual ~IBreakoutRoomsInfo() {};
	/// \brief Get Breakout Room ID
	/// \return If the function succeeds, the return value is Breakout Room ID.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetBID() = 0;

	/// \brief Get Breakout Room name
	/// \return If the function succeeds, the return value is Breakout Room name.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetBreakoutRoomName() = 0;
};

class IMeetingBreakoutRoomsEvent
{
public:
	//////////////////Callback for ATTENDEES///////////////////
	//Receive join BO request

	/// \brief host open Breakout Rooms callback
	/// \param stBID Specifies Breakout Room id.
	virtual void OnBreakoutRoomsStartedNotification(const wchar_t* stBID) = 0;
};

/// \brief Breakout Rooms controller interface
///
class IMeetingBreakoutRoomsController
{
public:
	/// \brief set a handler for IBreakoutRoomsEvent notification.
	/// \param pEvent which will be invoked for when this message type is received.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingBreakoutRoomsEvent* pEvent) = 0;

	/// \brief Join Breakout Room
	/// \param stBID Specifies Breakout Room id.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError JoinBreakoutRoom(const wchar_t* stBID) = 0;

	/// \brief Leave Breakout Room
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError LeaveBreakoutRoom() = 0;

	/// \brief Get Breakout Room list which can join
	/// \return If the function succeeds, the return value is Breakout Room list.
	///If the function fails, the return value is NULL.
	virtual IList<IBreakoutRoomsInfo* >* GetBreakoutRoomsInfoList() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif