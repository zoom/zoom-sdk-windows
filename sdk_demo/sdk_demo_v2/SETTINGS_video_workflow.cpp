#include "stdafx.h"
#include "SETTINGS_video_workflow.h"
CSDKVideoSettingsWorkFlow::CSDKVideoSettingsWorkFlow()
{
	m_pVideoSettingsUIEvent = NULL;
	m_pSettingsService = NULL;
	m_pVideoSettingsContext = NULL;
	m_pTestVideoDeviceHelper = NULL;
	Init();
}
CSDKVideoSettingsWorkFlow::~CSDKVideoSettingsWorkFlow()
{
	m_pVideoSettingsUIEvent = NULL;
	m_pSettingsService = NULL;
	m_pVideoSettingsContext = NULL;
	m_pTestVideoDeviceHelper = NULL;
}
bool CSDKVideoSettingsWorkFlow::Init()
{
	if(NULL == m_pSettingsService)
	{
		m_pSettingsService = SDKInterfaceWrap::GetInst().GetSettingService();
	}
	if(m_pSettingsService)
	{
		m_pVideoSettingsContext = m_pSettingsService->GetVideoSettings();
		if(m_pVideoSettingsContext)
		{
			ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
			err = m_pVideoSettingsContext->SetVideoDeviceEvent(this);
			if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != err)
			{
				return false;
			}
		}
	}
	if(m_pVideoSettingsContext)
	{
		m_pTestVideoDeviceHelper = m_pVideoSettingsContext->GetTestVideoDeviceHelper();
		if(m_pTestVideoDeviceHelper)
		{
			ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
			err = m_pTestVideoDeviceHelper->SetEvent(this);
			if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
			{
				return true;
			}
		}
	}
	return false;
}
void CSDKVideoSettingsWorkFlow::SetUIEvent(CSDKVideoSettingsUIEvent* event_)
{
	m_pVideoSettingsUIEvent = event_;
}
ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ICameraInfo*>* CSDKVideoSettingsWorkFlow::GetCameraList()
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ICameraInfo*>* list;
		list = m_pVideoSettingsContext->GetCameraList();
		if(NULL != list)
		{
			return list;
		}
	}
	return NULL;
}
bool CSDKVideoSettingsWorkFlow::EnableVideoMirrorEffect(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableVideoMirrorEffect(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::EnableFaceBeautyEffect(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableFaceBeautyEffect(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::EnableHDVideo(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableHDVideo(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::EnableAlwaysShowNameOnVideo(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableAlwaysShowNameOnVideo(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableAutoTurnOffVideoWhenJoinMeeting(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::EnableAlwaysUse16v9(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableAlwaysUse16v9(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::EnableSpotlightSelf(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableSpotlightSelf(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::EnableHardwareEncode(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableHardwareEncode(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::Enable49VideoesInGallaryView(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->Enable49VideoesInGallaryView(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::EnableHideNoVideoUsersOnWallView(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableHideNoVideoUsersOnWallView(bEnable);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;	
}
bool CSDKVideoSettingsWorkFlow::IsVideoMirrorEffectEnabled()
{
	if(m_pVideoSettingsContext)
	{
		bool bChecked = m_pVideoSettingsContext->IsVideoMirrorEffectEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::IsFaceBeautyEffectEnabled()
{
	if(m_pVideoSettingsContext)
	{
		bool bChecked = m_pVideoSettingsContext->IsFaceBeautyEffectEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::IsHDVideoEnabled()
{
	if(m_pVideoSettingsContext)
	{
		bool bChecked = m_pVideoSettingsContext->IsHDVideoEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::IsAlwaysShowNameOnVideoEnabled()
{
	if(m_pVideoSettingsContext)
	{
		bool bChecked = m_pVideoSettingsContext->IsAlwaysShowNameOnVideoEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::IsAutoTurnOffVideoWhenJoinMeetingEnabled()
{
	if(m_pVideoSettingsContext)
	{
		bool bChecked = m_pVideoSettingsContext->IsAutoTurnOffVideoWhenJoinMeetingEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::IsAlwaysUse16v9()
{
	if(m_pVideoSettingsContext)
	{
		bool bChecked = m_pVideoSettingsContext->IsAlwaysUse16v9();
		return bChecked;
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::IsSpotlightSelfEnabled()
{
	if(m_pVideoSettingsContext)
	{
		bool bChecked = m_pVideoSettingsContext->IsSpotlightSelfEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::IsHardwareEncodeEnabled()
{
	if(m_pVideoSettingsContext)
	{
		bool bChecked = m_pVideoSettingsContext->IsHardwareEncodeEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::Is49VideoesInGallaryViewEnabled()
{
	if(m_pVideoSettingsContext)
	{
		bool bChecked = m_pVideoSettingsContext->Is49VideoesInGallaryViewEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::IsHideNoVideoUsersOnWallViewEnabled()
{
	if(m_pVideoSettingsContext)
	{
		bool bChecked = m_pVideoSettingsContext->IsHideNoVideoUsersOnWallViewEnabled();
		return bChecked;
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::SetVideoPreviewParentWnd(HWND hParentWnd, RECT rc /* = _SDK_TEST_VIDEO_INIT_RECT */)
{
	if(m_pTestVideoDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestVideoDeviceHelper->SetVideoPreviewParentWnd(hParentWnd,rc);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::TestVideoStartPreview(const wchar_t* deviceID /* = NULL */)
{
	if(m_pTestVideoDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestVideoDeviceHelper->TestVideoStartPreview(deviceID);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::TestVideoStopPreview()
{
	if(m_pTestVideoDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestVideoDeviceHelper->TestVideoStopPreview();
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
bool CSDKVideoSettingsWorkFlow::TestVideoRotate(ZOOM_SDK_NAMESPACE::PREVIEW_VIDEO_ROTATION_ACTION action)
{
	if(m_pTestVideoDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestVideoDeviceHelper->TestVideoRotate(action);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			return true;
		}
	}
	return false;
}
void CSDKVideoSettingsWorkFlow::onComputerCamDeviceChanged(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ICameraInfo *>* pNewCameraList)
{
	if(m_pVideoSettingsUIEvent)
	{
		m_pVideoSettingsUIEvent->OnComputerCamDeviceChanged(pNewCameraList);
	}
}
void CSDKVideoSettingsWorkFlow::OnNoVideoDeviceIsUseful()
{
	if(m_pVideoSettingsUIEvent)
	{
		m_pVideoSettingsUIEvent->OnNoVideoDeviceIsUseful();
	}
}
void CSDKVideoSettingsWorkFlow::OnNoWindowToShowPreview()
{
	if(m_pVideoSettingsUIEvent)
	{
		m_pVideoSettingsUIEvent->OnNoWindowToShowPreview();
	}
}
void CSDKVideoSettingsWorkFlow::OnSelectedVideoDeviceIsChanged()
{
	if(m_pVideoSettingsUIEvent)
	{
		m_pVideoSettingsUIEvent->OnSelectedVideoDeviceIsChanged();
	}
}