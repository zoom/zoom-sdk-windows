/*!
* \file meeting_chat_interface.h
* \brief Meeting Service Chat Interface. 
* \remarks Valid for both ZOOM style and user custom interface mode.
*/
#ifndef _MEETING_CHAT_INTERFACE_H_
#define _MEETING_CHAT_INTERFACE_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Chat message interface.
///
class IChatMsgInfo
{
public:
	/// \brief Get the sender ID of the current message.
	/// \return If the function succeeds, the return value is the sender ID of the current message.
	///Otherwise failed, the return value is -1.
	virtual unsigned int GetSenderUserId() = 0;

	/// \brief Get the sender screen name of the current message.
	/// \return If the function succeeds, the return value is sender screen name of the current message.
	///Otherwise failed, the return value is NULL.
	/// \remarks If the message is sent to all or to all panelists, the return value will be NULL.
	virtual const wchar_t* GetSenderDisplayName() = 0;

	/// \brief Get the receiver ID of the current message.
	/// \return If the function succeeds, the return value is the receiver ID of the current message.
	///ZERO(0) indicates that the message is sent to all.
	///ONE(1) indicates that the messages are sent to all the panelists.
	///Otherwise failed, the return value is negative ONE(-1).
	virtual unsigned int GetReceiverUserId() = 0;

	/// \brief Get the receiver screen name of the current message.
	/// \return If the function succeeds, the return value is the receiver screen name of the current message.
	///Otherwise failed, the return value is the string of length zero(0).
	virtual const wchar_t* GetReceiverDisplayName() = 0;

	/// \brief Get the content of the current message.
	/// \return If the function succeeds, the return value is the pointer to the content of the current message.
	///Otherwise failed, the return value is NULL.
	virtual const wchar_t* GetContent() = 0;

	/// \brief Get the timestamps of the current message.
	/// \return If the function succeeds, the return value is the timestamps of the current message. 
	virtual time_t GetTimeStamp() = 0;

	/// \brief Determine if the current message is sent to all. 
	/// \return TRUE indicates that the current message is sent to all. Otherwise not. 
	virtual bool IsChatToAll() = 0;

	/// \brief Determine if the current message is sent to all the panelists.
	/// \return TRUE indicates that the current message is sent to all the panelists. Otherwise not. 
	virtual bool IsChatToAllPanelist() = 0;

	virtual ~IChatMsgInfo() {};
};

/*! \struct NormalMeetingChatStaus
    \brief The authority to chat in the normal meeting.  
    Here are more detailed structural descriptions..
*/
typedef struct tagNormalMeetingChatStaus
{
	bool can_chat_to_all;///<TRUE indicates that the user owns the authority to send message to all.
	bool can_chat_to_individual;///<TRUE indicates that the user owns the authority to send message to an individual attendee in the meeting.
	bool is_only_can_chat_to_host;///<TRUE indicates that the user owns the authority to send message only to the host.
}NormalMeetingChatStaus;

/*! \struct tagWebinarAttendeeChatStatus
    \brief The authority to chat for the normal attendee in the webinar.
    Here are more detailed structural descriptions..
*/
typedef struct tagWebinarAttendeeChatStatus
{
	bool can_chat;///<TRUE indicates that the attendee can send message to chat. 
	bool can_chat_to_all_panellist_and_attendee;///<TRUE indicates that the user owns the authority to send message to all the panelists and attendees.
	bool can_chat_to_all_panellist;///<TRUE indicates that the user owns the authority to send message to all the panelists.
}WebinarAttendeeChatStatus;

/*! \struct tagWebinarOtherUserRoleChatStatus
    \brief The authority to chat for the host, co-host and panelist to chat in webinar.
    Here are more detailed structural descriptions..
*/
typedef struct tagWebinarOtherUserRoleChatStatus
{
	bool can_chat_to_all_panellist;///<TRUE indicates that the user owns the authority to send message to all the panelists.
	bool can_chat_to_all_panellist_and_attendee;///<TRUE indicates that the user owns the authority to send message to all.
	bool can_chat_to_individual;///<TRUE indicates that the user owns the authority to send message to individual attendee.
}WebinarOtherUserRoleChatStatus;

/*! \struct tagChatStatus
    \brief The authority to chat in the specified meeting.
    Here are more detailed structural descriptions..
*/
typedef struct tagChatStatus
{
	union
	{
		NormalMeetingChatStaus normal_meeting_status;
		WebinarAttendeeChatStatus webinar_attendee_status;
		WebinarOtherUserRoleChatStatus webinar_other_status;
	}ut;///<The ut value depends on the value of the other members in the structure. When the value of is_webinar_meeting is false, the ut value is the NormalMeetingChatStausnormal_meeting_status. When the values of the is_webinar_meeting and the is_webinar_attendee is true, the ut value is WebinarAttendeeChatStatus webinar_attendee_status. The value of is_webinar_meeting is true while the is_webinar_attendee is false, the ut value is WebinarOtherUserRoleChatStatus webinar_other_status.
	bool is_chat_off;///<TRUE indicates that it is disabled to chat in the specified meeting. 
	bool is_webinar_attendee;///<TRUE indicates that the owner of the current message is the attendee of the webinar. 
	bool is_webinar_meeting;///<TRUE indicates that the current meeting is webinar.

	tagChatStatus()
	{
		Reset();
	}

	void Reset()
	{
		memset(this, 0, sizeof(tagChatStatus));
	}
}ChatStatus;

/// \brief Meeting chat callback event.
///
class IMeetingChatCtrlEvent
{
public:
	/// \brief Chat message callback. This function is used to inform the user once received the message sent by others.
	/// \param chatMsg An object pointer to the chat message.
	/// \param content A pointer to the chat message in json format. This parameter is currently invalid, hereby only for reservations. 
	virtual void onChatMsgNotifcation(IChatMsgInfo* chatMsg, const wchar_t* content = NULL) = 0;

	/// \brief The authority of chat changes callback. This function is used to inform the user when the authority of chat changes in the meeting or webinar.
	/// \param status_ The chat status. For more details, see \link ChatStatus \endlink.
	virtual void onChatStautsChangedNotification(ChatStatus* status_) = 0;
};

/*! \enum WebinarChatMsgType
    \brief The sending message type in webinar.
    Here are more detailed structural descriptions..
*/ 
enum WebinarChatMsgType
{
	WebinarChatMsgType_None,///<Disable to send message.
	WebinarChatMsgType_ToAllPanelist,///<Enable to send message to all the panelists.
	WebinarChatMsgType_ToAllPanelistAndAttendee,///<Enable to send message to all.
	WebinarChatMsgType_ToIndividualUser,///<Enable to send message to individual attendee.
};

/*! \struct tagSendChatItem4Webinar
    \brief The structure of chat message for webinar.
    Here are more detailed structural descriptions.
*/
typedef struct tagSendChatItem4Webinar 
{
	WebinarChatMsgType msgType;///<The authority to send chat message.
	const wchar_t* content;///<The content of the message.
	unsigned int userID;///<This member is only used to specify the attendee ID when the authority is WebinarChatMsgType_ToIndividualUser. 
	tagSendChatItem4Webinar()
	{
		msgType = WebinarChatMsgType_None;
		content = NULL;
		userID = -1;
	}
}SendChatItem4Webinar;

/// \brief Meeting chat controller interface
///
class IMeetingChatController
{
public:
	/// \brief Set meeting chat callback event.
	/// \param pEvent A pointer to the IMeetingChatCtrlEvent to receive chat callback event. For more details, see \link IMeetingChatCtrlEvent \endlink.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remark The event is used by SDK to pass the callback event to user's application. If this function is not called or fails, the user's application can not retrieve the callback event.
	virtual SDKError SetEvent(IMeetingChatCtrlEvent* pEvent) = 0;

	/// \brief Send chat message in the normal meeting.
	/// \param receiver Specify the user ID who receives the chat message. The message will be sent to all when the value is zero(0). 
	/// \param content The content of the chat message. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SendChatTo(unsigned int receiver, wchar_t* content) = 0;

	/// \brief Send chat message in webinar.
	/// \param chatIteam An instance of the structure of the chat message. For more details, see \link SendChatItem4Webinar \endlink structure.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SendChat4WebinarMeeting(SendChatItem4Webinar& chatIteam) = 0;

	/// \brief Get the authority status to send current message. 
	/// \return If the function succeeds, the return value is a pointer to the structure of ChatStatus. For more details, see \link ChatStatus \endlink structure.
	///Otherwise failed, the return value is NULL. To get extended error information, see \link ChatStatus \endlink.
	virtual const ChatStatus* GetChatStatus() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif