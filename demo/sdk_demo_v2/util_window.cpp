#include "stdafx.h"
#include "util_window.h"
#include "custom_ui_mgr.h"

CUtilWnd::CUtilWnd( CCustomizeInMeetingUIMgr* main_frame )
{
	m_main_frame = main_frame;
	m_hLayout = NULL;
	m_user_list_combo = NULL;
	m_user_list = NULL;
	m_ok = NULL;
	m_type = TypeNone;
	m_last_video_status = ZOOM_SDK_NAMESPACE::Video_OFF;
	m_last_user_id = 0;
	m_lb_changeto = NULL;
	m_user_name = NULL;
	m_change_user_name = NULL;

	SDKInterfaceWrap::GetInst().ListenMeetingVideoCtrEvent(this);
}

CUtilWnd::~CUtilWnd()
{
	m_main_frame = NULL;
	m_hLayout = NULL;
	m_user_list_combo = NULL;
	m_user_list = NULL;
	m_ok = NULL;
	m_type = TypeNone;
	m_last_video_status = ZOOM_SDK_NAMESPACE::Video_OFF;
	m_last_user_id = 0;
	m_lb_changeto = NULL;
	m_user_name = NULL;
	m_change_user_name = NULL;
	SDKInterfaceWrap::GetInst().UnListenMeetingVideoCtrEvent(this);
}
void CUtilWnd::InitControl()
{
	m_hLayout = new CHorizontalLayoutUI;
	m_user_list_combo = new CComboUI;
	m_ok = new CButtonUI;
	m_change_user_name = new CHorizontalLayoutUI;


	if (m_ok)
	{
		m_ok->SetText(L"OK");
		m_ok->SetAttribute(L"bkcolor", L"#ff5274ff");
		m_ok->SetAttribute(L"width",L"50");
		m_ok->SetAttribute(L"height",L"25");

	}
	if (m_user_list_combo)
	{
		m_user_list_combo->SetAttribute(L"bkcolor",L"#FFEAECEE");
		m_user_list_combo->SetAttribute(L"bordersize",L"1");
		m_user_list_combo->SetAttribute(L"bordercolor",L"#FFC0C0C0");
		m_user_list_combo->SetAttribute(L"itemhotbkcolor",L"#FFE9F5FF");
		m_user_list_combo->SetAttribute(L"width",L"120");
		m_user_list_combo->SetAttribute(L"height",L"25");
		m_user_list_combo->SetAttribute(L"textpadding",L"6,0,0,0");
	}

	if (m_lb_changeto == NULL)
	{
		m_lb_changeto = new CLabelUI;
		if (m_lb_changeto == NULL)
		{
			return;
		}
		m_lb_changeto->SetAttribute(L"text",L"Change to: ");
		m_lb_changeto->SetAttribute(L"height",L"20");
		m_lb_changeto->SetAttribute(L"width", L"80");


	}

	if (m_user_name == NULL)
	{
		m_user_name = new CRichEditUI;
		if (m_user_name == NULL)
		{
			return;
		}
		m_user_name->SetAttribute(L"height",L"20");
		m_user_name->SetAttribute(L"width", L"120");
		m_user_name->SetAttribute(L"bordersize",L"1");
		m_user_name->SetAttribute(L"bordercolor",L"#FFC0C0C0");
	}

	if (m_change_user_name)
	{
		m_change_user_name->SetAttribute(L"width",L"200");
		m_change_user_name->SetAttribute(L"height", L"50");
		m_change_user_name->SetAttribute(L"bkcolor", L"0xFFFFFFFF");
		m_change_user_name->Add(m_lb_changeto);
		m_change_user_name->Add(m_user_name);

	}

	if (m_hLayout)
	{
		m_hLayout->SetAttribute(L"width",L"260");
		m_hLayout->SetAttribute(L"height", L"50");
		m_hLayout->SetAttribute(L"bkcolor", L"0xFFFFFFFF");
		m_hLayout->Add(m_user_list_combo);
		m_hLayout->Add(m_change_user_name);
		m_hLayout->Add(m_ok);
		m_hLayout->SetAttribute(L"inset", L"20,10,20,10");
		//m_hLayout->SetAttribute(L"valign", L"center");
		m_hLayout->SetAttribute(L"childpadding", L"50");
	}

	if (m_change_user_name)
	{
		m_change_user_name->SetVisible(false);
	}
	
	if (m_main_frame)
	{
		m_user_list = m_main_frame->GetUserList();
	}
	UpdateUserList();
}
void CUtilWnd::InitWindow()
{
	
	RECT rc = { 0 };
	if( !::GetClientRect(m_hWnd, &rc) ) return;
	rc.right = rc.left + 300;
	rc.bottom = rc.top + 50;
	if( !::AdjustWindowRectEx(&rc, GetWindowStyle(m_hWnd), (!(GetWindowStyle(m_hWnd) & WS_CHILD) && (::GetMenu(m_hWnd) != NULL)), GetWindowExStyle(m_hWnd)) ) return;
	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	::SetWindowPos(m_hWnd, NULL, (ScreenX - (rc.right - rc.left)) / 2, 
		(ScreenY - (rc.bottom - rc.top)) / 2, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_SHOWWINDOW);
}

LRESULT CUtilWnd::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	if( uMsg == WM_CREATE ) 
	{
		InitControl();
		m_PaintManager.Init(m_hWnd);
		m_PaintManager.AttachDialog(m_hLayout);
		m_PaintManager.AddNotifier(this);
		InitWindow(); 
		return lRes;
	}
	if (uMsg == WM_CLOSE)
	{
		ShowWindow(false);
		return 1;
	}
	if (uMsg == WM_DESTROY)
	{
		return 1;
	}
	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

void CUtilWnd::Notify( TNotifyUI& msg )
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_ok)
		{
			DoClickOkBtn();
		}
	}
}

void CUtilWnd::UpdateUserList()
{
	if (m_user_list_combo)
	{
		m_user_list_combo->RemoveAll();
	}
	
	if (m_user_list)
	{
		int nCount = m_user_list->GetCount();
		for (int i =0; i < nCount; ++i)
		{
			ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = m_user_list->GetItem(i);
			if(!pUserInfo)
				continue;

			CListLabelElementUI* pUserLabel = new CListLabelElementUI();
			if (m_user_list_combo && pUserLabel)
			{
				m_user_list_combo->Add(pUserLabel);
				pUserLabel->SetText(pUserInfo->GetUserName());
			}

		}
	}
	if (m_user_list_combo)
	{
		m_user_list_combo->SelectItem(0);
	}
}

void CUtilWnd::DoClickOkBtn()
{
	if (m_user_list_combo)
	{
		std::wstring user_name = m_user_list_combo->GetText().GetData();
		unsigned int user_id = 0;
		if (m_user_list)
		{
			user_id = m_user_list->GetUserByName(user_name)->GetUserID();
		}
		switch (m_type)
		{
		case TypeNone:
			{
				break;
			}
		case PinVideo:
			{
				ZOOM_SDK_NAMESPACE::SDKError err = m_more_feature_workflow.PinVideo(true, true, user_id);
				if (err != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
				{
					ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
				}
				break;
			}
		case SpotlightVideo:
			{
				ZOOM_SDK_NAMESPACE::SDKError err = m_more_feature_workflow.SpotlightVideo(true, user_id);
				if (err != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
				{
					ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
				}
				break;
			}
		case StopAttendeeVideo:
			{
				ZOOM_SDK_NAMESPACE::SDKError err = m_more_feature_workflow.StopAttendeeVideo(user_id);
				if (err != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
				{
					ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
				}
				break;
			}
		case StartAttendeeVideo:
			{
				ZOOM_SDK_NAMESPACE::SDKError err = m_more_feature_workflow.StartAttendeeVideo(user_id);
				if (err != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
				{
					ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
				}
				break;
			}
		case MuteAudio:
			{
				ZOOM_SDK_NAMESPACE::SDKError err = m_more_feature_workflow.MuteAudio(user_id);
				if (err != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
				{
					ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
				}
				break;
			}
		case UnMuteAudio:
			{
				ZOOM_SDK_NAMESPACE::SDKError err = m_more_feature_workflow.UnMuteAudio(user_id);
				if (err != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
				{
					ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
				}
				break;
			}
		case ExpelUser:
			{
				ZOOM_SDK_NAMESPACE::SDKError err = m_more_feature_workflow.ExpelUser(user_id);
				if (err != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
				{
					ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
				}
				break;
			}
		case MakeHost:
			{
				ZOOM_SDK_NAMESPACE::SDKError err = m_more_feature_workflow.MakeHost(user_id);
				if (err != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
				{
					ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
				}
				break;
			}
		case ReclaimHost:
			{
				ZOOM_SDK_NAMESPACE::SDKError err = m_more_feature_workflow.ReclaimHost();
				if (err != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
				{
					ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
				}
				break;
			}
		case AssignCoHost:
			{
				ZOOM_SDK_NAMESPACE::SDKError err = m_more_feature_workflow.AssignCoHost(user_id);
				if (err != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
				{
					ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
				}
				break;
			}
		case RevokeCoHost:
			{
				ZOOM_SDK_NAMESPACE::SDKError err =m_more_feature_workflow.RevokeCoHost(user_id);
				if (err != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
				{
					ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
				}
				break;
			}
		case LowerHand:
			{
				ZOOM_SDK_NAMESPACE::SDKError err =m_more_feature_workflow.LowerHand(user_id);
				if (err != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
				{
					ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
				}
				break;
			}
		case ChangeUserName:
			{
				ZOOM_SDK_NAMESPACE::SDKError err;
				std::wstring user_name;
				if (m_user_name)
				{
					user_name = m_user_name->GetText().GetData();
				}

				if (user_name.size() == 0)
				{
					ShowErrorMsg(L"Please input your name.");
				}
				else
				{
					err = m_more_feature_workflow.ChangeUserName(user_id, user_name.c_str(), false);
					if (err != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
					{
						ShowErrorMsg(CSDKMessInfo::GetInst().GetErrorMessInfo());
					}
				}

				break;
			}
		}
		
	}

	ShowWindow(false);
}

void CUtilWnd::SetType( FEATURE_TYPE _type )
{
	if (m_type != ChangeUserName && _type == ChangeUserName)
	{
		AddChangeUserNameCtrs();
	}
	else if (m_type == ChangeUserName && _type != ChangeUserName)
	{
		AddChangeUserNameCtrs(false);
	}

	m_type = _type;

}

void CUtilWnd::ShowErrorMsg( const wchar_t* msg )
{
	::MessageBox(NULL,msg,L"Notify",MB_OK);
}

void CUtilWnd::onUserVideoStatusChange( unsigned int userId, ZOOM_SDK_NAMESPACE::VideoStatus status )
{

	//only show one time callback info
	if (m_last_video_status != status || m_last_user_id != userId)
	{
		std::wstring user_name;
		if (m_main_frame)
		{
			CSDKUserList* pUserList = m_main_frame->GetUserList();
			user_name = pUserList->GetUserByID(userId)->GetUserName();
		}
		TCHAR notify[MAX_PATH] = {0};
		if (status == ZOOM_SDK_NAMESPACE::Video_ON)
		{
			wsprintf(notify, L"user name: %s    user id: %d    video status: VIDEO_ON", user_name.c_str(),userId);
		}
		else
		{
			wsprintf(notify, L"user id: %d    video status: VIDEO_OFF", userId);
		}
		m_last_user_id = userId;
		m_last_video_status = status;
		::MessageBox(NULL, notify, L"Notify", MB_OK);
	}



	m_last_user_id = userId;
	m_last_video_status = status;
}

void CUtilWnd::onSpotlightVideoChangeNotification( bool bSpotlight, unsigned int userid )
{
	// todo
}

void CUtilWnd::onHostRequestStartVideo( ZOOM_SDK_NAMESPACE::IRequestStartVideoHandler* handler_ )
{
	if (handler_)
	{
		handler_->Accept();
	}
	::MessageBox(NULL, L"Host request you start video and you accept.", L"Notify", MB_OK);
}

void CUtilWnd::onActiveSpeakerVideoUserChanged( unsigned int userid )
{
	//todo
}

void CUtilWnd::onActiveVideoUserChanged( unsigned int userid )
{
	//todo
}

void CUtilWnd::AddChangeUserNameCtrs( bool bAdd /*= true*/ )
{
	if (bAdd)
	{
		if (m_hLayout)
		{
			m_hLayout->SetAttribute(L"width", L"510");
			ResizeClient(510, 50);
		}
		if (m_change_user_name)
		{
			m_change_user_name->SetVisible();
		}
	}
	else
	{

		if (m_hLayout)
		{
			m_hLayout->SetAttribute(L"width", L"260");
			ResizeClient(260, 50);
		}
		if (m_change_user_name)
		{
			m_change_user_name->SetVisible(false);
		}
	}
}