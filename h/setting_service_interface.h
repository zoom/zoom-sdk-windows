/*!
* \file setting_service_interface.h
* \brief Configure Service Interface.
* 
*/
#ifndef _SETTING_SERVICE_INTERFACE_H_
#define _SETTING_SERVICE_INTERFACE_H_
#include "zoom_sdk_def.h"
#include "zoom_sdk_util_define.h"

BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Camera device information interface.
///
class ICameraInfo
{
public:
	/// \brief Get the camera device ID.
	/// \return If the function succeeds, the return value is the camera device ID.
	///Otherwise failed, returns NULL.
	virtual const wchar_t* GetDeviceId() = 0;

	/// \brief Get the camera device name
	/// \return If the function succeeds, the return value is the camera device name.
	///Otherwise failed, returns NULL.
	virtual const wchar_t* GetDeviceName() = 0;

	/// \brief Determine if the current device is selected to use.
	/// \return TRUE indicates that the current device is selected.
	virtual bool IsSelectedDevice() = 0;

	virtual ~ICameraInfo() {};
};

/// \brief Microphone device information interface.
///
class IMicInfo
{
public:
	/// \brief Get the microphone device ID.
	/// \return If the function succeeds, the return value is the camera device ID.
	///Otherwise failed, returns NULL.
	virtual const wchar_t* GetDeviceId() = 0;

	/// \brief Get the microphone device name.
	/// \return If the function succeeds, the return value is the camera device name.
	///Otherwise failed, returns NULL.
	virtual const wchar_t* GetDeviceName() = 0;

	/// \brief Determine if the current device is selected to use.
	/// \return TRUE indicates that the current device is selected.
	virtual bool IsSelectedDevice() = 0;

	virtual ~IMicInfo() {};
};

/// \brief Audio speaker device information interface.
///
class ISpeakerInfo
{
public:
	/// \brief Get the speaker device ID.
	/// \return If the function succeeds, the return value is the camera device ID.
	///Otherwise failed, returns NULL.
	virtual const wchar_t* GetDeviceId() = 0;

	/// \brief Get the speaker device name.
	/// \return If the function succeeds, the return value is speaker device name.
	///Otherwise failed, returns NULL.
	virtual const wchar_t* GetDeviceName() = 0;

	/// \brief Determine if the current device is selected to use.
	/// \return TRUE indicates that the current device is selected.
	virtual bool IsSelectedDevice() = 0;

	virtual ~ISpeakerInfo() {};
};

/*! \enum SettingTabPage
    \brief Specify the shown tab page at the top of the displayed setting dialog.
    Here are more detailed structural descriptions.
*/ 
enum SettingTabPage
{
	SettingTabPage_General,///<General setting page.
	SettingTabPage_Audio,///<Audio setting page.
	SettingTabPage_Video,///<Video setting page.
};
/*! \struct tagShowChatDlgParam
    \brief Display the parameter of the meeting chat dialog.
    Here are more detailed structural descriptions.
*/
typedef struct tagShowSettingDlgParam
{
	HWND hParent;///<Parent window handle.
	int top;///<The Y-axis value of the top-left corner of the dialog uses the coordinate system of the monitor.
	int left;///<The X-axis value of the top-left corner of the dialog uses the coordinate system of the monitor.
	HWND hSettingWnd;///<Window handle of the dialog setting.
	bool bShow;///<Enable to display or nor.
	SettingTabPage eTabPageType; ///<The tab page shown at the top of the displayed setting dialog.
	tagShowSettingDlgParam()
	{
		hParent = NULL;
 		top = 0;
		left = 0;
		hSettingWnd = NULL;
		bShow = true;
		eTabPageType = SettingTabPage_General;
	}
}ShowSettingDlgParam;

/*! \struct tagSettingDlgShowTabPageOption
    \brief Define the strategy to show the tab pages in the setting dialog.
    Here are more detailed structural descriptions.
*/
typedef struct tagSettingDlgShowTabPageOption
{
	bool bShowGeneral;///<True indicates to show general page
	bool bShowVideo; ///<True indicates to show video page
	bool bShowAudio;///<True indicates to show audio page
	bool bShowShareScreen; ///<True indicates to show share screen page
	bool bShowVirtualBackGround;///<True indicates to show virtual background page
	bool bSHowRecording;///<True indicates to show recording page
	bool bShowAdvancedFeature;///<True indicates to show advance feature page
	bool bShowStatistics;///<True indicates to show staticstics page
	bool bShowFeedback;///<True indicates to show feed back page
	bool bShowKeyboardShortcuts;///<True indicates to show keyboard shortcuts page
	bool bShowAccessibility;///<True indicates to show accessibility page
	tagSettingDlgShowTabPageOption()
	{
		bShowGeneral = true;
		bShowVideo = true;
		bShowAudio = true;
		bShowShareScreen = true;
		bShowVirtualBackGround = true;
		bSHowRecording = true;
		bShowStatistics = true;
		bShowAccessibility = true;
		bShowKeyboardShortcuts = true;
		bShowAdvancedFeature = false;
		bShowFeedback = false;
	}

}SettingDlgShowTabPageOption;

/*! \enum SDK_TESTMIC_STATUS
    \brief Notify the status of the mic when testing.
    Here are more detailed structural descriptions.
*/
typedef	enum
{
	enuCanTest = 0,///<Test the mic via TestMicStartRecording. It is useless to call TestMicStopTesting/TestMicPlayRecording in this status.
	enuMicRecording,///<Test the mic via TestMicStopTesting/TestMicPlayRecording. It is useless to call TestMicStartRecording in this status.
	enuCanPlay,///<Test the mic via TestMicStopTesting/TestMicPlayRecording. It is useless call TestMicStartRecording in this status.
} SDK_TESTMIC_STATUS;

/// \brief Audio device testing callback events.
//
class ITestAudioDeviceHelperEvent
{
public:
	/// \brief Notify the current mic or speaker volume when testing.
	/// \param MicVolume Specify the volume of the mic.
	/// \param SpkVolume Specify the volume of the speaker.
	virtual void OnMicSpkVolumnChanged(unsigned int MicVolume, unsigned int SpkVolume) = 0;

	/// \brief Notify that either mic device or speaker device is not found.
	/// \param bMicOrSpk TRUE indicates no mic device. False no speaker device.
	virtual void OnNoAudioDeviceIsUseful(bool bMicOrSpk) = 0; 

	/// \brief Notify the mic status when testing.
	/// \param status The mic status. For more details, see \link SDK_TESTMIC_STATUS \endlink enum.
	/// \param bHandled The SDK default logic won't handle the mic status the value is set to be TRUE.
	///For more details, see \link SDK_TESTMIC_STATUS \endlink.
	/// \remarks The enuCanPlay status indicates that the SDK has recorded the microphone sound for the longest time (6 seconds). If the bHandled is not set to TURE hereby, the SDK will call TestMicStopTesting() itself. 
	virtual void OnTestMicStatusChanged(SDK_TESTMIC_STATUS status,bool& bHandled) = 0; 

	/// \brief Notify the user that a mic/speaker device is selected when testing. Then the SDK will close the mic/speaker testing. The user shall restart the test manually if he still wants to test.
	virtual void OnSelectedAudioDeviceIsChanged() = 0;
};

/// \brief Audio device test interface.
///
class ITestAudioDeviceHelper
{
public:
	/// \brief Audio device test callback handler. 
	/// \param pEvent A pointer to the ITestAudioDeviceHelperEvent that receives audio device test event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Call the function before using any other interface of the same class.
	virtual SDKError SetEvent(ITestAudioDeviceHelperEvent* pEvent) = 0;

	/// \brief Start to test the mic.
	/// \param deviceID Specify to test a mic device. If the param is a wrong mic ID, the SDK will return an error. Otherwise the SDK tests the specified device and sets it as selected.
	///The SDK will test the default device if no parameter is input.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///\remarks The function is disabled if no event handler is set.
	virtual SDKError TestMicStartRecording(const wchar_t* deviceID = NULL) = 0;

	/// \brief Stop the mic test. The SDK will return an error if there is no mic test.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///\remarks The function is disabled if no event handler is set.
	virtual SDKError TestMicStopTesting() = 0;

	/// \brief Play the mic recorded sound. If there is no mic testing, SDK return an error.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///\remarks The function is disabled if no event handler is set.
	virtual SDKError TestMicPlayRecording() = 0;
	
	/// \brief Start to test the speaker.
	/// \param deviceID Specify to test a speaker device. If the param is a wrong speaker ID, the SDK will return an error. Otherwise the SDK tests the specified device and sets it as selected.
	///The SDK will test the default device if no parameter is input.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///\remarks The function is disabled if no event handler is set.
	virtual SDKError TestSpeakerStartPlaying(const wchar_t* deviceID = NULL) = 0;
	
	/// \brief Stop the speaker test. The SDK will return an error if there is no speaker test.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///\remarks The function is disabled if no event handler is set.
	virtual SDKError TestSpeakerStopPlaying() = 0;
	
	/// \brief Set the time interval for audio test. 
	/// \param timerInterval Usually the SDK sends the mic and speaker volumes every 200 ms by default via ITestAudioDeviceHelperEvent::OnMicSpkVolumnChanged(). With this function, the user can modify the time interval instead of 200.
	///The time interval varies only from 50 to 1000 in millisecond.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///\remarks This interface will stop the mic/speaker test(if there is). It is suggested to call it before audio test.
	virtual SDKError SetTimerInterval(unsigned int timerInterval) = 0;
};

/// \brief General setting interface.
///
class IGeneralSettingContext
{
public:
	/// \brief Enable or disable dual screen mode.
	/// \param bEnable TRUE indicates to set to enable the dual screen mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableDualScreenMode(bool bEnable) = 0;

	/// \brief Determine if the dual screen mode is supported.
	/// \return TRUE indicates to enable the dual screen mode.
	virtual bool IsDualScreenModeEnabled() = 0;

	/// \brief Enable or disable the aero mode when sharing the screen.
	/// \param bTurnoff TRUE indicates to turn off the aero mode when sharing the screen.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks The function can only be called in windows 7 environment.
	virtual SDKError TurnOffAeroModeInSharing(bool bTurnoff) = 0;

	/// \brief Determine if the aero mode is turned off when sharing the screen.
	/// \return TRUE indicates to turn off the mode. 
	virtual bool IsAeroModeInSharingTurnOff() = 0;

	/// \brief Enable or disable to auto-fit the ZOOM window when viewing the shared content.
	/// \param bEnable TRUE indicates to resize automatically.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableAutoFitToWindowWhenViewSharing(bool bEnable) = 0;

	/// \brief Determine if it is able to auto-fit the ZOOM window when viewing the shared content.
	/// \return TRUE indicates to resize automatically.
	virtual bool IsAutoFitToWindowWhenViewSharingEnabled() = 0;

	/// \brief Enable or disable to enter the full screen video mode automatically when join meeting. 
	/// \param bEnable TRUE indicates to enter the full screen video mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \brief Determine if it is able to enter the full screen video mode automatically when join meeting.
	/// \return TRUE indicates to enter the full screen video mode. 
	virtual bool IsAutoFullScreenVideoWhenJoinMeetingEnabled() = 0;

	/// \brief Enable or disable to enter the full screen video mode automatically when viewing the sharing.
	/// \param bEnable TRUE indicates to enter the full screen video mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableAutoFullScreenVideoWhenViewShare(bool bEnable) = 0;

	/// \brief Determine if it is enable to enter the full screen video mode automatically when viewing the sharing.
	/// \return TRUE indicates to enter the full screen video mode.
	virtual bool IsAutoFullScreenVideoWhenViewShareEnabled() = 0;

	/// \brief Enable or disable to use the split screen mode, which enables the attendees to view the lectures or the gallery.
	/// \param bEnable TRUE indicates to enter the split screen mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableSplitScreenMode(bool bEnable) = 0;

	/// \brief Determine if the split screen mode is enabled.
	/// \return TRUE indicates enabled. FALSE not.
	virtual bool IsSplitScreenModeEnabled() = 0;
	
	/// \brief Enable/Disable reminder window when user exits the meeting. Available only for normal attendees (non-host).
	/// \param bEnable TRUE indicates to enable reminder window.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableDisplayReminderWindowWhenExit(bool bEnable) = 0;
	
	/// \brief Determine if reminder window is enabled when user exits the meeting.
	/// \return TRUE indicates enabled. FALSE not.
	virtual bool IsDisplayReminderWindowWhenExitEnabled() = 0;
	
	/// \brief Enable/Disable to show the elapsed time of the meeting.
	/// \param bEnable TRUE indicates to show the elapsed time. FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableShowMyMeetingElapseTime(bool bEnable) = 0;
	
	/// \brief Determine if showing elapsed time of the meeting is enabled.
	/// \return TRUE indicates to show. FALSE not.
	virtual bool IsShowMyMeetingElapseTimeEnabled() = 0;
	
	/// \brief Determine if the operating system supports the GPU acceleration when user shares.
	/// \return TRUE indicates support. FALSE not.
	virtual bool IsCurrentOSSupportAccelerateGPUWhenShare() = 0;
	
	/// \brief Enable/Disable the GPU acceleration when user shares.
	/// \param bEnable TRUE indicates to enable the acceleration. FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableAccelerateGPUWhenShare(bool bEnable) = 0;	
	
	/// \brief Determine if GPU acceleration is enabled when user shares.
	/// \param [out]bEnable TRUE indicates the GPU acceleration is enabled. FALSE not. It validates only when the return value is SDKErr_Success. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError IsAccelerateGPUWhenShareEnabled(bool& bEnable) = 0;
	
	/// \brief Enable/disable remote control of all applications.
	/// \param bEnable TRUE indicates to enable the remote control. FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableRemoteControlAllApplications(bool bEnable) = 0;	
	
	/// \brief Determine if remote control of all applications is enabled.
	/// \return TRUE indicates enabled. FALSE not.
	virtual bool IsRemoteControlAllApplicationsEnabled() = 0;
	
};

/*! \enum PREVIEW_VIDEO_ROTATION_ACTION
    \brief Notify to rotate the video preview based on the current view.
    Here are more detailed structural descriptions.
*/
typedef enum
{
	PREVIEW_VIDEO_ROTATION_ACTION_0,///< No rotation.
	PREVIEW_VIDEO_ROTATION_ACTION_CLOCK90,///<Rotate to the left.
	PREVIEW_VIDEO_ROTATION_ACTION_CLOCK180,///<Rotate 180 degrees.
	PREVIEW_VIDEO_ROTATION_ACTION_ANTI_CLOCK90///<Rotate to the right.
} PREVIEW_VIDEO_ROTATION_ACTION, *PPREVIEW_VIDEO_ROTATION_ACTION;

/// \brief Video Device test callback event.
///
class ITestVideoDeviceHelperEvent
{
public:
	/// \brief Notify that no camera device is found.
	virtual void OnNoVideoDeviceIsUseful() = 0;
	
	/// \brief Notify the user that a camera device is selected during the test, then the SDK will close the video testing. The user shall restart the test manually if he wants to test.
	virtual void OnSelectedVideoDeviceIsChanged() = 0; 
	
	/// \brief A window is needed to show the video preview. This event notifies that there is no window handle or a wrong window handle is used. 
	virtual void OnNoWindowToShowPreview() = 0;
};

/// \brief Video device test interface.
///
class ITestVideoDeviceHelper
{
public:
	/// \brief Video device test callback event handler. 
	/// \param pEvent A pointer to the ITestVideoDeviceHelperEvent that receives video device test event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Call the function before using any other interface of the same class.
	virtual SDKError SetEvent(ITestVideoDeviceHelperEvent* pEvent) = 0;
	
	/// \brief Set the window and the rectangle to display the video preview.
	/// \param hParentWnd Specify the window to display the video preview.
	/// \param rc Specify a rectangle on the window to display the video preview. The default value is {0,0,0,0}, which means the whole client area of the window.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks This function SHOULD only be called ONCE. Any redundant calling will return SDKERR_WRONG_USEAGE.
	virtual SDKError SetVideoPreviewParentWnd(HWND hParentWnd, RECT rc = _SDK_TEST_VIDEO_INIT_RECT) = 0;
	
	/// \brief Start to test the camera. 
	/// \param deviceID Specify a camera device to test. If the param is a wrong camera ID, SDK returns an error. Otherwise SDK tests the specified device and sets it to be the selected one.
	///The SDK will test the default device if no parameter is input.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks The function can not work if no event is set or no window handle is set.
	virtual SDKError TestVideoStartPreview(const wchar_t* deviceID = NULL) = 0;
	
	/// \brief Stop testing the camera.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks The function can not work if there is no event or window handle to be set.
	virtual SDKError TestVideoStopPreview() = 0;
	
	/// \brief Rotate the video preview.
	/// \param action Specify the action to rotate the video. 
	///For more details, see \link PREVIEW_VIDEO_ROTATION_ACTION \endlink.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks The function can not work if there is no event or window handle to be set. 
	///It works also in the meeting video when you rotate the preview video. Please use it with cautions.
	virtual SDKError TestVideoRotate(PREVIEW_VIDEO_ROTATION_ACTION action) = 0;	

	virtual ICameraController* GetTestCameraController() = 0;
};

/// \brief Video setting context callback event.
class IVideoSettingContextEvent
{
public:
	/// \brief Callback event if the SDK detects that the computer camera devices have been changed.
	/// \param pNewCameraList The new list of all camera devices plugged into the computer. 
	virtual void onComputerCamDeviceChanged(IList<ICameraInfo*>* pNewCameraList) = 0;

	/// \brief Notify the user that a camera device is selected.
	/// \param deviceId Specify a device to be selected.
	/// \param deviceName Specify the device name assigned by deviceId.
	virtual void onDefaultCamDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) = 0;
};
/// \brief Video setting interface.
///
class IVideoSettingContext
{
public:
	/// \brief Get camera device list.
	/// \return If the function succeeds, the return value the is camera device list.
	///Otherwise failed, returns NULL.
	virtual IList<ICameraInfo* >* GetCameraList() = 0;

	/// \brief Select camera device.
	/// \param deviceId Specify a device to be selected.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SelectCamera(const wchar_t* deviceId) = 0;

	/// \brief Enable or disable video mirror effect.
	/// \param bEnable TRUE indicates to enable the video mirror effect.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableVideoMirrorEffect(bool bEnable) = 0;

	/// \brief Get the flag to enable/disable the video mirror effect.
	/// \return Enabled or disabled.
	virtual bool IsVideoMirrorEffectEnabled() = 0;

	/// \brief Enable or disable the video facial beauty effect.
	/// \param bEnable TRUE indicates to enable the video facial beauty effect.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableFaceBeautyEffect(bool bEnable) = 0;

	/// \brief Get the flag to enable/disable the video facial beauty effect.
	/// \return Enabled or disabled.
	virtual bool IsFaceBeautyEffectEnabled() = 0;

	/// \brief Enable or disable HD video.
	/// \param bEnable TRUE indicates to enable the HD video.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableHDVideo(bool bEnable) = 0;

	/// \brief Get the flag to enable/disable the HD video.
	/// \return Enabled or disabled.
	virtual bool IsHDVideoEnabled() = 0;

	/// \brief Enable or disable to show the username on the video.
	/// \param bEnable TRUE indicates to show the username on the video.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableAlwaysShowNameOnVideo(bool bEnable) = 0;

	/// \brief Get the flag to enable/disable to show the username on video.
	/// \return Enabled or disabled.
	virtual bool IsAlwaysShowNameOnVideoEnabled() = 0;

	/// \brief Enable or disable to turn off the video when join meeting
	/// \param bEnable TRUE indicates to enable to turn off the video when join meeting
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \brief Get the flag to enable to turn off the video when join meeting.
	/// \return Enabled or disabled.
	virtual bool IsAutoTurnOffVideoWhenJoinMeetingEnabled() = 0;
	
	/// \brief Enable or disable the 16V9 video mode.
	/// \param bEnable TRUE indicates to enable the 16V9 video mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableAlwaysUse16v9(bool bEnable) = 0;

	/// \brief Get the flag to enable/disable the 16V9 video mode.
	/// \return Enabled or disabled.
	virtual bool IsAlwaysUse16v9() = 0;

	/// \brief Enable or disable to spotlight the video.
	/// \param bEnable TRUE indicates to enable to spotlight the video.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableSpotlightSelf(bool bEnable) = 0;

	/// \brief Get the flag to enable/disable to spotlight video.
	/// \return Enabled or disabled.
	virtual bool IsSpotlightSelfEnabled() = 0;

	/// \brief Enable or disable the hardware acceleration.
	/// \param bEnable TRUE indicates to enable the hardware acceleration.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableHardwareEncode(bool bEnable) = 0;

	/// \brief Get the flag to enable/disable the hardware acceleration.
	/// \return Enabled or disabled.
	virtual bool IsHardwareEncodeEnabled() = 0;

	/// \brief Enable or disable to show the participants in Gallery View up to 49 per screen.
	/// \param bEnable TRUE indicates to show the participants in Gallery View up to 49 per screen.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Enable49VideoesInGallaryView(bool bEnable) = 0;

	/// \brief Get the flag to enable/disable to show the participants in Gallery View up to 49 per screen.
	/// \return Enabled or disabled.
	virtual bool Is49VideoesInGallaryViewEnabled() = 0;

	/// \brief Enable or disable to hide the non-video participants.
	/// \param bEnable TRUE indicates to hide the non-video Participants.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableHideNoVideoUsersOnWallView(bool bEnable) = 0;

	/// \brief Get the flag to enable/disable to hide non-video participants.
	/// \return Enabled or disabled.
	virtual bool IsHideNoVideoUsersOnWallViewEnabled() = 0;

	/// \brief Get the pointer to ITestVideoDeviceHelper which is used to test camera device.
	/// \return If the function succeeds, the return value is the pointer to ITestVideoDeviceHelper.
	///Otherwise failed, returns NULL.
	///For more details, see \link ITestVideoDeviceHelper \endlink.
	virtual ITestVideoDeviceHelper* GetTestVideoDeviceHelper() = 0;

	/// \brief Video device monitor callback event. 
	/// \param pEvent A pointer to the IVideoSettingContextEvent. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///For more details, see \link IVideoSettingContextEvent \endlink.
	/// \remarks You must call the function if you want to monitor the video device plugged in/out.
	virtual SDKError SetVideoDeviceEvent(IVideoSettingContextEvent* pEvent) = 0;
};

/// \brief Audio setting context callback event.
class IAudioSettingContextEvent
{
public:
	/// \brief Callback event if the SDK detects that the computer mic devices have been changed.
	/// \param pNewMicList The new list of all mic devices plugged into the computer. 
	virtual void onComputerMicDeviceChanged(IList<IMicInfo*>* pNewMicList) = 0;
	
	/// \brief Callback event if the SDK detects that the computer speaker devices have been changed.
	/// \param pNewSpeakerList The new list of all speaker devices plugged into the computer. 
	virtual void onComputerSpeakerDeviceChanged(IList<ISpeakerInfo*>* pNewSpeakerList) = 0;

	/// \brief Notify the user that a microphone device is selected.
	/// \param deviceId Specify a device to be selected.
	/// \param deviceName Specify the device name assigned by deviceId.
	virtual void onDefaultMicDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \brief Notify the user that a speaker device is selected.
	/// \param deviceId Specify a device to be selected.
	/// \param deviceName Specify the device name assigned by deviceId.
	virtual void onDefaultSpeakerDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) = 0;
};

/// \brief Audio setting interface.
///
class IAudioSettingContext
{
public:
	/// \brief Get the mic device list.
	/// \return If the function succeeds, the return value is the camera device list.
	///Otherwise failed, returns NULL.
	virtual IList<IMicInfo* >* GetMicList() = 0;

	/// \brief Select mic device.
	/// \param deviceId Specify the device to be selected.
	/// \param deviceName Specify the device name assigned by deviceId.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SelectMic(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \brief Get the speaker device list.
	/// \return If the function succeeds, the return value is the camera device list.
	///Otherwise failed, returns NULL.
	virtual IList<ISpeakerInfo* >* GetSpeakerList() = 0;

	/// \brief Select speaker device.
	/// \param deviceId Specify the device to be selected.
	/// \param deviceName Specify the device the device name assigned by deviceId.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SelectSpeaker(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \brief Enable or disable the audio automatically when join meeting.
	/// \param bEnable TRUE indicates to enable the audio automatically when join meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableAutoJoinAudio(bool bEnable) = 0;

	/// \brief Get the flag to enable/disable the audio automatically when join meeting.
	/// \return Enabled or disabled.
	virtual bool IsAutoJoinAudioEnabled() = 0;

	/// \brief Enable or disable the auto-adjust mic volume.
	/// \param bEnable TRUE indicates to enable to auto-adjust the mic volume.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableAutoAdjustMic(bool bEnable) = 0;

	/// \brief Get the flag to enable/disable to auto-adjust the mic volume.
	/// \return Enabled or disabled.
	virtual bool IsAutoAdjustMicEnabled() = 0;

	/// \brief Enable or disable the stereo audio.
	/// \param bEnable TRUE indicates to enable the stereo audio.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableStereoAudio(bool bEnable) = 0;

	/// \brief Get the flag to enable/disable the stereo audio.
	/// \return Enabled or disabled.
	virtual bool IsStereoAudioEnable() = 0;

	/// \brief Enable or disable the original input of mic.
	/// \param bEnable TRUE indicates to enable the original input of mic.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableMicOriginalInput(bool bEnable) = 0;

	/// \brief Get the flag to enable/disable the original input of mic.
	/// \return Enabled or disabled.
	virtual bool IsMicOriginalInputEnable() = 0;
	
 	/// \brief Enable or disable to press and hold the Space-bar to speak when muted.
	/// \param bEnable TRUE indicates to press and hold the Space-bar to speak. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableHoldSpaceKeyToSpeak(bool bEnable) = 0;

	/// \brief Get the flag to enable/disable to press and hold the Space-bar to speak.
	/// \return Enabled or disabled.
	virtual bool IsHoldSpaceKeyToSpeakEnabled() = 0;

	/// \brief Enable or disable to mute always the mic when join the meeting by VoiP.
	/// \param bEnable TRUE indicates to enable to mute always the mic when join the meeting by VoiP.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableAlwaysMuteMicWhenJoinVoip(bool bEnable) = 0;

	/// \brief Get the flag to enable/disable to mute always the mic when join the meeting by VoiP.
	/// \return Enabled or disabled.
	virtual bool IsAlwaysMuteMicWhenJoinVoipEnabled() = 0;

	/// \brief Enable or disable to prompt when the user joins the meeting using the third party audio.
	/// \param bEnable TRUE indicates to enable to prompt.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableSuppressAudioNotify(bool bEnable) = 0;

	/// \brief Get the flag to enable/disable to prompt when the user joins the meeting using the third party audio.
	/// \return Enabled or disabled.
	virtual bool IsSuppressAudioNotifyEnabled() = 0;

	/// \brief Get the pointer to ITestAudioDeviceHelper which is used to test audio devices.
	/// \return If the function succeeds, the return value is the pointer to ITestAudioDeviceHelper.
	///Otherwise failed, returns NULL.
	///For more details, see \link ITestAudioDeviceHelper \endlink.
	virtual ITestAudioDeviceHelper* GetTestAudioDeviceHelper() = 0;
	
	/// \brief Set the volume of the selected mic.
	/// \param value Specify the volume of the mic that varies between 0 and 255.
	///The SDK will enable the default mic if there is no mic selected via SelectMic().
	virtual SDKError	SetMicVol(FLOAT& value) = 0;
	
	/// \brief Get the volume of the selected mic.
	/// \param value [out] Specify the current volume of the mic.
	virtual SDKError    GetMicVol(FLOAT& value) = 0;
	
	/// \brief Set the volume of the selected speaker.
	/// \param value Specify the volume of the speaker that varies between 0 and 255.
	///The SDK will enable the default speaker if there is no speaker selected via SelectSpeaker.
	virtual SDKError	SetSpeakerVol(FLOAT& value) = 0;
	
	/// \brief Get the volume of the selected speaker.
	/// \param value [out] Specify the current volume of the speaker.
	virtual SDKError    GetSpeakerVol(FLOAT& value) = 0;

	/// \brief Audio device monitor callback event. 
	/// \param pEvent A pointer to the IAudioSettingContextEvent that receives audio device plugged in/out event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///For more details, see \link IAudioSettingContextEvent \endlink.
	/// \remarks You must call the function if you want to monitor the audio device plugged in/out.
	virtual SDKError SetAudioDeviceEvent(IAudioSettingContextEvent* pEvent) = 0;

	/// \brief Set whether to enable the function of echo cancellation or not. 
	/// \param bEnable True means to enable the function, FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableEchoCancellation(bool bEnable) = 0;
	
	/// \brief Check whether the echo cancellation is enabled or not.
	/// \return If it is TRUE, it means the echo cancellation is enabled 
	virtual bool IsEchoCancellationEnabled() = 0;
	

};

/// \brief Recording setting context callback event.
class IRecordingSettingContextEvent
{
public:
	/// \brief Notification of the current cloud recording storage information.	/// \param storage_total_size Specify the total storage space.	/// \param storage_used_size Specify the used storage space.	/// \param allow_exceed_storage Specify whether the used space can overflow the total space. 
	virtual void onCloudRecordingStorageInfo(INT64 storage_total_size, INT64 storage_used_size, bool allow_exceed_storage) = 0;
};

/// \brief Recording setting interface.
///
class IRecordingSettingContext
{
public:
	/// \brief Set the path to save the recording file.
	/// \param szPath Specify the path to save the recording file.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetRecordingPath(const wchar_t* szPath) = 0;

	/// \brief Get the path to save the recording file.
	/// \return The path to save the recording file.
	virtual const wchar_t* GetRecordingPath() = 0;
	
	/// \brief Set the event of recording settings.
	/// \param pEvent The event of recording settings.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetRecordingSettingEvent(IRecordingSettingContextEvent* pEvent) = 0;
	
	/// \brief Check if the user has the privilege to get the storage information for cloud recording.
	/// \return TRUE indicates the user has the privilege. FALSE not.
	virtual bool CanGetCloudRecordingStorageInfo() = 0;

	/// \brief Get the storage information of cloud recording.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// If the return value is SDKErr_Success, IRecordingSettingContextEvent.onCloudRecordingStorageInfo() will be triggered after the infermation has be retrieved.
	virtual SDKError GetCloudRecordingStorageInfo() = 0;

	/// \brief Get the recording management URL.
	/// \return TRUE indicates enabled. FALSE not.
	virtual const wchar_t* GetRecordingManagementURL() = 0;
	
	/// \brief Set if it is able to get recording management URL.
	/// \param [out]bEnable TRUE means the recording management URL can be retrieved. FALSE not. It validates only when the return value is SDKErr_Success.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanGetRecordingManagementURL(bool& bEnable) = 0;
	
	/// \brief Set whether to enable the function of selecting the path to save the recording file after meeting.
	/// \param bEnable TRUE means to enable, FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableSelectRecordFileLocationAfterMeeting(bool bEnable) = 0;
	
	/// \brief Check if the function of selecting storage path for recording file is enabled.
	/// \return TRUE indicates enabled. FALSE not.
	virtual bool IsSelectRecordFileLocationAfterMeetingEnabled() = 0;
	
	/// \brief Enable/Disable multi-audio stream recording.
	/// \param bEnable TRUE indicates enabled. FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableMultiAudioStreamRecord(bool bEnable) = 0;
	
	/// \brief Determine if multi-audio stream recording is enabled.
	/// \return TRUE indicates enabled. FALSE not.
	virtual bool IsMultiAudioStreamRecordEnabled() = 0;
	
	/// \brief Enable/Disable watermark of timestamp.
	/// \param bEnable TRUE indicates enabled. FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableAddTimestampWatermark(bool bEnable) = 0;
	
	/// \brief Determine if the watermark of timestamps is enabled.
	/// \return TRUE indicates enabled. FALSE not.
	virtual bool IsAddTimestampWatermarkEnabled() = 0;
	
	/// \brief Enable/Disable the optimization for the third party video editor.
	/// \param bEnable TRUE indicates enabled. FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableOptimizeFor3rdPartyVideoEditor(bool bEnable) = 0;
	
	/// \brief Determine if the third party video editor is enabled.
	/// \return TRUE indicates enabled. FALSE not.
	virtual bool IsOptimizeFor3rdPartyVideoEditorEnabled() = 0;
	
	/// \brief Enable/Disable showing the video thumbnail when sharing.
	/// \param bEnable TRUE indicates enabled. FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableShowVideoThumbnailWhenShare(bool bEnable) = 0;
	
	/// \brief Determine if video thumbnail is enabled when sharing.
	/// \return TRUE indicates enabled. FALSE not.
	virtual bool IsShowVideoThumbnailWhenShareEnabled() = 0;
	
	/// \brief Enable/Disable placing the video layout next to the shared content in recording file.
	/// \param bEnable TRUE indicates enabled. FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnablePlaceVideoNextToShareInRecord(bool bEnable) = 0;
	
	/// \brief Determine if placing video next to the shared content in recording file is enabled.
	/// \return TRUE indicates enabled. FALSE not.
	virtual bool IsPlaceVideoNextToShareInRecordEnabled() = 0;
	
};

/*! \enum SettingsNetWorkType
    \brief Notify network type.
    Here are more detailed structural descriptions.
*/
enum SettingsNetWorkType 
{
	SETTINGS_NETWORK_WIRED	= 0,///<Wired LAN
	SETTINGS_NETWORK_WIFI	= 1,///<WIFI
	SETTINGS_NETWORK_PPP	= 2,///<PPP
	SETTINGS_NETWORK_3G		= 3,///<3G
	SETTINGS_NETWORK_OTHERS	= 4,///<Others

	SETTINGS_NETWORK_UNKNOWN = -1,///<Unknown network.
};

/*! \enum SettingConnectionType
    \brief Notify connection type.
    Here are more detailed structural descriptions.
*/
enum SettingConnectionType
{
	SETTINGS_CONNECTION_TYPE_CLOUD,///<Cloud connection.
	SETTINGS_CONNECTION_TYPE_DIRECT,///<Direct connection.
	SETTINGS_CONNECTION_TYPE_UNKNOWN = -1,///<Unknown connection.
};

/*! \struct tagOverallStatisticInfo
    \brief Notify overall statistic information.
    Here are more detailed structural descriptions.
*/
typedef struct tagOverallStatisticInfo
{
	SettingsNetWorkType net_work_type_;///<Network type.
	SettingConnectionType connection_type_;///<Connection type
	const wchar_t* proxy_addr_;///<Proxy address.
	tagOverallStatisticInfo()
	{
		net_work_type_ = SETTINGS_NETWORK_UNKNOWN;
		connection_type_ = SETTINGS_CONNECTION_TYPE_UNKNOWN;
		proxy_addr_ = NULL;
	}
}OverallStatisticInfo;

/*! \struct tagAudioSessionStatisticInfo
    \brief Notify the audio status information.
    Here are more detailed structural descriptions.
*/
typedef struct tagAudioSessionStatisticInfo
{
	int frequency_send_;///<Sending frequency, unit: KHz.
	int frequency_recv_;///<Receiving frequency, unit: KHz.
	int latency_send_;///<Sending latency, unit: ms.
	int latency_recv_;///<Receiving latency, unit: ms.
	int jitter_send_;///<Sending jitter, unit: ms.
	int jitter_recv_;///<Receiving jitter, unit: ms.
	float packetloss_send_;///<Sending packet loss, unit: %.
	float packetloss_recv_;///<Receiving packet loss, unit: %.

	tagAudioSessionStatisticInfo()
	{
		memset(this, 0, sizeof(tagAudioSessionStatisticInfo));
	}
}AudioSessionStatisticInfo;

/*! \struct tagASVSessionStatisticInfo
    \brief Notify video status information.
    Here are more detailed structural descriptions.
*/
typedef struct tagASVSessionStatisticInfo
{
	int latency_send_;///<Sending latency, unit: ms.
	int latency_recv_;///<Receiving latency, unit: ms.
	int jitter_send_;///<Sending jitter, unit: ms.
	int jitter_recv_;///<Receiving jitter, unit: ms.
	float packetloss_send_max_;///<Sending max packet loss, unit: %.
	float packetloss_recv_max_;///<Receiving max packet loss, unit: %.
	float packetloss_send_avg_;///<Sending average packet loss, unit: %.
	float packetloss_recv_avg_;///<Receiving average packet loss, unit: %.
	int resolution_send_;///<HIWORD->height, LOWORD->width.
	int resolution_recv_;///<HIWORD->height, LOWORD->width. 
	int fps_send_;///<Frame per second sending.
	int fps_recv_;///<Frame per second receiving.
	tagASVSessionStatisticInfo()
	{
		memset(this, 0, sizeof(tagASVSessionStatisticInfo));
	}
}ASVSessionStatisticInfo;


/// \brief Statistic setting interface.
///
class IStatisticSettingContext
{
public:
	/// \brief Query overall statistic information.
	/// \param info_ [out] Overall information. For more details, see \link OverallStatisticInfo \endlink structure.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///For more details, see \link OverallStatisticInfo \endlink.
	virtual SDKError QueryOverallStatisticInfo(OverallStatisticInfo& info_) = 0;

	/// \brief Query audio statistic information.
	/// \param info_ [out] Audio information. For more details, see \link AudioSessionStatisticInfo \endlink structure.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///For more details, see \link AudioSessionStatisticInfo \endlink.
	virtual SDKError QueryAudioStatisticInfo(AudioSessionStatisticInfo& info_) = 0;

	/// \brief Query video statistic information.
	/// \param info_ [out] Video information. For more details, see \link ASVSessionStatisticInfo \endlink structure.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///For more details, see \link ASVSessionStatisticInfo \endlink.
	virtual SDKError QueryVideoStatisticInfo(ASVSessionStatisticInfo& info_) = 0;

	/// \brief Query share statistic information.
	/// \param info_ [out] Share information. For more details, see \link ASVSessionStatisticInfo \endlink structure.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///For more details, see \link ASVSessionStatisticInfo \endlink.
	virtual SDKError QueryShareStatisticInfo(ASVSessionStatisticInfo& info_) = 0;
};

/// \brief Accessibility setting interface.
///
class IAccessibilitySettingContext
{
public:
	/// \brief Enable/Disable Always Show Meeting Controls in meeting window.
	/// \param bEnable TRUE indicates enabled. FALSE not.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableAlwaysShowMeetingControls(bool bEnable) = 0;

	/// \brief get the current setting status of Always Show Meeting Controls in meeting window.
	/// \param bEnable TRUE indicates enabled. FALSE not.
	/// \return If always show meeting controls is enable, the return value true else false
	virtual SDKError IsAlwaysShowMeetingControlsEnable(bool& bEnable) = 0;
};

/// \brief Setting user strategy interface.
///
class ISettingUIStrategy
{
public:
	/// \brief Hide the link to check the advanced settings on the General Setting page or not.
	/// \param bDisable TRUE indicates to hide the link.
	virtual void DisableAdvancedFeatures4GeneralSetting(bool bDisable) = 0;

	/// \brief Hide the Account Setting page or not.
	/// \param bDisable TRUE indicates to hide the account setting page.
	virtual void DisableAccountSettingTabPage(bool bDisable) = 0;

	/// \brief Custome the tab page show or hide
	/// \param showOption True indicates to show the corresponding tab page for each item.
	virtual void ConfSettingDialogShownTabPage(SettingDlgShowTabPageOption showOption) = 0;
};
/// \brief Virtual background image information interface.
///
class IVirtualBGImageInfo
{
public:
	/// \brief Determine the usage of current image.
	/// \return TRUE indicates that current image is used as the virtual background image.
	virtual bool isSelected() = 0;

	/// \brief Get the file path of current image.
	/// \return If the function succeeds, the return value is the file path of current image.
	///Otherwise failed, the return value is NULL.
	virtual const wchar_t* GetImageFilePath() = 0;

	/// \brief Get the name of current image.
	/// \return If the function succeeds, the return value is the name of current image.
	///Otherwise failed, the return value is NULL.
	virtual const wchar_t* GetImageName() = 0;

	virtual ~IVirtualBGImageInfo() {};
};

/// \brief Virtual background context Callback Event.
///
class IVirtualBGSettingContextEvent
{
public:
	/// \brief Callback event of notification that the default virtual background images supplied by ZOOM are downloaded.
	virtual void onVBImageDidDownloaded() = 0;
	
	/// \brief Callback event of notification that the virtual background effect is updated with the selected color.
	/// \param selectedColor The RGB value of the selected color, organized in the format 0xFFRRGGBB. 
	virtual void onGreenVBDidUpdateWithReplaceColor(DWORD selectedColor) = 0;

	/// \brief Callback event of notification that the virtual background image is changed.
	virtual void onSelectedVBImageChanged() = 0;
};

/// \brief Virtual background setting interface.
class IVirtualBGSettingContext
{
public:
	/// \brief Virtual background callback handler. 
	/// \param pEvent A pointer to the IVirtualBGSettingContextEvent that receives virtual background event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Call the function before using any other interface of the same class.
	virtual SDKError SetVirtualBGEvent(IVirtualBGSettingContextEvent* pEvent) = 0;

	/// \brief Determine if the virtual background feature is supported by the meeting.
	/// \return TRUE indicates that the meeting supports the virtual background feature.
	virtual bool IsSupportVirtualBG() = 0;

	/// \brief Determine if the smart virtual background feature can be supported by the machine.
	/// \return TRUE indicates that the machine can supports to use smart virtual background feature.
	virtual bool IsSupportSmartVirtualBG() = 0;

	/// \brief Determine if the green screen is using for the virtual background feature in the meeting.
	/// \return TRUE indicates to use the green screen for the virtual background feature.
	virtual bool IsUsingGreenScreenOn() = 0;

	/// \brief Set to use the green screen for the virtual background feature.
	/// \param bUse Specify to use the green screen or not.TRUE means using the green screen. FALSE means using smart virtual background feature.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///\remarks If the machine can not support smart virtual background feature, Calling of this interface with parameter 'FALSE'will return SDKERR_WRONG_USEAGE.
	virtual SDKError SetUsingGreenScreen(bool bUse) = 0;

	/// \brief Add a new image as the virtual background image and to the image list.
	/// \param file_path Specify the file name of the image. It must be the full path with the file name.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError AddBGImage(const wchar_t* file_path) = 0;

	/// \brief Remove an image from the virtual background image list.
	/// \param pRemoveImage Specify the image to remove. To get extended error information, see \link IVirtualBGImageInfo \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError RemoveBGImage(IVirtualBGImageInfo* pRemoveImage) = 0;

	/// \brief Get the list of the virtual background images.
	/// \return If there are images in the list, the return value is a list of the poiters to IVirtualBGImageInfo.
	///Otherwise return NULL. To get extended error information, see \link IVirtualBGImageInfo \endlink enum.
	virtual IList<IVirtualBGImageInfo* >* GetBGImageList() = 0;

	/// \brief Specify an image to be the virtual background image.
	/// \param pImage Specify the image to use. To get extended error information, see \link IVirtualBGImageInfo \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError UseBGImage(IVirtualBGImageInfo* pImage) = 0;

	/// \brief Get the selected color after called BeginSelectReplaceVBColor() and selected a color.
	/// \return If the function succeeds, the return value is the selected color.
	///Otherwise 0xFF000000. The value is the same one as the callback IVirtualBGSettingContextEvent.onGreenVBDidUpdateWithReplaceColor() does.
	virtual DWORD GetBGReplaceColor() = 0;

	/// \brief Start to capture a color from video preview.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError BeginSelectReplaceVBColor() = 0;

	/// \brief Get the pointer to ITestVideoDeviceHelper which is used to preview the video with virtual background image.
	/// \return If the function succeeds, the return value is the pointer to ITestVideoDeviceHelper.
	///Otherwise failed, returns NULL.
	///For more details, see \link ITestVideoDeviceHelper \endlink.
	virtual ITestVideoDeviceHelper* GetTestVideoDeviceHelper() = 0;
};

/// \brief Meeting setting interface.
///
class ISettingService
{
public:

	/// \brief Display Meeting Setting dialog.
	/// \param param Specify to display the Meeting Setting dialog. For more details, see \link ShowSettingDlgParam \endlink structure.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError ShowSettingDlg(ShowSettingDlgParam& param) = 0;

	/// \brief Hide meeting setting dialog.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError HideSettingDlg() = 0;

	/// \brief Get general setting interface.
	/// \return If the function succeeds, the return value is an object pointer to IGeneralSettingContext.
	///Otherwise failed, returns NULL.
	///For more details, see \link IGeneralSettingContext \endlink.
	virtual IGeneralSettingContext* GetGeneralSettings() = 0;

	/// \brief Get audio setting interface.
	/// \return If the function succeeds, the return value an object pointer to IAudioSettingContext.
	///Otherwise failed, returns NULL.
	///For more details, see \link IAudioSettingContext \endlink.
	virtual IAudioSettingContext* GetAudioSettings() = 0;

	/// \brief Get video setting interface.
	/// \return If the function succeeds, the return value is an object pointer to IVideoSettingContext.
	///Otherwise failed, returns NULL.
	///For more details, see \link IVideoSettingContext \endlink.
	virtual IVideoSettingContext* GetVideoSettings() = 0;

	/// \brief Get recording setting interface.
	/// \return If the function succeeds, the return value is an object pointer to IRecordingSettingContext.
	///Otherwise failed, returns NULL.
	///For more details, see \link IRecordingSettingContext \endlink.
	virtual IRecordingSettingContext* GetRecordingSettings() = 0;

	/// \brief Get statistic settings interface.
	/// \return If the function succeeds, the return value is an object pointer to IStatisticSettingContext.
	///Otherwise failed, returns NULL.
	///For more details, see \link IStatisticSettingContext \endlink.
	virtual IStatisticSettingContext* GetStatisticSettings() = 0;

	/// \brief Get Accessibility settings interface.
	/// \return If the function succeeds, the return value is an object pointer to IAccessibilitySettingContext.
	///Otherwise failed, returns NULL.
	///For more details, see \link IAccessibilitySettingContext \endlink.
	virtual IAccessibilitySettingContext* GetAccessibilitySettings() = 0;

	/// \brief Get setting user strategy interface.
	/// \return If the function succeeds, the return value is an object pointer to ISettingUIStrategy.
	///Otherwise failed, returns NULL.
	///For more details, see \link ISettingUIStrategy \endlink.
	virtual ISettingUIStrategy* GetSettingUIStrategy() = 0;

	/// \brief Get virtual background interface.
	/// \return If the function succeeds, the return value is an object pointer to IVirtualBGSettingContext.
	///Otherwise failed, returns NULL.
	///For more details, see \link IVirtualBGSettingContext \endlink.
	virtual IVirtualBGSettingContext* GetVirtualBGSettings() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif