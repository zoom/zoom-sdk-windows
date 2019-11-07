/*!
* \file meeting_remote_ctrl_interface.h
* \brief Meeting Service Remote Control Interface
* Valid for both ZOOM style and user custom interface mode.
*/
#ifndef _MEETING_REMOTE_CTRL_INTERFACE_H_
#define _MEETING_REMOTE_CTRL_INTERFACE_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum RemoteControlStatus
    \brief Information category for authority and status changes during the remote Control.
    Here are more detailed structural descriptions.
*/
enum RemoteControlStatus
{
	Remote_Control_None,///<For initialization.
	Remote_Control_I_Can_Request_Control_Who,///<Remote control information. I can enable the remote control.	
	Remote_Control_I_Can_Control_Who_Begin,///<The authority of remote control. I get control when remote control begins.
	Remote_Control_I_Can_Control_Who_End,///<The authority of remote control. I lose control when remote control ends. 
	Remote_Control_I_Control_Who_Begin,///<The status of remote control. I am in the status of remote control.
	Remote_Control_I_Control_Who_End,///<The status of remote control. I am out of the remote control.
	Remote_Control_Who_Control_Me,///<The status of remote control. I am controlled by whom. 
	Remote_Control_I_Recv_Decline_Msg,///<Remote control information. I have received a refused information of remote control.
	Remote_Control_I_Recv_Request_Msg,///<Remote control information. I have received an information of request for remote control.
};

/// \brief Meeting remote control callback event.
///
class IMeetingRemoteCtrlEvent
{
public:
	/// \brief Callback event of notification of the remote control status. 
	/// \param status The value of remote control status. For more details, see \link RemoteControlStatus \endlink enum.
	/// \param userId The remote control user ID. For more details, see \link RemoteControlStatus \endlink enum.
	virtual void onRemoteControlStatus(RemoteControlStatus status, unsigned int userId) = 0;
};

/// \brief Meeting remote control interface.
///
class IMeetingRemoteController
{
public:
	/// \brief Set meeting remote control callback event handler.
	/// \param pEvent A pointer to the IMeetingRemoteCtrlEvent that receives the remote control event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks When the remote control or the authority changes, the user will receive a callback event.
	virtual SDKError SetEvent(IMeetingRemoteCtrlEvent* pEvent) = 0;

	/// \brief Determine if it is able to ask for controlling the specified user by long-distance.
	/// \param userId Specify the user ID to check.
	/// \return If it is able to request to control the specified user by long-distance, the return value is SDKErr_Success. 
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanRequestControl(unsigned int userId) = 0;

	/// \brief Determine if it is able to control the specified user by long-distance.
	/// \param userId Specify the user ID to check.
	/// \return If it is able to control the specified user by long-distance, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError IsHaveRemoteControlRight(unsigned int userId) = 0;

	/// \brief Determine if the specified user is in process of remote control.
	/// \param userId Specify the user ID to check.
	/// \return If the specified user is in process of remote control, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError IsInRemoteControllingStatus(unsigned int userId) = 0;

	/// \brief Control the specified user by long-distance.
	/// \param userId Specify the user ID to be controlled.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnterRemoteControllingStatus(unsigned int userId) = 0;

	/// \brief End controlling the specified user by long distance.
	/// \param userId Specify the user ID that you want to end the remote control.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError LeaveRemoteControllingStatus(unsigned int userId) = 0;

	/// \brief Send the request of remote control to the specified user.
	/// \param userId Specify the user ID that you want to send the request.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError RequestRemoteControl(unsigned int userId) = 0;

	/// \brief Abandon the remote control to the specified user.
	/// \param userId Specify the user ID.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError GiveupRemoteControl(unsigned int userId) = 0;

	/// \brief Give the authority of remote control to the specified user.
	/// \param userId Specify the user ID that you want to give the authority.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError GiveRemoteControlTo(unsigned int userId) = 0;

	/// \brief Refuse the request to remote control from the specified user.
	/// \param userId Specify the user ID to be disabled to remote control.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError DeclineRemoteControlRequest(unsigned int userId) = 0;

	/// \brief Get back all the authority of remote control.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError RevokeRemoteControl() = 0;

	/// \brief Get the controller ID who is currently controlling by long-distance.
	/// \param [out] userId The user ID who is currently controlling by long-distance. ZERO(0) indicates that there is no controller for the moment.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError GetCurrentRemoteController(unsigned int& userId) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif