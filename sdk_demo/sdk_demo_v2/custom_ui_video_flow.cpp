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

bool CCustomizeUIVideoFlow::DestroryVideoElementFlow(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pVideoElement)
{
	bool bDeleteSucc = false;
	if(m_pVideoContainer && pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = m_pVideoContainer->DestroyVideoElement(pVideoElement);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
			bDeleteSucc = true;
	}
	return bDeleteSucc;
}

bool CCustomizeUIVideoFlow::CreateVideoElementFlow(ZOOM_SDK_NAMESPACE::IVideoRenderElement** pVideoElement,ZOOM_SDK_NAMESPACE::VideoRenderElementType type)
{
	bool bCreateSucc = false;
	if(m_pVideoContainer)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = m_pVideoContainer->CreateVideoElement(pVideoElement, type);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
			bCreateSucc = true;
	}
	return bCreateSucc;
}

bool CCustomizeUIVideoFlow::ShowPreviewVideo(ZOOM_SDK_NAMESPACE::IPreviewVideoRenderElement* pVideoElement, RECT rc)
{
	bool bRet = false;
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->SetPos(rc);
		err = pVideoElement->Start();
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
			bRet = true;
	}
	return bRet;
}

bool CCustomizeUIVideoFlow::HidePreviewVideo(ZOOM_SDK_NAMESPACE::IPreviewVideoRenderElement* pVideoElement)
{
	bool bRet = false;
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->Stop();
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
			bRet = true;
	}
	return bRet;
}

bool CCustomizeUIVideoFlow::ShowActiveViewVideo(ZOOM_SDK_NAMESPACE::IActiveVideoRenderElement* pVideoElement, RECT rc)
{
	bool bRet = false;
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->SetPos(rc);
		err = pVideoElement->Start();
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
			bRet = true;
	}
	return bRet;
}
bool CCustomizeUIVideoFlow::HideActiveViewVideo(ZOOM_SDK_NAMESPACE::IActiveVideoRenderElement* pVideoElement)
{
	bool bRet = false;
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->Stop();
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
			bRet = true;
	}
	return bRet;
}

bool CCustomizeUIVideoFlow::ShowGalleryViewVideo(ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement, RECT rc)
{
	bool bRet = false;
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->SetPos(rc);
		if(pVideoElement->GetCurrentRenderUserId() > 0)
			err = pVideoElement->Show();
		else
			err = pVideoElement->Hide();
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
			bRet = true;
	}
	return bRet;
}
bool CCustomizeUIVideoFlow::HideGalleryViewVideo(ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement)
{
	bool bRet = false;
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->Hide();
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
			bRet = true;
	}
	return bRet;
}
bool CCustomizeUIVideoFlow::SubscribeVideoSource(ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement, unsigned int userID)
{
	bool bRet = false;
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->Subscribe(userID);
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
			bRet = true;
	}
	return bRet;
}
bool CCustomizeUIVideoFlow::UnSubscribeVideoSource(ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement, unsigned int userID)
{
	bool bRet = false;
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->Unsubscribe(userID);
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
			bRet = true;
	}
	return bRet;
}

bool CCustomizeUIVideoFlow::SetVideoElementPos(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pVideoElement, RECT rc)
{
	bool bRet = false;
	if(pVideoElement)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pVideoElement->SetPos(rc);
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
			bRet = true;
	}
	return bRet;
}

void CCustomizeUIVideoFlow::HandleSizeChanged(RECT newRC)
{
	if(m_pVideoContainer)
		m_pVideoContainer->Resize(newRC);
}