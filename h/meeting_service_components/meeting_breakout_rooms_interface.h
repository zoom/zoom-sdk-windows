/*!
* \file meeting_breakout_rooms_interface.h
* \brief Meeting Service BreakoutRooms Interface
* \This interface is will be deprecated, please use new version: meeting_breakout_rooms_interface_v2.h
*/
#ifndef _MEETING_BreakoutRooms_INTERFACE_H_
#define _MEETING_BreakoutRooms_INTERFACE_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/// \deprecated This interface will be deprecated, please stop using it. 
/// \brief Meeting breakout rooms information interface.
class IBreakoutRoomsInfo
{
public:
	virtual ~IBreakoutRoomsInfo() {};
	/// \brief Get Breakout Room ID.
	/// \return If the function succeeds, the return is a pointer to the string of Breakout Room ID.
	///Otherwise failed, the return is NULL.
	virtual const wchar_t* GetBID() = 0;

	/// \brief Get Breakout Room name.
	/// \return If the function succeeds, the return is a pointer to the string of Breakout Room name. 
	///Otherwise failed, the return is NULL.
	virtual const wchar_t* GetBreakoutRoomName() = 0;
};

/// \deprecated This interface will be deprecated, please stop using it. 
/// \brief Meeting Breakout Room callback event
class IMeetingBreakoutRoomsEvent
{
public:
	/// \brief Callback event of creating the Breakout Room by the host.
	/// \param stBID Specify the Breakout Room ID.
	/// \remarks The host will inform the related attendees to come in the Breakout Room by this callback event once the Room is created.
	virtual void OnBreakoutRoomsStartedNotification(const wchar_t* stBID) = 0;
};

/// \deprecated This interface will be deprecated, please stop using it. 
/// \brief Breakout Rooms controller interface
///
class IMeetingBreakoutRoomsController
{
public:
	/// \brief Breakout room callback event handler.
	/// \param pEvent A pointer to the IMeetingBreakoutRoomsEvent that receives meeting Breakout out room callback event.
	///If the function succeeds, the return value is SDKErr_Success. 
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks The event is used by the SDK to pass the callback event to user's application. If this function is not called or failed, the user's application can not retrieve the callback event.
	virtual SDKError SetEvent(IMeetingBreakoutRoomsEvent* pEvent) = 0;

	/// \brief Join the assigned Breakout Room.
	/// \param stBID Specify the Breakout Room ID to join.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid only for ZOOM style user interface mode. 
	virtual SDKError JoinBreakoutRoom(const wchar_t* stBID) = 0;

	/// \brief Leave Breakout Room.
	/// \return If the function succeeds, the return value is SDKErr_Success. 
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid only for ZOOM style user interface mode.
	virtual SDKError LeaveBreakoutRoom() = 0;

	/// \brief Get the list of the Breakout Rooms.
	/// \return If the function succeeds, the return is a pointer to the list of Breakout Rooms. For more details, see \link IBreakoutRoomsInfo \endlink.
	///Otherwise failed, the return is NULL.
	/// \remarks Valid only for ZOOM style user interface mode.
	virtual IList<IBreakoutRoomsInfo* >* GetBreakoutRoomsInfoList() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif