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
ZOOM_SDK_NAMESPACE::SDKError CSDKVideoSettingsWorkFlow::Init()
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
				return err;
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
			return err;
		}
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
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
ZOOM_SDK_NAMESPACE::SDKError CSDKVideoSettingsWorkFlow::EnableVideoMirrorEffect(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableVideoMirrorEffect(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKVideoSettingsWorkFlow::EnableFaceBeautyEffect(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableFaceBeautyEffect(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKVideoSettingsWorkFlow::EnableHDVideo(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableHDVideo(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKVideoSettingsWorkFlow::EnableAlwaysShowNameOnVideo(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableAlwaysShowNameOnVideo(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKVideoSettingsWorkFlow::EnableAutoTurnOffVideoWhenJoinMeeting(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableAutoTurnOffVideoWhenJoinMeeting(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKVideoSettingsWorkFlow::EnableAlwaysUse16v9(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableAlwaysUse16v9(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKVideoSettingsWorkFlow::EnableSpotlightSelf(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableSpotlightSelf(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKVideoSettingsWorkFlow::EnableHardwareEncode(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableHardwareEncode(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKVideoSettingsWorkFlow::Enable49VideoesInGallaryView(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->Enable49VideoesInGallaryView(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKVideoSettingsWorkFlow::EnableHideNoVideoUsersOnWallView(bool bEnable)
{
	if(m_pVideoSettingsContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVideoSettingsContext->EnableHideNoVideoUsersOnWallView(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
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
ZOOM_SDK_NAMESPACE::SDKError CSDKVideoSettingsWorkFlow::SetVideoPreviewParentWnd(HWND hParentWnd, RECT rc /* = _SDK_TEST_VIDEO_INIT_RECT */)
{
	if(m_pTestVideoDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestVideoDeviceHelper->SetVideoPreviewParentWnd(hParentWnd,rc);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKVideoSettingsWorkFlow::TestVideoStartPreview(const wchar_t* deviceID /* = NULL */)
{
	if(m_pTestVideoDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestVideoDeviceHelper->TestVideoStartPreview(deviceID);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKVideoSettingsWorkFlow::TestVideoStopPreview()
{
	if(m_pTestVideoDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestVideoDeviceHelper->TestVideoStopPreview();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKVideoSettingsWorkFlow::TestVideoRotate(ZOOM_SDK_NAMESPACE::PREVIEW_VIDEO_ROTATION_ACTION action)
{
	if(m_pTestVideoDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestVideoDeviceHelper->TestVideoRotate(action);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
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