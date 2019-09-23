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

	virtual ~ICameraInfo() {};
};

/// \brief Microphone device information Interface
///
class IMicInfo
{
public:
	/// \brief Get microphone device id
	/// \return If the function succeeds, the return value is camera device id.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetDeviceId() = 0;

	/// \brief Get microphone device name
	/// \return If the function succeeds, the return value is camera device name.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetDeviceName() = 0;

	/// \brief Selected device flag
	/// \return If the return value is true, this device is selected.
	virtual bool IsSelectedDevice() = 0;

	virtual ~IMicInfo() {};
};

/// \brief Audio speaker device information Interface
///
class ISpeakerInfo
{
public:
	/// \brief Get speaker device id
	/// \return If the function succeeds, the return value is camera device id.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetDeviceId() = 0;

	/// \brief Get speaker device name
	/// \return If the function succeeds, the return value is camera device name.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetDeviceName() = 0;

	/// \brief Selected device flag
	/// \return If the return value is true, this device is selected.
	virtual bool IsSelectedDevice() = 0;

	virtual ~ISpeakerInfo() {};
};

enum SettingTabPage
{
	SettingTabPage_General,
	SettingTabPage_Audio,
	SettingTabPage_Video
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
	SettingTabPage eTabPageType;
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

/// \brief Notify the status of the mic during the mic testing.
typedef	enum
{
	enuCanTest = 0, ///< Can call TestMicStartRecording to start testing mic. Useless to call TestMicStopTesting/TestMicPlayRecording.
	enuMicRecording,///< Can call TestMicStopTesting/TestMicPlayRecording. Useless to call TestMicStartRecording.
	enuCanPlay,		///< Can call TestMicStopTesting/TestMicPlayRecording. Useless to call TestMicStartRecording.
					///< enuCanPlay status means SDK has recorded the mic sound for the longest time (6 seconds). In this status, if the bHandled is not set to be 'true', SDK will call TestMicStopTesting itself.
} SDK_TESTMIC_STATUS;

/// \brief Audio Device testing Callback events
//
class ITestAudioDeviceHelperEvent
{
public:
	/// \brief Notify the current mic volume and speaker volume during the mic/speaker testing.
	/// \param MicVolume [out] Specifies the voulme of the mic.
	/// \param SpkVolume [out] Specifies the voulme of the speaker.
	///These values can be used to show a volume process bar during mic/speaker testing.
	virtual void OnMicSpkVolumnChanged(unsigned int MicVolume, unsigned int SpkVolume) = 0;

	/// \brief Notify that no mic device or speaker device is found.
	/// \param bMicOrSpk True means no mic device. False means no speaker device.
	virtual void OnNoAudioDeviceIsUseful(bool bMicOrSpk) = 0; 

	/// \brief Notify the status of the mic duing the mic testing.
	/// \param status Refer to the enum SDK_TESTMIC_STATUS for more details.
	/// \param bHandled Set it to be 'true' to notify the SDK that the default logic in SDK should be ignored to handle the mic status. 
	/// \see SDK_TESTMIC_STATUS
	virtual void OnTestMicStatusChanged(SDK_TESTMIC_STATUS status,bool& bHandled) = 0; 

	/// \brief Notify the user that a mic/speaker device is selected during the testing. SDK will close the mic/speaker testing. User should restart the test again manually.
	virtual void OnSelectedAudioDeviceIsChanged() = 0;
};

/// \brief Audio devices testing interface.
///
class ITestAudioDeviceHelper
{
public:
	/// \brief Audio device testing callback event. \remarks It must be called before using any other interface in this class.
	/// \param pEvent [in] A pointer to an ITestAudioDeviceHelperEvent* that receives audio device testing event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \see ITestAudioDeviceHelperEvent
	/// \remarks It must be called before using any other interface in this class.
	virtual SDKError SetEvent(ITestAudioDeviceHelperEvent* pEvent) = 0;

	/// \brief Start to test the mic.
	/// \param deviceID [in] Specifies a mic device to test. If the param is a wrong mic ID, SDK returns an error. Otherwise SDK tests the specified device and sets it to be the selected one.
	///If no param is passed in, SDK tests the default device.
	///\remarks The function can not work if no event is set.
	virtual SDKError TestMicStartRecording(const wchar_t* deviceID = NULL) = 0;

