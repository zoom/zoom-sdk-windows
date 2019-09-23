/*!
* \file meeting_sharing_interface.h
* \brief Sharing of Meeting Service Interface
* 
*/
#ifndef _MEETING_SHARING_INTERFACE_H_
#define _MEETING_SHARING_INTERFACE_H_
#include "..\zoom_sdk_def.h"

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum SharingStatus
    \brief Sharing status.
    A more detailed struct description.
*/
enum SharingStatus
{
	Sharing_Self_Send_Begin,
	Sharing_Self_Send_End,
	Sharing_Other_Share_Begin,
	Sharing_Other_Share_End,
	Sharing_View_Other_Sharing,
	Sharing_Pause,
	Sharing_Resume,
};

/*! \struct tagViewableShareSource
    \brief Viewable share source info.
    A more detailed struct description.
*/
typedef struct tagViewableShareSource
{
	unsigned int userid;
	bool isShowingInFirstView;
	bool isShowingInSecondView;
	bool isCanBeRemoteControl;
	tagViewableShareSource()
	{
		userid = 0;
		isShowingInFirstView = false;
		isShowingInSecondView = false;
		isCanBeRemoteControl = false;
	}
}ViewableShareSource;

/*! \enum Type of current sharing.
    A more detailed struct description.
*/
enum ShareType
{
	SHARE_TYPE_UNKNOWN, //unknown
	SHARE_TYPE_AS,	//application share
	SHARE_TYPE_DS,	//desktop share
	SHARE_TYPE_WB,	//whiteboard share
	SHARE_TYPE_AIRHOST,	//mobile device from PC
	SHARE_TYPE_CAMERA,	//camera share
	SHARE_TYPE_DATA,	//data share
};

/*! \struct tagShareInfo
    \brief Information of current sharing.
    A more detailed struct description.
*/
typedef struct tagShareInfo
{
	ShareType eShareType;  //share type, refer to ShareType
	union
	{
		HWND hwndSharedApp;  //handle of sharing application or whiteboard, it is valid only when eShareType is SHARE_TYPE_AS or SHARE_TYPE_WB
		const wchar_t* monitorID;  //monitor id of sharing desktop, it is valid only when eShareType is SHARE_TYPE_DS
	}ut;
	tagShareInfo()
	{
		eShareType = SHARE_TYPE_UNKNOWN;
		memset(&ut, 0, sizeof(ut));
	}
}ShareInfo;

/// \brief Meeting share controller callback event
///
class IMeetingShareCtrlEvent
{
public:
	/// \brief Sharing status notify callback
	/// \param status Sharing status value.
	/// \param userId Sharing user id.
	virtual void onSharingStatus(SharingStatus status, unsigned int userId) = 0;

	/// \brief lock share status notify call back 
	/// \param bLocked specify if sharing is locked.
	virtual void onLockShareStatus(bool bLocked) = 0;

	/// \brief Sharing content changed callback
	/// \param shareInfo Sharing information such as, share type, handle of shared app and monitor id, refer to ShareInfo.
	virtual void onShareContentNotification(ShareInfo& shareInfo) = 0;	
};

/// \brief Meeting share controller interface
///
class IMeetingShareController
{
public:
	/// \brief Set meeting share controller callback event
	/// \param pEvent A pointer to a IMeetingShareCtrlEvent* that receives sharing event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingShareCtrlEvent* pEvent) = 0;
	/// \brief Start application share
	/// \param hwndSharedApp Specifies which the window is to be shared.
	///if hwndSharedApp can't be shared, return SDKERR_INVALID_PARAMETER error code.if hwndSharedApp is NULL, will show select application dialog.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \support for zoom style and customized style ui mode
	virtual SDKError StartAppShare(HWND hwndSharedApp) = 0;

	/// \brief Start monitor share
	/// \param monitorID Specifies which the monitor is to be shared.Using EnumDisplayMonitors System api to get this value.
	/// refer to szDevice in MONITORINFOEX struct. if monitorID is NULL, will show select application dialog. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \support for zoom style and customized style ui mode
	virtual SDKError StartMonitorShare(const wchar_t* monitorID) = 0;

	/// \brief Start share with IOS device.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \support for zoom style and customized style ui mode
	virtual SDKError StartAirPlayShare() = 0;

	/// \brief Start share with White board.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	///If you use our sdk in customized mode, please draw your own annotate bar when you got onShareContentNotification with SHARE_TYPE_WB
	/// \support for zoom style and customized style ui mode
	virtual SDKError StartWhiteBoardShare() = 0;

	/// \brief Show sharing app select window.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \only for zoom style ui mode
	virtual SDKError ShowSharingAppSelectWnd() = 0;

	/// \brief Stop current sharing
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \support for zoom style and customized style ui mode
	virtual SDKError StopShare() = 0;

	/// \brief Block window form screen share. 
	///This api will change the window's property.we don't suggest to use.
	///After call this api, you need to redraw this window to take effect.
	/// \param bBlock block window from screen share or not.
	/// \param hWnd Specifies which window to be blocked.
	/// \param bChangeWindowStyle if false, please call this api after StartMonitorShare api 
	/// or after you got onSharingStatus  callback with Sharing_Self_Send_Begin.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \only for zoom style ui mode
	virtual SDKError BlockWindowFromScreenshare(bool bBlock, HWND hWnd, bool bChangeWindowStyle = true) = 0;

	/// \brief Lock current meeting's sharing
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \support for zoom style and customized style ui mode
	virtual SDKError LockShare() = 0;

	/// \brief Lock current meeting's sharing
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \support for zoom style and customized style ui mode
	virtual SDKError UnlockShare() = 0;

	/// \brief Switch the sharing view window to fit window mode when view sharing.
	/// \param type Specifies which view you want to set, first monitor or second monitor.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \only for zoom style ui mode
	virtual SDKError SwitchToFitWindowModeWhenViewShare(SDKViewType type) = 0;

	/// \brief Switch the sharing view window to original size mode when view sharing.
	/// \param type Specifies which view you want to set, first monitor or second monitor.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \only for zoom style ui mode
	virtual SDKError SwitchToOriginalSizeModeWhenViewShare(SDKViewType type) = 0;

	/// \brief Pause current sharing
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \support for zoom style and customized style ui mode
	virtual SDKError PauseCurrentSharing() = 0;

	/// \brief Resume current sharing
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \support for zoom style and customized style ui mode
	virtual SDKError ResumeCurrentSharing() = 0;

	/// \brief get current viewable share source list.
	/// \return If the function succeeds, the return value is the viewable share source user id list.
	///If the function fails, the return value is NULL.
	/// \support for zoom style and customized style ui mode
	virtual IList<unsigned int >* GetViewableShareSourceList() = 0;

	/// \brief get viewable share source by userid.
	/// \param userid Specifies which viewable share source info you want to get.
	/// \param shareSource store the viewable share source info
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \support for zoom style and customized style ui mode
	virtual SDKError GetViewabltShareSourceByUserID(unsigned int userid, ViewableShareSource& shareSource) = 0;

	/// \brief view share by userid.
	/// \param userid Specifies who you want to view.
	/// \param type Specifies which view you want to view the sharing, first monitor or second monitor.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \only for zoom style ui mode
	virtual SDKError ViewShare(unsigned int userid, SDKViewType type) = 0;

	/// \brief show share option dialog.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \only for zoom style ui mode
	virtual SDKError ShowShareOptionDialog() = 0;

	/// \brief can start share or not.
	/// \return can start share or not.
	/// \support for zoom style and customized style ui mode
	virtual bool CanStartShare() = 0;

	/// \brief query if sharing is locked.
	/// \param bLocked store if sharing is locked.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \support for zoom style and customized style ui mode
	virtual SDKError IsShareLocked(bool& bLocked) = 0;

	/// \brief query sharing support share computer sound or not.
	/// \param bCurEnableOrNot store the enable or not flag if support share computer sound.
	/// \return support share computer sound or not.
	/// \support for zoom style and customized style ui mode
	virtual bool	 IsSupportEnableShareComputerSound(bool& bCurEnableOrNot) = 0;

	/// \brief query sharing support optimize for full screen video clip or not.
	/// \param bCurEnableOrNot store the enable or not flag if optimize for full screen video clip.
	/// \return support optimize for full screen video clip or not.
	/// \support for zoom style and customized style ui mode
	virtual bool	 IsSupportEnableOptimizeForFullScreenVideoClip(bool& bCurEnableOrNot) = 0;

	/// \brief enable share computer sound.
	/// \param bEnable enable or not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \support for zoom style and customized style ui mode
	virtual SDKError EnableShareComputerSound(bool bEnable) = 0;

	/// \brief enable optimize for full screen video clip.
	/// \param bEnable enable or not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \support for zoom style and customized style ui mode
	virtual SDKError EnableOptimizeForFullScreenVideoClip(bool bEnable) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif