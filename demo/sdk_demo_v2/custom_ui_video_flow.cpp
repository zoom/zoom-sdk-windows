#include "stdafx.h"
#include "custom_ui_video_flow.h"

CCustomizeUIVideoFlow::CCustomizeUIVideoFlow()
{
	Reset();
}

CCustomizeUIVideoFlow::~CCustomizeUIVideoFlow()
{
	Reset();
}

void CCustomizeUIVideoFlow::Reset()
{
	m_pVideoContainer = NULL;
}

void CCustomizeUIVideoFlow::SetVideoContainer(ZOOM_SDK_NAMESPACE::ICustomizedVideoContainer* pContainer)
{
	m_pVideoContainer = pContainer;
}

void CCustomizeUIVideoFlow::SetEvent(ZOOM_SDK_NAMESPACE::ICustomizedVideoContainerEvent* pEvent)
{
	if(m_pVideoContainer)
		m_pVideoContainer->SetEvent(pEvent);
}

void CCustomizeUIVideoFlow::Show()
{
	if(m_pVideoContainer)
		m_pVideoContainer->Show();
}

ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIVideoFlow::DestroryVideoElementFlow(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pVideoElement)
{
	if(m_pVideoContainer && pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = m_pVideoContainer->DestroyVideoElement(pVideoElement);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIVideoFlow::CreateVideoElementFlow(ZOOM_SDK_NAMESPACE::IVideoRenderElement** pVideoElement,ZOOM_SDK_NAMESPACE::VideoRenderElementType type)
{
	if(m_pVideoContainer)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = m_pVideoContainer->CreateVideoElement(pVideoElement, type);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIVideoFlow::ShowPreviewVideo(ZOOM_SDK_NAMESPACE::IPreviewVideoRenderElement* pVideoElement, RECT rc)
{
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->SetPos(rc);
		err = pVideoElement->Start();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIVideoFlow::HidePreviewVideo(ZOOM_SDK_NAMESPACE::IPreviewVideoRenderElement* pVideoElement)
{
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->Stop();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIVideoFlow::ShowActiveViewVideo(ZOOM_SDK_NAMESPACE::IActiveVideoRenderElement* pVideoElement, RECT rc)
{
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->SetPos(rc);
		err = pVideoElement->Start();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIVideoFlow::HideActiveViewVideo(ZOOM_SDK_NAMESPACE::IActiveVideoRenderElement* pVideoElement)
{
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->Stop();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIVideoFlow::ShowGalleryViewVideo(ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement, RECT rc)
{
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->SetPos(rc);
		if(pVideoElement->GetCurrentRenderUserId() > 0)
			err = pVideoElement->Show();
		else
			err = pVideoElement->Hide();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIVideoFlow::HideGalleryViewVideo(ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement)
{
	bool bRet = false;
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->Hide();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIVideoFlow::SubscribeVideoSource(ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement, unsigned int userID)
{
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->Subscribe(userID);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIVideoFlow::UnSubscribeVideoSource(ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement, unsigned int userID)
{
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->Unsubscribe(userID);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIVideoFlow::SetVideoElementPos(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pVideoElement, RECT rc)
{
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->SetPos(rc);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}

ZOOM_SDK_NAMESPACE::SDKError CCustomizeUIVideoFlow::HandleSizeChanged(RECT newRC)
{
	if(m_pVideoContainer)
		return m_pVideoContainer->Resize(newRC);
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}