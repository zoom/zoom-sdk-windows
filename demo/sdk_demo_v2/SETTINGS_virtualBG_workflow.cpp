#include "stdafx.h"
#include "SETTINGS_virtualBG_workflow.h"

CSDKVirtualBGSettingsWorkFlow::CSDKVirtualBGSettingsWorkFlow()
{
	m_pSettingService = NULL;
	m_pVBGSettingContext = NULL;
	m_pVideoSettingsContext = NULL;
	m_pTestVideoDeviceHelper = NULL;
	Init();
}
CSDKVirtualBGSettingsWorkFlow::~CSDKVirtualBGSettingsWorkFlow()
{
	m_pSettingService = NULL;
	m_pVBGSettingContext = NULL;
	m_pTestVideoDeviceHelper = NULL;
	m_pVideoSettingsContext = NULL;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKVirtualBGSettingsWorkFlow::Init()
{
	if(NULL == m_pSettingService)
	{
		m_pSettingService = SDKInterfaceWrap::GetInst().GetSettingService();
	}
	if(m_pSettingService)
	{
		m_pVBGSettingContext = m_pSettingService->GetVirtualBGSettings();
		m_pVideoSettingsContext = m_pSettingService->GetVideoSettings();
	}
	if(NULL == m_pVBGSettingContext)
	{
		return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
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
	return ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
}

bool CSDKVirtualBGSettingsWorkFlow::IsSupportVirtualBG()
{
	if(m_pVBGSettingContext)
		return m_pVBGSettingContext->IsSupportVirtualBG();
	return false;
}

bool CSDKVirtualBGSettingsWorkFlow::IsSupportSmartVirtualBG()
{
	if(m_pVBGSettingContext)
		return m_pVBGSettingContext->IsSupportSmartVirtualBG();
	return false;
}

bool CSDKVirtualBGSettingsWorkFlow::IsUsingGreenScreenOn()
{
	if(m_pVBGSettingContext)
		return m_pVBGSettingContext->IsUsingGreenScreenOn ();
	return false;
}

DWORD CSDKVirtualBGSettingsWorkFlow::GetBGReplaceColor()
{
	if(m_pVBGSettingContext)
		return m_pVBGSettingContext->GetBGReplaceColor();
	return 0;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKVirtualBGSettingsWorkFlow::SetUsingGreenScreen(bool bUse)
{
	if(m_pVBGSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVBGSettingContext->SetUsingGreenScreen(bUse);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKVirtualBGSettingsWorkFlow::AddBGImage(const wchar_t* file_path, bkItemType itemType)
{
	if(m_pVBGSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		if (virtualbackground_type_image == itemType)
			err = m_pVBGSettingContext->AddBGImage(file_path);
		else if (virtualbackground_type_video == itemType)
			err = m_pVBGSettingContext->AddBGVideo(file_path);
		else
			err = ZOOM_SDK_NAMESPACE::SDKERR_INVALID_PARAMETER;
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKVirtualBGSettingsWorkFlow::RemoveBGImage(ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* pRemoveImage, bkItemType itemType)
{
	if(m_pVBGSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		if (virtualbackground_type_image == itemType)
			err = m_pVBGSettingContext->RemoveBGImage(pRemoveImage);
		else if (virtualbackground_type_video == itemType)
			err = m_pVBGSettingContext->RemoveBGVideo(pRemoveImage);
		else
			err = ZOOM_SDK_NAMESPACE::SDKERR_INVALID_PARAMETER;
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* >* CSDKVirtualBGSettingsWorkFlow::GetBGImageList()
{
	if(m_pVBGSettingContext)
	{
		return m_pVBGSettingContext->GetBGImageList();
	}
	return NULL;
}

ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* >* CSDKVirtualBGSettingsWorkFlow::GetBGVideoList()
{
	if (m_pVBGSettingContext)
	{
		return m_pVBGSettingContext->GetBGVideoList();
	}
	return NULL;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKVirtualBGSettingsWorkFlow::UseBGImage(ZOOM_SDK_NAMESPACE::IVirtualBGImageInfo* pImage, bkItemType itemType)
{
	if(m_pVBGSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		if (virtualbackground_type_image == itemType)
			err = m_pVBGSettingContext->UseBGImage(pImage);
		else if (virtualbackground_type_video == itemType)
			err = m_pVBGSettingContext->UseBGVideo(pImage);
		else
			err = ZOOM_SDK_NAMESPACE::SDKERR_INVALID_PARAMETER;
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKVirtualBGSettingsWorkFlow::BeginSelectReplaceVBColor()
{
	if(m_pVBGSettingContext)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pVBGSettingContext->BeginSelectReplaceVBColor();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKVirtualBGSettingsWorkFlow::SetVideoPreviewParentWnd(HWND hParentWnd, RECT rc /* = _SDK_TEST_VIDEO_INIT_RECT */)
{
	if(m_pTestVideoDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestVideoDeviceHelper->SetVideoPreviewParentWnd(hParentWnd,rc);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CSDKVirtualBGSettingsWorkFlow::TestVideoStartPreview(const wchar_t* deviceID /* = NULL */)
{
	if(m_pTestVideoDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestVideoDeviceHelper->TestVideoStartPreview(deviceID);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKVirtualBGSettingsWorkFlow::TestVideoStopPreview()
{
	if(m_pTestVideoDeviceHelper)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pTestVideoDeviceHelper->TestVideoStopPreview();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
