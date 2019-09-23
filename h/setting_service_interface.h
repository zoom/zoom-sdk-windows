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

/// \brief General setting Interface
///
class IGeneralSettingContext
{
public:
	/// \brief Enable or disable dual screen mode
	/// \param bEnable Specifies enable or disable dual screen mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableDualScreenMode(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of dual screen mode.
	/// \return Enable or disable
	virtual bool IsDualScreenModeEnabled() = 0;

	/// \brief turn off or on aero mode in screen sharing
	/// \param bEnable Specifies turn off or on aero mode in screen sharing.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	///Just support windows 7.
	virtual SDKError TurnOffAeroModeInSharing(bool bTurnoff) = 0;

	/// \brief Get Turn Off flag of on aero mode in screen sharing.
	/// \return Turn Off or not
	virtual bool IsAeroModeInSharingTurnOff() = 0;

	/// \brief Enable or disable auto fit to window when view sharing content.
	/// \param bEnable Specifies enable or disable auto fit to window when view sharing content.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAutoFitToWindowWhenViewSharing(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of auto fit to window when view sharing content.
	/// \return Enable or disable
	virtual bool IsAutoFitToWindowWhenViewSharingEnabled() = 0;

	/// \brief Enable or disable auto enter full screen video mode when join meeting.
	/// \param bEnable Specifies enable or disable auto enter full screen video mode when join meeting.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAutoFullScreenVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of auto enter full screen video mode when join meeting.
	/// \return Enable or disable
	virtual bool IsAutoFullScreenVideoWhenJoinMeetingEnabled() = 0;

	/// \brief Enable or disable auto enter full screen video mode when view share.
	/// \param bEnable Specifies enable or disable auto enter full screen video mode when view share.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAutoFullScreenVideoWhenViewShare(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of auto enter full screen video mode when view share.
	/// \return Enable or disable
	virtual bool IsAutoFullScreenVideoWhenViewShareEnabled() = 0;

	/// \brief Enable or disable split screen mode when view share.
	/// \param bEnable Specifies enable or disable split screen mode when view share.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableSplitScreenMode(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of split screen mode.
	/// \return Enable or disable
	virtual bool IsSplitScreenModeEnabled() = 0;
};

/// \brief Video setting Interface
///
class IVideoSettingContext
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

	/// \brief Enable or disable video mirror effect
	/// \param bEnable Specifies enable or disable video mirror effect
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableVideoMirrorEffect(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of video mirror effect.
	/// \return Enable or disable
	virtual bool IsVideoMirrorEffectEnabled() = 0;

	/// \brief Enable or disable video face beauty effect
	/// \param bEnable Specifies enable or disable video face beauty effect
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableFaceBeautyEffect(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of video face beauty effect.
	/// \return Enable or disable
	virtual bool IsFaceBeautyEffectEnabled() = 0;

	/// \brief Enable or disable hd video
	/// \param bEnable Specifies enable or disable hd video
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableHDVideo(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of hd video.
	/// \return Enable or disable
	virtual bool IsHDVideoEnabled() = 0;

	// \brief Enable or disable always show name on video
	/// \param bEnable Specifies enable or disable always show name on video
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAlwaysShowNameOnVideo(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of always show name on video.
	/// \return Enable or disable
	virtual bool IsAlwaysShowNameOnVideoEnabled() = 0;

	// \brief Enable or disable turn off video when join meeting
	/// \param bEnable Specifies enable or disable turn off video when join meeting
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of turn off video when join meeting.
	/// \return Enable or disable
	virtual bool IsAutoTurnOffVideoWhenJoinMeetingEnabled() = 0;
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
	/// \param deviceId Specifies which device to select.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SelectMic(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \brief Get speaker device list
	/// \return If the function succeeds, the return value is camera device list pointer.
	///If the function fails, the return value is NULL.
	virtual IList<ISpeakerInfo* >* GetSpeakerList() = 0;

	/// \brief Select speaker device
	/// \param deviceId Specifies which device to select.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SelectSpeaker(const wchar_t* deviceId, const wchar_t* deviceName) = 0;

	/// \brief Enable or disable auto join audio when join meeting
	/// \param bEnable Specifies enable or disable dual screen mode.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAutoJoinAudio(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of auto join audio when join meeting
	/// \return Enable or disable
	virtual bool IsAutoJoinAudioEnabled() = 0;

	/// \brief Enable or disable auto adjust mic volume.
	/// \param bEnable Specifies enable or disable auto adjust mic volume.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableAutoAdjustMic(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of auto adjust mic volume.
	/// \return Enable or disable
	virtual bool IsAutoAdjustMicEnabled() = 0;

	/// \brief Enable or disable stereo audio.
	/// \param bEnable Specifies enable or disable stereo audio.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableStereoAudio(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of stereo audio.
	/// \return Enable or disable
	virtual bool IsStereoAudioEnable() = 0;

	/// \brief Enable or disable original input of mic.
	/// \param bEnable Specifies enable or disable original input of mic.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableMicOriginalInput(bool bEnable) = 0;

	/// \brief Get Enable or disable flag of original input of mic.
	/// \return Enable or disable
	virtual bool IsMicOriginalInputEnable() = 0;
};

/// \brief Recording setting Interface
///
class IRecordingSettingContext
{
public:
	/// \brief Set the recording path in setting dialog.
	/// \param szPath Specifies the path of recording.
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
	/// \info_ Overall information 
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError QueryOverallStatisticInfo(OverallStatisticInfo& info_) = 0;

	/// \brief Query audio information
	/// \info_ Audio information 
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError QueryAudioStatisticInfo(AudioSessionStatisticInfo& info_) = 0;

	/// \brief Query video information
	/// \info_ Video information 
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError QueryVideoStatisticInfo(ASVSessionStatisticInfo& info_) = 0;

	/// \brief Query share information
	/// \info_ Share information 
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError QueryShareStatisticInfo(ASVSessionStatisticInfo& info_) = 0;
};

/// \brief Meeting setting Interface
///
class ISettingService
{
public:
	/// \brief Show meeting setting dialog
	/// \param param Specifies how to show chat dialog.
	/// \return If the function succeeds, the return value is camera device list pointer.
	///If the function fails, the return value is NULL.
	virtual SDKError ShowSettingDlg(ShowSettingDlgParam& param) = 0;

	/// \brief Hide meeting setting dialog
	/// \return If the function succeeds, the return value is camera device list pointer.
	///If the function fails, the return value is NULL.
	virtual SDKError HideSettingDlg() = 0;

	/// \brief Get general settings.
	/// \return If the function succeeds, the return value is general settings interface.
	///If the function fails, the return value is NULL.
	virtual IGeneralSettingContext* GetGeneralSettings() = 0;

	/// \brief Get audio settings.
	/// \return If the function succeeds, the return value is audio settings interface.
	///If the function fails, the return value is NULL.
	virtual IAudioSettingContext* GetAudioSettings() = 0;

	/// \brief Get video settings.
	/// \return If the function succeeds, the return value is video settings interface.
	///If the function fails, the return value is NULL.
	virtual IVideoSettingContext* GetVideoSettings() = 0;

	/// \brief Get recording settings.
	/// \return If the function succeeds, the return value is recording settings interface.
	///If the function fails, the return value is NULL.
	virtual IRecordingSettingContext* GetRecordingSettings() = 0;

	/// \brief Get statistic settings.
	/// \return If the function succeeds, the return value is statistic settings interface.
	///If the function fails, the return value is NULL.
	virtual IStatisticSettingContext* GetStatisticSettings() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif