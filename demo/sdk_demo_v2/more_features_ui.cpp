#include "stdafx.h"

#include "more_features_ui.h"
#include "custom_ui_mgr.h"

CMoreFeaturesUIMgr::CMoreFeaturesUIMgr(int left, int bottom,  CCustomizeInMeetingUIMgr* _main_frame)
{
	m_ListMenu = NULL;
	posX = left;
	posY = bottom;
	m_main_frame = _main_frame;
	m_util_wnd = NULL;
	SDKInterfaceWrap::GetInst().ListenMeetingParticipantsCtrEvent(this);
}

CMoreFeaturesUIMgr::~CMoreFeaturesUIMgr()
{
	m_ListMenu = NULL; 
	posX = 0;
	posY = 0;

	DestroyUtilWindow();
	SDKInterfaceWrap::GetInst().UnListenMeetingParticipantsCtrEvent(this);
}

void CMoreFeaturesUIMgr::InitWindow()
{
	m_ListMenu = static_cast<CListUI* >(m_PaintManager.FindControl(L"menu_list"));
	
	UpdateUI();

	RepaintClient(posX, posY);
	


}

LRESULT CMoreFeaturesUIMgr::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
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
	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

void CMoreFeaturesUIMgr::Notify( TNotifyUI& msg )
{
	if (msg.sType == _T("itemclick"))
	{
		if (msg.pSender == m_PaintManager.FindControl(L"Mute All"))
		{
			DoClickMuteAllBtn();
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Unmute All"))
		{
			DoClickUnmuteAllBtn();
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Pin Video"))
		{
			DoUtilWindowShow(L"Pin Video", PinVideo);
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Spotlight Video"))
		{
			DoUtilWindowShow(L"Spotlight Video", SpotlightVideo);
		}
		else if(msg.pSender == m_PaintManager.FindControl(L"Stop Attendee Video"))
		{
			DoUtilWindowShow(L"Stop Attendee Video",StopAttendeeVideo);
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Start Attendee Video"))
		{
			DoUtilWindowShow(L"Start Attendee Video",StartAttendeeVideo);
		}
		else if(msg.pSender == m_PaintManager.FindControl(L"Mute Audio"))
		{
			DoUtilWindowShow(L"Mute Audio",MuteAudio);
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"UnMute Audio"))
		{
			DoUtilWindowShow(L"UnMute Audio", UnMuteAudio);
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Expel User"))
		{
			DoUtilWindowShow(L"Expel User",ExpelUser);
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Make Host"))
		{
			DoUtilWindowShow(L"Make Host", MakeHost);
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Reclaim Host"))
		{
			DoUtilWindowShow(L"Reclaim Host",ReclaimHost);
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Assign CoHost"))
		{
			DoUtilWindowShow(L"Assign CoHost",AssignCoHost);
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Revoke CoHost"))
		{
			DoUtilWindowShow(L"Revoke CoHost",RevokeCoHost);
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Mute On Entry"))
		{
			DoClickMuteOnEntry();
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Lower All Hands"))
		{
			DoClickLowerAllHandsBtn();
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Lower Hand"))
		{
			DoUtilWindowShow(L"Lower Hand", LowerHand);
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Raise Hand"))
		{
			DoClickRaiseHandBtn();
		}
		else if (msg.pSender == m_PaintManager.FindControl(L"Change User Name"))
		{
			DoUtilWindowShow(L"Change User Name",ChangeUserName);
		}
	}
}

bool CMoreFeaturesUIMgr::RepaintClient( int X, int Y )
{
	RECT rc={0};
	GetClientRect(m_hWnd,&rc);
	//cx,cy: window size
	int nOption;
	if (m_ListMenu)
	{
		nOption	= m_ListMenu->GetCount();
	}

	cx = WND_DEFAULT_MENU_OPTION_WIDTH;
	cy = WND_DEFAULT_MENU_OPYION_HEIGHT*nOption+2*(nOption+1);
	return ::SetWindowPos(m_hWnd, NULL, X,  Y - cy, cx, cy, SWP_NOZORDER | SWP_SHOWWINDOW );
}

bool CMoreFeaturesUIMgr::AddElement( LPCTSTR textDisplay )
{
	CListLabelElementUI* pElement = new CListLabelElementUI;
	if (pElement)
	{
		pElement->SetAttribute(L"name",textDisplay);
		pElement->SetAttribute(L"text",textDisplay);
		pElement->SetAttribute(L"height",L"20");
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

CControlUI* CMoreFeaturesUIMgr::FindElementByName( LPCTSTR ElementName )
{
	if (m_ListMenu)
	{
		return m_ListMenu->FindSubControl(ElementName);
	}
	return NULL;
}

bool CMoreFeaturesUIMgr::RemoveElement( CControlUI* pElement )
{
	if (m_ListMenu)
	{
		return m_ListMenu->Remove(pElement);
	}
	return false;
}

void CMoreFeaturesUIMgr::DoClickMuteAllBtn()
{
	if (m_main_frame)
	{
		bool bRet = m_more_features_workflow.MuteAll(m_main_frame->GetUserList());
		if (!bRet)
		{
			ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
		}
	}
}

void CMoreFeaturesUIMgr::DoClickUnmuteAllBtn()
{
	if (m_main_frame)
	{
		bool bRet = m_more_features_workflow.UnMuteAll(m_main_frame->GetUserList());
		if (!bRet)
		{
			ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
		}
	}
}

void CMoreFeaturesUIMgr::DoUtilWindowShow(const wchar_t* window_name, FEATURE_TYPE _type)
{
	if (NULL == m_util_wnd)
	{
		m_util_wnd = new CUtilWnd( m_main_frame);
		m_util_wnd->Create(m_hWnd, L"", UI_WNDSTYLE_DIALOG , WS_EX_WINDOWEDGE);
		m_util_wnd->SetIcon(IDI_ICON_LOGO);
	}
	else
	{
		m_util_wnd->ShowWindow();
	}
	::SetWindowText(m_util_wnd->GetHWND(),window_name);

	if(m_util_wnd)
	{
		m_util_wnd->SetType(_type);
		m_util_wnd->UpdateUserList();
	}
}

void CMoreFeaturesUIMgr::DestroyUtilWindow()
{
	if (m_util_wnd)
	{
		if (IsWindow(m_util_wnd->GetHWND()))
		{
			::DestroyWindow(m_util_wnd->GetHWND());
		}
		m_util_wnd = NULL;
	}
}

void CMoreFeaturesUIMgr::onHostChangeNotification( unsigned int userId )
{
	
	int nList = m_ListMenu->GetCount();
	if (m_ListMenu)
	{
		for (int i = nList-1; i>=0; i--)
		{
			m_ListMenu->RemoveAt(i, true);
		}
	}
	UpdateUI();
	RepaintClient(posX, posY);
	SendMessageW(WM_PAINT);// must send paint message, maybe it's duilib's bug.

	if (m_main_frame)
	{
		m_main_frame->UpdateParticipantsWindow();
	}
}

void CMoreFeaturesUIMgr::onUserNameChanged( unsigned int userId, const wchar_t* userName )
{
	//todo
	if (m_main_frame)
	{
		m_main_frame->UpdateParticipantsWindow();
	}
}

void CMoreFeaturesUIMgr::onCoHostChangeNotification( unsigned int userId, bool isCoHost )
{
	//todo
	int nList = m_ListMenu->GetCount();
	if (m_ListMenu)
	{
		for (int i = nList-1; i>=0; i--)
		{
			m_ListMenu->RemoveAt(i, true);
		}
	}
	UpdateUI();
	RepaintClient(posX, posY);
	SendMessageW(WM_PAINT);// must send paint message, maybe it's duilib's bug.

	if (m_main_frame)
	{
		m_main_frame->UpdateParticipantsWindow();
	}
}

void CMoreFeaturesUIMgr::onLowOrRaiseHandStatusChanged( bool bLow, unsigned int userid )
{
	if (m_main_frame)
	{
		m_main_frame->UpdateParticipantsWindow();
	}
}

void CMoreFeaturesUIMgr::UpdateUI()
{
	ZOOM_SDK_NAMESPACE::IMeetingParticipantsController* pParticipantsCtr = SDKInterfaceWrap::GetInst().GetMeetingParticipantsController();
	bool bHost(false);
	if (pParticipantsCtr)
	{
		bHost = (pParticipantsCtr->GetUserByUserID(0))->IsHost();
	}
	if (bHost)
	{
		AddElement(L"Mute On Entry");
		AddElement(L"Mute All");
		AddElement(L"Unmute All");
		AddElement(L"Spotlight Video");
		AddElement(L"Stop Attendee Video");
		AddElement(L"Start Attendee Video");
		AddElement(L"Mute Audio");//host
		AddElement(L"UnMute Audio");
		AddElement(L"Expel User");
		AddElement(L"Assign CoHost");
		AddElement(L"Revoke CoHost");
		AddElement(L"Lower All Hands");
		AddElement(L"Lower Hand");
		AddElement(L"Change User Name");
		
	}

	//AddElement(L"Pin Video");//Valid only for Zoom style user interface mode.

	AddElement(L"Make Host");
	AddElement(L"Reclaim Host");
	AddElement(L"Raise Hand");

	UpdateWindow(m_hWnd);
	
}

void CMoreFeaturesUIMgr::DoClickMuteOnEntry( bool bEnable /*= true*/ )
{
	ZOOM_SDK_NAMESPACE::SDKError err = m_more_features_workflow.EnableMuteOnEntry(bEnable);

	if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != err)
	{
		ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
	}
}

void CMoreFeaturesUIMgr::ShowErrorMsg( const wchar_t* msg )
{
	::MessageBox(NULL,msg,L"Notify",MB_OK);
}

void CMoreFeaturesUIMgr::DoClickLowerAllHandsBtn()
{
	ZOOM_SDK_NAMESPACE::SDKError err = m_more_features_workflow.LowerAllHands();
	if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != err)
	{
		ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
	}
	//else
	//{
	//	Sleep(1500);
	//	if (m_main_frame)
	//	{
	//		m_main_frame->UpdateParticipantsWindow();
	//	}
	//}
}

void CMoreFeaturesUIMgr::DoClickRaiseHandBtn()
{
	ZOOM_SDK_NAMESPACE::SDKError err = m_more_features_workflow.RaiseHand();
	if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != err)
	{
		ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
	}
}


