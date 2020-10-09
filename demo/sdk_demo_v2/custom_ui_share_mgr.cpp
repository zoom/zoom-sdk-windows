#include "StdAfx.h"
#include "custom_ui_share_mgr.h"
#include "ShareToolbarWindow.h"
#include "ViewOptionsWindow.h"


CCustomizeUIShareRenderUI::CCustomizeUIShareRenderUI(CCustomizeUIShareMgr* pCustomizeShareUIMgr)
{
	m_pCustomizeShareUIMgr = pCustomizeShareUIMgr;
}

CCustomizeUIShareRenderUI::~CCustomizeUIShareRenderUI()
{
	m_pCustomizeShareUIMgr = NULL;
}

void CCustomizeUIShareRenderUI::InitWindow()
{
	create_owner_hwnd(this, Default_Share_Window_Width, Default_Share_Window_Height);
	if (NULL == m_hOwnerHwnd || !::IsWindow(m_hOwnerHwnd))
		return;
	SetDefaultRenderPos();
}

void CCustomizeUIShareRenderUI::HandleDestroyWindow()
{
	destroy_owner_wnd();
}

HWND CCustomizeUIShareRenderUI::GetWindowHandle()
{
	return m_hOwnerHwnd;
}
void CCustomizeUIShareRenderUI::SetDefaultRenderPos()
{
	if(NULL == m_hOwnerHwnd)
		return;
	RECT rc = {0};
	rc.left = 0;
	rc.right = Default_Share_Window_Width;
	rc.top = 0;
	rc.bottom = Default_Share_Window_Height;

	adjust_wnd_pos(Default_Share_Window_Width, Default_Share_Window_Height, m_hOwnerHwnd);
	/*
	DWORD dwStyle = ::GetWindowLong(m_hOwnerHwnd, GWL_STYLE);
	DWORD dwExStyle = ::GetWindowLong(m_hOwnerHwnd, GWL_EXSTYLE);

	::AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);
	int cx = rc.right - rc.left;
	int cy = rc.bottom - rc.top;
	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	::SetWindowPos(m_hOwnerHwnd, NULL, (nScreenWidth-cx)/2, (nScreenHeight-cy)/2, cx, cy, SWP_NOZORDER|SWP_NOOWNERZORDER);
	*/
}

void CCustomizeUIShareRenderUI::onSize(RECT& rc)
{
	if(m_pCustomizeShareUIMgr)
		m_pCustomizeShareUIMgr->HandleSizeChanged(rc);
}

void CCustomizeUIShareRenderUI::onDestroyed()
{
	if(m_pCustomizeShareUIMgr)
	{
		m_pCustomizeShareUIMgr->HandleRenderUIDestroyed();
	}
}

void CCustomizeUIShareRenderUI::onMove()
{
	if(m_pCustomizeShareUIMgr)
	{
		m_pCustomizeShareUIMgr->HandleWindowMoveMsg();
	}
}

void CCustomizeUIShareRenderUI::ShowMe()
{
	if(m_hOwnerHwnd && ::IsWindow(m_hOwnerHwnd))
	{
		::ShowWindow(m_hOwnerHwnd, SW_SHOWNORMAL | SW_RESTORE);
	}
}

void CCustomizeUIShareRenderUI::HideMe()
{
	if(m_hOwnerHwnd && ::IsWindow(m_hOwnerHwnd))
	{
		::ShowWindow(m_hOwnerHwnd, SW_HIDE);
	}
}

////////////////////////////////////////////////////////////////////
BOOL ShouldWindowBeDisplayed(HWND window, LPARAM lparam)
{
	if (!IsWindow(window))
		return FALSE;

	CRect rc(0, 0, 0, 0);
	GetWindowRect(window, &rc);
	if (rc.Width() <= 0 || rc.Height() <= 0)
		return FALSE;

	if (!IsWindowVisible(window))
		return FALSE;

	DWORD current_process_id = GetCurrentProcessId();
	DWORD window_process_id = 0;
	GetWindowThreadProcessId(window, &window_process_id);
	if (window_process_id == current_process_id)
		return FALSE;

	UINT wnd_style_ex = GetWindowLong(window, GWL_EXSTYLE);
	if ((WS_EX_APPWINDOW & wnd_style_ex) == WS_EX_APPWINDOW)
		return TRUE;

	if ((WS_EX_TOOLWINDOW & wnd_style_ex) == WS_EX_TOOLWINDOW)
		return FALSE;

	HWND owner = GetWindow(window, GW_OWNER);
	if (owner == NULL) {
		return TRUE;
	} else {
		CRect owner_rect(0, 0, 0, 0);
		GetWindowRect(owner, &owner_rect);
		if (!IsWindowVisible(owner))
			return TRUE;

		if (owner_rect.Width() <= 0 || owner_rect.Height() <= 0)
			return TRUE;
	}

	return FALSE;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lparam)
{
	if (!ShouldWindowBeDisplayed(hwnd, lparam))
		return TRUE;

	if (lparam != 0 && ::IsWindow(hwnd))
	{
		CCustomizeUIShareSelectUI* pSelectAppsWnd = static_cast<CCustomizeUIShareSelectUI*>((void*)lparam);
		if(pSelectAppsWnd)
			pSelectAppsWnd->AddToAppList(hwnd);
	}
	return TRUE;
}

CCustomizeUIShareSelectUI::CCustomizeUIShareSelectUI(CCustomizeUIShareMgr* pCustomizeShareUIMgr)
{
	m_pCustomizeShareUIMgr = pCustomizeShareUIMgr;
	m_hwndSelectedApp = NULL;
	m_btnShareDesktop = NULL;
	m_btnShareWhiteBoard = NULL;
	m_btnShareSelectApp = NULL;
	m_pAppList = NULL;
	m_iAppCountToList = 0;
}

CCustomizeUIShareSelectUI::~CCustomizeUIShareSelectUI()
{
	m_pCustomizeShareUIMgr = NULL;
}

void CCustomizeUIShareSelectUI::InitWindow()
{
	RECT rc = { 0 };
	if( !::GetClientRect(m_hWnd, &rc) ) return;
	rc.right = rc.left + 524;
	rc.bottom = rc.top + 376;
	if( !::AdjustWindowRectEx(&rc, GetWindowStyle(m_hWnd), (!(GetWindowStyle(m_hWnd) & WS_CHILD) && (::GetMenu(m_hWnd) != NULL)), GetWindowExStyle(m_hWnd)) ) return;
	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	::SetWindowPos(m_hWnd, NULL, (ScreenX - (rc.right - rc.left)) / 2, 
		(ScreenY - (rc.bottom - rc.top)) / 2, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_SHOWWINDOW);
	m_btnShareDesktop = static_cast<CButtonUI* >(m_PaintManager.FindControl(_T("btn_share_desktop")));
	m_btnShareWhiteBoard = static_cast<CButtonUI* >(m_PaintManager.FindControl(_T("btn_share_whiteboard")));
	m_btnShareSelectApp = static_cast<CButtonUI* >(m_PaintManager.FindControl(_T("btn_share_selectedapp")));
	m_pAppList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("share_applist")));
	//other controls go here
	AdjustListUIPos();
}

LRESULT CCustomizeUIShareSelectUI::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	else if(uMsg == WM_CLOSE)
	{
		
		if(m_pCustomizeShareUIMgr)
		{
			m_pCustomizeShareUIMgr->onSelectShareUIClosed();
			//return lRes;
		}
		
	}

	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

void CCustomizeUIShareSelectUI::Notify(TNotifyUI& msg)
{
	if(msg.sType == _T("click"))
	{
		if(msg.pSender == m_btnShareDesktop)
			DoShareButtonClick(SDK_SHARE_DESKTOP);
		else if(msg.pSender == m_btnShareWhiteBoard)
			DoShareButtonClick(SDK_SHARE_WHITEBOARD);
		else if(msg.pSender == m_btnShareSelectApp)
			DoShareButtonClick(SDK_SHARE_APP);
	}
	else if(msg.sType == DUI_MSGTYPE_ITEMACTIVATE || msg.sType == DUI_MSGTYPE_ITEMCLICK)
	{
		do 
		{
			int iIndex = (int)msg.pSender->GetTag();
			CListTextElementUI* pListElement = (CListTextElementUI*)m_pAppList->GetItemAt(iIndex);
			if(pListElement)
			{
				std::wstring strWinHandle = pListElement->GetText(APPLIST_TEXT_APPHWND);
				if(strWinHandle.length() <=0)
					break;
				swscanf_s(strWinHandle.c_str(),_T("%x"),&m_hwndSelectedApp);
				return;
			}
		} while (0);
		m_hwndSelectedApp = NULL;
	}
}

bool CCustomizeUIShareSelectUI::DestroyWindow()
{
	if(::IsWindow(m_hWnd))
	{
		return ::DestroyWindow(m_hWnd) ? true:false;
	}
	return false;
}

void CCustomizeUIShareSelectUI::DoShareButtonClick(SDKShareType shareType)
{
	if(!m_pCustomizeShareUIMgr)
		return;

	m_pCustomizeShareUIMgr->StartShare(shareType, m_hwndSelectedApp);
}

void CCustomizeUIShareSelectUI::EnumAllWindows()
{
	EnumWindows(EnumWindowsProc, (LPARAM)this);
}

void CCustomizeUIShareSelectUI::InitAppList()
{
	if(!m_pAppList)
		return;

	m_pAppList->RemoveAll();
	m_iAppCountToList = 0;
	EnumAllWindows();
}

void CCustomizeUIShareSelectUI::AddToAppList(HWND hwndAdd)
{
	if(!m_pAppList || !::IsWindow(hwndAdd))
		return;

	TCHAR strWindowText[256] = {0};
	::GetWindowText(hwndAdd, strWindowText, 255);
	if(wcslen(strWindowText) == 0)
		return;

	CListTextElementUI* pListElement = new CListTextElementUI;
	pListElement->SetTag(m_iAppCountToList);
	m_iAppCountToList++;
	m_pAppList->Add(pListElement);

	pListElement->SetText(APPLIST_TEXT_APPNAME, strWindowText);
	TCHAR strWinHandle[20] = {0};
	wsprintf(strWinHandle, _T("%p"), hwndAdd);
	pListElement->SetText(APPLIST_TEXT_APPHWND, strWinHandle);
	pListElement->Select(true);
}

void CCustomizeUIShareSelectUI::AdjustListUIPos()
{
	RECT rc = {0};
	::GetClientRect(m_hWnd, &rc);
	int nWidth = rc.right - rc.left;
	rc.left = 0;
	rc.right = nWidth;
	int nHeight = rc.bottom - rc.top;
	rc.top = 0;
	if(nHeight > 100)
		rc.bottom = nHeight - 50;
	else
		rc.bottom = nHeight;
	if(m_pAppList)
	{
		m_pAppList->SetPos(rc);
	}
	CListHeaderItemUI* pListFirstColumn = static_cast<CListHeaderItemUI*>(m_PaintManager.FindControl(_T("column_app_name")));
	CListHeaderItemUI* pListSecondColumn = static_cast<CListHeaderItemUI*>(m_PaintManager.FindControl(_T("column_app_handle")));
	int fWidth = (rc.right-rc.left)/6;
	if(pListFirstColumn)
		pListFirstColumn->SetFixedWidth(fWidth*5);
	if(pListSecondColumn)
		pListSecondColumn->SetFixedWidth(fWidth);
}

/////////////////////////////////////////////////////////////////////////////
CCustomizeUIShareMgr::CCustomizeUIShareMgr(CCustomizeInMeetingUIMgr* pMainUI)
{
	m_pMainUI = pMainUI;
	m_pCustomizedShareRender = NULL;
	m_pViewOptionsWindow = NULL;
	m_pShareToolbarWin = NULL;
	m_pSelectShareUI = NULL;
}

CCustomizeUIShareMgr::~CCustomizeUIShareMgr()
{
	
}

void CCustomizeUIShareMgr::Init()
{
	m_pSelectShareUI = NULL;
	m_pShareRenderUI = NULL;
	if(NULL != m_pCustomizedShareRender)
		DestroyCustomShareRender();
	m_pCustomizedShareRender = NULL;
	m_bInSendShare = false;
	m_bInViewShare = false;
	m_bNeedDeleteShareUIInstance = false;
	m_pCustomizeUIShareFlow.SetShareRender(m_pCustomizedShareRender);
}

void CCustomizeUIShareMgr::uninit()
{
	DestroySelectShareUI();
	DestroyShareRenderUI();
	DestroyCustomShareRender();
}

void CCustomizeUIShareMgr::Show()
{
	m_pCustomizeUIShareFlow.Show();
}

void CCustomizeUIShareMgr::SetEvent(ZOOM_SDK_NAMESPACE::ICustomizedShareRenderEvent* pEvent)
{
	m_pCustomizeUIShareFlow.SetEvent(pEvent);
}

void CCustomizeUIShareMgr::CreateCustomShareRender(ZOOM_SDK_NAMESPACE::ICustomizedUIMgr* pUIMgr)
{
	if(!m_pMainUI)
		return;
	CreateShareRenderUI();
	if(!m_pShareRenderUI)
		return;
	HWND hParent = m_pShareRenderUI->GetWindowHandle();
	RECT rc = {0};
	if(pUIMgr && ::IsWindow(hParent))
	{
		GetWindowRect(hParent, &rc);
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_UNKNOWN;
		err = pUIMgr->CreateShareRender(&m_pCustomizedShareRender, hParent, rc);
		if(m_pCustomizedShareRender)
		{
			m_pCustomizeUIShareFlow.SetShareRender(m_pCustomizedShareRender);
			m_pCustomizeUIShareFlow.SetEvent(dynamic_cast<ZOOM_SDK_NAMESPACE::ICustomizedShareRenderEvent*>(m_pMainUI));
		}
	}
}

void CCustomizeUIShareMgr::DestroyCustomShareRender()
{
	if(!m_pMainUI)
		return;
	if(m_pMainUI->GetCustomizedMgr() && m_pCustomizedShareRender)
	{
		m_pMainUI->GetCustomizedMgr()->DestroyShareRender(m_pCustomizedShareRender);
		m_pCustomizedShareRender = NULL;
	}
}

void CCustomizeUIShareMgr::CreateSelectShareUI()
{
	if(m_pSelectShareUI)
	{
		if(!m_bNeedDeleteShareUIInstance)
			return;
		else
		{
			DestroySelectShareUI();
		}
	}

	m_pSelectShareUI = new CCustomizeUIShareSelectUI(this);
	if(m_pSelectShareUI)
	{
		m_pSelectShareUI->Create(NULL, _T("Select an app to share"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
		m_pSelectShareUI->SetIcon(IDI_ICON_LOGO);
		m_pSelectShareUI->ShowWindow(false);
	}
}

void CCustomizeUIShareMgr::DestroySelectShareUI()
{
	if(m_pSelectShareUI)
	{
		if(::IsWindow(m_pSelectShareUI->GetHWND()))
		{
			m_pSelectShareUI->DestroyWindow();
		}
		delete m_pSelectShareUI;
		m_pSelectShareUI = NULL;
		m_bNeedDeleteShareUIInstance = false;
	}
}

void CCustomizeUIShareMgr::CreateShareRenderUI()
{
	if(m_pShareRenderUI)
	{
		return;
	}

	m_pShareRenderUI = new CCustomizeUIShareRenderUI(this);
	if(m_pShareRenderUI)
	{
		m_pShareRenderUI->InitWindow();
		m_pShareRenderUI->HideMe();
	}
}

void CCustomizeUIShareMgr::DestroyShareRenderUI()
{
	if(m_pShareRenderUI)
	{
		if(::IsWindow(m_pShareRenderUI->GetWindowHandle()))
		{
			m_pShareRenderUI->HandleDestroyWindow();
		}
		delete m_pShareRenderUI;
		m_pShareRenderUI = NULL;
	}
}

bool CCustomizeUIShareMgr::IsInSendShareMode()
{
	return m_bInSendShare;
}

void CCustomizeUIShareMgr::ShowSelectShareUI()
{
	if(IsInSendShareMode())
	{
		StopShare();
		return;
	}

	if(!m_pCustomizedShareRender)
		return;

	if(!m_pSelectShareUI || m_bNeedDeleteShareUIInstance)
	{
		CreateSelectShareUI();
	}
	if(m_pSelectShareUI)
	{
		m_pSelectShareUI->InitAppList();
		m_pSelectShareUI->ShowWindow(true);
	}
}

void CCustomizeUIShareMgr::ShowSharedContent()
{
	unsigned int iSenderID = GetShareContentSender();
	if(0 != iSenderID ){
		ShowNextShareContent(iSenderID);
	}
}

void CCustomizeUIShareMgr::StartShare(SDKShareType shareType, HWND hwndShared)
{
	ZOOM_SDK_NAMESPACE::SDKError ret = m_pCustomizeUIShareFlow.StartShare(shareType, hwndShared);
	if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == ret)
	{
		m_bInSendShare = true;
	}
	else
	{
		m_bInSendShare = false;
	}
}

void CCustomizeUIShareMgr::StopShare()
{
	ZOOM_SDK_NAMESPACE::SDKError ret = m_pCustomizeUIShareFlow.StopShare();
	if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == ret)
	{
		m_bInSendShare = false;
		DestroyShareRenderUI();
	}
}

void CCustomizeUIShareMgr::onSelectShareUIClosed()
{
	m_bNeedDeleteShareUIInstance = true;
}

void CCustomizeUIShareMgr::HandleShareRenderDestroyed(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* pRender)
{
	DestroySelectShareUI();
	DestroyShareRenderUI();
	m_pCustomizedShareRender = NULL;
}

void CCustomizeUIShareMgr::HandleSharingShareAnnotationStatusChanged(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* share_render_, ZOOM_SDK_NAMESPACE::CustomizedShareAnnotationStatus status_)
{
	switch (status_)
	{
	case ZOOM_SDK_NAMESPACE::CS_ANNO_READYTOUSE:
		{   
			//TODO, when as viewer, sender stop share->start share again, can't get here!!!
			//ShowViewOptionsWindow(true);
		}
		break;
	case ZOOM_SDK_NAMESPACE::CS_ANNO_CLOSE:
		{   
			
			//TODO, now can't get here!!! destroy render can get here???
			//DestroyViewOptionsWindow();
		}
		break;
	}
}

void CCustomizeUIShareMgr::HandleShareRenderWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ZOOM_SDK_NAMESPACE::IMeetingRemoteController* pRemoteCtrl = SDKInterfaceWrap::GetInst().GetMeetingRemoteController();

	if (pRemoteCtrl && m_pCustomizedShareRender)
	{
		if (WM_LBUTTONDOWN == uMsg)
		{
			unsigned int nUserId = m_pCustomizedShareRender->GetUserID();
			if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == pRemoteCtrl->CanRequestControl(nUserId))
			{
				pRemoteCtrl->EnterRemoteControllingStatus(nUserId);
			}
		}
	}
}

void CCustomizeUIShareMgr::HandleSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId)
{
	if(!m_pCustomizedShareRender)
		return;

	switch (status)
	{
	case ZOOM_SDK_NAMESPACE::Sharing_Other_Share_Begin:
		{
			//more logic can go here. such as whether to pop up a window to remind the user
			if(m_bInSendShare)
				break;

			if (m_bInViewShare)
			{
				m_pCustomizeUIShareFlow.SetUserID(userId);
			}
			else
			{
				ShowNextShareContent(userId);
			}
			ShowViewOptionsWindow(true);
		}
		break;
	case ZOOM_SDK_NAMESPACE::Sharing_Other_Share_End:
		{
			if(m_bInSendShare)
				break;

			unsigned int iSenderID = GetShareContentSender();
			if(0 != iSenderID)
			{
				ShowNextShareContent(iSenderID);
			}
			else
			{
				m_bInViewShare = false;
				m_pCustomizeUIShareFlow.SetUserID(0);
				m_pCustomizeUIShareFlow.Hide();
				if(m_pShareRenderUI)
					m_pShareRenderUI->HideMe();
				DestroyViewOptionsWindow(); 
			}
		}	
		break;
	case ZOOM_SDK_NAMESPACE::Sharing_Self_Send_Begin:
		{
			m_bInSendShare = true;
			DestroySelectShareUI();
			ShowShareToolbarWindow(true);
		}
		break;
	case ZOOM_SDK_NAMESPACE::Sharing_Self_Send_End:
		{
			m_bInSendShare = false;
			DestroyShareToolbarWindow();
			ShowSharedContent();
		}
		break;
	default:
		break;
	}
	if(m_pMainUI)
	{
		m_pMainUI->UpdateShareButtonStatus();
	}
}


