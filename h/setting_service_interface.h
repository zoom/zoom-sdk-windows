/*!
* \file setting_service_interface.h
* \brief Setting Service Interface
* 
*/
#ifndef _SETTING_SERVICE_INTERFACE_H_
#define _SETTING_SERVICE_INTERFACE_H_
#include "zoom_sdk_def.h"
/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Camera device information Interface
///
class ICameraInfo
{
public:
	/// \brief Get camera device id
	/// \return If the function succeeds, the return value is camera device id.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetDeviceId() = 0;

	/// \brief Get camera device name
	/// \return If the function succeeds, the return value is camera device name.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetDeviceName() = 0;

	/// \brief Selected device flag
	/// \return If the return value is true, this device is selected.
	virtual bool IsSelectedDevice() = 0;
};

/*! \struct tagShowChatDlgParam
    \brief Show meeting chat dialog Parameter.
    A more detailed struct description.
*/
typedef struct tagShowSettingDlgParam
{
	HWND hParent;///< Parent window handle
	int top;///< setting dialog top position
	int left;///< setting dialog left position
	HWND hSettingWnd;///< return setting dialog handle
	bool bShow;///< show or not
	tagShowSettingDlgParam()
	{
		hParent = NULL;
 		top = 0;
		left = 0;
		hSettingWnd = NULL;
		bShow = true;
	}
}ShowSettingDlgParam;

/// \brief Meeting setting Interface
///
class ISettingService
{
public:
	/// \brief Get camera device list
	/// \return If the function succeeds, the return value is camera device list pointer.
	///If the function fails, the return value is NULL.
	virtual IList<ICameraInfo* >* GetCameraList() = 0;

	/// \brief Select camera device
	/// \param deviceId Specifies which device to select.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SelectCamera(const wchar_t* deviceId) = 0;

	/// \brief Enable or disable dual screen mode
	/// \param bEnable Specifies enable or disable dual screen mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableDualScreenMode(bool bEnable) = 0;

	/// \brief Enable or disable auto join audio when join meeting
	/// \param bEnable Specifies enable or disable dual screen mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAutoJoinAudio(bool bEnable) = 0;

	/// \brief turn off or on aero mode in screen sharing
	/// \param bEnable Specifies turn off or on aero mode in screen sharing.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	///Just support windows 7.
	virtual SDKError TurnOffAeroModeInSharing(bool bTurnoff) = 0;

	/// \brief Set the recording path in setting dialog.
	/// \param szPath Specifies the path of recording.
	/// \return If the function succeeds, the return value is camera device list pointer.
	///If the function fails, the return value is NULL.
	virtual SDKError SetRecordingPath(const wchar_t* szPath) = 0;

	/// \brief Show meeting setting dialog
	/// \param param Specifies how to show chat dialog.
	/// \return If the function succeeds, the return value is camera device list pointer.
	///If the function fails, the return value is NULL.
	virtual SDKError ShowSettingDlg(ShowSettingDlgParam& param) = 0;

	/// \brief Hide meeting setting dialog
	/// \return If the function succeeds, the return value is camera device list pointer.
	///If the function fails, the return value is NULL.
	virtual SDKError HideSettingDlg() = 0;

	/// \brief Enable or disable auto fit to window when view sharing content.
	/// \param bEnable Specifies enable or disable auto fit to window when view sharing content.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAutoFitToWindowWhenViewSharing(bool bEnable) = 0;

	/// \brief Enable or disable auto enter full screen video mode when join meeting.
	/// \param bEnable Specifies enable or disable auto enter full screen video mode when join meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable) = 0;

};
END_ZOOM_SDK_NAMESPACE
#endif