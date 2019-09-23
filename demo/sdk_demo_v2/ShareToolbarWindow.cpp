#include "stdafx.h"
#include "ShareToolbarWindow.h"
#include "custom_ui_mgr.h"
#include "AnnotateBarWindow.h"

ShareToolbarWindow::ShareToolbarWindow(CCustomizeInMeetingUIMgr* pMainUI)
{
	m_pMainUI   = pMainUI;
	m_btnGiveControlTo = NULL;
	m_btnStopRemoteControl = NULL;
	m_pComboxUsers = NULL;
	m_pAnnotateBarWindow = NULL;
	m_btnAnnotate = NULL;
}

ShareToolbarWindow::~ShareToolbarWindow()
{
	if (m_pAnnotateBarWindow){
		delete m_pAnnotateBarWindow;
		m_pAnnotateBarWindow = NULL;
	}
	if (::IsWindow(m_hWnd)) {
		::DestroyWindow(m_hWnd);
	}
}

void ShareToolbarWindow::ShowAnnotateBarWindow()
{
	if (m_pAnnotateBarWindow == NULL) {
		m_pAnnotateBarWindow = new AnnotateBarWindow(NULL);
		m_pAnnotateBarWindow->Create(m_hWnd, _T("Annotate Bar"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, WS_EX_TOPMOST|WS_EX_TOOLWINDOW);
	}

	if (::IsWindowVisible(m_pAnnotateBarWindow->GetHWND())){
		m_pAnnotateBarWindow->ShowWindow(false);
		m_pAnnotateBarWindow->HideOwnedWindows();
	}else {
		m_pAnnotateBarWindow->MoveWindowPosTo(m_hWnd);
		m_pAnnotateBarWindow->ShowWindow(true);
	}
}

void ShareToolbarWindow::UpdateUserList()
{
	CSDKUserList* pUserList = NULL;

	if (!m_pMainUI){
		return;
	}
	pUserList = m_pMainUI->GetUserList();
	if (!pUserList){
		return;
	}
	
	m_pComboxUsers->RemoveAll();
	int nCount = pUserList->GetCount();
	for (int i =0; i < nCount; ++i)
	{
		ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = pUserList->GetItem(i);
		if( !pUserInfo || (pUserInfo->IsMySelf()) )
		{
			continue;
		}
		CListLabelElementUI* pUserLabel = new CListLabelElementUI();
		if (m_pComboxUsers && pUserLabel)
		{
			m_pComboxUsers->Add(pUserLabel);
			pUserLabel->SetText(pUserInfo->GetUserName());
		}
	}
	
	if (m_pComboxUsers){
		m_pComboxUsers->SelectItem(0);
	}
}

unsigned int ShareToolbarWindow::GetSelectedUserID()
{
	CSDKUserList* pUserList = NULL;

	pUserList = m_pMainUI->GetUserList();
	if (!pUserList || !m_pComboxUsers){
		return 0;
	}
	
	CControlUI* pCurrentSelect = m_pComboxUsers->GetItemAt(m_pComboxUsers->GetCurSel());
	if(!pCurrentSelect){
		return 0;
	}

	LPCTSTR user_name = pCurrentSelect->GetText().GetData();
	ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = pUserList->GetUserByName(user_name);
	if (!pUserInfo){
		return 0;
	}
	return pUserInfo->GetUserID();
}

void ShareToolbarWindow::InitWindow()
{
	m_btnStopShare = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_stop_share"));
	m_btnGiveControlTo = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_give_control_to"));
	m_btnStopRemoteControl = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_stop_remote_control"));
	m_pComboxUsers = static_cast<CComboUI*>(m_PaintManager.FindControl(L"cmb_users"));
	m_btnAnnotate  = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_annotate"));

	//position
	RECT rc = {0};
	if (!::GetWindowRect(m_hWnd, &rc)) {
		return;
	}
	::SetWindowPos(m_hWnd, NULL, 0, 0, rc.right-rc.left, rc.bottom-rc.top, SWP_HIDEWINDOW);

	//TODO
	//HWND hOwnerWnd = GetWindow(m_hWnd, GW_OWNER);
	//SetWindowLong(m_hWnd, GWL_HWNDPARENT, (LONG)hOwnerWnd); 
}

void ShareToolbarWindow::Notify( TNotifyUI& msg )
{
	if (msg.sType ==_T("click"))
	{
		if (msg.pSender == m_btnGiveControlTo)
		{
			unsigned int nUserID;
			if (nUserID = GetSelectedUserID()){
				SDKInterfaceWrap::GetInst().GetMeetingRemoteController()->GiveRemoteControlTo(nUserID);
			}else {
				::MessageBox(m_hWnd, _T("no participant"), _T("remote control"), MB_OK);
			}
		}
		else if (msg.pSender == m_btnStopRemoteControl)
		{
			unsigned int nUserID;
			if (nUserID = GetSelectedUserID()){
				SDKInterfaceWrap::GetInst().GetMeetingRemoteController()->RevokeRemoteControl();
			}
		}
		else if (msg.pSender == m_btnStopShare)
		{
			ZOOM_SDK_NAMESPACE::IMeetingService* pMeetingService    = SDKInterfaceWrap::GetInst().GetMeetingService();
			ZOOM_SDK_NAMESPACE::IMeetingShareController* pShareCtrl = pMeetingService->GetMeetingShareController();
			pShareCtrl->StopShare();
		}
		else if (msg.pSender == m_btnAnnotate)
		{
			ShowAnnotateBarWindow();
		}
	}
}

LRESULT ShareToolbarWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	else if (uMsg == WM_CLOSE)
	{
		OnClose(uMsg, wParam, lParam, bHandled);		
		this->ShowWindow(false);
		return lRes;
	}
	else if (uMsg == WM_DESTROY)
	{
		OnDestroy(uMsg, wParam, lParam, bHandled);		
	}
	else if (uMsg == WM_NCDESTROY)
	{
		//delete this;
		//window obj pointer = NULL
	}

	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT ShareToolbarWindow::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return true;
}

LRESULT ShareToolbarWindow::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return true;
}

HWND ShareToolbarWindow::GetWindowHandle()
{
	return m_hWnd;
}