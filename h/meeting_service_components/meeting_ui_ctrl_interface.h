/*!
* \file meeting_ui_ctrl_interface.h
* \brief UI Controller of Meeting Service Interface
* 
*/
#ifndef _MEETING_UI_CTRL_INTERFACE_H_
#define _MEETING_UI_CTRL_INTERFACE_H_
#include "..\zoom_sdk_def.h"

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum SDKMeetingUIType
    \brief The type of meeting ui.
    A more detailed struct description.
*/
enum SDKMeetingUIType
{
	SDK_Meeting_UI_None,
	SDK_Meeting_UI_VideoWall_Mode,
	SDK_Meeting_UI_ActiveRender_Mode,
};

/*! \struct tagVideoWallPageInfoParam
    \brief The information of video wall page.
    A more detailed struct description.
*/
typedef struct tagVideoWallPageInfoParam
{
	int nCurrentPage;
	int nTotalPages;
}VideoWallPageInfoParam;

/*! \struct tagShowChatDlgParam
    \brief Show meeting chat dialog Parameter.
    A more detailed struct description.
*/
typedef struct tagShowChatDlgParam
{
	HWND hParent;///< Parent window handle
	RECT rect;///< chat dialog position
	HWND hChatWnd;///< return chat windows handle
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
    \brief The type of float video ui.
    A more detailed struct description.
*/
enum SDKFloatVideoType
{
	FLOATVIDEO_List,
	FLOATVIDEO_Small,
	FLOATVIDEO_Large,
	FLOATVIDEO_Minimize,
};

/*! \enum SDKMinimizeUIMode
    \brief The type of minimize UI mode.
    A more detailed struct description.
*/
enum SDKMinimizeUIMode
{
	MinimizeUIMode_NONE,
	MinimizeUIMode_SHARE,
	MinimizeUIMode_VIDEO,
	MinimizeUIMode_ACTIVESPEAKER,
};

/*! \struct tagSplitScreenInfo
    \brief The information of split screen mode.
    A more detailed struct description.
*/
typedef struct tagSplitScreenInfo
{
	bool bSupportSplitScreen;
	bool bInSplitScreenMode;
	tagSplitScreenInfo()
	{
		bSupportSplitScreen = false;
		bInSplitScreenMode = false;
	}
}SplitScreenInfo;

/// \brief Meeting UI Controller Callback Event
///
class IMeetingUIControllerEvent
{
public:
	virtual void onInviteBtnClicked() = 0;
	virtual void onStartShareBtnClicked() = 0;
	virtual void onEndMeetingBtnClicked() = 0;
};

/// \brief Meeting UI Controller Interface
///
class IMeetingUIController
{
public:
	/// \brief Set meeting ui controller callback event
	/// \param pEvent A pointer to a IMeetingUIControllerEvent* that receives meeting ui event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingUIControllerEvent* pEvent) = 0;

	/// \brief Show meeting chat dialog
	/// \param param Specifies how to show chat dialog.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ShowChatDlg(ShowChatDlgParam& param) = 0;

	/// \brief Hide meeting chat dialog
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError HideChatDlg() = 0;

	/// \brief Enter full screen mode
	/// \param firstView Specifies the first monitor enter full screen mode or not.
	/// \param secondView Specifies the second monitor enter full screen mode or not, if enable dual monitor mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnterFullScreen(bool firstView, bool secondView) = 0;

	/// \brief Exit full screen mode
	/// \param firstView Specifies the first monitor exit full screen mode or not.
	/// \param secondView Specifies the second monitor exit full screen mode or not, if enable dual monitor mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ExitFullScreen(bool firstView, bool secondView) = 0;

	/// \brief Switch to video wall view
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SwitchToVideoWall() = 0;

	/// \brief Switch to active speaker view
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SwtichToAcitveSpeaker() = 0;

	/// \brief Move Float Video window
	/// \param left Specifies The left position of the Float Video window.
	/// \param top Specifies The top position of the Float Video window.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError MoveFloatVideoWnd(int left, int top) = 0;

	/// \brief Show sharing float toolbar
	/// \param bShow Specifies the sharing float toolbar show or not
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ShowSharingToolbar(bool bShow) = 0;

	/// \brief Switch float video bar to active speaker view
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SwitchFloatVideoToActiveSpkMod() = 0;

	/// \brief Change float active speaker video bar size
	/// \param type Specifies the float video panel view type.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ChangeFloatoActiveSpkVideoSize(SDKFloatVideoType type) = 0;

	/// \brief Switch float video bar to gallery view
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SwitchFloatVideoToGalleryMod() = 0;

	/// \brief Show Participants List window
	/// \param bShow Specifies the participants List Window show or not
	/// \param hParticipantsListWnd if bShow is true,and api call success, will return the handle of the participants List window
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ShowParticipantsListWnd(bool bShow, HWND& hParticipantsListWnd) = 0;

	/// \brief Show bottom float toolbar window
	/// \param bShow Specifies the bottom float toolbar window show or not
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ShowBottomFloatToolbarWnd(bool bShow) = 0;

	/// \brief Retrieves the handle of the meeting UI window
	/// \param hFirstView the variable where the first view handle of the meeting UI window is returned.
	/// \param hSecondView the variable where the second view handle of the meeting UI window is returned.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GetMeetingUIWnd(HWND& hFirstView, HWND& hSecondView) = 0;

	/// \brief Show join audio dialog
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ShowJoinAudioDlg() = 0;

	/// \brief Hide join audio dialog
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError HideJoinAudioDlg() = 0;

	/// \brief get page info on video wall mode.
	/// \param videoWallPageInfoParam store current page index and total pages.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GetWallViewPageInfo(VideoWallPageInfoParam& videoWallPageInfoParam) = 0;

	/// \brief show previous or next page video user on video wall mode.
	/// \param bPageUp specifies previous or next page.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ShowPreOrNextPageVideo(bool bPageUp) = 0;

	/// \brief show or hide the sharing frame window of the application which you shared.
	/// \param bShow specifies show or hide.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ShowSharingFrameWindows(bool bShow) = 0;

	/// \brief Determines the minimize state of the meeting ui window on frist screen.
	/// \param mode return the minimize mode if the meeting ui window on frist screen is in the minimize state.
	/// \return true or false
	virtual bool IsMinimizeModeOfFristScreenMeetingUIWnd(SDKMinimizeUIMode& mode) = 0;

	/// \brief Change the minimize mode if the meeting ui window on frist screen is in the minimize state. 
	/// \param mode specifies the minimize mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SwitchMinimizeUIMode4FristScreenMeetingUIWnd(SDKMinimizeUIMode mode) = 0;

	/// \brief Get information of current split screen mode
	/// \param info store the information of current split screen mode .
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GetCurrentSplitScreenModeInfo(SplitScreenInfo& info) = 0;

	/// \brief Switch split screen mode or not when you view share and don't enable dual-monitor mode.
	/// \param bSplit split screen mode or not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SwitchSplitScreenMode(bool bSplit) = 0;
};

END_ZOOM_SDK_NAMESPACE
#endif