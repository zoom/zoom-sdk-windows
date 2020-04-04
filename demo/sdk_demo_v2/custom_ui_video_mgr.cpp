#include "stdafx.h"
#include "custom_ui_video_mgr.h"

CCustomizeUIVideoMgr::CCustomizeUIVideoMgr(CCustomizeInMeetingUIMgr* pMainUI)
{
	m_pMainUI = pMainUI;
	m_pCustomizedContainer = NULL;
}
void CCustomizeUIVideoMgr::CreateCustomVideoContainer(ZOOM_SDK_NAMESPACE::ICustomizedUIMgr* pUIMgr, HWND hParent, RECT rc)
{
	if(!m_pMainUI)
		return;
	/*
	if(m_pCustomizedContainer)
	{
		m_customUIVideoFlow.SetVideoContainer(m_pCustomizedContainer);
		return;
	}
	*/
	if(pUIMgr && ::IsWindow(hParent))
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pUIMgr->CreateVideoContainer(&m_pCustomizedContainer, hParent, rc);
		if ((err == ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS) && m_pCustomizedContainer )
		{
			m_customUIVideoFlow.SetVideoContainer(m_pCustomizedContainer);
			m_pCustomizedContainer->SetEvent(dynamic_cast<ZOOM_SDK_NAMESPACE::ICustomizedVideoContainerEvent*>(m_pMainUI));
			SetParentHWND(hParent);
			m_rcActiveView = rc;
		}
	}
}

void CCustomizeUIVideoMgr::DestroyCustomVideoContainer()
{
	if(!m_pMainUI)
		return;
	if(m_pMainUI->GetCustomizedMgr())
	{
		m_pMainUI->GetCustomizedMgr()->DestroyVideoContainer(m_pCustomizedContainer);
		m_pCustomizedContainer = NULL;
	}
}

void CCustomizeUIVideoMgr::init()
{
	m_pActiveElem = NULL;
	m_pPreviewElem = NULL;
	m_hParentWnd = NULL;
	m_iVideoCountInOnePage = GalleryView_Need_Init;
	m_bNeedInitGalleryView = true;
	m_iGalleryCurrentPage = 1;
	m_iGalleryTotalPage = 1;
	m_bIsGalleryViewShown = false;
	ZeroMemory(m_pNormalElemGallery, NormalVideo_Elem_MaxCount*sizeof(m_pNormalElemGallery[0]));
	m_bIsGalleryViewShown = false;
}

void CCustomizeUIVideoMgr::uninit()
{
	DestroyPreviewVideo();
	DestroyActiveViewVideo();
	DestroyGalleryViewVideo();
	DestroyCustomVideoContainer();
}

void CCustomizeUIVideoMgr::SetEvent(ZOOM_SDK_NAMESPACE::ICustomizedVideoContainerEvent* pEvent)
{
		m_customUIVideoFlow.SetEvent(pEvent);
}

void CCustomizeUIVideoMgr::Show()
{
	m_customUIVideoFlow.Show();
}

void CCustomizeUIVideoMgr::DestroyPreviewVideo()
{
	if(m_pPreviewElem)
	{
		m_customUIVideoFlow.HidePreviewVideo(m_pPreviewElem);
		m_customUIVideoFlow.DestroryVideoElementFlow(m_pPreviewElem);
		m_pPreviewElem = NULL;
	}
}

void CCustomizeUIVideoMgr::DestroyActiveViewVideo()
{
	if(m_pActiveElem)
	{
		m_customUIVideoFlow.HideActiveViewVideo(m_pActiveElem);
		m_customUIVideoFlow.DestroryVideoElementFlow(m_pActiveElem);
		m_pActiveElem = NULL;
	}
}

void CCustomizeUIVideoMgr::DestroyGalleryViewVideo()
{
	for (int i = 0; i < NormalVideo_Elem_MaxCount; i++)
	{
		if(m_pNormalElemGallery[i])
		{	
			ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pVideoElement = m_pNormalElemGallery[i];
			if (pVideoElement )
			{
				m_customUIVideoFlow.HideGalleryViewVideo(pVideoElement);
				m_customUIVideoFlow.DestroryVideoElementFlow(dynamic_cast<ZOOM_SDK_NAMESPACE::IVideoRenderElement*>(pVideoElement));
				m_pNormalElemGallery[i] = NULL;
			}
		}
	}
}

void CCustomizeUIVideoMgr::CreateGalleryViewVideo()
{
	for (int i = 0; i < NormalVideo_Elem_MaxCount; i++)
	{
		ZOOM_SDK_NAMESPACE::IVideoRenderElement* pVideoElement = NULL;
		if(!m_pNormalElemGallery[i])
		{	
			m_customUIVideoFlow.CreateVideoElementFlow(&pVideoElement, ZOOM_SDK_NAMESPACE::VideoRenderElement_NORMAL);
			ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pNormalVideoElement = dynamic_cast<ZOOM_SDK_NAMESPACE::INormalVideoRenderElement*>(pVideoElement);
			if(pNormalVideoElement)
			{
				m_pNormalElemGallery[i] = pNormalVideoElement;
			}
		}
	}
}

void CCustomizeUIVideoMgr::ShowPreviewVideo(RECT rc)
{
	if(NULL == m_pPreviewElem)
	{	
		ZOOM_SDK_NAMESPACE::IVideoRenderElement* pVideoElement = NULL;
		m_customUIVideoFlow.CreateVideoElementFlow(&pVideoElement, ZOOM_SDK_NAMESPACE::VideoRenderElement_PRVIEW);
		m_pPreviewElem = dynamic_cast<ZOOM_SDK_NAMESPACE::IPreviewVideoRenderElement*>(pVideoElement);
		if(NULL == m_pPreviewElem)
			return;
	}
	m_customUIVideoFlow.ShowPreviewVideo(m_pPreviewElem, rc);
	m_rcActiveView = rc;
}

void CCustomizeUIVideoMgr::HidePreviewVideo()
{
	if(!m_pPreviewElem)
		return;
	m_customUIVideoFlow.HidePreviewVideo(m_pPreviewElem);
}


void CCustomizeUIVideoMgr::ShowActiveViewVideo()
{
	if(NULL == m_pActiveElem)
	{
		ZOOM_SDK_NAMESPACE::IVideoRenderElement* pVideoElement = NULL;
		m_customUIVideoFlow.CreateVideoElementFlow(&pVideoElement, ZOOM_SDK_NAMESPACE::VideoRenderElement_ACTIVE);
		m_pActiveElem = dynamic_cast<ZOOM_SDK_NAMESPACE::IActiveVideoRenderElement*>(pVideoElement);
		if(NULL == m_pActiveElem)
			return;
	}
	m_customUIVideoFlow.ShowActiveViewVideo(m_pActiveElem, m_rcActiveView);
}

void CCustomizeUIVideoMgr::HideActiveViewVideo()
{
	if(!m_pActiveElem)
		return;
	m_customUIVideoFlow.HideActiveViewVideo(m_pActiveElem);
}


void CCustomizeUIVideoMgr::ShowGalleryViewVideo(GalleryViewSubscribeType nType)
{	
	CreateGalleryViewVideo();
	ReSubscribeNormalUser(nType);
	int nElementHight = (m_rcGalleryView.bottom-m_rcGalleryView.top)/m_iVideoCountInOnePage;
	int iShowed = 0;
	for (int i = 0; i < m_iVideoCountInOnePage; i++)
	{
		ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pElementNormal = m_pNormalElemGallery[i];
		if (pElementNormal)
		{
			RECT element_rc_ = m_rcGalleryView;
			element_rc_.top = iShowed * nElementHight;
			element_rc_.bottom = nElementHight + element_rc_.top;
			pElementNormal->SetPos(element_rc_);

			if (pElementNormal->GetCurrentRenderUserId() > 0)
			{
				m_customUIVideoFlow.ShowGalleryViewVideo(pElementNormal, element_rc_);
				iShowed++;
				m_bIsGalleryViewShown = true;
			}
			else
			{
				m_customUIVideoFlow.HideGalleryViewVideo(pElementNormal);
			}
		}
	}
}

void CCustomizeUIVideoMgr::HideGalleryViewVideo()
{
	for (int i = 0; i < m_iVideoCountInOnePage; i++)
	{
		ZOOM_SDK_NAMESPACE::INormalVideoRenderElement* pElementNormal = m_pNormalElemGallery[i];
		if (pElementNormal)
		{
			m_customUIVideoFlow.HideGalleryViewVideo(pElementNormal);
		}
	}
	m_bIsGalleryViewShown = false;
	//reized the active view here
}

int CCustomizeUIVideoMgr::getVideoGalleryPage()
{
	return m_iGalleryTotalPage;
}

int CCustomizeUIVideoMgr::getVideoGalleryCurrPage()
{
	return m_iGalleryCurrentPage;
}

void CCustomizeUIVideoMgr::SetGalleryViewStatus(bool bIn)
{
	m_bIsGalleryViewShown = bIn;
}

void CCustomizeUIVideoMgr::CalulateViewRect()
{
	CalculateCurrentActiveViewRect();
}

void CCustomizeUIVideoMgr::CalculateCurrentActiveViewRect()
{
	RECT rcMain = {0};
	if(m_hParentWnd && ::IsWindow(m_hParentWnd))
	{
		::GetClientRect(m_hParentWnd, &rcMain);
		rcMain.bottom = rcMain.bottom-rcMain.top;
		rcMain.top = 0;
		rcMain.right = rcMain.right - rcMain.left;
		rcMain.left = 0;
		rcMain.bottom = rcMain.bottom - DEFAULT_TOOLBAR_HEIGHT;
		if(m_bIsGalleryViewShown)
		{
			int nWidth = rcMain.right - rcMain.left - VideoElement_Normal_width;
			rcMain.right = nWidth;
			CalculateCurrentGalleryViewRect();
		}
		m_rcActiveView = rcMain;
	}
}

void CCustomizeUIVideoMgr::CalculateCurrentGalleryViewRect()
{
	RECT rcMain = {0};
	if(!m_bIsGalleryViewShown)
		return;

	if(m_hParentWnd && ::IsWindow(m_hParentWnd))
	{
		::GetClientRect(m_hParentWnd, &rcMain);
		rcMain.bottom = rcMain.bottom-rcMain.top;
		rcMain.top = 0;
		rcMain.right = rcMain.right - rcMain.left;
		rcMain.left = 0;

		rcMain.bottom = rcMain.bottom - DEFAULT_TOOLBAR_HEIGHT;
		int nWidth = rcMain.right - rcMain.left - VideoElement_Normal_width;
		rcMain.left = nWidth;
		m_rcGalleryView = rcMain;
	}
}

void CCustomizeUIVideoMgr::CalculateCountInOnePages()
{
	if(m_hParentWnd && IsWindow(m_hParentWnd))
	{
		int nCount = (m_rcActiveView.bottom - m_rcActiveView.top) / VideoElement_Normal_height; 
		if( 0 >= nCount)
			nCount = 1;
		if(nCount > NormalVideo_Elem_MaxCount)
			nCount = NormalVideo_Elem_MaxCount;
		m_iVideoCountInOnePage = nCount;
	}
}

void CCustomizeUIVideoMgr::CalculateTotalPages()
{
	do 
	{
		if(!m_pMainUI)
			break;
		CSDKUserList* pUserList = m_pMainUI->GetUserList();
		if(!pUserList)
			break;

		CalculateCountInOnePages();
		int nUserCount = pUserList->GetCount();
		m_iGalleryTotalPage = nUserCount/m_iVideoCountInOnePage;
		if (nUserCount % m_iVideoCountInOnePage > 0)
			++m_iGalleryTotalPage;
		if(m_iGalleryTotalPage < m_iGalleryCurrentPage)
			m_iGalleryCurrentPage = m_iGalleryTotalPage;
	} while (0);
}

void CCustomizeUIVideoMgr::ReSubscribeNormalUser(GalleryViewSubscribeType nType)
{
	CalculateTotalPages();
	if (0 == m_iGalleryTotalPage)
		return;
	if (!m_pMainUI)
		return;
	CSDKUserList* pUserList = m_pMainUI->GetUserList();
	if(!pUserList)
		return;

	int nStart = 0;
	int nCurrentPage = m_iGalleryCurrentPage;
	switch(nType)
	{
	case GalleryView_Subscribe_CurrentPage:
		break;
	case GalleryView_Subscribe_PrePage:
		nCurrentPage -= 1;
		if(nCurrentPage < 1)
			return;
		break;
	case GalleryView_Subscribe_NextPage:
		nCurrentPage += 1;
		break;
	default:
		break;
	}
	nStart = (nCurrentPage-1) * m_iVideoCountInOnePage;
	int nTotalCount = pUserList->GetCount();
	if (nStart > nTotalCount - 1)
		return;

	if(nStart < 0 )
		nStart = 0;
	
	m_iGalleryCurrentPage = nCurrentPage;
	int nElemIndex = 0;
	for (int i = nStart; (i < nTotalCount && nElemIndex < m_iVideoCountInOnePage); i++)
	{
		ZOOM_SDK_NAMESPACE::IUserInfo* pUser = pUserList->GetItem(i);
		if(!pUser)
			continue;
		unsigned int nUserID = pUser->GetUserID();

		if (0 == nUserID || NULL == m_pNormalElemGallery[nElemIndex] || pUser->IsInWaitingRoom())
			continue;

		if (nUserID != m_pNormalElemGallery[nElemIndex]->GetCurrentRenderUserId())
		{
			m_pNormalElemGallery[nElemIndex]->Subscribe(nUserID);
			nElemIndex++;
		}
		else if(nUserID == m_pNormalElemGallery[nElemIndex]->GetCurrentRenderUserId() && GalleryView_Subscribe_CurrentPage == nType)
		{
			nElemIndex++;
		}
	}

	if (nElemIndex < (m_iVideoCountInOnePage-1))
	{
		for (;nElemIndex < m_iVideoCountInOnePage; nElemIndex++)
		{
			if (NULL == m_pNormalElemGallery[nElemIndex])
				continue;
			if (0 != m_pNormalElemGallery[nElemIndex]->GetCurrentRenderUserId())
				m_pNormalElemGallery[nElemIndex]->Unsubscribe(m_pNormalElemGallery[nElemIndex]->GetCurrentRenderUserId());
		}
	}
}

void CCustomizeUIVideoMgr::HandleSizeChanged(RECT newRC)
{
	m_customUIVideoFlow.HandleSizeChanged(newRC);
}

void CCustomizeUIVideoMgr::HandleUserChanged()
{
	CalculateTotalPages();
	if(m_bIsGalleryViewShown)
	{
		ShowGalleryViewVideo(GalleryView_Subscribe_CurrentPage);
	}
}
void CCustomizeUIVideoMgr::HandleSwitchGalleryPage(ArrowButtonType btnType)
{
	GalleryViewSubscribeType nType = GalleryView_Subscribe_CurrentPage;
	switch(btnType)
	{
	case Arrow_button_up:
		nType = GalleryView_Subscribe_PrePage;
		break;
	case Arrow_button_down:
		nType = GalleryView_Subscribe_NextPage;
		break;
	default:
		break;
	}
	ShowGalleryViewVideo(nType);
}
void CCustomizeUIVideoMgr::HandleVideoRenderElementDestroyed(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement)
{
	if (pElement)
	{
		switch (pElement->GetType())
		{
		case ZOOM_SDK_NAMESPACE::VideoRenderElement_PRVIEW:
			{
				if(m_pPreviewElem)
				{
					HidePreviewVideo();
					m_pPreviewElem= NULL;					
				}				
			}
			break;
		case ZOOM_SDK_NAMESPACE::VideoRenderElement_ACTIVE:
			{
				m_pActiveElem = NULL;
			}
			break;
		case ZOOM_SDK_NAMESPACE::VideoRenderElement_NORMAL:
			{
				//todo
				for (int i = 0; i < NormalVideo_Elem_MaxCount; i++)
				{
					if(m_pNormalElemGallery[i])
					{
						ZOOM_SDK_NAMESPACE::IVideoRenderElement* pVideoElement = dynamic_cast<ZOOM_SDK_NAMESPACE::IVideoRenderElement*>(m_pNormalElemGallery[i]);
						if (pVideoElement == pElement)
						{
							m_pNormalElemGallery[i] = NULL;
						}
					}
				}

			}
			break;
		}
	}
}
void CCustomizeUIVideoMgr::HandleVideoContainerDestroyed(ZOOM_SDK_NAMESPACE::ICustomizedVideoContainer* pContainer)
{
	//to do
}

RECT CCustomizeUIVideoMgr::GetCurrentAcviteViewRect()
{
	return m_rcActiveView;
}

RECT CCustomizeUIVideoMgr::GetCurrentGalleryViewRect()
{
	return m_rcGalleryView;
}