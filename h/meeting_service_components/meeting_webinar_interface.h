/*!
* \file meeting_webinar_interface.h
* \brief Chat of Meeting Service Interface
* 
*/

#ifndef _MEETING_WEBINAR_INTERFACE_H_
#define _MEETING_WEBINAR_INTERFACE_H_
/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Meeting webinar callback event
///
class IMeetingWebinarCtrlEvent
{
public:
	/// \brief change attendee to panlist result callback
	/// \param result if success, result is zero, otherwise is the error code.
	virtual void onPromptAttendee2PanelistResult(int result) = 0;

	/// \brief change panlist to attendee result callback
	/// \param result if success, result is zero, otherwise is the error code.
	virtual void onDepromptPanelist2AttendeeResult(int result) = 0;

	/// \brief allow panelist to start video result callback
	virtual void onAllowPanelistStartVideoNotification() = 0;

	/// \brief disallow panelist to start video result callback
	virtual void onDisallowPanelistStartVideoNotification() = 0;

	/// \brief self allow to talk notification callback
	virtual void onSelfAllowTalkNotification() = 0;

	/// \brief self disallow to talk notification callback
	virtual void onSelfDisallowTalkNotification() = 0;

	/// \brief allow attendee to chat result callback
	virtual void onAllowAttendeeChatNotification() = 0;

	/// \brief disallow attendee to chat result callback
	virtual void onDisallowAttendeeChatNotification() = 0;

	/// \brief attendee audio status notification callback
	/// \param userid which attendee's audio status changed
	/// \param can_talk can talk or not
	/// \param is_muted mute or not, if can_talk is true, available
	virtual void onAttendeeAudioStatusNotification(unsigned int userid, bool can_talk, bool is_muted) = 0;
};

/*! \struct tagWebinarMeetingStatus
    \brief chat message item for webinar meeting
    A more detailed struct description.
*/
typedef struct tagWebinarMeetingStatus
{
	bool allow_panellist_start_video;///< panellist can start video or not
	bool allow_attendee_chat;///< attendee can chat or not
	tagWebinarMeetingStatus()
	{
		Reset();
	}

	void Reset()
	{
		allow_panellist_start_video = false;
		allow_attendee_chat = false;
	}
}WebinarMeetingStatus;

/// \brief Webinar controller interface
///
class IMeetingWebinarController
{
public:
	/// \brief Set meeting webinar controller callback event
	/// \param pEvent A pointer to a IMeetingWebinarCtrlEvent* that receives webinar meeting event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingWebinarCtrlEvent* pEvent) = 0;

	/// \brief Change attendee to panellist,only meeting host can call this api
	/// \param userid Specifies which user you want to prompt.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError PromptAttendee2Panelist(unsigned int userid) = 0;

	/// \brief Change panellist to attendee,only meeting host can call this api
	/// \param userid Specifies which user you want to downgrade.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DepromptPanelist2Attendee(unsigned int userid) = 0;

	/// \brief Check is support allow attendee talk or not of this meeting
	/// \return If is support allow attendee talk, the return value is SDKErr_Success.
	///If don't support, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError IsSupportAttendeeTalk() = 0;

	/// \brief allow attendee to talk,only meeting host can call this api
	/// \param userid Specifies which user you want to allow.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError AllowAttendeeTalk(unsigned int userid) = 0;

	/// \brief disallow attendee to talk,only meeting host can call this api
	/// \param userid Specifies which user you want to disallow.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DisallowAttendeeTalk(unsigned int userid) = 0;

	/// \brief allow panellist to start video,only meeting host can call this api
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError AllowPanelistStartVideo() = 0;

	/// \brief disallow panellist to start video,only meeting host can call this api
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DisallowPanelistStartVideo() = 0;

	/// \brief allow attendee to chat,only meeting host can call this api
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError AllowAttendeeChat() = 0;

	/// \brief disallow attendee to chat,only meeting host can call this api
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DisallowAttendeeChat() = 0;

	/// \brief Get webinar meeting status.
	/// \return webinar meeting status
	virtual WebinarMeetingStatus* GetWebinarMeetingStatus() = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif