/*!
* \file meeting_chat_interface.h
* \brief Chat of Meeting Service Interface
* \support for zoom style and customized style ui mode
*/
#ifndef _MEETING_CHAT_INTERFACE_H_
#define _MEETING_CHAT_INTERFACE_H_
#include "..\zoom_sdk_def.h"

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Chat message information Interface
///
class IChatMsgInfo
{
public:
	/// \brief Get sender user id
	/// \return If the function succeeds, the return value is sender user id.
	///If the function fails, the return value is -1.
	virtual unsigned int GetSenderUserId() = 0;

	/// \brief Get sender user display name
	/// \return If the function succeeds, the return value is sender user display name.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetSenderDisplayName() = 0;

	/// \brief Get receiver user id
	/// \return If the function succeeds, the return value is receiver user id.
	///if return value is 0, this message is send to everyone
	///If the function fails, the return value is -1.
	virtual unsigned int GetReceiverUserId() = 0;

	/// \brief Get receiver user display name
	/// \return If the function succeeds, the return value is receiver user display name.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetReceiverDisplayName() = 0;

	/// \brief Get chat message content
	/// \return If the function succeeds, the return value is chat message content.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetContent() = 0;

	/// \brief Get chat message timestamp
	/// \return If the function succeeds, the return value is chat message timestamp.
	virtual time_t GetTimeStamp() = 0;

	// \brief Is a to all chat message
	/// \return If true, it is to all chat message, otherwise not
	virtual bool IsChatToAll() = 0;

	// \brief Is a to all panellist chat message
	/// \return If true, it is to all panellist chat message, otherwise not
	virtual bool IsChatToAllPanelist() = 0;

	virtual ~IChatMsgInfo() {};
};

/*! \struct tagNormalMeetingChatStaus
    \brief chat status of normal meeting
    A more detailed struct description.
*/
typedef struct tagNormalMeetingChatStaus
{
	bool can_chat_to_all;///< can chat to all or not
	bool can_chat_to_individual;///< can chat to individual or not
	bool is_only_can_chat_to_host;///< is only can chat to host or not
}NormalMeetingChatStaus;

/*! \struct tagWebinarAttendeeChatStatus
    \brief chat status of webinar attendee,only used for webinar attendee
    A more detailed struct description.
*/
typedef struct tagWebinarAttendeeChatStatus
{
	bool can_chat;///< can chat not
	bool can_chat_to_all_panellist_and_attendee;///< can chat to all panellist and attendee or not
	bool can_chat_to_all_panellist;///< can chat to all panellist or not
}WebinarAttendeeChatStatus;

/*! \struct tagWebinarOtherUserRoleChatStatus
    \brief chat status of webinar meeting,only used for webinar host/cohost/panellist
    A more detailed struct description.
*/
typedef struct tagWebinarOtherUserRoleChatStatus
{
	bool can_chat_to_all_panellist;///< can chat to all panellist or not
	bool can_chat_to_all_panellist_and_attendee;///< can chat to all panellist and attendee or not
	bool can_chat_to_individual;///< can chat to individual or not
}WebinarOtherUserRoleChatStatus;

/*! \struct tagChatStatus
    \brief chat status of current meeting
    A more detailed struct description.
*/
typedef struct tagChatStatus
{
	union
	{
		NormalMeetingChatStaus normal_meeting_status;///< if is_webinar_meeting is false, available.refer to tagNormalMeetingChatStaus
		WebinarAttendeeChatStatus webinar_attendee_status;///< if is_webinar_meeting is true and is_webinar_attendee is true, available.refer to tagWebinarAttendeeChatStatus
		WebinarOtherUserRoleChatStatus webinar_other_status;///< if is_webinar_meeting is true and is_webinar_attendee is false, available.refer to tagWebinarOtherUserRoleChatStatus
	}ut;
	bool is_chat_off;///< is chat off or not for current meeting
	bool is_webinar_attendee;///< is webinar attendee role or not
	bool is_webinar_meeting;///< is webinar meeting or not

	tagChatStatus()
	{
		Reset();
	}

	void Reset()
	{
		memset(this, 0, sizeof(tagChatStatus));
	}
}ChatStatus;

/// \brief Meeting chat callback event
///
class IMeetingChatCtrlEvent
{
public:
	/// \brief chat message callback
	/// \param chatMsg chat message object. This param will invalid after this function call end.
	/// \param content chat message in json format,Reserved.
	virtual void onChatMsgNotifcation(IChatMsgInfo* chatMsg, const wchar_t* content = NULL) = 0;

	/// \brief chat status changed notification callback
	/// \param status_ chat status object. This param will invalid after this function call end.
	virtual void onChatStautsChangedNotification(ChatStatus* status_) = 0;
};

/*! \enum WebinarChatMsgType
    \brief chat message type of webinar meeting.
    A more detailed struct description.
*/ 
enum WebinarChatMsgType
{
	WebinarChatMsgType_None,///< None
	WebinarChatMsgType_ToAllPanelist,///< send chat to all panellist
	WebinarChatMsgType_ToAllPanelistAndAttendee,///< send chat to all panellist and attendee
	WebinarChatMsgType_ToIndividualUser,///< send chat to individual user
};

/*! \struct tagSendChatItem4Webinar
    \brief chat message item for webinar meeting
    A more detailed struct description.
*/
typedef struct tagSendChatItem4Webinar
{
	WebinarChatMsgType msgType;///< chat message type
	const wchar_t* content;///< chat content
	unsigned int userID;///< send chat to,if msgType is WebinarChatMsgType_ToIndividualUser, available
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
	/// \brief Set meeting chat callback event
	/// \param pEvent A pointer to a IMeetingChatCtrlEvent* that receives chat event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingChatCtrlEvent* pEvent) = 0;

	/// \brief Send chat message to somebody or All
	/// \param receiver the chat message receiver. if this parameter is zero, this message send to all
	/// \param content	the chat message content.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SendChatTo(unsigned int receiver, wchar_t* content) = 0;

	/// \brief Send chat message to somebody or All in webinar meeting
	/// \param chatIteam the chat message item. refer to SendChatItem4Webinar
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SendChat4WebinarMeeting(SendChatItem4Webinar& chatIteam) = 0;

	/// \brief Get current privilege status of chat session.
	/// \return If the function succeeds, the return value is the status of chat session.
	///If the function fails, the return value is NULL.To get extended error information, refer to ChatStatus.
	virtual const ChatStatus* GetChatStatus() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif