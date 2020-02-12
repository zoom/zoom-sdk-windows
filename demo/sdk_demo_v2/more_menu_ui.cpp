#include "stdafx.h"
#include "more_menu_ui.h"
#include "custom_ui_mgr.h"
#include "CustomizedUIRecordMgr.h"

CMoreMenuUIMgr::CMoreMenuUIMgr()
{
	m_ListMenu = NULL;
	posX = 400;//default window show position
	posY = 800;
	m_pListElementLocalRecord = NULL;
	m_pListElementCloudRecord = NULL;
	m_pListElementStopRecord = NULL;
	m_pListElementStopCMR = NULL;
}

CMoreMenuUIMgr::CMoreMenuUIMgr( int left, int bottom , CCustomizeInMeetingUIMgr* main_frame)
{
	m_ListMenu = NULL;
	posX = left;
	posY = bottom;
	m_main_frame = main_frame;
	m_cc_frame = NULL;
	m_invite_frame = NULL;
	m_more_features_frame = NULL;
	m_pListElementLocalRecord = NULL;
	m_pListElementCloudRecord = NULL;
	m_pListElementStopRecord = NULL;
	m_pListElementStopCMR = NULL;
}
CMoreMenuUIMgr::~CMoreMenuUIMgr()
{
	m_ListMenu = NULL; 
	posX = 0;
	posY = 0;
	m_main_frame = NULL;
	DestroyClosedCaptionWnd();
	DestroyInvitationWnd();
	DestroyMoreFeaturesWnd();
}

void CMoreMenuUIMgr::InitWindow()
{
	m_ListMenu = static_cast<CListUI* >(m_PaintManager.FindControl(L"menu_list"));
	AddElement(L"Local Record");
	AddElement(L"Cloud Record");
	AddElement(L"Stop Record");
	AddElement(L"Stop Cloud Record");
	AddElement(L"Invite");
	AddElement(L"CC");
	AddElement(L"Camera Control");
	AddElement(L"More Features");
	RepaintClient(posX, posY);

	m_pListElementLocalRecord = dynamic_cast<CListLabelElementUI*>(m_PaintManager.FindControl(L"Local Record"));
	m_pListElementCloudRecord = dynamic_cast<CListLabelElementUI*>(m_PaintManager.FindControl(L"Cloud Record"));
    m_pListElementStopRecord  = dynamic_cast<CListLabelElementUI*>(m_PaintManager.FindControl(L"Stop Record"));
	if (m_pListElementStopRecord) m_pListElementStopRecord->SetEnabled(false);
	m_pListElementStopCMR  = dynamic_cast<CListLabelElementUI*>(m_PaintManager.FindControl(L"Stop Cloud Record"));
	if (m_pListElementStopCMR) m_pListElementStopCMR->SetEnabled(false);

	// for test add and remove element.
	/*
	AddElement(L"dd ee");
	RepaintClient(posX, posY);
	RemoveElement(FindElementByName(L"dd ee"));
	RepaintClient(posX, posY);
	*/

}
LRESULT CMoreMenuUIMgr::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	if( uMsg == WM_CREATE ) 
	{
		m_PaintManager.Init(m_hWnd);
		CDialogBuilder builder;
		STRINGorID xml(GetSkinRes());
		CControlUI* pRoot = builder.Create(xml, _T("xml"), 0, &m_PaintManager);
		ASSERT(pRoot && "Failed to parse XML");

		m_PaintManager.AttachDialog(pRoot);
		m_PaintManager.AddNotifier(this);
		InitWindow(); 
		return lRes;
	}

	if (uMsg == WM_INITMENU)
	{
		return 0;
	}
	if( uMsg == WM_NCCALCSIZE)
	{
		return 0;
	}
	if( uMsg == WM_NCPAINT)
	{
		CWindowWnd::SendMessageW(WM_PAINT);
	}
	if (uMsg == WM_SHOWWINDOW)
	{
		if (m_more_features_frame)
		{
			m_more_features_frame->ShowWindow(false);
		}
		return lRes;
	}
	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

void CMoreMenuUIMgr::Notify( TNotifyUI& msg )
{
	if (msg.sType == _T("itemclick"))
	{
		if (msg.pSender == m_PaintManager.FindControl(L"Invite"))
		{
			DoClickInviteBtn();
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"CC"))
		{

			DoClickClosedCaptionBtn();
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Camera Control"))
		{
			m_main_frame->ShowHideCameraControlWindow();
		}
		else if(msg.pSender == m_PaintManager.FindControl(L"More Features"))
		{
			DoClickMoreFeaturesBtn();
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Local Record"))
		{
			time_t timeNow;
			if (CustomizedUIRecordMgr::GetInstance()->CanIStartLocalRecording() == false){
				::MessageBox(NULL, _T("you can not start local recording, please apply to the host"), _T("winsdk demo"), MB_OK);
				return;
			}
			time(&timeNow);
			CustomizedUIRecordMgr::GetInstance()->StartRecording(timeNow);
			m_pListElementLocalRecord->SetEnabled(false);
			m_pListElementCloudRecord->SetEnabled(false);
			m_pListElementStopRecord->SetEnabled(true);
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Cloud Record"))
		{
			if (CustomizedUIRecordMgr::GetInstance()->CanIStartCloudRecording() == false){
				::MessageBox(NULL, _T("you can not start could recording"), _T("winsdk demo"), MB_OK);
				return;
			}
			CustomizedUIRecordMgr::GetInstance()->StartCloudRecording();
			m_pListElementLocalRecord->SetEnabled(false);
			m_pListElementCloudRecord->SetEnabled(false);
			m_pListElementStopCMR->SetEnabled(true);
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Stop Record"))
		{
			time_t timeNow;
			time(&timeNow);
			CustomizedUIRecordMgr::GetInstance()->StopRecording(timeNow);
			m_pListElementLocalRecord->SetEnabled(true);
			m_pListElementCloudRecord->SetEnabled(true);
			m_pListElementStopRecord->SetEnabled(false);
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Stop Cloud Record"))
		{
			CustomizedUIRecordMgr::GetInstance()->StopCloudRecording();
			m_pListElementStopCMR->SetEnabled(false);
			m_pListElementLocalRecord->SetEnabled(true);
			m_pListElementCloudRecord->SetEnabled(true);
		}

		if (msg.pSender != m_PaintManager.FindControl(L"More Features"))
		{
			ShowWindow(false);
		}
		
	}
}

bool CMoreMenuUIMgr::AddElement( LPCTSTR textDisplay )//call RepaintClient function after call it
{
	CListLabelElementUI* pElement = new CListLabelElementUI;
	if (pElement)
	{
		pElement->SetAttribute(L"name",textDisplay);
		pElement->SetAttribute(L"text",textDisplay);
		pElement->SetAttribute(L"height",L"25");
		pElement->SetAttribute(L"borderround",L"4,4");
		pElement->SetAttribute(L"padding",L"0,2,0,0");
		if (m_ListMenu)
		{
			return m_ListMenu->Add(pElement);
		}
		return false;
	}
	return false;
}

bool CMoreMenuUIMgr::RemoveElement( CControlUI* pElement )//call RepaintClient function after call it
{
	if (m_ListMenu)
	{
		return m_ListMenu->Remove(pElement);
	}
	return false;
}

bool CMoreMenuUIMgr::RepaintClient( int X, int Y)
{ 
	RECT rc={0};
	GetClientRect(m_hWnd,&rc);
	//cx,cy: window size
	int nOption;
	if (m_ListMenu)
	{
		nOption	= m_ListMenu->GetCount();
	}

	cx = DEFAULT_MENU_OPTION_WIDTH;
	cy = DEFAULT_MENU_OPYION_HEIGHT*nOption+2*(nOption+1);
	posX = X;
	posY = Y;
	return ::SetWindowPos(m_hWnd, NULL, X,  Y - cy, cx, cy, SWP_NOZORDER | SWP_SHOWWINDOW );
}

CControlUI* CMoreMenuUIMgr::FindElementByName( LPCTSTR ElementName )//used for RemoveElement function
{
	if (m_ListMenu)
	{
		return m_ListMenu->FindSubControl(ElementName);
	}
	return NULL;
}

int CMoreMenuUIMgr::GetWindowWidth()
{
	return cx;
}

int CMoreMenuUIMgr::GetWindowHeight()
{
	return cy;
}

void CMoreMenuUIMgr::DoClickClosedCaptionBtn()
{
	if ( NULL == m_cc_frame)
	{
		if (m_main_frame)
		{
			m_cc_frame = new CCloseCaptionUIMgr(m_main_frame);
		}
		if (NULL == m_cc_frame)
		{
			return;
		}
		#define WND_STYLE (WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
		m_cc_frame->Create(m_hWnd, _T("Close Caption - in play"), WND_STYLE , WS_EX_WINDOWEDGE/*|WS_EX_TOOLWINDOW*/);
		m_cc_frame->SetIcon(IDI_ICON_LOGO);

		if (m_cc_frame->IsHost())
		{
			m_cc_frame->ShowWindow();
		}
		else
		{
			m_cc_frame->HideAssignLayout();
			if (m_cc_frame->GetAssignedStatus())
			{
				m_cc_frame->ShowWindow();
			}
		}
		
	}
	else
	{
		if (NULL == m_cc_frame)
		{
			return;
		}
		if (IsWindowVisible(m_cc_frame->GetHWND()))
		{
			m_cc_frame->ShowWindow();
			::SetForegroundWindow(m_cc_frame->GetHWND());
		}
		else
		{
			if (m_cc_frame->IsHost())
			{
				m_cc_frame->ShowWindow();
			}
		}

	}
}

void CMoreMenuUIMgr::HandleUserChange()
{
	if (m_cc_frame)
	{
		m_cc_frame->UpdateListCombox();
	}
}

void CMoreMenuUIMgr::DoClickInviteBtn()
{
	if ( NULL == m_invite_frame )
	{
		m_invite_frame =new CInvitationUIMgr;
		if ( NULL == m_invite_frame )
		{
			return;
		}
		m_invite_frame->Create(m_hWnd, _T("Invite"), UI_WNDSTYLE_DIALOG , WS_EX_WINDOWEDGE);
		m_invite_frame->SetIcon(IDI_ICON_LOGO);
	}
	else
	{
		m_invite_frame->ShowWindow(true);
	}

}

void CMoreMenuUIMgr::DoClickMoreFeaturesBtn()
{
	int nCount = 0;
	if (m_ListMenu)
	{
		nCount = m_ListMenu->GetCount();
	}
	int posx =posX + DEFAULT_MENU_OPTION_WIDTH + 5/* padding */;
	int posy = posY - cy + nCount*DEFAULT_MENU_OPYION_HEIGHT;

	if ( NULL == m_more_features_frame )
	{
		m_more_features_frame =new CMoreFeaturesUIMgr(posx, posy, m_main_frame);
		if ( NULL == m_more_features_frame )
		{
			return;
		}
		m_more_features_frame->Create(m_hWnd, _T("More Features"), UI_WNDSTYLE_DIALOG , WS_EX_WINDOWEDGE/*|WS_EX_TOOLWINDOW*/);
		m_more_features_frame->SetIcon(IDI_ICON_LOGO);
	}
	else
	{
		if (IsWindowVisible(m_more_features_frame->GetHWND()))
		{
			m_more_features_frame->ShowWindow(false);
			return;
		}
		m_more_features_frame->RepaintClient(posx, posy);
		m_more_features_frame->ShowWindow(true);
	}
}

void CMoreMenuUIMgr::DestroyClosedCaptionWnd()
{
	if (m_cc_frame)
	{
		if (IsWindow(m_cc_frame->GetHWND()))
		{
			DestroyWindow(m_cc_frame->GetHWND());
			delete m_cc_frame;
			m_cc_frame = NULL;
		}
	}
}

void CMoreMenuUIMgr::DestroyInvitationWnd()
{
	if (m_invite_frame)
	{
		if (IsWindow(m_invite_frame->GetHWND()))
		{
			DestroyWindow(m_invite_frame->GetHWND());
			delete m_invite_frame;
			m_invite_frame = NULL;
		}
	}
}

void CMoreMenuUIMgr::DestroyMoreFeaturesWnd()
{
	if (m_more_features_frame)
	{
		if (IsWindow(m_more_features_frame->GetHWND()))
		{
			DestroyWindow(m_more_features_frame->GetHWND());
			delete m_more_features_frame;
			m_more_features_frame = NULL;
		}
	}
}

void CMoreMenuUIMgr::HandleMoveAndResize()
{
	if (m_more_features_frame)
	{
		m_more_features_frame->ShowWindow(false);
	}
}