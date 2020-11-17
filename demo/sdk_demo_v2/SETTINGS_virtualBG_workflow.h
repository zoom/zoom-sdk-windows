#pragma once
#include "sdk_util.h"
#include "stdafx.h"
#include "sdk_demo_app_common.h"
#include "setting_service_interface.h"

class CSDKVirtualBGUIEvent
{
public:
	virtual void onVBImageDidDownloaded() = 0;
	virtual void onGreenVBDidUpdateWithReplaceColor(DWORD selectedColor) = 0;
	virtual void onSelectedVBImageChanged() = 0;
};

class CSDKVirtualBGSettingsWorkFlow:public ZOOM_SDK_NAMESPACE::ITestVideoDeviceHelperEvent
{
public:
	CSDKVirtualBGSettingsWorkFlow();
	virtual ~CSDKVirtualBGSettingsWorkFlow();
	ZOOM_SDK_NAMESPACE::SDKError Init();

	bool IsSupportVirtualBG();
	bool IsSupportSmartVirtualBG();
	bool IsUsingGreenScreenOn();
	DWORD GetBGReplaceColor();

	ZOOM_SDK_NAMESPACE::SDKError SetUsingGreenScreen(bool bUse);
	ZOOM_SDK_NAMESPACE::SDKError AddBGImage(const wchar_t* file_path, bkItemType itemType);
	ZOOM_SDK_NAMESPACE::SDKError RemoveBGImage(ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* pRemoveImage, bkItemType itemType);
	ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* >* GetBGImageList();
	ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* >* GetBGVideoList();
	ZOOM_SDK_NAMESPACE::SDKError UseBGImage(ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* pImage, bkItemType itemType);
	ZOOM_SDK_NAMESPACE::SDKError BeginSelectReplaceVBColor();
	ZOOM_SDK_NAMESPACE::SDKError SetVideoPreviewParentWnd(HWND hParentWnd, RECT rc /* = _SDK_TEST_VIDEO_INIT_RECT */);
	ZOOM_SDK_NAMESPACE::SDKError TestVideoStartPreview(const wchar_t* deviceID /* = NULL */);
	ZOOM_SDK_NAMESPACE::SDKError TestVideoStopPreview();

	//ITestVideoDeviceHelperEvent
	virtual void OnNoVideoDeviceIsUseful() {}
	virtual void OnSelectedVideoDeviceIsChanged() {}
	virtual void OnNoWindowToShowPreview() {}

private:
	ZOOM_SDK_NAMESPACE::ISettingService* m_pSettingService;
	ZOOM_SDK_NAMESPACE::IVirtualBGSettingContext* m_pVBGSettingContext;
	ZOOM_SDK_NAMESPACE::IVideoSettingContext* m_pVideoSettingsContext;
	ZOOM_SDK_NAMESPACE::ITestVideoDeviceHelper* m_pTestVideoDeviceHelper;
};