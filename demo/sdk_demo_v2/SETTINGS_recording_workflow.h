#pragma once
#include "sdk_util.h"
#include "stdafx.h"
#include "setting_service_interface.h"

class CSDKRecordingSettingsWorkFlow
{
public:
	CSDKRecordingSettingsWorkFlow();
	virtual ~CSDKRecordingSettingsWorkFlow();
	ZOOM_SDK_NAMESPACE::SDKError Init();
	void Cleanup(){}
	ZOOM_SDK_NAMESPACE::SDKError SetRecordingPath(const wchar_t* szPath);
	const wchar_t* GetRecordingPath();
	
	const wchar_t* GetRecordingManagementURL();
	ZOOM_SDK_NAMESPACE::SDKError CanGetRecordingManagementURL(bool& m_bEnable);
	ZOOM_SDK_NAMESPACE::SDKError EnableSelectRecordFileLocationAfterMeeting(bool m_bEnable);
	bool IsSelectRecordFileLocationAfterMeetingEnabled();
	ZOOM_SDK_NAMESPACE::SDKError EnableMultiAudioStreamRecord(bool m_bEnable);
	bool IsMultiAudioStreamRecordEnabled();
	ZOOM_SDK_NAMESPACE::SDKError EnableAddTimestampWatermark(bool m_bEnable);
	bool IsAddTimestampWatermarkEnabled();
	ZOOM_SDK_NAMESPACE::SDKError EnableOptimizeFor3rdPartyVideoEditor(bool m_bEnable);
	bool IsOptimizeFor3rdPartyVideoEditorEnabled();
	ZOOM_SDK_NAMESPACE::SDKError EnableShowVideoThumbnailWhenShare(bool m_bEnable);
	bool IsShowVideoThumbnailWhenShareEnabled();
	ZOOM_SDK_NAMESPACE::SDKError EnablePlaceVideoNextToShareInRecord(bool m_bEnable);
	bool IsPlaceVideoNextToShareInRecordEnabled();
	
private:
	ZOOM_SDK_NAMESPACE::ISettingService* m_pSettingService;
	ZOOM_SDK_NAMESPACE::IRecordingSettingContext* m_pRecordingSettingContext;
};