#include "StdAfx.h"
#include "chat_controller_ui.h"
//////////////////////////////////////////////////////////////////////////

CSDKMeetingChatUIMgr::CSDKMeetingChatUIMgr(CCustomizeInMeetingUIMgr* pMainUI)
{
	m_pMainUI = pMainUI;
	m_pUserList = NULL;
	m_pUserListCombox = NULL;
	m_input_content = NULL;
	m_show_chat_info = NULL;
}

CSDKMeetingChatUIMgr::~CSDKMeetingChatUIMgr()
{
	m_pMainUI = NULL;
	m_pUserList = NULL;
	m_pUserListCombox = NULL;
	m_input_content = NULL;
	m_show_chat_info = NULL;
}

void CSDKMeetingChatUIMgr::InitWindow()
{
	m_chat_controller_workflow.SetEvent(this);
	RECT rc = { 0 };
	if( !::GetClientRect(m_hWnd, &rc) ) return;
	rc.right = rc.left + 380;
	rc.bottom = rc.top + 500;
	if( !::AdjustWindowRectEx(&rc, GetWindowStyle(m_hWnd), (!(GetWindowStyle(m_hWnd) & WS_CHILD) && (::GetMenu(m_hWnd) != NULL)), GetWindowExStyle(m_hWnd)) ) return;
	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	::SetWindowPos(m_hWnd, NULL, (ScreenX - (rc.right - rc.left)) / 2, 
		(ScreenY - (rc.bottom - rc.top)) / 2, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_SHOWWINDOW);

	m_pUserListCombox = static_cast<CComboUI* >(m_PaintManager.FindControl(L"chat_to_who"));
	m_input_content = static_cast<CRichEditUI* >(m_PaintManager.FindControl(L"chat_input_content_edit"));
	m_show_chat_info = static_cast<CRichEditUI* >(m_PaintManager.FindControl(L"chat_show_content_edit"));
}

void CSDKMeetingChatUIMgr::Notify( TNotifyUI& msg )
{
	if (msg.sType ==_T("return"))
	{
		if (msg.pSender == m_input_content)
		{
			std::wstring content = m_input_content->GetText().GetData();
			if (content.size() == 0)
			{
				::MessageBox(NULL,L"Please input content !", L"notify", MB_OK);
				return;
			}
			else
			{
				DoPressEnterKey();
			}
		}
	}
}

LRESULT CSDKMeetingChatUIMgr::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
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
		return lRes;

	}
	else if (uMsg == WM_DESTROY)
	{
		OnDestroy(uMsg, wParam, lParam, bHandled);
	}
	
	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CSDKMeetingChatUIMgr::OnClose( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	//m_chat_controller_workflow.UnInit();
	if(m_pMainUI)
		m_pMainUI->HandleChatWindowBeClosed();
	return true;
}

LRESULT CSDKMeetingChatUIMgr::OnDestroy( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	m_chat_controller_workflow.UnInit();
	return true;
}

void CSDKMeetingChatUIMgr::HandleUserChanged()
{
	GetUserList();
	UpdateUserListCombox();
}

void CSDKMeetingChatUIMgr::GetUserList()
{
	if(m_pMainUI)
		m_pUserList = m_pMainUI->GetUserList();
	else
		m_pUserList = NULL;
}

void CSDKMeetingChatUIMgr::UpdateUserListCombox()
{
	if (m_pUserListCombox)
	{
		m_pUserListCombox->RemoveAll();
		CListLabelElementUI* pAll = new CListLabelElementUI;
		if (pAll)
		{
			m_pUserListCombox->Add(pAll);
			pAll->SetText(L"Everyone");
		}
	}

	if (m_pUserList)
	{
		int nCount = m_pUserList->GetCount();
		for (int i =0; i < nCount; ++i)
		{
			ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = m_pUserList->GetItem(i);
			if(!pUserInfo)
				continue;
			if (!pUserInfo->IsMySelf())
			{
				CListLabelElementUI* pUserLabel = new CListLabelElementUI();
				if (m_pUserListCombox && pUserLabel)
				{
					m_pUserListCombox->Add(pUserLabel);
					pUserLabel->SetText(pUserInfo->GetUserName());
				}
			}
		}
	}
	if (m_pUserListCombox)
	{
		m_pUserListCombox->SelectItem(0);
	}

}

void CSDKMeetingChatUIMgr::onChatMsgNotifcation( ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* ccc )
{
	if (chatMsg)
	{
		std::wstring content;
		ZOOM_SDK_NAMESPACE::IUserInfo* pUser = NULL;
		if (chatMsg->IsChatToAll())
		{
			unsigned int user_id = chatMsg->GetSenderUserId();
			if (m_pUserList)
			{
				pUser = m_pUserList->GetUserByID(user_id);
			}

			if (pUser && (!pUser->IsMySelf()))
			{
				const wchar_t* name = pUser->GetUserName();
				content = std::wstring(L"From ")+std::wstring(name)+std::wstring( L" send to Everyone :\n");
				m_show_chat_info->AppendText(content.c_str());
				content = std::wstring(chatMsg->GetContent())+L"\n";
				m_show_chat_info->AppendText(content.c_str());
			}
		}
		else if (chatMsg->IsChatToAllPanelist())
		{
			content = std::wstring(L"From ")+std::wstring(chatMsg->GetSenderDisplayName())+std::wstring( L" send to Everyone :\n");
			m_show_chat_info->AppendText(content.c_str());
			content = std::wstring(chatMsg->GetContent())+L"\n";
			m_show_chat_info->AppendText(content.c_str());
		}
		else if (chatMsg->GetReceiverUserId() == chatMsg->GetSenderUserId())
		{
			content = std::wstring(chatMsg->GetContent())+L"\n";
			m_show_chat_info->AppendText(content.c_str());
		}
		else
		{
			unsigned int user_id = chatMsg->GetSenderUserId();
			if (m_pUserList)
				pUser = m_pUserList->GetUserByID(user_id);

			if(pUser&& !pUser->IsMySelf())
			{
				content = std::wstring(L"From ")+std::wstring(chatMsg->GetSenderDisplayName())+std::wstring( L" send to Me :(Privately)\n");
				m_show_chat_info->AppendText(content.c_str());
				content = std::wstring(chatMsg->GetContent())+L"\n";
				m_show_chat_info->AppendText(content.c_str());
			}
		}
	}
}

void CSDKMeetingChatUIMgr::onChatStautsChangedNotification( ZOOM_SDK_NAMESPACE::ChatStatus* status_ )
{

}

void CSDKMeetingChatUIMgr::DoPressEnterKey()
{
	std::wstring chat_info;
	if (m_input_content)
	{
		chat_info = std::wstring(m_input_content->GetText().GetData());
		m_input_content->SetText(L"");
	}
	unsigned int user_id = 0;
	if (m_pUserList && m_pUserListCombox)
	{
		CControlUI* pCurrentSelect = m_pUserListCombox->GetItemAt(m_pUserListCombox->GetCurSel());
		LPCTSTR user_name = pCurrentSelect->GetText().GetData();
		ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = m_pUserList->GetUserByName(user_name);
		if (pUserInfo)
		{
			user_id = pUserInfo->GetUserID();
		}
	}

	std::wstring show_info;
	if (SendChatMsg(user_id, const_cast<wchar_t* >(chat_info.c_str())))
	{
		if (user_id == 0)
		{
			show_info = std::wstring(L"From Me send to Everyone:\n")+chat_info+L"\n";
		}
		else
		{
			ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = m_pUserList->GetUserByID(user_id);
			if (pUserInfo)
			{
				show_info = std::wstring(L"From Me send to ") +std::wstring(pUserInfo->GetUserName())+L":\n"+chat_info+L"\n";
			}
		}		
		if (m_show_chat_info)
		{
			m_show_chat_info->AppendText(show_info.c_str());
		}
	}
}

bool CSDKMeetingChatUIMgr::SendChatMsg( unsigned int receiver, wchar_t* content )
{
	return (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == m_chat_controller_workflow.SendChatMsg(receiver, content))? true:false;
}

bool CSDKMeetingChatUIMgr::DestroyWindow()
{
	if(::IsWindow(m_hWnd))
	{
		return ::DestroyWindow(m_hWnd) ? true:false;
	}
	return false;
}
