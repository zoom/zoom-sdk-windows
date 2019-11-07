/*!
* \file meeting_sharing_interface.h
* \brief Meeting Service Sharing Interface
* 
*/
#ifndef _MEETING_SHARING_INTERFACE_H_
#define _MEETING_SHARING_INTERFACE_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum SharingStatus
    \brief Sharing status.
    Here are more detailed structural descriptions..
*/
enum SharingStatus
{
	Sharing_Self_Send_Begin,///<Begin to share by the user himself.
	Sharing_Self_Send_End,///<Stop sharing by the user.
	Sharing_Other_Share_Begin,///<Others begin to share.
	Sharing_Other_Share_End,///<Others stop sharing.
	Sharing_View_Other_Sharing,///<View the sharing of others.
	Sharing_Pause,///<Pause sharing.
	Sharing_Resume,///<Resume sharing.
};

/*! \struct tagViewableShareSource
    \brief Visible shared source information.
    Here are more detailed structural descriptions..
*/
typedef struct tagViewableShareSource
{
	unsigned int userid;///<User ID.
	bool isShowingInFirstView;///<Display or not on the primary view.
	bool isShowingInSecondView;///<Display or not on the secondary view. 
	bool isCanBeRemoteControl;///<Enable or disable the remote control.
	tagViewableShareSource()
	{
		userid = 0;
		isShowingInFirstView = false;
		isShowingInSecondView = false;
		isCanBeRemoteControl = false;
	}
}ViewableShareSource;

/*! \enum ShareType 
    Type of current sharing received by the user.
    Here are more detailed structural descriptions..
*/
enum ShareType
{
	SHARE_TYPE_UNKNOWN,///<Type unknown.
	SHARE_TYPE_AS,///<Type of sharing the application.
	SHARE_TYPE_DS,///<Type of sharing the desktop.
	SHARE_TYPE_WB,///<Type of sharing the white-board.
	SHARE_TYPE_AIRHOST,///<Type of sharing data from the device connected WIFI. 
	SHARE_TYPE_CAMERA,///<Type of sharing the camera.
	SHARE_TYPE_DATA,///<Type of sharing the data.
};
/*! \enum AdvanceShareOption 
    Additional type of current sharing sent to others.
    Here are more detailed structural descriptions.
*/
enum AdvanceShareOption
{
	AdvanceShareOption_ShareFrame,///<Type of sharing a selected area of desktop.
	AdvanceShareOption_PureComputerAudio,///<Type of sharing only the computer audio.
	AdvanceShareOption_ShareCamera,///<Type of sharing the camera.
};
/*! \struct tagShareInfo
    \brief Information of current sharing.
    Here are more detailed structural descriptions.
*/
enum MultiShareOption
{
	Enable_Multi_Share = 0, ///<Multi-participants can share simultaneously.
	Enable_Only_HOST_Start_Share, ///<Only host can share at a time.
	Enable_Only_HOST_Grab_Share, ///<One participant can share at a time, during sharing only host can start a new sharing and the previous sharing will be replaced.
	Enable_All_Grab_Share, ///<One participant can share at a time, during sharing everyone can start a new sharing and the previous sharing will be replaced.
};

typedef struct tagShareInfo
{
	ShareType eShareType;///<Type of sharing, see \link ShareType \endlink enum.
	union
	{
		HWND hwndSharedApp;///<Handle of sharing application or white-board. It is invalid unless the value of the eShareType is SHARE_TYPE_AS or SHARE_TYPE_WB.
		const wchar_t* monitorID;///<The ID of screen to be shared. It is invalid unless the value of the eShareType is SHARE_TYPE_DS.
	}ut;
	tagShareInfo()
	{
		eShareType = SHARE_TYPE_UNKNOWN;
		memset(&ut, 0, sizeof(ut));
	}
}ShareInfo;

/// \brief Reminder handler of switching from multi-share to single share.
///
class IShareSwitchMultiToSingleConfirmHandler
{
public:
	/// \brief Cancel to switch multi-share to single share. All sharing will be remained.
	virtual SDKError Cancel() = 0;

	/// \brief Switch multi-share to single share. All sharing will be remained.
	virtual SDKError Confirm() = 0;

	virtual ~IShareSwitchMultiToSingleConfirmHandler() {};
};

/// \brief Callback event of meeting share controller.
///
class IMeetingShareCtrlEvent
{
public:
	/// \brief Callback event of the changed sharing status. 
	/// \param status The values of sharing status. For more details, see \link SharingStatus \endlink enum.
	/// \param userId Sharer ID. 
	/// \remarks The userId changes according to the status value. When the status value is the Sharing_Self_Send_Begin or Sharing_Self_Send_End, the userId is the user own ID. Otherwise, the value of userId is the sharer ID.
	virtual void onSharingStatus(SharingStatus status, unsigned int userId) = 0;

	/// \brief Callback event of locked share status.
	/// \param bLocked TRUE indicates that it is locked. FALSE unlocked.
	virtual void onLockShareStatus(bool bLocked) = 0;

	/// \brief Callback event of changed sharing information.
	/// \param shareInfo Sharing information. For more details, see \link ShareInfo \endlink structure.
	virtual void onShareContentNotification(ShareInfo& shareInfo) = 0;

	/// \brief Callback event of switching multi-participants share to one participant share.
	/// \param handler_ An object pointer used by user to complete all the related operations. For more details, see \link IShareSwitchMultiToSingleConfirmHandler \endlink.
	virtual void onMultiShareSwitchToSingleShareNeedConfirm(IShareSwitchMultiToSingleConfirmHandler* handler_) = 0;		
};

/// \brief Meeting share controller interface.
///
class IMeetingShareController
{
public:
	/// \brief Set meeting share controller callback event handler.
	/// \param pEvent A pointer to the IMeetingShareCtrlEvent that receives sharing event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IMeetingShareCtrlEvent* pEvent) = 0;
	
	/// \brief Share the specified application.
	/// \param hwndSharedApp Specify the window handle of the application to be shared. If the hwndSharedApp can't be shared, the return value is the SDKERR_INVALID_PARAMETER error code. If the hwndSharedApp is NULL, the primary monitor will be shared. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError StartAppShare(HWND hwndSharedApp) = 0;

	/// \brief Share the specified monitor.
	/// \param monitorID Specify the monitor ID to be shared. You may get the value via EnumDisplayMonitors System API. If the monitorID is NULL, the primary monitor will be shared. For more details, see szDevice in MONITORINFOEX structure.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError StartMonitorShare(const wchar_t* monitorID) = 0;

	/// \brief Start sharing with mobile device. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError StartAirPlayShare() = 0;

	/// \brief Start sharing with White board.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///You need to draw your own annotation bar for custom mode when you get the onShareContentNotification with SHARE_TYPE_WB.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError StartWhiteBoardShare() = 0;

	/// \brief A dialog box pops up that enable the user to choose the application or window to share.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid only for ZOOM style mode. 
	virtual SDKError ShowSharingAppSelectWnd() = 0;
	
	/// \brief Determine if the specified ADVANCE SHARE OPTION is supported. 
	/// \param option_ The ADVANCE SHARE OPTION to be determined. For more information, see \link AdvanceShareOption \endlink enum.
	/// \return If it is supported, the return value is SDKErr_Success.
	///Otherwise not. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError IsSupportAdvanceShareOption(AdvanceShareOption option_) = 0;
	
	/// \brief Start sharing frame.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError StartShareFrame() = 0;

	/// \brief Start sharing only the computer audio.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.	
	virtual SDKError StartSharePureComputerAudio() = 0;
	
	/// \brief Start sharing camera.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.	
	virtual SDKError StartShareCamera() = 0;
	
	/// \brief Stop the current sharing.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError StopShare() = 0;

	/// \brief Block the window when sharing in full screen.
	///Once the function is called, you need to redraw the window to take effect.
	/// \param bBlock TRUE indicates to block the window when sharing in full screen.
	/// \param hWnd Specify the window to be blocked.
	/// \param bChangeWindowStyle If it is FALSE, please call this function either after the StartMonitorShare is called or when you get the callback event of the onSharingStatus with Sharing_Self_Send_Begin. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid only for ZOOM style user interface mode.
	///It is not suggested to use this function for it will change the property of the window and leads to some unknown errors.
	///It won't work until the IMeetingShareController::StartMonitorShare() is called if the bChangeWindowStyle is set to FALSE. 
	///If you want to use the specified window during the share, you need to redraw the window.
	///Set the bBlock to FALSE before ending the share and call the function for the specified window to resume the property of the window.
	virtual SDKError BlockWindowFromScreenshare(bool bBlock, HWND hWnd, bool bChangeWindowStyle = true) = 0;

	/// \deprecated This interface is deprecated because Zoom meeting doesn't support this feature anymore. Please stop using it. 
	/// \brief Lock the current meeting sharing.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError LockShare() = 0;

	/// \deprecated This interface is deprecated because Zoom meeting doesn't support this feature anymore. Please stop using it.
	/// \brief Unlock the current meeting sharing.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError UnlockShare() = 0;

	/// \brief Switch to auto-adjust mode from sharing window by the function when watching the share on the specified view.
	/// \param type Specify the view you want to set, either primary or secondary. For more details, see \link SDKViewType \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid only for ZOOM style user interface mode.
	virtual SDKError SwitchToFitWindowModeWhenViewShare(SDKViewType type) = 0;

	/// \brief Switch the window size to originality by the function when watching the share on the specified view.
	/// \param type Specify the view you want to set, either primary or secondary. For more details, see \link SDKViewType \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid only for ZOOM style user interface mode.
	virtual SDKError SwitchToOriginalSizeModeWhenViewShare(SDKViewType type) = 0;

	/// \brief Pause the current sharing.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError PauseCurrentSharing() = 0;

	/// \brief Resume the current sharing.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError ResumeCurrentSharing() = 0;

	/// \brief Get the list of all the sharers in the current meeting.
	/// \return If the function succeeds, the return value is list of user ID.
	///If the function fails, the return value is NULL.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual IList<unsigned int >* GetViewableShareSourceList() = 0;

	/// \brief Get the sharing information from the specified sharer.
	/// \param userid Specify the user ID that you want to get his sharing information.
	/// \param [out] shareSource Store the viewable sharing information. For more details, see \link ViewableShareSource \endlink structure.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError GetViewabltShareSourceByUserID(unsigned int userid, ViewableShareSource& shareSource) = 0;

	/// \brief View the share from the specified user.
	/// \param userid Specify the user ID that you want to view his share. 
	/// \param type Specify the view that you want to display the share, either primary or secondary. For more details, see \link SDKViewType \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid only for ZOOM style user interface mode.
	virtual SDKError ViewShare(unsigned int userid, SDKViewType type) = 0;

	/// \brief Display the dialog of sharing configuration.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid only for ZOOM style user interface mode.
	virtual SDKError ShowShareOptionDialog() = 0;

	/// \brief Determine if it is able to share. 
	/// \return Enable or disable to start sharing.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual bool CanStartShare() = 0;

	/// \brief Determine if the sharing is locked. 
	/// \param bLocked TRUE indicates that the sharing is locked. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError IsShareLocked(bool& bLocked) = 0;

	/// \brief Determine if the sound of the computer in the current sharing is supported. 
	/// \param [out] bCurEnableOrNot The parameter is valid only when the return value is TRUE. And TRUE indicates to sharing the sound of the computer for the moment.
	/// \return If it is TRUE, the value of bCurEnableOrNot can be used to check whether the computer sound is supported or not when sharing. FALSE not.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual bool IsSupportEnableShareComputerSound(bool& bCurEnableOrNot) = 0;

	/// \brief Determine whether to optimize the video fluidity when sharing in full screen mode. 
	/// \param bCurEnableOrNot This parameter is valid only when the return value is TRUE. And TRUE indicates to optimize video for the moment. 
	/// \return If it is TRUE, the value of bCurEnableOrNot can be used to check whether to support optimize video fluidity or not. FALSE not.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual bool IsSupportEnableOptimizeForFullScreenVideoClip(bool& bCurEnableOrNot) = 0;

	/// \brief Set to enable or disable the audio when sharing.
	/// \param bEnable TRUE indicates to enable. FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError EnableShareComputerSound(bool bEnable) = 0;

	/// \brief Set to enable the video optimization when sharing. 
	/// \param bEnable TRUE indicates to enable. FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual SDKError EnableOptimizeForFullScreenVideoClip(bool bEnable) = 0;

	/// \brief Set the options for multi-participants share.
	/// \param [in] shareOption New options for sharing, see \link MultiShareOption \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetMultiShareSettingOptions(MultiShareOption shareOption) = 0;

	virtual SDKError GetMultiShareSettingOptions(MultiShareOption& shareOption) = 0;

	/// \brief Determine whether can switch to next camera, when share camera. 
	/// \param [Out] bCan, if bCan is true it means you can switch, else can not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanSwitchToShareNextCamera(bool& bCan) = 0;

	/// \brief switch to next camera, when you are sharing the camera.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SwitchToShareNextCamera() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif