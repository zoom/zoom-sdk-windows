/*!
* \file customized_local_recording.h
* \brief ZOOM Custom Local Recording Interface.
* 
*/
#ifndef _CUSTOMIZED_LOCAL_RECORDING_H_
#define _CUSTOMIZED_LOCAL_RECORDING_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum RECORDING_LAYOUT_MODE
    \brief Layout mode of local recording.
    Here are more detailed structural descriptions.
*/ 
enum RECORDING_LAYOUT_MODE
{
	RECORDING_LAYOUT_MODE_NONE = 0,///<For initialization.
	RECORDING_LAYOUT_MODE_ACTIVE_VIDEO_ONLY = 1,///<Record only the active video for the moment. 
	RECORDING_LAYOUT_MODE_VIDEO_WALL = (1<<1),///<Record the video wall.
	RECORDING_LAYOUT_MODE_SHARE_AND_VIDEO = (1<<2),///<Record the shared content, video or other specified videos.
	RECORDING_LAYOUT_MODE_ONLY_AUDIO = (1<<3),///<Record only the audio.
	RECORDING_LAYOUT_MODE_ONLY_SHARE = (1<<4),///<Record only the shared content.
};
class ICustomizedLocalRecordingLayoutHelper
{
public:
	/// \brief Get the layout mode supported by the current meeting. see \link RECORDING_LAYOUT_MODE \endlink enum. 
	/// \return If the function succeeds, the return value is the layout type supported by the current meeting. For more details, see \link RECORDING_LAYOUT_MODE \endlink enum.
	virtual int GetSupportLayout() = 0;
	
	/// \brief Get the list of users whose video source is available.
	/// \return The list of users. ZERO(0) indicates that there is no available video source of users. 
	/// \remarks The value saved in the list is the user ID.
	virtual IList<unsigned int >* GetValidVideoSourceList() = 0;

	/// \brief Get the available list of users who can receive the shared content.
	/// \return The available list of users who can receive the shared content. ZERO(0) indicates that there is no available users.
	/// \remarks The value saved in the list is the user ID.
	virtual IList<unsigned int >* GetValidRecvSharingSourceList() = 0;
	
	/// \brief Determine if there exists user who is sharing the content. 
	/// \return TRUE indicates that there is user who is sharing the content.
	virtual bool IsSendSharingSourceAvailable() = 0;
	
	/// \brief Determine if there exists the active video source.
	/// \return TRUE indicates that there is the active video source.
	virtual bool HasActiveVideoSource() = 0;
	
	/// \brief Set the specified recording layout mode.
	/// \param mode_ Specify the recording layout mode that you want. For more details, see \link RECORDING_LAYOUT_MODE \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_SUCCESS. Otherwise returns the RECORDING_LAYOUT_MODE.
	virtual SDKError SelectRecordingLayoutMode(RECORDING_LAYOUT_MODE mode_) = 0;
	
	/// \brief Add the video source of specified user to the list of videos recorded.
	/// \param user_id Specify the user ID.
	/// \return If the function succeeds, the return value is SDKErr_SUCCESS. If the specified user is out of the list of available video source, it returns SDKERR_INVALID_PARAMETER.
	virtual SDKError AddVideoSourceToRecList(unsigned int user_id) = 0;
	
	/// \brief Choose the current active video source.
	/// \return If the function succeeds, the return value is SDKErr_SUCCESS. Otherwise returns the SDKERR_INVALID_PARAMETER.
	virtual SDKError SelectActiveVideoSource() = 0;
	
	/// \brief Choose the video source in the list of shared content via specified user ID.
	/// \param user_id Specify the user ID.
	/// \return If the function succeeds, the return value is SDKErr_SUCCESS. If the specified user ID is out of the list to receive the shared content, it returns SDKERR_INVALID_PARAMETER.	
	virtual SDKError SelectRecvSharingSource(unsigned int user_id) = 0;
	
	/// \brief Mark the found video source that sends shared content.
	/// \return If the function succeeds,the return value is SDKErr_SUCCESS. If there is no user who is sending the sharing, it returns SDKERR_WRONG_USEAGE. 
	virtual SDKError SelectSendSharingSource() = 0;
	virtual ~ICustomizedLocalRecordingLayoutHelper(){}
};
END_ZOOM_SDK_NAMESPACE
#endif