void CCustomizeUIShareMgr::HandleSizeChanged(RECT& rc)
{
	m_pCustomizeUIShareFlow.Resize(rc);
}

void CCustomizeUIShareMgr::HandleWindowMoveMsg()
{
	m_pCustomizeUIShareFlow.HandleWindowsMoveMsg();
}

void CCustomizeUIShareMgr::HandleRenderUIDestroyed()
{
	m_bInViewShare = false;
	m_bInSendShare = false;
	m_bNeedDeleteShareUIInstance = true;
	//m_pCustomizeUIShareFlow.SetUserID(0);
	//m_pCustomizeUIShareFlow.Hide();
}

unsigned int CCustomizeUIShareMgr::GetShareContentSender()
{
	if(m_bInSendShare)
		return 0;

	ZOOM_SDK_NAMESPACE::IMeetingShareController* pMeetingShareCtrl = m_pCustomizeUIShareFlow.GetMeetingShareController();
	if(!pMeetingShareCtrl)
		return 0;

	ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstSharingSource = pMeetingShareCtrl->GetViewableShareSourceList();
	if (lstSharingSource && lstSharingSource->GetCount() > 0)
	{
		unsigned int nSenderID = lstSharingSource->GetItem(0);
		return nSenderID;
	}
	return 0;
}

void CCustomizeUIShareMgr::ShowNextShareContent(unsigned int userId)
{
	if(0 == userId)
		return;

	if(!m_pShareRenderUI)
	{
		CreateShareRenderUI();
	}
	else if(m_pShareRenderUI && NULL == m_pShareRenderUI->GetWindowHandle())
	{
		CreateShareRenderUI();
	}
	if(m_pShareRenderUI)
	{
		m_pShareRenderUI->ShowMe();
		m_pCustomizeUIShareFlow.SetUserID(userId);
		m_pCustomizeUIShareFlow.Show();
		//full window rendering. if not, share display in the lower right corner.
		if(::IsWindow(m_pShareRenderUI->GetWindowHandle()))
		{
			RECT rc = {0};
			::GetClientRect(m_pShareRenderUI->GetWindowHandle(), &rc);
			m_pCustomizeUIShareFlow.Resize(rc);
		}
		m_bInViewShare = true;
	}
}

void CCustomizeUIShareMgr::ShowShareToolbarWindow(bool bShow)
{   
	if (m_pShareToolbarWin == NULL){
		m_pShareToolbarWin = new(std::nothrow) ShareToolbarWindow(m_pMainUI);
		if (!m_pShareToolbarWin){
			return;
		}
		//m_pShareToolbarWin->Create(m_pMainUI->GetRootWindowHwnd(), _T("Share Toolbar"), /*WS_OVERLAPPEDWINDOW*/WS_OVERLAPPED, WS_EX_TOPMOST|WS_EX_TOOLWINDOW);
		m_pShareToolbarWin->Create(NULL, _T("Share Toolbar"), /*WS_OVERLAPPEDWINDOW*/WS_OVERLAPPED, WS_EX_TOPMOST|WS_EX_TOOLWINDOW);
		m_pShareToolbarWin->UpdateUserList();
	}
	m_pShareToolbarWin->ShowWindow(bShow);
}

void CCustomizeUIShareMgr::DestroyShareToolbarWindow()
{
	if (m_pShareToolbarWin){
		delete m_pShareToolbarWin;
		m_pShareToolbarWin = NULL;
	}
}

void CCustomizeUIShareMgr::ShowViewOptionsWindow(bool bShow)
{   
	if (m_pViewOptionsWindow == NULL){
		m_pViewOptionsWindow = new(std::nothrow) ViewOptionsWindow(m_pCustomizedShareRender);
		if (!m_pViewOptionsWindow){
			return;
		}
		m_pViewOptionsWindow->Create(NULL, _T("View Options"), /*WS_OVERLAPPEDWINDOW*/WS_OVERLAPPED, WS_EX_TOPMOST|WS_EX_TOOLWINDOW);
	}
	m_pViewOptionsWindow->ShowWindow(bShow);
}

void CCustomizeUIShareMgr::DestroyViewOptionsWindow()
{
	if (m_pViewOptionsWindow){
		delete m_pViewOptionsWindow;
		m_pViewOptionsWindow = NULL;
	}
}

void CCustomizeUIShareMgr::DestroyAllShareWindows()
{
	DestroySelectShareUI();
	DestroyShareRenderUI();
	DestroyShareToolbarWindow();
	DestroyViewOptionsWindow();
}

void CCustomizeUIShareMgr::HandleUserChanged()
{
	if (m_pShareToolbarWin){
		m_pShareToolbarWin->UpdateUserList();
	}
}

void CCustomizeUIShareMgr::onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId)
{
	wstring wstrMsg;
	ZOOM_SDK_NAMESPACE::IMeetingParticipantsController* pParticipantsCtrl = SDKInterfaceWrap::GetInst().GetMeetingParticipantsController();
	ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = pParticipantsCtrl->GetUserByUserID(userId);
	const wchar_t* pUserName = pUserInfo->GetUserName();

	//wstrMsg += pUserName;

	switch (status)
	{
	case ZOOM_SDK_NAMESPACE::Remote_Control_I_Can_Control_Who_Begin:
		{
			wstrMsg = _T("you can control ");
			::MessageBox(NULL, wstrMsg.c_str(), _T("zoom"), MB_OK);
		}
		break;
	case ZOOM_SDK_NAMESPACE::Remote_Control_I_Can_Control_Who_End:
		{
			wstrMsg = _T("you can't control ");
			::MessageBox(NULL, wstrMsg.c_str(), _T("zoom"), MB_OK);
		}
		break;
	case ZOOM_SDK_NAMESPACE::Remote_Control_I_Can_Request_Control_Who:
		{
			wstrMsg = _T("I can enable the remote control ");
			//::MessageBox(NULL, wstrMsg.c_str(), _T("zoom"), MB_OK);
		}
		break;
	case ZOOM_SDK_NAMESPACE::Remote_Control_I_Control_Who_Begin:
		{
			wstrMsg = _T("I am in the status of remote control ");
			::MessageBox(NULL, wstrMsg.c_str(), _T("zoom"), MB_OK);
		}
		break;
	case ZOOM_SDK_NAMESPACE::Remote_Control_I_Control_Who_End:
		{
			wstrMsg = _T("I am out of the remote control ");
			::MessageBox(NULL, wstrMsg.c_str(), _T("zoom"), MB_OK);
		}
		break;
	case ZOOM_SDK_NAMESPACE::Remote_Control_I_Recv_Decline_Msg:
		{		
			wstrMsg = _T("I have received a refused information of remote control from.");
			::MessageBox(NULL, wstrMsg.c_str(), _T("zoom"), MB_OK);
		}
		break;
	case ZOOM_SDK_NAMESPACE::Remote_Control_I_Recv_Request_Msg:
		{   
			wstrMsg = _T("you received an request for remote control. Accept?");
			int nRtn = ::MessageBox(NULL, wstrMsg.c_str(), _T("zoom"), MB_YESNO|MB_ICONQUESTION);
			if (nRtn == IDYES){
				SDKInterfaceWrap::GetInst().GetMeetingRemoteController()->GiveRemoteControlTo(userId);
			}else {
				SDKInterfaceWrap::GetInst().GetMeetingRemoteController()->DeclineRemoteControlRequest(userId);
			}
		}
		break;
	case ZOOM_SDK_NAMESPACE::Remote_Control_Who_Control_Me:
		{
			//TODO: give control to someone,call back to here. 
			//      when revoke remote control/viewer give up, it still call back to here!!!!!!!!

			//wstrMsg = _T("I am controlled by whom");
			//::MessageBox(NULL, wstrMsg.c_str(), _T("zoom"), MB_OK);
		}
		break;
	default:
		break;
	}
}