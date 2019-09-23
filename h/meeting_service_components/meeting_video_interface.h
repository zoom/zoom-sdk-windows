/*!
* \file meeting_video_interface.h
* \brief Video of Meeting Service Interface
* 
*/
#ifndef _MEETING_VIDEO_INTERFACE_H_
#define _MEETING_VIDEO_INTERFACE_H_
#include "..\zoom_sdk_def.h"

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
enum VideoStatus
{
	Video_ON,
	Video_OFF,
};

class IRequestStartVideoHandler
{
public:
	virtual ~IRequestStartVideoHandler(){};

	virtual unsigned int GetReqFromUserId() = 0;
	virtual SDKError Ignore() = 0;
	virtual SDKError Accept() = 0;
	virtual SDKError Cancel() = 0;
};

/// \brief Meeting video controller event callback
///
class IMeetingVideoCtrlEvent
{
public:
	/// \brief User's video status change callback
	/// \param userId 
	/// \param status
	virtual void onUserVideoStatusChange(unsigned int userId, VideoStatus status) = 0;

	/// \brief spotlight video change callback
	/// \param userId 
	virtual void onSpotlightVideoChangeNotification(bool bSpotlight, unsigned int userid) = 0;

	virtual void onHostRequestStartVideo(IRequestStartVideoHandler* handler_) = 0;
};

/// \brief Meeting video controller interface
///
class IMeetingVideoController
{
public:
	/// \brief Set meeting video controller callback event
	/// \param pEvent A pointer to a IMeetingVideoCtrlEvent* that receives video event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingVideoCtrlEvent* pEvent) = 0;
	/// \brief Mute video
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError MuteVideo() = 0;

	/// \brief Unmute video
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError UnmuteVideo() = 0;

	/// \brief Pin or Unpin video
	/// \param bPin pin or unpin video
	/// \param bFirstView first screen or not to pin the video.
	/// \param userid Specifies which the user is to be pinned.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError PinVideo(bool bPin, bool bFirstView, unsigned int userid) = 0;

	/// \brief Spotlight video
	/// \param bSpotlight spotlight video or not
	/// \param userid Specifies which the user is to be spotlighted.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SpotlightVideo(bool bSpotlight, unsigned int userid) = 0;

	/// \brief Hide or show no video user on video wall mode
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError HideOrShowNoVideoUserOnVideoWall(bool bHide) = 0;

	/// \brief Check Can Ask Attendee To Start Video
	/// \param userid Specifies which user you want to check.
	/// \return If you can, the return value is SDKErr_Success.
	///If you can't, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError CanAskAttendeeToStartVideo(unsigned int userid) = 0;

	/// \brief Ask Attendee To Start Video
	/// \param userid Specifies which user you want to ask.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError AskAttendeeToStartVideo(unsigned int userid) = 0;

	/// \brief Check Can Stop Attendee Video
	/// \param userid Specifies which user you want to check.
	/// \return If you can, the return value is SDKErr_Success.
	///If you can't, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError CanStopAttendeeVideo(unsigned int userid) = 0;

	/// \brief Stop Attendee Video
	/// \param userid Specifies which user you want to stop.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StopAttendeeVideo(unsigned int userid) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif