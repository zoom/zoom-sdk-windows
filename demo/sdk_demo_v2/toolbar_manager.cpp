#include "stdafx.h"
#include "toolbar_manager.h"

CToolbarMgr& CToolbarMgr::GetInstance()
{
	static CToolbarMgr instance_;
	return instance_;
}

CToolbarMgr::CToolbarMgr():m_ToolbarBottom(NULL)
{
	m_hParentWnd = NULL;
	m_pAppEvent = NULL;
	m_pMeetingService = NULL;
	IsMeetingServiceReady();
}

CToolbarMgr::~CToolbarMgr()
{
	UnInit();
}

void CToolbarMgr::SetEvent(CSDKDemoAppEvent* pAppEvent)
{
	m_pAppEvent = pAppEvent;
}

void CToolbarMgr::Init()
{

}

void CToolbarMgr::UnInit()
{
	if (m_ToolbarBottom) {
		if (m_ToolbarBottom->IsWindow())
			m_ToolbarBottom->DestroyWindow();

		delete m_ToolbarBottom;
		m_ToolbarBottom = NULL;
	}
}

bool CToolbarMgr::SetParentWnd(HWND hParent)
{
	if(!IsWindow(hParent))
		return false;
	m_hParentWnd = hParent;
	GetToolbarBottom();
	return true;
}

HWND CToolbarMgr::GetParentWnd()
{
	return m_hParentWnd;
}
bool CToolbarMgr::IsMeetingServiceReady()
{
	if(NULL == m_pMeetingService)
	{
		m_pMeetingService = SDKInterfaceWrap::GetInst().GetMeetingService();
		if(NULL ==m_pMeetingService)
			return false;
	}
	return true;
}

bool CToolbarMgr::GetMeetingType()
{
	if(NULL != m_pMeetingService)
	{
		ZOOM_SDK_NAMESPACE::IMeetingInfo* meetingInfo = m_pMeetingService->GetMeetingInfo();
		m_meetingType = meetingInfo->GetMeetingType();
		return true;
	}
	return false;
}

bool CToolbarMgr::GetToolbarBottom()
{
	do
	{
		if(NULL == m_hParentWnd)
			break;
		if(NULL == m_ToolbarBottom || !m_ToolbarBottom->IsWindow())
		{
			if(NULL == m_ToolbarBottom)
				m_ToolbarBottom = new CToolbarBottom(this);

			if(NULL == m_ToolbarBottom)
				break;
			
			if (!m_ToolbarBottom->IsWindow()) {
				wchar_t* strTitleName = MEETING_BOTTOM_TOOLBAR_TITLE;
				m_ToolbarBottom->Create(m_hParentWnd, strTitleName, WS_CHILDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_TOPMOST);
			}

			if (!m_ToolbarBottom->IsWindow()) {
				break;
			}

			if (m_ToolbarBottom->GetParent() != m_hParentWnd)
				m_ToolbarBottom->SetParent(m_hParentWnd);
			m_ToolbarBottom->ShowWindow(false);
			return true;
		}	
		else
		{
			return true;
		}
	}while(0);

	return false;
}

bool CToolbarMgr::ShowToolbarBottom()
{
	ResizeToolbarBottom();
	if(m_ToolbarBottom)
	{
		m_ToolbarBottom->ShowWindow(true);
	}
	return true;
}

bool CToolbarMgr::HideToolbarBottom()
{
	if(m_ToolbarBottom)
		m_ToolbarBottom->ShowWindow(false);
	return true;
}

void CToolbarMgr::ResizeToolbarBottom()
{
	if (!m_ToolbarBottom || !m_ToolbarBottom->IsWindow())
		return;

	HWND hParentWnd = m_ToolbarBottom->GetParent();
	if (!::IsWindow(hParentWnd))
		return;

	RECT rcParentClient = { 0 };
	::GetClientRect(hParentWnd, &rcParentClient);
	const int nFitHeight = DEFAULT_TOOLBAR_HEIGHT;
	//int nFitLeft = rcParentClient.left;
	int nFitTop = rcParentClient.bottom - nFitHeight;
	int nFitWidth = rcParentClient.right - rcParentClient.left;
	::MoveWindow(m_ToolbarBottom->GetHWND(), 0, nFitTop, nFitWidth, nFitHeight, true);
}

void CToolbarMgr::UpdateButton(ToolbarButtonType btnNeedUpdate, buttonStatusType btnStatus)
{
	if(!IsInMeeting(m_pMeetingService->GetMeetingStatus()))
		return;
	
	if(m_ToolbarBottom)
		m_ToolbarBottom->UpdateButton(btnNeedUpdate, btnStatus);
}

void CToolbarMgr::ShowChatWindow()
{
	if(m_pAppEvent)
		m_pAppEvent->onShowChatWindow();
}

void CToolbarMgr::ShowShareWindow()
{
	if(m_pAppEvent)
		m_pAppEvent->onShowShareWindow();
}
void CToolbarMgr::ShowGalleryViewWindow()
{
	if(m_pAppEvent)
		m_pAppEvent->onShowGalleryViewWindow();
}

void CToolbarMgr::ShowParticipantWindow()
{
	if(m_pAppEvent)
		m_pAppEvent->onShowParticipantWindow();
}
void CToolbarMgr::EndMeeting()
{
	if(m_ToolbarBottom)
	{
		m_ToolbarBottom->EndMeeting();
	}
}

void CToolbarMgr::ShowMoreMenuWindow(int x, int y)
{
	if (m_pAppEvent)
	{
		m_pAppEvent->onShowMoreMenuWindow(x, y);
	}
}

void CToolbarMgr::SetGalleryViewStatus(bool bOn)
{
	if(m_ToolbarBottom)
		m_ToolbarBottom->SetGalleryViewStatus(bOn);
}

void CToolbarMgr::SetChatUIStatus(bool bOn)
{
	if(m_ToolbarBottom)
		m_ToolbarBottom->SetChatUIStatus(bOn);
}

void CToolbarMgr::SetParticipantUIStatus(bool bOn)
{
	if(m_ToolbarBottom)
		m_ToolbarBottom->SetParticipantUIStatus(bOn);
}

void CToolbarMgr::SetShareUIStatus(bool bOn)
{
	if(m_ToolbarBottom)
		m_ToolbarBottom->SetShareUIStatus(bOn);
}

bool CToolbarMgr::IsHost()
{
	do
	{
		if(IsInMeeting(m_pMeetingService->GetMeetingStatus()))
		{
			ZOOM_SDK_NAMESPACE::IMeetingParticipantsController* pParticipantCtrl = m_pMeetingService->GetMeetingParticipantsController();
			if(!pParticipantCtrl)
				break;
			ZOOM_SDK_NAMESPACE::IUserInfo* pMe = pParticipantCtrl->GetUserByUserID(0);
			if(!pMe)
				break;
			return pMe->IsHost();
		}
	}while(0);
	return false;
}

