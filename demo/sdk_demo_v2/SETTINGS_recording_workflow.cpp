#include "stdafx.h"
#include "SETTINGS_recording_workflow.h"
CSDKRecordingSettingsWorkFlow::CSDKRecordingSettingsWorkFlow()
{
	m_pSettingService = NULL;
	m_pRecordingSettingContext = NULL;
	Init();
}
CSDKRecordingSettingsWorkFlow::~CSDKRecordingSettingsWorkFlow()
{
	m_pSettingService = NULL;
	m_pRecordingSettingContext = NULL;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKRecordingSettingsWorkFlow::Init()
{
	if(NULL == m_pSettingService)
	{
		m_pSettingService = SDKInterfaceWrap::GetInst().GetSettingService();
	}
	if(m_pSettingService)
	{
		m_pRecordingSettingContext = m_pSettingService->GetRecordingSettings();
	}
	if(NULL == m_pRecordingSettingContext)
	{
		return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKRecordingSettingsWorkFlow::SetRecordingPath(const wchar_t* szPath)
{
	if(m_pRecordingSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pRecordingSettingContext->SetRecordingPath(szPath);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
const wchar_t* CSDKRecordingSettingsWorkFlow::GetRecordingPath()
{
	if(m_pRecordingSettingContext)
	{
		const wchar_t* Path = m_pRecordingSettingContext->GetRecordingPath();
		if(Path != NULL)
		{
			return Path;
		}
	}
	return NULL;
}

const wchar_t* CSDKRecordingSettingsWorkFlow::GetRecordingManagementURL()
{
	if(m_pRecordingSettingContext)
	{
		const wchar_t* RecordingManagementURL = m_pRecordingSettingContext->GetRecordingManagementURL();

		if(RecordingManagementURL != NULL)
		{
			return RecordingManagementURL;
		}
	}
	return NULL;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKRecordingSettingsWorkFlow::CanGetRecordingManagementURL(bool& m_bEnable)
{
	if(m_pRecordingSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pRecordingSettingContext->CanGetRecordingManagementURL(m_bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKRecordingSettingsWorkFlow::EnableSelectRecordFileLocationAfterMeeting(bool bEnable)
{
	if(m_pRecordingSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pRecordingSettingContext->EnableSelectRecordFileLocationAfterMeeting(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
bool CSDKRecordingSettingsWorkFlow::IsSelectRecordFileLocationAfterMeetingEnabled()
{
	if(m_pRecordingSettingContext)
	{
		bool bChecked = m_pRecordingSettingContext->IsSelectRecordFileLocationAfterMeetingEnabled();
		return bChecked;
	}
	return false;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKRecordingSettingsWorkFlow::EnableMultiAudioStreamRecord(bool bEnable)
{
	if(m_pRecordingSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pRecordingSettingContext->EnableMultiAudioStreamRecord(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
bool CSDKRecordingSettingsWorkFlow::IsMultiAudioStreamRecordEnabled()
{
	if(m_pRecordingSettingContext)
	{
		bool bChecked = m_pRecordingSettingContext->IsMultiAudioStreamRecordEnabled();
		return bChecked;
	}
	return false;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKRecordingSettingsWorkFlow::EnableAddTimestampWatermark(bool bEnable)
{
	if(m_pRecordingSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pRecordingSettingContext->EnableAddTimestampWatermark(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
bool CSDKRecordingSettingsWorkFlow::IsAddTimestampWatermarkEnabled()
{
	if(m_pRecordingSettingContext)
	{
		bool bChecked = m_pRecordingSettingContext->IsAddTimestampWatermarkEnabled();
		return bChecked;
	}
	return false;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKRecordingSettingsWorkFlow::EnableOptimizeFor3rdPartyVideoEditor(bool bEnable)
{
	if(m_pRecordingSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pRecordingSettingContext->EnableOptimizeFor3rdPartyVideoEditor(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
bool CSDKRecordingSettingsWorkFlow::IsOptimizeFor3rdPartyVideoEditorEnabled()
{
	if(m_pRecordingSettingContext)
	{
		bool bChecked = m_pRecordingSettingContext->IsOptimizeFor3rdPartyVideoEditorEnabled();
		return bChecked;
	}
	return false;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKRecordingSettingsWorkFlow::EnableShowVideoThumbnailWhenShare(bool bEnable)
{
	if(m_pRecordingSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pRecordingSettingContext->EnableShowVideoThumbnailWhenShare(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
bool CSDKRecordingSettingsWorkFlow::IsShowVideoThumbnailWhenShareEnabled()
{
	if(m_pRecordingSettingContext)
	{
		bool bChecked = m_pRecordingSettingContext->IsShowVideoThumbnailWhenShareEnabled();
		return bChecked;
	}
	return false;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKRecordingSettingsWorkFlow::EnablePlaceVideoNextToShareInRecord(bool bEnable)
{
	if(m_pRecordingSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pRecordingSettingContext->EnablePlaceVideoNextToShareInRecord(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
bool CSDKRecordingSettingsWorkFlow::IsPlaceVideoNextToShareInRecordEnabled()
{
	if(m_pRecordingSettingContext)
	{
		bool bChecked = m_pRecordingSettingContext->IsPlaceVideoNextToShareInRecordEnabled();
		return bChecked;
	}
	return false;
}