	/// \brief Stop the mic testing. If there is no mic testing, SDK return an error.
	///\remarks The function can not work if no event is set.
	virtual SDKError TestMicStopTesting() = 0;

	/// \brief Play the mic reocrded sound. If there is no mic testing, SDK return an error.
	///\remarks The function can not work if no event is set.
	virtual SDKError TestMicPlayRecording() = 0;
	
	/// \brief Start to test the speaker.
	/// \ param deviceID [in] Specified a speaker device to test. If the param is a wrong speaker ID, SDK returns an error. Otherwise SDK tests the specified device and sets it to be the selected one.
	///If no param is passed in, SDK tests the default device.
	///\remarks The function can not work if no event is set.
	virtual SDKError TestSpeakerStartPlaying(const wchar_t* deviceID = NULL) = 0;
	
	/// \brief Stop the speaker testing. If there is no speaker testing, SDK return an error.
	///\remarks The function can not work if no event is set.
	virtual SDKError TestSpeakerStopPlaying() = 0;
	
	/// \brief Set the time interval for audio test. 
	/// \param timerInterval [in] SDK sends mic and speaker volumes every 200 ms by default. This function allows the user to set another time interval instead of 200.
	///The unit of time interval is millisecond. If the value is bigger than 1000 or lesser than 50, SDK will change it to be 200.
	///\remarks Using this interface will stop the mic/speaker testing, if there is any. So, calling it before you do any audio test.
	virtual SDKError SetTimerInterval(unsigned int timerInterval) = 0;
};

/// \brief General setting Interface
///
class IGeneralSettingContext
{
public:
	/// \brief Enable or disable dual screen mode
	/// \param bEnable [in] Specifies enable or disable dual screen mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableDualScreenMode(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of dual screen mode.
	/// \return Enable or disable
	virtual bool IsDualScreenModeEnabled() = 0;

	/// \brief turn off or on aero mode in screen sharing
	/// \param bTurnoff [in] Specifies turn off or on aero mode in screen sharing.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	///Just support windows 7.
	virtual SDKError TurnOffAeroModeInSharing(bool bTurnoff) = 0;

	/// \brief Get Turn Off flag of on aero mode in screen sharing.
	/// \return Turn Off or not
	virtual bool IsAeroModeInSharingTurnOff() = 0;

	/// \brief Enable or disable auto fit to window when view sharing content.
	/// \param bEnable [in] Specifies enable or disable auto fit to window when view sharing content.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAutoFitToWindowWhenViewSharing(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of auto fit to window when view sharing content.
	/// \return Enable or disable
	virtual bool IsAutoFitToWindowWhenViewSharingEnabled() = 0;

	/// \brief Enable or disable auto enter full screen video mode when join meeting.
	/// \param bEnable [in] Specifies enable or disable auto enter full screen video mode when join meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of auto enter full screen video mode when join meeting.
	/// \return Enable or disable
	virtual bool IsAutoFullScreenVideoWhenJoinMeetingEnabled() = 0;

	/// \brief Enable or disable auto enter full screen video mode when view share.
	/// \param bEnable [in] Specifies enable or disable auto enter full screen video mode when view share.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAutoFullScreenVideoWhenViewShare(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of auto enter full screen video mode when view share.
	/// \return Enable or disable
	virtual bool IsAutoFullScreenVideoWhenViewShareEnabled() = 0;

	/// \brief Enable or disable split screen mode when view share.
	/// \param bEnable [in] Specifies enable or disable split screen mode when view share.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableSplitScreenMode(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of split screen mode.
	/// \return Enable or disable
	virtual bool IsSplitScreenModeEnabled() = 0;
};

///\brief Notify the action to rotate the video preview based on current view.
typedef enum
{
	PREVIEW_VIDEO_ROTATION_ACTION_0, 			///< No rotation.
	PREVIEW_VIDEO_ROTATION_ACTION_CLOCK90,		///< Rotate left.
	PREVIEW_VIDEO_ROTATION_ACTION_CLOCK180,		///< Rotate 180 degrees.
	PREVIEW_VIDEO_ROTATION_ACTION_ANTI_CLOCK90	///< Rotate right.
} PREVIEW_VIDEO_ROTATION_ACTION, *PPREVIEW_VIDEO_ROTATION_ACTION;

/// \brief Video Device testing Callback events
///
class ITestVideoDeviceHelperEvent
{
public:
	/// \brief Notify that no camera device is found.
	virtual void OnNoVideoDeviceIsUseful() = 0;
	
	/// \brief Notify the user that a camera device is selected during the testing. SDK will close the video testing. User should restart the test again manually.
	virtual void OnSelectedVideoDeviceIsChanged() = 0; 
	
	/// \brief SDK need a window to show the video preview. This event notifies that no window handle or a wrong window handle is used. 
	virtual void OnNoWindowToShowPreview() = 0;
};

/// \brief Video device testing interface.
///
class ITestVideoDeviceHelper
{
public:
	/// \brief Video device testing callback event. \remarks This function must be called before using any other interface in this class.
	/// \param pEvent [in] A pointer to an ITestVideoDeviceHelperEvent that receives video device testing event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(ITestVideoDeviceHelperEvent* pEvent) = 0;
	
	/// \brief Set the window and the rect to display the video preview.
	/// \param hParentWnd [in] Specifies the window to display the video preview.
	/// \param rc [in] Specifies a rectangle in the window to display the video preview. The default value is {0,0,0,0}. Using the default rc value means using the whole client area of the window to display the preview.
	virtual SDKError SetVideoPreviewParentWnd(HWND hParentWnd, RECT rc = _SDK_TEST_VIDEO_INIT_RECT) = 0;
	
	/// \brief Start to test the camera. 
	/// \param deviceID [in] Specifies a camera device to test. If the param is a wrong camera ID, SDK returns an error. Otherwise SDK tests the specified device and sets it to be the selected one.
	///If no param is passed in, SDK tests the default device.
	///\remarks The function can not work if no event is set or no window handle is set.
	virtual SDKError TestVideoStartPreview(const wchar_t* deviceID = NULL) = 0;
	
	/// \brief Stop testing the camera.
	///\remarks The function can not work if no event is set or no window handle is set.
	virtual SDKError TestVideoStopPreview() = 0;
	
	/// \brief Rotate the video preview.
	/// \param action [in] Specified the action to rotate the video. Refer to enum PREVIEW_VIDEO_ROTATION_ACTION for more details.
	/// \see PREVIEW_VIDEO_ROTATION_ACTION
	///\remarks The function can not work if no event is set or no window handle is set.
	virtual SDKError TestVideoRotate(PREVIEW_VIDEO_ROTATION_ACTION action) = 0;	
};

/// \brief Video setting Interface
///
class IVideoSettingContext
{
public:
	/// \brief Get camera device list.
	/// \return If the function succeeds, the return value is camera device list pointer.
	///If the function fails, the return value is NULL.
	virtual IList<ICameraInfo* >* GetCameraList() = 0;

	/// \brief Select camera device.
	/// \param [in] deviceId Specifies which device to select.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SelectCamera(const wchar_t* deviceId) = 0;

	/// \brief Enable or disable video mirror effect.
	/// \param [in] bEnable Specifies enable or disable video mirror effect.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableVideoMirrorEffect(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of video mirror effect.
	/// \return Enable or disable.
	virtual bool IsVideoMirrorEffectEnabled() = 0;

	/// \brief Enable or disable video face beauty effect.
	/// \param [in] bEnable Specifies enable or disable video face beauty effect.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableFaceBeautyEffect(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of video face beauty effect.
	/// \return Enable or disable.
	virtual bool IsFaceBeautyEffectEnabled() = 0;

	/// \brief Enable or disable hd video.
	/// \param [in] bEnable Specifies enable or disable hd video
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableHDVideo(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of hd video.
	/// \return Enable or disable.
	virtual bool IsHDVideoEnabled() = 0;

	// \brief Enable or disable always show name on video
	/// \param [in] bEnable Specifies enable or disable always show name on video
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAlwaysShowNameOnVideo(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of always show name on video.
	/// \return Enable or disable.
	virtual bool IsAlwaysShowNameOnVideoEnabled() = 0;

	// \brief Enable or disable turn off video when join meeting
	/// \param [in] bEnable Specifies enable or disable turn off video when join meeting
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of turn off video when join meeting.
	/// \return Enable or disable.
	virtual bool IsAutoTurnOffVideoWhenJoinMeetingEnabled() = 0;
	
	// \brief Enable or disable to use 16v9 video mode.
	/// \param bEnable [in] Specifies enable or disable to use 16v9 video mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAlwaysUse16v9(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of use 16v9 video mod.
	/// \return Enable or disable.
	virtual bool IsAlwaysUse16v9() = 0;

	// \brief Enable or disable to spotlight video.
	/// \param bEnable [in] Specifies enable or disable to spotlight video.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableSpotlightSelf(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of Spotlight video.
	/// \return Enable or disable.
	virtual bool IsSpotlightSelfEnabled() = 0;

	// \brief Enable or disable to use hardware acceleration.
	/// \param bEnable [in] Specifies enable or disable to use hardware acceleration.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableHardwareEncode(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of Enable hardware acceleration.
	/// \return Enable or disable.
	virtual bool IsHardwareEncodeEnabled() = 0;

	// \brief Enable or disable to display up to 49 participants per screen in Gallery View.
	/// \param bEnable [in] Specifies enable or disable to display up to 49 participants per screen in Gallery View.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Enable49VideoesInGallaryView(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of Display up to 49 participants per screen in Gallery View.
	/// \return Enable or disable.
	virtual bool Is49VideoesInGallaryViewEnabled() = 0;

	// \brief Enable or disable to hide Non-Video Participants.
	/// \param bEnable [in] Specifies enable or disable to hide Non-Video Participants.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableHideNoVideoUsersOnWallView(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of Hide Non-Video Participants.
	/// \return Enable or disable.
	virtual bool IsHideNoVideoUsersOnWallViewEnabled() = 0;

	// \brief Get the pointer of ITestVideoDeviceHelper which is used to test camera device.
	/// \return If the function succeeds, the return value is the pointer of ITestVideoDeviceHelper.
	///If the function fails, the pointer is NULL.
	/// \see ITestVideoDeviceHelper
	virtual ITestVideoDeviceHelper* GetTestVideoDeviceHelper() = 0;
};

/// \brief Audio setting Interface
///
class IAudioSettingContext
{
public:
	/// \brief Get mic device list
	/// \return If the function succeeds, the return value is camera device list pointer.
	///If the function fails, the return value is NULL.
	virtual IList<IMicInfo* >* GetMicList() = 0;

	/// \brief Select mic device
	/// \param deviceId [in] Specifies which device to select.
	/// \param deviceName [in] Specifies which device to select. It should be the same device specified by deviceId.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SelectMic(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \brief Get speaker device list
	/// \return If the function succeeds, the return value is camera device list pointer.
	///If the function fails, the return value is NULL.
	virtual IList<ISpeakerInfo* >* GetSpeakerList() = 0;

	/// \brief Select speaker device
	/// \param deviceId [in] Specifies which device to select.
	/// \param deviceName [in] Specifies which device to select. It should be the same device specified by deviceId.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SelectSpeaker(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \brief Enable or disable auto join audio when join meeting
	/// \param bEnable [in] Specifies enable or disable dual screen mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAutoJoinAudio(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of auto join audio when join meeting
	/// \return Enable or disable
	virtual bool IsAutoJoinAudioEnabled() = 0;

	/// \brief Enable or disable auto adjust mic volume.
	/// \param bEnable [in] Specifies enable or disable auto adjust mic volume.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAutoAdjustMic(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of auto adjust mic volume.
	/// \return Enable or disable
	virtual bool IsAutoAdjustMicEnabled() = 0;

	/// \brief Enable or disable stereo audio.
	/// \param bEnable [in] Specifies enable or disable stereo audio.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableStereoAudio(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of stereo audio.
	/// \return Enable or disable
	virtual bool IsStereoAudioEnable() = 0;

	/// \brief Enable or disable original input of mic.
	/// \param bEnable [in] Specifies enable or disable original input of mic.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableMicOriginalInput(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of original input of mic.
	/// \return Enable or disable
	virtual bool IsMicOriginalInputEnable() = 0;
	
 	/// \brief Enable or disable hold and press space key to speak.
	/// \param bEnable [in] Specifies enable or disable hold and press space key to speak. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableHoldSpaceKeyToSpeak(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of hold and press space key to speak.
	/// \return Enable or disable
	virtual bool IsHoldSpaceKeyToSpeakEnabled() = 0;

	/// \brief Enable or disable always mute mic when join voip.
	/// \param bEnable [in] Specifies enable or disable always mute mic when join voip. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAlwaysMuteMicWhenJoinVoip(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of always mute mic when join voip.
	/// \return Enable or disable
	virtual bool IsAlwaysMuteMicWhenJoinVoipEnabled() = 0;

	// \brief Get the pointer of ITestAudioDeviceHelper which is used to test audio devices.
	/// \return If the function succeeds, the return value is the pointer of ITestAudioDeviceHelper.
	///If the function fails, the pointer is NULL.
	/// \see ITestAudioDeviceHelper
	virtual ITestAudioDeviceHelper* GetTestAudioDeviceHelper() = 0;
	
	/// \brief Set the volume of the selected mic.
	/// \param value [in]Specifies the volume of the mic. The value interval is 0 to 255
	///SDK uses the default mic if no mic is selected via calling the function SelectMic.
	virtual SDKError	SetMicVol(FLOAT& value) = 0;
	
	/// \brief Get the volume of the selected mic.
	/// \param value [out]Specifies the current volume of the mic.
	virtual SDKError    GetMicVol(FLOAT& value) = 0;
	
	/// \brief Set the volume of the selected speaker.
	/// \param value [in]Specifies the volume of the speaker. The value interval is 0 to 255
	///SDK uses the default speaker if no speaker is selected via calling the function SelectSpeaker.
	virtual SDKError	SetSpeakerVol(FLOAT& value) = 0;
	
	/// \brief Get the volume of the selected speaker.
	/// \param value [out]Specifies the current volume of the speaker.
	virtual SDKError    GetSpeakerVol(FLOAT& value) = 0;
};

/// \brief Recording setting Interface
///
class IRecordingSettingContext
{
public:
	/// \brief Set the recording path in setting dialog.
	/// \param szPath [in] Specifies the path of recording.
	/// \return If the function succeeds, the return value is camera device list pointer.
	///If the function fails, the return value is NULL.
	virtual SDKError SetRecordingPath(const wchar_t* szPath) = 0;

	/// \brief Get the recording path in setting dialog.
	/// \return the path of recording.
	virtual const wchar_t* GetRecordingPath() = 0;
};

enum SettingsNetWorkType 
{
	SETTINGS_NETWORK_WIRED	= 0,
	SETTINGS_NETWORK_WIFI	= 1,
	SETTINGS_NETWORK_PPP	= 2,
	SETTINGS_NETWORK_3G		= 3,
	SETTINGS_NETWORK_OTHERS	= 4,

	SETTINGS_NETWORK_UNKNOWN = -1,
};

enum SettingConnectionType
{
	SETTINGS_CONNECTION_TYPE_CLOUD,
	SETTINGS_CONNECTION_TYPE_DIRECT,
	SETTINGS_CONNECTION_TYPE_UNKNOWN = -1,
};
typedef struct tagOverallStatisticInfo
{
	SettingsNetWorkType net_work_type_;  	
	SettingConnectionType connection_type_; 
	const wchar_t* proxy_addr_;
	tagOverallStatisticInfo()
	{
		net_work_type_ = SETTINGS_NETWORK_UNKNOWN;
		connection_type_ = SETTINGS_CONNECTION_TYPE_UNKNOWN;
		proxy_addr_ = NULL;
	}
}OverallStatisticInfo;

typedef struct tagAudioSessionStatisticInfo
{
	int frequency_send_; //KHz
	int frequency_recv_; //KHz
	int latency_send_;//ms
	int latency_recv_;//ms
	int jitter_send_;//ms
	int jitter_recv_;//ms
	float packetloss_send_;//%
	float packetloss_recv_;//%

	tagAudioSessionStatisticInfo()
	{
		memset(this, 0, sizeof(tagAudioSessionStatisticInfo));
	}
}AudioSessionStatisticInfo;

typedef struct tagASVSessionStatisticInfo
{
	int latency_send_;//ms
	int latency_recv_;//ms
	int jitter_send_;//ms
	int jitter_recv_;//ms
	float packetloss_send_max_;//%
	float packetloss_recv_max_;//%
	float packetloss_send_avg_;//%
	float packetloss_recv_avg_;//%
	int resolution_send_; //HIWORD->height,LOWORD->width
	int resolution_recv_; //HIWORD->height,LOWORD->width 
	int fps_send_;//fps
	int fps_recv_;//fps
	tagASVSessionStatisticInfo()
	{
		memset(this, 0, sizeof(tagASVSessionStatisticInfo));
	}
}ASVSessionStatisticInfo;


/// \brief Statistic setting Interface
///
class IStatisticSettingContext
{
public:
	/// \brief Query overall information
	/// \param info_ [out] Overall information 
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \see OverallStatisticInfo
	virtual SDKError QueryOverallStatisticInfo(OverallStatisticInfo& info_) = 0;

	/// \brief Query audio information
	/// \param info_ [out] Audio information 
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \see AudioSessionStatisticInfo
	virtual SDKError QueryAudioStatisticInfo(AudioSessionStatisticInfo& info_) = 0;

	/// \brief Query video information
	/// \param info_ [out] Video information 
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \see ASVSessionStatisticInfo
	virtual SDKError QueryVideoStatisticInfo(ASVSessionStatisticInfo& info_) = 0;

	/// \brief Query share information
	/// \param info_ [out] Share information 
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \see ASVSessionStatisticInfo
	virtual SDKError QueryShareStatisticInfo(ASVSessionStatisticInfo& info_) = 0;
};

/// \brief Setting UI strategy Interface
///
class ISettingUIStrategy
{
public:
	/// \brief Disable ui of advanced features on general setting tab.
	/// \param bDisable [in] Specifies enable or disable.
	virtual void DisableAdvancedFeatures4GeneralSetting(bool bDisable) = 0;

	/// \brief Disable ui of account setting tab.
	/// \param bDisable [in] Specifies enable or disable.
	virtual void DisableAccountSettingTabPage(bool bDisable) = 0;
};

/// \brief Meeting setting Interface
///
class ISettingService
{
public:

	/// \brief Show meeting setting dialog
	/// \param [in] param Specifies to show the chat dialog.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError ShowSettingDlg(ShowSettingDlgParam& param) = 0;

	/// \brief Hide meeting setting dialog
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError HideSettingDlg() = 0;

	/// \brief Get general settings.
	/// \return If the function succeeds, the return value is general settings interface.
	///If the function fails, the return value is NULL.
	/// \see IGeneralSettingContext
	virtual IGeneralSettingContext* GetGeneralSettings() = 0;

	/// \brief Get audio settings.
	/// \return If the function succeeds, the return value is audio settings interface.
	///If the function fails, the return value is NULL.
	/// \see IAudioSettingContext
	virtual IAudioSettingContext* GetAudioSettings() = 0;

	/// \brief Get video settings.
	/// \return If the function succeeds, the return value is video settings interface.
	///If the function fails, the return value is NULL.
	/// \see IVideoSettingContext
	virtual IVideoSettingContext* GetVideoSettings() = 0;

	/// \brief Get recording settings.
	/// \return If the function succeeds, the return value is recording settings interface.
	///If the function fails, the return value is NULL.
	/// \see IRecordingSettingContext
	virtual IRecordingSettingContext* GetRecordingSettings() = 0;

	/// \brief Get statistic settings.
	/// \return If the function succeeds, the return value is statistic settings interface.
	///If the function fails, the return value is NULL.
	/// \see IStatisticSettingContext
	virtual IStatisticSettingContext* GetStatisticSettings() = 0;

	/// \brief Get setting UI strategy.
	/// \return If the function succeeds, the return value is setting UI strategy interface.
	///If the function fails, the return value is NULL.
	/// \see ISettingUIStrategy
	virtual ISettingUIStrategy* GetSettingUIStrategy() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif