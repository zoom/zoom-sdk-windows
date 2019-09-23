#include "stdafx.h"

#include "close_caption_ui.h"
#include "custom_ui_mgr.h"



CCloseCaptionUIMgr::CCloseCaptionUIMgr(CCustomizeInMeetingUIMgr* _main_frame)
{
	m_bAssigned = false;
	m_user_list = _main_frame->GetUserList();
	m_pCCDisplayUI = NULL;
	m_main_frame = _main_frame;
}

CCloseCaptionUIMgr::~CCloseCaptionUIMgr()
{
	m_bAssigned = false;
	m_user_list = NULL;
	if (m_pCCDisplayUI)
	{
		DestroyWindow(m_pCCDisplayUI->GetHWND());
		m_pCCDisplayUI = NULL;
	}
	if (m_main_frame)
	{
		m_main_frame->DestroyDisplayCCWnd();
	}
}

void CCloseCaptionUIMgr::InitWindow()
{
	SetIcon(IDI_ICON_LOGO);
	RECT rc = { 0 };
	if( !::GetClientRect(m_hWnd, &rc) ) return;
	rc.right = rc.left + 415;
	rc.bottom = rc.top + 470;
	if( !::AdjustWindowRectEx(&rc, GetWindowStyle(m_hWnd), (!(GetWindowStyle(m_hWnd) & WS_CHILD) && (::GetMenu(m_hWnd) != NULL)), GetWindowExStyle(m_hWnd)) ) return;
	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	::SetWindowPos(m_hWnd, NULL, (ScreenX - (rc.right - rc.left)) / 2, 
		(ScreenY - (rc.bottom - rc.top)) / 2, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_HIDEWINDOW);

	m_closed_caption_workflow.SetEvent(this);

	m_assign_list_combox = dynamic_cast<CComboUI* >(m_PaintManager.FindControl(L"cc_sender_list"));
	m_assign_layout = dynamic_cast<CHorizontalLayoutUI* >(m_PaintManager.FindControl(L"assign_layout"));
	m_assign_btn = dynamic_cast<CButtonUI* >(m_PaintManager.FindControl(L"assign_btn"));
	m_copy_link_btn = dynamic_cast<CButtonUI* >(m_PaintManager.FindControl(L"copy_btn"));
	m_input_cc = dynamic_cast<CRichEditUI* >(m_PaintManager.FindControl(L"input_cc_content"));
	m_show_cc = dynamic_cast<CRichEditUI* >(m_PaintManager.FindControl(L"show_cc_content"));
	m_save_cc_layout = dynamic_cast<CHorizontalLayoutUI* >(m_PaintManager.FindControl(L"save_cc_layout"));
	m_save_cc_btn = dynamic_cast<CButtonUI* >(m_PaintManager.FindControl(L"save_cc_btn"));
	UpdateListCombox();
	Init();
}

LRESULT CCloseCaptionUIMgr::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
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
		ShowWindow(false);
		if (m_main_frame)
		{
			SetForegroundWindow(m_main_frame->GetHWND());
		}
		return lRes;
	}
	else if (uMsg == WM_DESTROY)
	{
		return lRes;
	}

	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

void CCloseCaptionUIMgr::Notify( TNotifyUI& msg )
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_assign_btn)
		{
			DoClickAssignedBtn();
		}
		else if (msg.pSender == m_copy_link_btn)
		{
			DoClickCopyBtn();
		}
		else if(msg.pSender == m_save_cc_btn)
		{
			DoClickSaveBtn();
		}
	}

	if (msg.sType == _T("return"))
	{
		if(msg.pSender == m_input_cc)
		{
			DoClickEnterBtn();
		}
	}
}

void CCloseCaptionUIMgr::onAssignedToSendCC( bool bAssigned )
{
	m_bAssigned = bAssigned;
	if (bAssigned)
	{
		ShowWindow(true);
	}

	if(!bAssigned && !IsHost())
	{
		ShowWindow(false);
	}
}

void CCloseCaptionUIMgr::onClosedCaptionMsgReceived( const wchar_t* ccMsg, time_t time )
{
	if (m_bAssigned && ccMsg)
	{
		if (m_save_cc_layout)
		{
			m_save_cc_layout->SetVisible();
		}
		
	}
	if (m_show_cc)
	{	
		TCHAR recv_time[MAX_PATH] = {0};
		wcsftime(recv_time,80, L"%Y-%m-%d %H:%M:%S", localtime(&time));
		std::wstring msg = std::wstring(recv_time)+L"	"+std::wstring(ccMsg)+L"\n\n";
		m_show_cc->AppendText(msg.c_str());
	}
	if (m_pCCDisplayUI)
	{
		m_pCCDisplayUI->SetDisplayContent(ccMsg);
	}
	SetForegroundWindow(m_hWnd);
}

bool CCloseCaptionUIMgr::IsHost()
{
	return m_closed_caption_workflow.CanIAssignOthersToSendCC();
}

void CCloseCaptionUIMgr::HideAssignLayout()
{
	if (m_assign_layout)
	{
		m_assign_layout->SetVisible(false);
	}

}

void CCloseCaptionUIMgr::UpdateListCombox()
{
	if (m_assign_list_combox)
	{
		m_assign_list_combox->RemoveAll();
		CListLabelElementUI* pAll = new CListLabelElementUI;
		if (pAll)
		{
			m_assign_list_combox->Add(pAll);
			pAll->SetText(L"Host & me");
		}
	}

	if (m_user_list)
	{
		int nCount = m_user_list->GetCount();
		for (int i =0; i < nCount; ++i)
		{
			ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = m_user_list->GetItem(i);
			if(!pUserInfo)
				continue;
			if (!pUserInfo->IsMySelf())
			{
				CListLabelElementUI* pUserLabel = new CListLabelElementUI();
				if (m_assign_list_combox && pUserLabel)
				{
					m_assign_list_combox->Add(pUserLabel);
					pUserLabel->SetText(pUserInfo->GetUserName());
				}
			}
		}
	}
	if (m_assign_list_combox)
	{
		m_assign_list_combox->SelectItem(0);
	}
	
}

void CCloseCaptionUIMgr::DoClickAssignedBtn()
{

	if (m_assign_list_combox)
	{
		std::wstring userName = m_assign_list_combox->GetText().GetData();
		unsigned int host_id;
		unsigned int select_user_id;
		if (m_user_list)
		{
			int nCount = m_user_list->GetCount();
			for (int i =0; i<nCount; ++i)
			{
				ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = m_user_list->GetItem(i);
				if (pUserInfo)
				{
					if(pUserInfo->IsHost())
					{
						host_id = pUserInfo->GetUserID();
					}
					if ( 0 == StrCmpCW(pUserInfo->GetUserName(), userName.c_str()))
					{
						select_user_id = pUserInfo->GetUserID();
					}
				}

			}
		}
		unsigned int assigned_user_id = (L"Host & me" == userName)?host_id:select_user_id;
		
		if (m_assign_btn)
		{
			std::wstring assign_btn_txt = m_assign_btn->GetText().GetData();
			if (assign_btn_txt == L"Reclaim")
			{
				goto Label;
			}
		}
		// solve assign
		if (m_closed_caption_workflow.CanBeAssignedToSendCC(assigned_user_id))
		{
			ZOOM_SDK_NAMESPACE::SDKError err = m_closed_caption_workflow.AssignCCPriviledge(assigned_user_id, true);
			if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
			{
				if ( NULL == m_assign_btn )
				{
					return;
				}
				if (assigned_user_id != host_id)
				{
					m_assign_btn->SetText(L"Reclaim");
					m_assign_list_combox->SetEnabled(false);
				}
			}
			else
			{
				ShowErrorsMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
			}
			return;
		}
		else
		{
			ShowErrorsMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
			return;
		}

		// solve reclaim 
		Label:{
				if (m_closed_caption_workflow.CanBeAssignedToSendCC(assigned_user_id))
				{
					ZOOM_SDK_NAMESPACE::SDKError err = m_closed_caption_workflow.AssignCCPriviledge(assigned_user_id, false);
					if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
					{
						if (m_assign_btn && m_assign_list_combox)
						{
							m_assign_btn->SetText(L"Assign");
							m_assign_list_combox->SetEnabled(true);
						}	
					}
					else
					{
						ShowErrorsMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
					}
				}
				else
				{
					ShowErrorsMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
				}
			  }
	}

	
}

void CCloseCaptionUIMgr::DoClickCopyBtn()
{
	bool bCopy = SetDataToClipboard(m_closed_caption_workflow.GetClosedCaptionUrlFor3rdParty(), m_hWnd);
	if (bCopy)
	{
		ShowErrorsMsg(L"Url have been copied to clipboard.");
	}
	else
	{
		ShowErrorsMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
	}
}

void CCloseCaptionUIMgr::DoClickEnterBtn()
{
	if (m_bAssigned)
	{
		if (NULL == m_input_cc)
		{
			return;
		}
		std::wstring input_content = m_input_cc->GetText().GetData();
		if (input_content.size() == 0)
		{
			return;
		}
		if (input_content.size()>125)
		{
			ShowErrorsMsg(L"You input too many characters!");
			return;
		}
		if (m_closed_caption_workflow.CanSendClosedCaption())
		{
			ZOOM_SDK_NAMESPACE::SDKError err = m_closed_caption_workflow.SendClosedCaption(input_content.c_str());
			if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
			{
				if (m_input_cc)
				{
					m_input_cc->SetText(L"");
				}
			}
			else
			{
				ShowErrorsMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
			}
		}
		else
		{
			ShowErrorsMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
		}
	}
	else
	{
		//todo warning
		ShowErrorsMsg(L"You do not have priviledge to send CC.");
	}
}

void CCloseCaptionUIMgr::ShowErrorsMsg(const wchar_t* msg)
{
	::MessageBox(NULL, msg, L"Notify", MB_OK);
}

bool CCloseCaptionUIMgr::GetAssignedStatus()
{
	return m_bAssigned;
}

void CCloseCaptionUIMgr::DoClickSaveBtn()
{
	ZOOM_SDK_NAMESPACE::SDKError err = m_closed_caption_workflow.SaveCCHistory();
	
	if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
	{
		const wchar_t* save_path = m_closed_caption_workflow.GetClosedCaptionSavePath();
		if (save_path)
		{
			ShellExecute(NULL, L"open", NULL, NULL, save_path, SW_SHOWNORMAL);
		}
	}
	else
	{
		ShowErrorsMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
	}
}

void CCloseCaptionUIMgr::Init()
{
	//init host as CC sender
	unsigned int host_id;
	if (m_user_list)
	{
		int nCount = m_user_list->GetCount();
		for (int i =0; i<nCount; ++i)
		{
			ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = m_user_list->GetItem(i);
			if (pUserInfo)
			{
				if(pUserInfo->IsHost())
				{
					host_id = pUserInfo->GetUserID();
				}
			}

		}
	}
	if (IsHost())
	{
		m_closed_caption_workflow.AssignCCPriviledge(host_id, true);
	}

	if (m_main_frame)
	{
		 m_pCCDisplayUI = m_main_frame->CreateDisplayCCWnd();
	}
	
}
