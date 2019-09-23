/*!
* \file meeting_participants_ctrl_interface.h
* \brief Participants Controller of Meeting Service Interface
* 
*/
#ifndef _MEETING_ParticipantsCtrl_INTERFACE_H_
#define _MEETING_ParticipantsCtrl_INTERFACE_H_
#include "..\zoom_sdk_def.h"

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum UserRole
    \brief User role.
    A more detailed struct description.
*/
enum UserRole
{
	USERROLE_NONE,
	USERROLE_HOST,
	USERROLE_COHOST,
	USERROLE_PANELIST,
	USERROLE_BREAKOUTROOM_MODERATOR,
	USERROLE_ATTENDEE,
};

/// \brief User information Interface
///
class IUserInfo
{
public:
	/// \brief Get user name
	/// \return If the function succeeds, the return value is user name.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetUserName() = 0;

	/// \brief Get user email
	/// \return If the function succeeds, the return value is user email.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetEmail() = 0;

	/// \brief Is host or not
	/// \return host or not
	virtual bool IsHost() = 0;

	/// \brief Get user ID
	/// \return If the function succeeds, the return value is user ID.
	///If the function fails, the return value is 0.
	virtual unsigned int GetUserID() = 0;

	/// \brief Is video on or off 
	/// \return video on or off
	virtual bool IsVideoOn() = 0;

	/// \brief Is audio Muted or UnMuted 
	/// \return audio Muted or UnMuted 
	virtual bool IsAudioMuted() = 0;

	/// \brief Audio type
	/// \return Audio join type
	virtual AudioType GetAudioJoinType() = 0;

	/// \brief Is me or not
	/// \return me or not
	virtual bool IsMySelf() = 0;

	/// \brief Is in waiting room or not
	/// \return in waiting room or not 
	virtual bool IsInWaitingRoom() = 0;

	/// \brief Is raise hand or not
	/// \return Is raise hand or not
	virtual bool IsRaiseHand() = 0;

	/// \brief User Role
	/// \return User Role
	virtual UserRole GetUserRole() = 0;

	/// \brief Is pure phone user or not
	/// \return Is pure phone user or not
	virtual bool IsPurePhoneUser() = 0;
};

/// \brief Meeting Participants Controller Callback Event
///
class IMeetingParticipantsCtrlEvent
{
public:
	/// \brief New user join notify callback
	/// \param lstUserID List of new user.
	/// \param strUserList User list in json format,Reserved.
	virtual void onUserJoin(IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL) = 0;

	/// \brief User left meeting notify callback
	/// \param lstUserID List of the user left.
	/// \param strUserList User list in json format,Reserved.
	virtual void onUserLeft(IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL) = 0;

	/// \brief host change callback
	/// \param userId 
	virtual void onHostChangeNotification(unsigned int userId) = 0;

	/// \brief Low Or Raise Hand Status change callback
	/// \param bLow
	/// \param userid 
	virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid) = 0;

	/// \brief User name change callback
	/// \param userId
	/// \param userName 
	virtual void onUserNameChanged(unsigned int userId, const wchar_t* userName) = 0;
};

/// \brief Meeting waiting room controller interface
///
class IMeetingParticipantsController
{
public:
	/// \brief Set participants controller callback event
	/// \param pEvent A pointer to a IParticipantsControllerEvent* that receives participants event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingParticipantsCtrlEvent* pEvent) = 0;

	/// \brief Get meeting participants list
	/// \return the return value is current meeting all participants list.if not in meeting, return NULL.
	virtual IList<unsigned int >* GetParticipantsList() = 0;

	/// \brief Get user information via user id
	/// \param userId Specifies which the user's information to get.if zero,to get current user information.
	/// \return If the function succeeds, the return value is user information interface.
	///If the function fails, the return value is NULL.
	virtual IUserInfo* GetUserByUserID(unsigned int userid) = 0;

	/// \brief Lower all attendee hands in meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError LowerAllHands() = 0;

	/// \brief Change user name.if you want to change other user name, you should be the host or cohost.
	/// \param userId Specifies the user's name need change.
	/// \param userName Specifies the new user name.
	/// \param bSaveUserName Specifies which the user uses this name when join meeting next time.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ChangeUserName(const unsigned int userid, const wchar_t* userName, bool bSaveUserName) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif