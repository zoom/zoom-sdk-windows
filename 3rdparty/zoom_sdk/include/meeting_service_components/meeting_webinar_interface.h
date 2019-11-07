/*!
* \file meeting_webinar_interface.h
* \brief Meeting Service Webinar Interface.
* 
*/

#ifndef _MEETING_WEBINAR_INTERFACE_H_
#define _MEETING_WEBINAR_INTERFACE_H_

BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Webinar callback event.
///
class IMeetingWebinarCtrlEvent
{
public:
	/// \brief Callback to promote attendees to panelist.
	/// \param result If the promotion is successful, the result is zero(0). Otherwise it is an error code.
	virtual void onPromptAttendee2PanelistResult(int result) = 0;

	/// \brief Callback to demote attendees to panelist.
	/// \param result If the demotion is successful, the result is zero(0), otherwise an error code.
	virtual void onDepromptPanelist2AttendeeResult(int result) = 0;

	/// \brief Callback to enable the panelist to start the video.
	virtual void onAllowPanelistStartVideoNotification() = 0;

	/// \brief Callback to disable the panelist to start the video.
	virtual void onDisallowPanelistStartVideoNotification() = 0;

	/// \brief Callback event that attendees are required to enable the mic in the view-only mode of webinar.
	virtual void onSelfAllowTalkNotification() = 0;

	/// \brief Callback event that attendees are required to turn off the mic in the view-only mode of webinar.
	virtual void onSelfDisallowTalkNotification() = 0;

	/// \brief Callback to enable the attendees to chat. Available only for the host and the co-host.
	virtual void onAllowAttendeeChatNotification() = 0;

	/// \brief Callback to disable the attendees to chat. Available only for the host and the co-host.
	virtual void onDisallowAttendeeChatNotification() = 0;
  
	/// \brief Attendee will receive this callback if his audio status changes.
	/// \param userid The ID of the user whose audio status changes.
	/// \param can_talk True indicates that it is able to use the audio. False not.  
	/// \param is_muted TRUE indicates muted, FALSE not. This parameter works only when the value of can_talk is TRUE.
	virtual void onAttendeeAudioStatusNotification(unsigned int userid, bool can_talk, bool is_muted) = 0;
};

/*! \struct tagWebinarMeetingStatus
    \brief Webinar Meeting Status.
    Here are more detailed structural descriptions.
*/
typedef struct tagWebinarMeetingStatus
{
	bool allow_panellist_start_video;///<TRUE indicates that the panelist is able to turn on the video. FALSE not.
	bool allow_attendee_chat;///<TRUE indicates that the attendee is able to chat. FALSE not.
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
	/// \brief Set webinar controller callback event handler.
	/// \param pEvent A pointer to the IMeetingWebinarCtrlEvent that receives the webinar callback event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IMeetingWebinarCtrlEvent* pEvent) = 0;

	/// \brief Promote the attendee to panelist. Available only for the meeting host.
	/// \param userid Specifies the user ID to promote.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks If the function succeeds, the user will receive the IMeetingWebinarCtrlEvent::onPromptAttendee2PanelistResult() callback event.
	virtual SDKError PromptAttendee2Panelist(unsigned int userid) = 0;

	/// \brief Demote the panelist to attendee. Available only for the host.
	/// \param userid Specifies the user ID to demote.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks If the function succeeds, the user will receive the IMeetingWebinarCtrlEvent::onDepromptPanelist2AttendeeResult() callback event.
	virtual SDKError DepromptPanelist2Attendee(unsigned int userid) = 0;

	/// \brief Query if the webinar supports the user to use the audio device.
	/// \return If it supports, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError IsSupportAttendeeTalk() = 0;

	/// \brief The attendee is permitted to use the audio device.
	/// \param userid Specifies the permitted user ID.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks If the function succeeds, the user will receive the IMeetingWebinarCtrlEvent::onAllowAttendeeChatNotification() callback event. Available only for the host.
	virtual SDKError AllowAttendeeTalk(unsigned int userid) = 0;

	/// \brief Forbid the attendee to use the audio device.
	/// \param userid Specifies the forbidden user ID.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks If the function succeeds, the user will receive the IMeetingWebinarCtrlEvent::onDisallowAttendeeChatNotification() callback event. Available only for the host.
	virtual SDKError DisallowAttendeeTalk(unsigned int userid) = 0;

	/// \brief The panelist is permitted to start the video.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks If the function succeeds, the user will receive the IMeetingWebinarCtrlEvent::onAllowPanelistStartVideoNotification() callback event. Available only for the host.
	virtual SDKError AllowPanelistStartVideo() = 0;

	/// \brief Forbid the panelist to start video.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks If the function succeeds, the user will receive the IMeetingWebinarCtrlEvent::onDisallowPanelistStartVideoNotification() callback event. Available only for the host.
	virtual SDKError DisallowPanelistStartVideo() = 0;

	/// \brief The attendees are permitted to chat.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks If the function succeeds, the user will receive the IMeetingWebinarCtrlEvent::onAllowAttendeeChatNotification() callback event. Available only for the host.
	virtual SDKError AllowAttendeeChat() = 0;

	/// \brief Forbid the attendees to chat.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks If the function succeeds, the user will receive the IMeetingWebinarCtrlEvent::onDisallowAttendeeChatNotification() callback event. Available only for the host.
	virtual SDKError DisallowAttendeeChat() = 0;

	/// \brief Get the webinar status.
	/// \return The status of webinar. For more details, see \link WebinarMeetingStatus \endlink.
	virtual WebinarMeetingStatus* GetWebinarMeetingStatus() = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif