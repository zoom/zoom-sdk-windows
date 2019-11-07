/*!
* \file meeting_participants_ctrl_interface.h
* \brief Meeting Participants Controller Interface.
* 
*/
#ifndef _MEETING_ParticipantsCtrl_INTERFACE_H_
#define _MEETING_ParticipantsCtrl_INTERFACE_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum UserRole
    \brief Role of user.
    Here are more detailed structural descriptions.
*/
enum UserRole
{
	USERROLE_NONE,///<For initialization.
	USERROLE_HOST,///<Role of the host.
	USERROLE_COHOST,///<Role of co-host.
	USERROLE_PANELIST,///<Role of the panelist, valid only in webinar.
	USERROLE_BREAKOUTROOM_MODERATOR,///<Host role in breakout room.
	USERROLE_ATTENDEE,///<Role of attendee.
};

/*! \struct tagWebinarAttendeeStatus
    \brief Status of webinar attendee.
    Here are more detailed structural descriptions.
*/
typedef struct tagWebinarAttendeeStatus
{
	bool allow_talk;///<TRUE indicates that it is able to talk.
	tagWebinarAttendeeStatus()
	{
		allow_talk = false;
	}
}WebinarAttendeeStatus;

/// \brief User information interface.
///
class IUserInfo
{
public:
	/// \brief Get the username matched with the current user information.
	/// \return If the function succeeds, the return value is the username.
	///Otherwise failed, the return value is NULL.
	virtual const wchar_t* GetUserName() = 0;

	/// \brief Get the email matched with the current user information.
	/// \return If the function succeeds, the return value is user email.
	///Otherwise failed, the return value is NULL.
	virtual const wchar_t* GetEmail() = 0;

	/// \brief Determine whether the member corresponding with the current information is the host or not.
	/// \return TRUE indicates the host.
	virtual bool IsHost() = 0;

	/// \brief Get the user ID matched with the current user information.
	/// \return If the function succeeds, the return value is the user ID.
	///Otherwise failed, the return value is ZERO(0).
	virtual unsigned int GetUserID() = 0;

	/// \brief Determine the video status of the user specified by the current information.
	/// \return TRUE indicates that the video is turned on.
	virtual bool IsVideoOn() = 0;

	/// \brief Determine the audio status of the user specified by the current information.
	/// \return TRUE indicates that the audio status is muted.
	virtual bool IsAudioMuted() = 0;

	/// \brief Get the audio type of the user specified by the current information when joins the meeting.
	/// \return The type of audio when the user joins the meeting. For more details, see \link AudioType \endlink enum.
	virtual AudioType GetAudioJoinType() = 0;

	/// \brief Determine whether the current information corresponds to the user himself or not.
	/// \return TRUE indicates that the current information corresponds to the user himself.
	virtual bool IsMySelf() = 0;

	/// \brief Determine whether the user specified by the current information is in the waiting room or not.
	/// \return TRUE indicates that the specified user is in the waiting room.
	virtual bool IsInWaitingRoom() = 0;

	/// \brief Determine whether the user specified by the current information raises hand or not.
	/// \return TRUE indicates that the user raises hand.
	virtual bool IsRaiseHand() = 0;

	/// \brief Get the type of role of the user specified by the current information.
	/// \return The role of the user. For more details, see \link UserRole \endlink enum.
	virtual UserRole GetUserRole() = 0;

	/// \brief Determine whether the user corresponding to the current information joins the meeting by telephone or not.
	/// \return TRUE indicates that the user joins the meeting by telephone.
	virtual bool IsPurePhoneUser() = 0;

	/// \brief Get the Mic level of the user corresponding to the current information.
	/// \return The mic level of the user.
	virtual int GetAudioVoiceLevel() = 0;

	/// \brief Determine whether the user corresponding to the current information is the sender of Closed Caption or not.
	/// \return TRUE indicates that the user is the sender of Closed Caption.
	virtual bool IsClosedCaptionSender() = 0;

	/// \brief Get the webinar status of the user specified by the current information.
	/// \return The status of the specified user. For more details, see \link WebinarAttendeeStatus \endlink structure.
	virtual WebinarAttendeeStatus* GetWebinarAttendeeStauts() = 0;
	
	virtual ~IUserInfo(){};
};

/// \brief Meeting Participants Controller Callback Event.
///
class IMeetingParticipantsCtrlEvent
{
public:
	/// \brief Callback event of notification of users who are in the meeting.
	/// \param lstUserID List of the user ID. 
	/// \param strUserList List of user in json format. This function is currently invalid, hereby only for reservations.
	virtual void onUserJoin(IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL) = 0;

	/// \brief Callback event of notification of user who leaves the meeting.
	/// \param lstUserID List of the user ID who leaves the meeting.
	/// \param strUserList List of the user in json format. This function is currently invalid, hereby only for reservations.
	virtual void onUserLeft(IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL) = 0;

	/// \brief Callback event of notification of the new host. 
	/// \param userId Specify the ID of the new host. 
	virtual void onHostChangeNotification(unsigned int userId) = 0;

	/// \brief Callback event of changing the state of the hand.
	/// \param bLow TRUE indicates to put down the hand, FALSE indicates to raise the hand. 
	/// \param userid Specify the user ID whose status changes.
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid) = 0;

	/// \brief Callback event of changing the screen name. 
	/// \param userId Specify the user ID whose status changes.
	/// \param userName New screen name displayed.
	virtual void onUserNameChanged(unsigned int userId, const wchar_t* userName) = 0;

	/// \brief Callback event of changing the co-host.
	/// \param userId Specify the user ID whose status changes. 
	/// \param isCoHost TRUE indicates that the specified user is co-host.
	virtual void onCoHostChangeNotification(unsigned int userId, bool isCoHost) = 0;
};

/// \brief Meeting waiting room controller interface
///
class IMeetingParticipantsController
{
public:
	/// \brief Set the participants controller callback event handler.
	/// \param pEvent A pointer to the IParticipantsControllerEvent that receives the participants event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IMeetingParticipantsCtrlEvent* pEvent) = 0;

	/// \brief Get the list of all the panelists in the meeting.
	/// \return If the function succeeds, the return value is the list of the panelists in the meeting.
	///Otherwise failed, the return value is NULL.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual IList<unsigned int >* GetParticipantsList() = 0;

	/// \brief Get the information of specified user.
	/// \param userid Specify the user ID for which you want to get the information. 
	///Zero(0) indicates to get the information of the current user.
	/// \return If the function succeeds, the return value is a pointer to the IUserInfo. For more details, see \link IUserInfo \endlink.
	///Otherwise failed, the return value is NULL.
	/// \remarks Valid for both ZOOM style and user custom interface mode..
	virtual IUserInfo* GetUserByUserID(unsigned int userid) = 0;

	/// \brief Cancel all hands raised.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode..
	virtual SDKError LowerAllHands() = 0;

	/// \brief Change the screen name of specified user. Only the host or co-host can change the others' name.
	/// \param userid Specify the user ID whose name needed to be changed. 
	/// \param userName Specify a new screen name for the user.
	/// \param bSaveUserName Save the screen name to join the meeting next time.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode..
	virtual SDKError ChangeUserName(const unsigned int userid, const wchar_t* userName, bool bSaveUserName) = 0;

	/// \brief Cancel the hands raised of specified user.
	/// \param userid Specify the user ID to put down the hands.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode..
	virtual SDKError LowerHand(unsigned int userid) = 0;

	/// \brief Raise hands in the meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode..
	virtual SDKError RaiseHand() = 0;

	/// \brief Set the specified user as the host.
	/// \param userid Specify the user ID to be the host.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode..
	virtual SDKError MakeHost(unsigned int userid) = 0;

	/// \brief Determine if it is able to change the specified user role as the co-host.
	/// \param userid Specify the user ID.
	/// \return If the specified user can be the co-host, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode..
	virtual SDKError CanbeCohost(unsigned int userid) = 0;

	/// \brief Set the specified user as the co-host.
	/// \param userid Specify the user ID who is to be the co-host.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode..
	virtual SDKError AssignCoHost(unsigned int userid) = 0;

	/// \brief Get back the co-host role from the specified user.
	/// \param userid Specify the user ID to get back the co-host.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode..
	virtual SDKError RevokeCoHost(unsigned int userid) = 0;

	/// \brief Expel the specified user.
	/// \param userid Specify the ID of user to be expelled.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode..
	virtual SDKError ExpelUser(unsigned int userid) = 0;

	/// \brief Reclaim the role of the host.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid only for Zoom style user interface mode.
	virtual SDKError ReclaimHost() = 0;

	/// \brief Determine if the user has the right to reclaim the host role.
	/// \param [out] bCanReclaimHost TRUE indicates to have the right to reclaim the host role.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode..
	virtual SDKError CanReclaimHost(bool& bCanReclaimHost) = 0;

	/// \brief Reclaim role of host via host_key.
	/// \param host_key The key to get the role of host.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode..
	virtual SDKError ReclaimHostByHostKey(const wchar_t* host_key) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif