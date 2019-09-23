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
};
class CSDKVideoSettingsWorkFlow:public ZOOM_SDK_NAMESPACE::ITestVideoDeviceHelperEvent,ZOOM_SDK_NAMESPACE::IVideoSettingContextEvent
{
public:
	CSDKVideoSettingsWorkFlow();
	virtual ~CSDKVideoSettingsWorkFlow();
	bool Init();
	void Cleanup(){}
	void SetUIEvent(CSDKVideoSettingsUIEvent* event_);
	///video setting context
	ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ICameraInfo*>* GetCameraList();
	bool EnableVideoMirrorEffect(bool bEnable);
	bool EnableFaceBeautyEffect(bool bEnable);
	bool EnableHDVideo(bool bEnable);
	bool EnableAlwaysShowNameOnVideo(bool bEnable);
	bool EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable);
	bool EnableAlwaysUse16v9(bool bEnable);
	bool EnableSpotlightSelf(bool bEnable);
	bool EnableHardwareEncode(bool bEnable);
	bool Enable49VideoesInGallaryView(bool bEnable);
	bool EnableHideNoVideoUsersOnWallView(bool bEnable);
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
	bool SetVideoPreviewParentWnd(HWND hParentWnd, RECT rc = ZOOM_SDK_NAMESPACE::_SDK_TEST_VIDEO_INIT_RECT);
	bool TestVideoStartPreview(const wchar_t* deviceID = NULL);
	bool TestVideoStopPreview();
	bool TestVideoRotate(ZOOM_SDK_NAMESPACE::PREVIEW_VIDEO_ROTATION_ACTION action);

	virtual void OnNoVideoDeviceIsUseful();
	virtual void OnSelectedVideoDeviceIsChanged(); 
	virtual void OnNoWindowToShowPreview();
	virtual void onComputerCamDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ICameraInfo*>* pNewCameraList);
private:
	CSDKVideoSettingsUIEvent* m_pVideoSettingsUIEvent;
	ZOOM_SDK_NAMESPACE::ISettingService* m_pSettingsService;
	ZOOM_SDK_NAMESPACE::IVideoSettingContext* m_pVideoSettingsContext;
	ZOOM_SDK_NAMESPACE::ITestVideoDeviceHelper* m_pTestVideoDeviceHelper;
};