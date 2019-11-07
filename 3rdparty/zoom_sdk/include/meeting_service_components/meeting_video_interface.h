/*!
* \file meeting_video_interface.h
* \brief Meeting Service Video Interface
* 
*/
#ifndef _MEETING_VIDEO_INTERFACE_H_
#define _MEETING_VIDEO_INTERFACE_H_
#include "..\zoom_sdk_def.h"
#include "..\zoom_sdk_util_define.h"
BEGIN_ZOOM_SDK_NAMESPACE

/*! \enum VideoStatus
    \brief The video status of the user.
    Here are more detailed structural descriptions.
*/
enum VideoStatus
{
	Video_ON, ///<Video is on.
	Video_OFF, ///<Video is off.
};

/// \brief Process after the user receives the requirement from the host to turn on the video.
class IRequestStartVideoHandler
{
public:
	virtual ~IRequestStartVideoHandler(){};
	/// \brief Get the user ID who asks to turn on the video.
	/// \return If the function succeeds, the return value is the user ID. FALSE 0.
	virtual unsigned int GetReqFromUserId() = 0;
	/// \brief Instance to ignore the requirement, return nothing and finally self-destroy.
	virtual SDKError Ignore() = 0;
	/// \brief Instance to accept the requirement, turn on the video and finally self-destroy.
	virtual SDKError Accept() = 0;
	
	/// \brief Ignore the request to enable the video in the meeting and finally the instance self-destroys.
	virtual SDKError Cancel() = 0;
};

/// \brief Meeting video controller event callback
///
class IMeetingVideoCtrlEvent
{
public:
	/// \brief Callback event of the user video status changes.
	/// \param userId The user ID whose video status changes
	/// \param status New video status. For more details, see \link VideoStatus \endlink enum.
	virtual void onUserVideoStatusChange(unsigned int userId, VideoStatus status) = 0;

	/// \brief Callback event of the user video spotlight status changes. 
	/// \param bSpotlight TRUE indicates that the video is currently spotlighted.
	/// \param userid The ID of user whose spotlight status changes.
	virtual void onSpotlightVideoChangeNotification(bool bSpotlight, unsigned int userid) = 0;

	/// \brief Callback event of the requirement to turn on the video from the host.
	/// \param handler_ A pointer to the IRequestStartVideoHandler. For more details, see \link IRequestStartVideoHandler \endlink.
	virtual void onHostRequestStartVideo(IRequestStartVideoHandler* handler_) = 0;

	/// \brief Callback event of the active speaker video user changes. 
	/// \param userid The ID of user who becomes the new active speaker.
	virtual void onActiveSpeakerVideoUserChanged(unsigned int userid) = 0;

	/// \brief Callback event of the active video user changes. 
	/// \param userid The ID of user who becomes the new active speaker.
	virtual void onActiveVideoUserChanged(unsigned int userid) = 0;
};

/// \brief Meeting video controller interface
///
class IMeetingVideoController
{
public:
	/// \brief Set the meeting video controller callback event handler
	/// \param pEvent A pointer to the IRequestStartVideoHandler that receives the video controller event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IMeetingVideoCtrlEvent* pEvent) = 0;
	
	/// \brief Turn off the user's own video.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both Zoom style and customize user interface mode.
	virtual SDKError MuteVideo() = 0;

	/// \brief Turn on the user's own video.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both Zoom style and customize user interface mode.
	virtual SDKError UnmuteVideo() = 0;

	/// \brief Pin the video of the assigned user.
	/// \param bPin TRUE indicates to pin.
	/// \param bFirstView TRUE indicates to pin the video on the primary view. FALSE indicates to pin the video on the secondary view. The function does not work when the user chooses FALSE without dual view.
	/// \param userid Specifies the user ID to be pinned. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid only for Zoom style user interface mode. 
	virtual SDKError PinVideo(bool bPin, bool bFirstView, unsigned int userid) = 0;

	/// \brief Spotlight the video of the assigned user.
	/// \param bSpotlight TRUE indicates to spotlight.
	/// \param userid Specifies the user ID to be spotlighted.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both Zoom style and customize user interface mode.
	virtual SDKError SpotlightVideo(bool bSpotlight, unsigned int userid) = 0;

	/// \brief Display or not the user who does not turn on the video in the video all mode.
	/// \return TRUE indicates to hide, FALSE show.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid only for Zoom style user interface mode.
	virtual SDKError HideOrShowNoVideoUserOnVideoWall(bool bHide) = 0;

	/// \brief Query if it is able to demand the specified user to turn on the video.
	/// \param userid Specifies the user ID to query.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both Zoom style and customize user interface mode.
	virtual SDKError CanAskAttendeeToStartVideo(unsigned int userid) = 0;

	/// \brief Demand the assigned user to turn on the video.
	/// \param userid Specifies the user ID to demand.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both Zoom style and customize user interface mode.
	virtual SDKError AskAttendeeToStartVideo(unsigned int userid) = 0;

	/// \brief Query if it is able to demand the specified user to turn off the video.
	/// \param userid Specifies the user ID to query.  
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both Zoom style and customize user interface mode.
	virtual SDKError CanStopAttendeeVideo(unsigned int userid) = 0;

	/// \brief Turn off the video of the assigned user.
	/// \param userid Specifies the user ID to turn off.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both Zoom style and customize user interface mode.
	virtual SDKError StopAttendeeVideo(unsigned int userid) = 0;

	virtual ICameraController* GetMyCameraController() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif