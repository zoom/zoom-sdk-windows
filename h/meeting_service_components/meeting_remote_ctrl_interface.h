/*!
* \file meeting_remote_ctrl_interface.h
* \brief Remote Controller of Meeting Service Interface
* 
*/
#ifndef _MEETING_REMOTE_CTRL_INTERFACE_H_
#define _MEETING_REMOTE_CTRL_INTERFACE_H_
#include "..\zoom_sdk_def.h"

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum RemoteControlStatus
    \brief Remote Control Status.
    A more detailed struct description.
*/
enum RemoteControlStatus
{
	Remote_Control_None,
	Remote_Control_I_Can_Request_Control_Who,

	Remote_Control_I_Can_Control_Who_Begin,
	Remote_Control_I_Can_Control_Who_End,

	Remote_Control_I_Control_Who_Begin,
	Remote_Control_I_Control_Who_End,

	Remote_Control_Who_Control_Me,
	Remote_Control_I_Recv_Decline_Msg,
	Remote_Control_I_Recv_Request_Msg,
};

/// \brief Meeting remote controller event callback
///
class IMeetingRemoteCtrlEvent
{
public:
	/// \brief Remote Control status notify callback
	/// \param status Remote control status value.
	/// \param userId Remote control user id.
	virtual void onRemoteControlStatus(RemoteControlStatus status, unsigned int userId) = 0;
};

/// \brief Meeting remote controller interface
///
class IMeetingRemoteController
{
public:
	/// \brief Set meeting remote controller callback event
	/// \param pEvent A pointer to a IMeetingRemoteCtrlEvent* that receives remote control event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingRemoteCtrlEvent* pEvent) = 0;
	/// \brief Request meeting Remote control
	/// \param userId Specifies which the user you want to remote control.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError RequestRemoteControl(unsigned int userId) = 0;

	/// \brief Give up meeting Remote control
	/// \param userId Specifies which the user you want to give up the remote control right.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GiveupRemoteControl(unsigned int userId) = 0;

	/// \brief Give meeting Remote control right to other attendee
	/// \param userId Specifies which the user to control your screen.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GiveRemoteControlTo(unsigned int userId) = 0;

	/// \brief Decline meeting Remote control request
	/// \param userId Specifies which the user can't to control your screen.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DeclineRemoteControlRequest(unsigned int userId) = 0;

	/// \brief Revoke Current Remote Controller's right
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError RevokeRemoteControl() = 0;

	/// \brief Get meeting current remote controller
	/// \param userId Store the current remote controller userid, if zero, now meeting don't have remote controller.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GetCurrentRemoteController(unsigned int& userId) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif