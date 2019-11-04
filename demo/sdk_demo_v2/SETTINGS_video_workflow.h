#pragma once
#include "sdk_util.h"
#include "stdafx.h"
#include "setting_service_interface.h"
class CSDKVideoSettingsUIEvent
{
public:
	virtual void OnNoVideoDeviceIsUseful() = 0;
	virtual void OnSelectedVideoDeviceIsChanged() = 0; 
	virtual void OnNoWindowToShowPreview() = 0;
	virtual void OnComputerCamDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ICameraInfo*>* pNewCameraList) = 0;
	virtual void onDefaultCamDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) = 0;
};
class CSDKVideoSettingsWorkFlow:public ZOOM_SDK_NAMESPACE::ITestVideoDeviceHelperEvent,ZOOM_SDK_NAMESPACE::IVideoSettingContextEvent
{
public:
	CSDKVideoSettingsWorkFlow();
	virtual ~CSDKVideoSettingsWorkFlow();
	ZOOM_SDK_NAMESPACE::SDKError Init();
	void Cleanup(){}
	void SetUIEvent(CSDKVideoSettingsUIEvent* event_);
	///video setting context
	ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ICameraInfo*>* GetCameraList();
	ZOOM_SDK_NAMESPACE::SDKError EnableVideoMirrorEffect(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableFaceBeautyEffect(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableHDVideo(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableAlwaysShowNameOnVideo(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableAlwaysUse16v9(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableSpotlightSelf(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableHardwareEncode(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError Enable49VideoesInGallaryView(bool bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableHideNoVideoUsersOnWallView(bool bEnable);
	bool IsVideoMirrorEffectEnabled();
	bool IsFaceBeautyEffectEnabled();
	bool IsHDVideoEnabled();
	bool IsAlwaysShowNameOnVideoEnabled();
	bool IsAutoTurnOffVideoWhenJoinMeetingEnabled();
	bool IsAlwaysUse16v9();
	bool IsSpotlightSelfEnabled();
	bool IsHardwareEncodeEnabled();
	bool Is49VideoesInGallaryViewEnabled();
	bool IsHideNoVideoUsersOnWallViewEnabled();
	///video test device
	ZOOM_SDK_NAMESPACE::SDKError SetVideoPreviewParentWnd(HWND hParentWnd, RECT rc = ZOOM_SDK_NAMESPACE::_SDK_TEST_VIDEO_INIT_RECT);
	ZOOM_SDK_NAMESPACE::SDKError TestVideoStartPreview(const wchar_t* deviceID = NULL);
	ZOOM_SDK_NAMESPACE::SDKError TestVideoStopPreview();
	ZOOM_SDK_NAMESPACE::SDKError TestVideoRotate(ZOOM_SDK_NAMESPACE::PREVIEW_VIDEO_ROTATION_ACTION action);

	virtual void OnNoVideoDeviceIsUseful();
	virtual void OnSelectedVideoDeviceIsChanged(); 
	virtual void OnNoWindowToShowPreview();
	virtual void onComputerCamDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ICameraInfo*>* pNewCameraList);
	virtual void onDefaultCamDeviceChanged(const wchar_t* deviceId, const wchar_t* deviceName) {}
private:
	CSDKVideoSettingsUIEvent* m_pVideoSettingsUIEvent;
	ZOOM_SDK_NAMESPACE::ISettingService* m_pSettingsService;
	ZOOM_SDK_NAMESPACE::IVideoSettingContext* m_pVideoSettingsContext;
	ZOOM_SDK_NAMESPACE::ITestVideoDeviceHelper* m_pTestVideoDeviceHelper;
};