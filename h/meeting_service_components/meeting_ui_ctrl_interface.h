/*!
* \file meeting_ui_ctrl_interface.h
* \brief UI Controller of Meeting Service Interface
* Valid only for ZOOM style user interface mode.
*/
#ifndef _MEETING_UI_CTRL_INTERFACE_H_
#define _MEETING_UI_CTRL_INTERFACE_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum SDKMeetingUIType
    \brief The displayed type of the user videos in the meeting.
    Here are more detailed structural descriptions.
*/
enum SDKMeetingUIType
{
	SDK_Meeting_UI_None,///<For initialization.
	SDK_Meeting_UI_VideoWall_Mode,///<Video wall mode. 
	SDK_Meeting_UI_ActiveRender_Mode,///<Active user mode. 
};

/*! \struct tagVideoWallPageInfoParam
    \brief Video wall page information.
    Here are more detailed structural descriptions.
*/
typedef struct tagVideoWallPageInfoParam
{
	int nCurrentPage;///<The page in video wall mode for the moment.
	int nTotalPages;///<The total number of pages in video wall mode.
}VideoWallPageInfoParam;

/*! \struct tagShowChatDlgParam
    \brief The configuration of the parameters to display the dialog. 
    Here are more detailed structural descriptions.
*/
typedef struct tagShowChatDlgParam
{
	HWND hParent;///<Parent window handle.
	RECT rect;///<Chat dialog position.
	HWND hChatWnd;///<Chat dialog handle. 
	tagShowChatDlgParam()
	{
		hParent = NULL;
		hChatWnd = NULL;
 		rect.top = 0;
 		rect.bottom = 0;
 		rect.left = 0;
 		rect.right = 0;
	}
}ShowChatDlgParam;

/*! \enum SDKFloatVideoType
    \brief The user interface type of float video.
    Here are more detailed structural descriptions.
*/
enum SDKFloatVideoType
{
	FLOATVIDEO_List,///<Type of list.
	FLOATVIDEO_Small,///<Small. 
	FLOATVIDEO_Large,///<Large.
	FLOATVIDEO_Minimize,///<Minimized.
};

/*! \enum SDKMinimizeUIMode
    \brief The type of minimize user interface mode.
    Here are more detailed structural descriptions.
*/
enum SDKMinimizeUIMode
{
	MinimizeUIMode_NONE,///<For initialization.
	MinimizeUIMode_SHARE,///<Minimized mode for sharing.
	MinimizeUIMode_VIDEO,///<Minimized mode for video.
	MinimizeUIMode_ACTIVESPEAKER,///<Minimized mode for speaking.
};

/*! \struct tagSplitScreenInfo
    \brief Split screen mode information.
    Here are more detailed structural descriptions.
*/
typedef struct tagSplitScreenInfo
{
	bool bSupportSplitScreen;///<Support display the video in a row.
	bool bInSplitScreenMode;///<In the process of displaying the video in the row.
	tagSplitScreenInfo()
	{
		bSupportSplitScreen = false;
		bInSplitScreenMode = false;
	}
}SplitScreenInfo;

/*! \enum AudioCallbackActionInfo
    \brief The action user suggested to take after getting the callback event "IMeetingUIControllerEvent::onAudioBtnClicked()"
    Here are more detailed structural descriptions.
*/
enum AudioCallbackActionInfo
{
	ACTION_NONE = 0,///<For initialization.
	ACTION_CHOOSE_AUDIO_DEVICE_NOAUDIODEVICECONNECTTED,///<Choose audio device because no audio device is connected yet.
	ACTION_CHOOSE_AUDIO_DEVICE_COMPUTERAUDIODEVICEERROR,///<Choose audio device because there is an error in the connected computer audio device.
	ACTION_CHOOSE_AUDIO_DEVICE_PHONECALLDEVICEERROR,///<Choose audio device because there is an error in the connected phone call device.
	ACTION_NEED_JOIN_VOIP,///<Need to join voip.
	ACTION_MUTE_UNMUTE_AUDIO,///<Mute or unmute some user's audio according to the "AudioBtnClickedCallbackInfo::userid_MuteUnmute"
	ACTION_SHOW_AUDIO_SETTING_WINDOW,///<Show audio setting window.
};

/*! \struct tagAudioBtnClickedCallbackInfo
    \brief The suggested action information for user to handle after getting the callback event "IMeetingUIControllerEvent::onAudioBtnClicked()"
    Here are more detailed structural descriptions.
*/
typedef struct tagAudioBtnClickedCallbackInfo
{
	unsigned int userid_MuteUnmute;///<The id of the user that should be muted or unmuted. When no mute or unmute operation is required, the value is 0
	AudioCallbackActionInfo audio_clicked_action;///<The suggested action for user to take.
	tagAudioBtnClickedCallbackInfo()
	{
		userid_MuteUnmute = 0;
		audio_clicked_action = ACTION_NONE;
	}

}AudioBtnClickedCallbackInfo;

/// \brief Callback Event of Meeting UI Controller.
///
class IMeetingUIControllerEvent
{
public:
	/// \brief Callback event to click the INVITE button.
	/// \param [out] bHandled True indicates to show the user's own custom dialog interface. Default value: FALSE.
	/// \remarks If the value of bHandled is not set to TRUE, the default interface will pop up. 
	virtual void onInviteBtnClicked(bool& bHandled) = 0;
	
	/// \brief Callback event for clicking START SHARE button.
	/// \remarks The user won't receive this callback event unless he sets to redirect the process of clicking the SHARE button. For more details, see \link IMeetingUIElemConfiguration::RedirectClickShareBTNEvent() \endlink.
	virtual void onStartShareBtnClicked() = 0;
	
	/// \brief Callback event of clicking the END MEETING button.
	/// \remarks The user won't receive this callback event unless he sets to redirect the process of clicking the END MEETING button. For more details, see \link IMeetingUIElemConfiguration::RedirectClickEndMeetingBTNEvent() \endlink.
	virtual void onEndMeetingBtnClicked() = 0;
	
	/// \brief Callback event of clicking PRTICIPANT LIST button.
	/// \remarks The user won't receive this callback event unless he sets to redirect the process of clicking the PARTICIPANT LIST button. For more details, see \link IMeetingUIElemConfiguration::RedirectClickParticipantListBTNEvent() \endlink.
	virtual void onParticipantListBtnClicked() = 0;
	
	/// \brief Callback event of clicking CUSTOME LIVE STREAM menu.
	/// \remarks The user won't receive this callback event unless he sets to redirect the process of clicking the CUSTOME LIVE STREAM menu. For more details, see \link IMeetingUIElemConfiguration::RedirectClickCustomLiveStreamMenuEvent() \endlink.
	virtual void onCustomLiveStreamMenuClicked() = 0;
	
	/// \brief Notification occurs only when the SDK fails to display the default ZOOM INVITE dialog.
	virtual void onZoomInviteDialogFailed() = 0;

	/// \brief Callback event of clicking CC menu.
	/// \remarks The user won't receive this callback event unless he redirects the process of clicking the CUSTOME LIVE STREAM menu. For more details, see \link IMeetingUIElemConfiguration::RedirectClickCCBTNEvent() \endlink.
	virtual void onCCBTNClicked() = 0;

	/// \brief Callback event for clicking Audio button in the meeting.
	/// \remarks The user won't receive this callback event unless he sets to redirect the process of clicking the Audio button in the meeting. For more details, see \link IMeetingUIElemConfiguration::RedirectClickAudioBTNEvent() \endlink.
	virtual void onAudioBtnClicked(AudioBtnClickedCallbackInfo info) = 0;
	
	/// \brief Callback event for clicking Audio Menu button in the meeting.
	/// \remarks The user won't receive this callback event unless he sets to redirect the process of clicking the Audio Menu button in the meeting. For more details, see \link IMeetingUIElemConfiguration::RedirectClickAudioMenuBTNEvent() \endlink.
	virtual void onAudioMenuBtnClicked() = 0;
	
};

/// \brief Meeting UI Controller Interface.
///
class IMeetingUIController
{
public:
	/// \brief Set meeting UI controller callback event handler. 
	/// \param pEvent A pointer to the IMeetingUIControllerEvent that receives the meeting user interface event. For more details, see \link IMeetingUIControllerEvent \endlink.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IMeetingUIControllerEvent* pEvent) = 0;

	/// \brief Show the chat dialog during the meeting.
	/// \param param Specifies the way to show the chat dialog. For more details, see \link ShowChatDlgParam \endlink structure. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError ShowChatDlg(ShowChatDlgParam& param) = 0;

	/// \brief Hide the chat dialog during the meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError HideChatDlg() = 0;

	/// \brief Enter full screen display mode.
	/// \param firstView True indicates to enable the full screen mode for the first view.
	/// \param secondView True indicates to enable the full screen mode for the second view if it is in the dual view mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnterFullScreen(bool firstView, bool secondView) = 0;

	/// \brief Exit the full screen display mode.
	/// \param firstView True indicates to exit the full screen mode for the first view.
	/// \param secondView True indicates to exit the full screen mode for the second view if it is in the dual view mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError ExitFullScreen(bool firstView, bool secondView) = 0;

	/// \brief Active the principal window of meeting and place it on top.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError BackToMeeting() = 0;

	/// \brief Switch to video wall mode. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SwitchToVideoWall() = 0;

	/// \brief Switch to the mode of showing the current speaker.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SwtichToAcitveSpeaker() = 0;

	/// \brief Move the floating video window.
	/// \param left Sets the left margin edge for the floating video window. Please use the coordinate of the screen.
	/// \param top Sets the top margin edge for the floating video window. Please use the coordinate of the screen.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError MoveFloatVideoWnd(int left, int top) = 0;

	/// \brief Enable or disable to display the floating sharing toolbar.
	/// \param bShow TRUE indicates to display the floating toolbar.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks This function works only in the share mode. 
	virtual SDKError ShowSharingToolbar(bool bShow) = 0;

	/// \brief Switch to current speaker mode on the floating window. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SwitchFloatVideoToActiveSpkMod() = 0;

	/// \brief Adjust the display mode of floating window. 
	/// \param type Specify the type of the floating video. For more details, see \link SDKFloatVideoType \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError ChangeFloatoActiveSpkVideoSize(SDKFloatVideoType type) = 0;

	/// \brief Switch to gallery view mode on the floating window. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SwitchFloatVideoToGalleryMod() = 0;

	/// \brief Display/hide the window which is used to display the list of the participants. 
	/// \param bShow TRUE indicates to display the list of the participants.
	/// \param [out] hParticipantsListWnd This function will return the window handle if the bShow value is set to TRUE and API calls successfully. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError ShowParticipantsListWnd(bool bShow, HWND& hParticipantsListWnd) = 0;

	/// \brief Display/hide the toolbar at the bottom of the meeting window. 
	/// \param bShow TRUE indicates to display the toolbar.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks This function does not work if the user sets to hide the toolbar via IMeetingUIElemConfiguration::SetBottomFloatToolbarWndVisibility().
	virtual SDKError ShowBottomFloatToolbarWnd(bool bShow) = 0;

	/// \brief Get the window handle of the meeting user interface.
	/// \param [out] hFirstView If the function succeeds, the parameter will save the window handle of the meeting user interface displayed by the first view.
	/// \param [out] hSecondView If the function succeeds, the parameter will save the window handle of the meeting user interface displayed by the second view.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError GetMeetingUIWnd(HWND& hFirstView, HWND& hSecondView) = 0;

	/// \brief Display the dialog to choose the audio to join the meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError ShowJoinAudioDlg() = 0;

	/// \brief Hide the dialog to choose the audio to join the meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError HideJoinAudioDlg() = 0;

	/// \brief Get the information in video wall mode.
	/// \param [out] videoWallPageInfoParam If the function succeeds, the parameter will save the current page index and the number of the pages. For more details, see \link VideoWallPageInfoParam \endlink structure.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError GetWallViewPageInfo(VideoWallPageInfoParam& videoWallPageInfoParam) = 0;

	/// \brief Show the video users on previous page or next page in video wall mode.
	/// \param bPageUp TRUE indicates to show the video users on previous page, FALSE next page.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks The function does not work if the window shows the first or last page. The return value is SDKErr_Success in this case.
	virtual SDKError ShowPreOrNextPageVideo(bool bPageUp) = 0;

	/// \brief Set the visibility of the green frame when sharing the application.	/// \param bShow TRUE indicates to display the frame. FALSE hide.	/// \return If the function succeeds, the return value is SDKErr_Success.	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError ShowSharingFrameWindows(bool bShow) = 0;

	/// \brief Determines the minimize state of the first view.
	/// \param [out] mode If the function succeeds, the parameter will save the display mode. For more details, see \link SDKMinimizeUIMode \endlink enum.
	/// \return TRUE indicates the minimize state. FALSE not.
	virtual bool IsMinimizeModeOfFristScreenMeetingUIWnd(SDKMinimizeUIMode& mode) = 0;

	/// \brief Change the display mode of the minimized meeting window for the first view.
	/// \param mode Specifies the minimized mode. For more details, see \link SDKMinimizeUIMode \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SwitchMinimizeUIMode4FristScreenMeetingUIWnd(SDKMinimizeUIMode mode) = 0;

	/// \brief Get the information whether the current view supports split screen mode or not. If supports, check it if it is already in the split screen mode.
	/// \param [out] info If the function succeeds, the parameter will save the configuration of split screen mode. For more details, see \link SplitScreenInfo \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError GetCurrentSplitScreenModeInfo(SplitScreenInfo& info) = 0;

	/// \brief Switch to the split screen mode or cancel.
	/// \param bSplit TRUE indicates to switch to the split screen mode. FALSE cancel.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///\remarks TRUE does not work if it is in the split screen mode. FALSE does not work if it is not the split screen mode.
	virtual SDKError SwitchSplitScreenMode(bool bSplit) = 0;

	/// \brief when someone else shares, and meeting window is not full screen. you can call the api to switch video & share display postion. 
	/// \param bToDisplayShare TRUE means to display share, otherwise video.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SwapToShowShareViewOrVideo(bool bToDisplayShare) = 0;

	/// \brief Determine if the meeting is displaying the sharing screen now.
	/// \param [out] bIsShare TRUE means is showing sharing screen, FALSE means is showing video.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError IsDisplayingShareViewOrVideo(bool& bIsShare) = 0;

	/// \brief Determine if the user can swap to show sharing screen or video now.
	/// \param [out] bCan TRUE means Can, otherwise not
	/// \return SDKErr_Success means success, otherwise not
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanSwapToShowShareViewOrVideo(bool& bCan) = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif