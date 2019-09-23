#include "stdafx.h"
#include "LOGIN_sdk_login_UI.h"
#include <stdarg.h>
#include "auth_service_interface.h"
#include "httpRequestHelper.h"
#include "zoomHmacSHA256.h"
#include "mess_info.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class CSDKLoginWithEmailUIGroup 
CSDKLoginWithEmailUIGroup::CSDKLoginWithEmailUIGroup()
{
	m_loginWithEmailPage = NULL;
	m_editUserAccount = NULL;
	m_editUserPassword = NULL;
	m_btnLogin = NULL;
	m_chkRemember = NULL;
	m_parentFrame = NULL;
	m_login_bottom = NULL;
}
CSDKLoginWithEmailUIGroup::~CSDKLoginWithEmailUIGroup()
{
	m_loginWithEmailPage = NULL;
	m_editUserAccount = NULL;
	m_editUserPassword = NULL;
	m_btnLogin = NULL;
	m_chkRemember = NULL;
	m_parentFrame = NULL;
	m_login_bottom = NULL;
}
void CSDKLoginWithEmailUIGroup::InitWindow(CPaintManagerUI& ui_mgr, CSDKLoginUIMgr* main_frame_)
{
	m_loginWithEmailPage = static_cast<CVerticalLayoutUI* >(ui_mgr.FindControl(_T("panel_Login_With_Email")));
	m_editUserAccount = static_cast<CRichEditUI* >(ui_mgr.FindControl(_T("edit_user_email")));
	m_editUserPassword = static_cast<CRichEditUI* >(ui_mgr.FindControl(_T("edit_user_password")));
	m_login_bottom = static_cast<CVerticalLayoutUI* >(ui_mgr.FindControl(_T("panel_Login_Buttom")));
	m_btnLogin = static_cast<CButtonUI* >(ui_mgr.FindControl(_T("btn_login")));
	m_chkRemember = static_cast<CCheckBoxUI* >(ui_mgr.FindControl(_T("chk_remember_me")));
	m_editUserPassword = static_cast<CRichEditUI* >(ui_mgr.FindControl(_T("edit_user_password")));
	
	m_parentFrame = main_frame_;
}
void CSDKLoginWithEmailUIGroup::UninitWindow()
{
	m_loginEmailWorkFlow.Cleanup();
}
void CSDKLoginWithEmailUIGroup::Show()
{
	if (m_loginWithEmailPage)
	{
		m_loginWithEmailPage->SetVisible(true);
		if(NULL == m_chkRemember || NULL == m_btnLogin)
			return;
		m_chkRemember->SetVisible(true);
		m_btnLogin->SetText(L"login");
		if (m_parentFrame)
		{
			m_parentFrame->SetCurrentPage(m_loginWithEmailPage);
		}
	}

}
void CSDKLoginWithEmailUIGroup::Hide()
{
	if (m_loginWithEmailPage)
	{
		m_loginWithEmailPage->SetVisible(false);
	}
	
}
void CSDKLoginWithEmailUIGroup::Notify( TNotifyUI& msg )
{
	if (msg.sType == _T("click") && m_loginWithEmailPage->IsVisible())
	{
		if (msg.pSender == m_btnLogin)
		{
			DoLoginWithEmailBtnClick();
		}
	}
}

void CSDKLoginWithEmailUIGroup::DoLoginWithEmailBtnClick()
{
	if (NULL == m_editUserAccount || NULL == m_editUserPassword || NULL == m_chkRemember)
	{
		return ;
	}
	std::wstring userAccount = m_editUserAccount->GetText().GetData();
	std::wstring userPassword = m_editUserPassword->GetText().GetData();
	bool remember = m_chkRemember->GetCheck();
	if (userAccount.size()>0&&userPassword.size()>0)
	{
		ZOOM_SDK_NAMESPACE::LoginParam loginParam;
		loginParam.ut.emailLogin.userName = userAccount.c_str();
		loginParam.ut.emailLogin.password = userPassword.c_str();
		loginParam.ut.emailLogin.bRememberMe = remember;
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != m_loginEmailWorkFlow.Login(loginParam))
		{
			//if (m_parentFrame)
			//{
			//	m_parentFrame->ShowErrorMessage(_T("login failed!"));
			//}
		}
		else
		{
			if(m_parentFrame)
			{
				m_parentFrame->SetCurrentPage(m_loginWithEmailPage);
				m_parentFrame->SwitchToWaitingPage(_T("waiting login ...."), true);
			}
		}
	}
}

bool CSDKLoginWithEmailUIGroup::LogOut()
{
	return (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == m_loginEmailWorkFlow.LogOut() )?true:false;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class CSDKLoginWithSSOUIGroup 
CSDKLoginWithSSOUIGroup::CSDKLoginWithSSOUIGroup()
{
	m_loginWithSSOPage = NULL;
	m_editSSOtoken = NULL;
	m_parentFrame = NULL;
	m_btnLogin = NULL;
	m_chkRemember = NULL;
	m_login_bottom = NULL;
}
CSDKLoginWithSSOUIGroup::~CSDKLoginWithSSOUIGroup()
{
	m_loginWithSSOPage = NULL;
	m_editSSOtoken = NULL;
	m_parentFrame = NULL;
	m_btnLogin = NULL;
	m_chkRemember = NULL;
	m_login_bottom = NULL;
}
void CSDKLoginWithSSOUIGroup::InitWindow(CPaintManagerUI& ui_mgr, CSDKLoginUIMgr* main_frame_)
{
	m_loginWithSSOPage = static_cast<CVerticalLayoutUI* >(ui_mgr.FindControl(_T("panel_Login_With_SSO")));
	m_editSSOtoken = static_cast<CRichEditUI* >(ui_mgr.FindControl(_T("edit_sso_token")));

	m_login_bottom = static_cast<CVerticalLayoutUI* >(ui_mgr.FindControl(_T("panel_Login_Buttom")));
	m_btnLogin = static_cast<CButtonUI* >(ui_mgr.FindControl(_T("btn_login")));
	m_chkRemember = static_cast<CCheckBoxUI* >(ui_mgr.FindControl(_T("chk_remember_me")));
	m_parentFrame = main_frame_;
}
void CSDKLoginWithSSOUIGroup::UninitWindow()
{
	m_loginSSOWorkFlow.Cleanup();

}
void CSDKLoginWithSSOUIGroup::Show()
{
	if (m_loginWithSSOPage)
	{
		m_loginWithSSOPage->SetVisible(true);
		if(NULL == m_chkRemember || NULL == m_btnLogin)
			return;
		m_chkRemember->SetVisible(true);
		m_btnLogin->SetText(L"login");
		if (m_parentFrame)
		{
			m_parentFrame->SetCurrentPage(m_loginWithSSOPage);
		}
	}

}
void CSDKLoginWithSSOUIGroup::Hide()
{
	if (m_loginWithSSOPage)
	{
		m_loginWithSSOPage->SetVisible(false);
	}

}
void CSDKLoginWithSSOUIGroup::Notify( TNotifyUI& msg )
{
	if (msg.sType == _T("click") && m_loginWithSSOPage->IsVisible())
	{
		if (msg.pSender == m_btnLogin)
		{
			DoLoginWithSSOBtnClick();
		}
	}
}

void CSDKLoginWithSSOUIGroup::DoLoginWithSSOBtnClick()
{
	if(NULL == m_editSSOtoken || NULL ==m_chkRemember)
		return;
	std::wstring ssoToken = m_editSSOtoken->GetText().GetData();
	bool bRemember = m_chkRemember->GetCheck();
	if (ssoToken.size()>0)
	{
		ZOOM_SDK_NAMESPACE::LoginParam ssoLoginParam;
		ssoLoginParam.loginType = ZOOM_SDK_NAMESPACE::LoginType_SSO;
		ssoLoginParam.ut.ssoLogin.ssoToken = ssoToken.c_str();
		ssoLoginParam.ut.ssoLogin.bRememberMe = bRemember;
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_loginSSOWorkFlow.Login(ssoLoginParam);
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != err)
		{
			//if(m_parentFrame)
			//	m_parentFrame->ShowErrorMessage(L"SSO Login failed!");
		}
		else
		{
			if(m_parentFrame)
			{
				m_parentFrame->SetCurrentPage(m_loginWithSSOPage);
				m_parentFrame->SwitchToWaitingPage(L"waiting sso login...", true);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////class CSDKWithoutLoginStartJoinMeetingUIGroup
CSDKWithoutLoginStartJoinMeetingUIGroup::CSDKWithoutLoginStartJoinMeetingUIGroup()
{
	m_WithoutLoginStartJoinMeetingPage = NULL;
	m_editMeetingNumber = NULL;
	m_editScreenName = NULL;
	m_editMeetingPassword = NULL;
	m_btnJoin = NULL;
	m_chkRemember = NULL;
	m_parentFrame = NULL;
	m_bInMeeting = false;
}

CSDKWithoutLoginStartJoinMeetingUIGroup::~CSDKWithoutLoginStartJoinMeetingUIGroup()
{
	m_WithoutLoginStartJoinMeetingPage = NULL;
	m_editMeetingNumber = NULL;
	m_editScreenName = NULL;
	m_editMeetingPassword = NULL;
	m_btnJoin = NULL;
	m_chkRemember = NULL;
	m_parentFrame = NULL;
	m_bInMeeting = false;
}

void CSDKWithoutLoginStartJoinMeetingUIGroup::InitWindow(CPaintManagerUI& ui_mgr, CSDKLoginUIMgr* main_frame_)
{
	m_WithoutLoginStartJoinMeetingPage = static_cast<CVerticalLayoutUI* >(ui_mgr.FindControl(_T("panel_Join_Meeting_Only")));
	m_editMeetingNumber = static_cast<CRichEditUI* >(ui_mgr.FindControl(_T("edit_meeting_number")));
	m_editScreenName = static_cast<CRichEditUI* >(ui_mgr.FindControl(_T("edit_screen_name")));
	m_editMeetingPassword = static_cast<CRichEditUI* >(ui_mgr.FindControl(_T("edit_meeting_password")));
	m_btnJoin = static_cast<CButtonUI* >(ui_mgr.FindControl(_T("btn_login")));
	m_chkRemember = static_cast<CCheckBoxUI* >(ui_mgr.FindControl(_T("chk_remember_me")));
	m_parentFrame = main_frame_;
	m_withoutLoginJoinMeetingWorkFlow.SetUIEvent(this);
}

void CSDKWithoutLoginStartJoinMeetingUIGroup::UninitWindow()
{
	m_withoutLoginJoinMeetingWorkFlow.SetUIEvent(NULL);
	m_withoutLoginJoinMeetingWorkFlow.Cleanup();
}

void CSDKWithoutLoginStartJoinMeetingUIGroup::Show()
{
	if (m_WithoutLoginStartJoinMeetingPage)
	{
		m_WithoutLoginStartJoinMeetingPage->SetVisible(true);
		if(NULL == m_btnJoin || NULL == m_chkRemember)
			return;
		m_btnJoin->SetText(_T("join"));
		m_chkRemember->SetVisible(false);
		if (m_parentFrame)
		{
			m_parentFrame->SetCurrentPage(m_WithoutLoginStartJoinMeetingPage);
		}
	}
}

void CSDKWithoutLoginStartJoinMeetingUIGroup::Hide()
{
	if (m_WithoutLoginStartJoinMeetingPage)
	{
		m_WithoutLoginStartJoinMeetingPage->SetVisible(false);
	}
}

void CSDKWithoutLoginStartJoinMeetingUIGroup::Notify( TNotifyUI& msg )
{
	if(msg.sType == _T("click") && m_WithoutLoginStartJoinMeetingPage->IsVisible())
	{
		if(msg.pSender == m_btnJoin)
		{
			DoWithoutLoginStartJoinMeetingBtnClick();
		}
	}
}

void CSDKWithoutLoginStartJoinMeetingUIGroup::DoWithoutLoginStartJoinMeetingBtnClick()
{
	if(NULL == m_editMeetingNumber  || NULL == m_editMeetingPassword || NULL == m_editScreenName )
		return;
	ZOOM_SDK_NAMESPACE::tagJoinParam joinParam;
	joinParam.userType = ZOOM_SDK_NAMESPACE::SDK_UT_WITHOUT_LOGIN;
	ZOOM_SDK_NAMESPACE::JoinParam4WithoutLogin& withoutloginParam = joinParam.param.withoutloginuserJoin;
	std::wstring MeetingNumber = m_editMeetingNumber->GetText().GetData();
	std::wstring MeetingPassword = m_editMeetingPassword->GetText().GetData();
	std::wstring ScreenName = m_editScreenName->GetText().GetData();
	withoutloginParam.meetingNumber = _wtoi64(MeetingNumber.c_str());
	withoutloginParam.vanityID = NULL;
	withoutloginParam.userName = ScreenName.c_str();
	withoutloginParam.psw = MeetingPassword.c_str();
	withoutloginParam.hDirectShareAppWnd = NULL;
	withoutloginParam.toke4enfrocelogin = NULL;
	withoutloginParam.participantId = NULL;
	withoutloginParam.webinarToken = NULL;
	withoutloginParam.isDirectShareDesktop = false;
	withoutloginParam.isVideoOff = false;
	withoutloginParam.isAudioOff = false;

	if(MeetingNumber.size() > 0)
	{
		if(m_parentFrame)
		{
			m_parentFrame->SetCurrentPage(m_WithoutLoginStartJoinMeetingPage);
			m_parentFrame->SwitchToWaitingPage(_T("waiting to join meeting..."),true);
		}
		
		if (SDKInterfaceWrap::GetInst().IsSelectCustomizedUIMode())
		{
			CSDKDemoAppEvent* pAppEvent = m_parentFrame->GetAppEvent();
			if(pAppEvent)
				pAppEvent->InitCustomizedUI();
		}
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_withoutLoginJoinMeetingWorkFlow.JoinMeeting(joinParam);
		if(ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == err)
		{
			m_bInMeeting = true;
		}
		return;
	}
	if (m_parentFrame)
	{
		if(MeetingNumber.size() <=0)
		{
			m_parentFrame->ShowErrorMessage(_T("Meeting number could not be NULL!"));
			m_editMeetingNumber->SetFocus();
		}
		else
		{
			m_parentFrame->ShowErrorMessage(_T("Join meeting failed!"));
		}
		m_parentFrame->SetCurrentPage(m_WithoutLoginStartJoinMeetingPage);
		m_parentFrame->SwitchToWaitingPage(_T("waiting to join meeting...."), false);
		m_bInMeeting = false;
	}
}

void CSDKWithoutLoginStartJoinMeetingUIGroup::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult)
{
	switch (status)
	{
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_RECONNECTING:
		if (SDKInterfaceWrap::GetInst().IsSelectCustomizedUIMode())
		{
			CSDKDemoAppEvent* pAppEvent = m_parentFrame->GetAppEvent();
			if(pAppEvent)
				pAppEvent->InitCustomizedUI();
		}
		break;
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_CONNECTING:
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_DISCONNECTING:
		break;
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_ENDED:
		{
			if(m_parentFrame)
			{
				m_parentFrame->GetAppEvent()->onJoinFailed();
				m_parentFrame->SetCurrentPage(m_WithoutLoginStartJoinMeetingPage);
			}

		}
		break;
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_FAILED:
		{
			if(m_parentFrame)
			{
				m_parentFrame->SetCurrentPage(m_WithoutLoginStartJoinMeetingPage);
				m_parentFrame->ShowErrorMessage(L"Join meeting failed");
			}
		}
		break;
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_INMEETING:
		{
			if(m_parentFrame)
			{
				m_parentFrame->GetAppEvent()->onShowLoggedInUI(Demo_Meeting_Join_Only);
			}
		}
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
//class CSDKRestAPIUserUIGroup 
CSDKRestAPIUserUIGroup::CSDKRestAPIUserUIGroup()
{
	m_WithoutLoginRestAPIPage = NULL;
	m_editRestAPIKey = NULL;
	m_editRestAPISecret = NULL;
	m_editEmail = NULL;
	m_chkRemember = NULL;
	m_editScreenName = NULL;
	m_btnStartMeeting = NULL;
	m_parentFrame = NULL;
}
CSDKRestAPIUserUIGroup::~CSDKRestAPIUserUIGroup()
{
	m_WithoutLoginRestAPIPage = NULL;
	m_editRestAPIKey = NULL;
	m_editRestAPISecret = NULL;
	m_editEmail = NULL;
	m_chkRemember = NULL;
	m_editScreenName = NULL;
	m_btnStartMeeting = NULL;
	m_parentFrame = NULL;
}
void CSDKRestAPIUserUIGroup::InitWindow(CPaintManagerUI& ui_mgr, CSDKLoginUIMgr* main_frame_)
{
	m_WithoutLoginRestAPIPage = static_cast<CVerticalLayoutUI* >(ui_mgr.FindControl(_T("panel_RestAPI_Without_Login")));
	m_editRestAPIKey = static_cast<CRichEditUI* >(ui_mgr.FindControl(_T("edit_restapi_key")));
	if(m_editRestAPIKey)
		m_editRestAPIKey->SetLimitText(KEY_SECRET_LIMIT_LENGTH_MAX);
	m_editRestAPISecret = static_cast<CRichEditUI* >(ui_mgr.FindControl(_T("edit_restapi_secret")));
	if(m_editRestAPISecret)
		m_editRestAPISecret->SetLimitText(KEY_SECRET_LIMIT_LENGTH_MAX);
	m_editScreenName = static_cast<CRichEditUI* >(ui_mgr.FindControl(_T("edit_restapi_ScreenName")));	
	m_editEmail = static_cast<CRichEditUI* >(ui_mgr.FindControl(_T("edit_restapi_email")));
	m_btnStartMeeting = static_cast<CButtonUI* >(ui_mgr.FindControl(_T("btn_login")));
	m_chkRemember = static_cast<CCheckBoxUI* >(ui_mgr.FindControl(_T("chk_remember_me")));
	m_parentFrame = main_frame_;
	m_RestAPIUserWorkFlow.SetUIEvent(this);

}
void CSDKRestAPIUserUIGroup::UninitWindow()
{
	m_RestAPIUserWorkFlow.SetUIEvent(NULL);
	m_RestAPIUserWorkFlow.Cleanup();
}

void CSDKRestAPIUserUIGroup::Show()
{
	if (m_WithoutLoginRestAPIPage)
	{
		m_WithoutLoginRestAPIPage->SetVisible(true);
		if(NULL == m_chkRemember || NULL == m_btnStartMeeting)
			return;
		m_chkRemember->SetVisible(false);
		m_btnStartMeeting->SetText(L"Start an instance meeting");
		if (m_parentFrame)
		{
			m_parentFrame->SetCurrentPage(m_WithoutLoginRestAPIPage);
		}
	}

}
void CSDKRestAPIUserUIGroup::Hide()
{
	if (m_WithoutLoginRestAPIPage)
	{
		m_WithoutLoginRestAPIPage->SetVisible(false);
	}

}
void CSDKRestAPIUserUIGroup::Notify( TNotifyUI& msg )
{
	if (msg.sType == _T("click") && m_WithoutLoginRestAPIPage->IsVisible())
	{
		if (msg.pSender == m_btnStartMeeting)
		{
			DoWithoutLoginStartMeetingBtnClick();
		}
	}
}

void CSDKRestAPIUserUIGroup::DoWithoutLoginStartMeetingBtnClick()
{
	if ( NULL == m_editRestAPIKey || NULL == m_editRestAPISecret || NULL == m_editEmail || NULL == m_editScreenName)
		return;
	std::wstring userKey = m_editRestAPIKey->GetText().GetData();
	std::wstring userSecret = m_editRestAPISecret->GetText().GetData();
	std::wstring userEmail = m_editEmail->GetText().GetData();
	std::wstring userScreenName = m_editScreenName->GetText().GetData();
	zoomHmacSHA256* hmacHelper = new zoomHmacSHA256();
	CZoomHttpRequestHelper* zoomHttpHelper = new CZoomHttpRequestHelper();
	if (userKey.size()> 0&& userSecret.size()>0 )
	{
		if(m_parentFrame)
		{
			m_parentFrame->SetCurrentPage(m_WithoutLoginRestAPIPage);
			m_parentFrame->SwitchToWaitingPage(_T("waiting to start meeting...."), true);
		}
		//here is the flow to get the real rest api token
		bool bGetTokenSucc = false;
		char pcUserKey[ZOOM_ENCODE_DEFAULT_BUFFER];
		char pcUserSecret[ZOOM_ENCODE_DEFAULT_BUFFER];
		char* pcUserTokenForRestAPI;
		wchar_t userTokenForRestAPI[1024];
		UINT64 uPMI = 0;
		std::wstring userFinalToken;
		std::wstring userZaktoken;
		std::wstring userRealID;
		do 
		{
			if(NULL == hmacHelper || NULL == zoomHttpHelper)
				break;
			hmacHelper->WcharToChar(userKey.c_str(), pcUserKey);
			hmacHelper->WcharToChar(userSecret.c_str(), pcUserSecret);
			if(false == hmacHelper->SetRestAPIKey(&pcUserKey[0]) || false == hmacHelper->SetRestAPISecret(&pcUserSecret[0]))
				break;
			//set the period of token validify to be 1 hour
			hmacHelper->SetTokenValidityPeriod(3600);
			if( 0 != hmacHelper->MakeToken())
				break;
			pcUserTokenForRestAPI = hmacHelper->GetToken();	
			if(NULL == pcUserTokenForRestAPI)
				break;
			hmacHelper->CharToWchar(pcUserTokenForRestAPI, userTokenForRestAPI);
			zoomHttpHelper->SetRestAPIDomain(_T("zoom.us"));
			zoomHttpHelper->SetRestAPIAccessToken(userTokenForRestAPI);
			zoomHttpHelper->SetUserEmail((wchar_t*)m_editEmail->GetText().GetData());
			if(!zoomHttpHelper->MakeAPIUrlTokens())
				break;
			//now we get the final useful token
			userFinalToken = zoomHttpHelper->GetSDKURLUserToken();
			userZaktoken = zoomHttpHelper->GetSDKURLZakToken();
			userRealID = zoomHttpHelper->GetSDKURLUserID();
			uPMI = zoomHttpHelper->GetSDKUserPMI();
			bGetTokenSucc = true;
		} while (0);

		bool bNeedWaiting = false;
		if(bGetTokenSucc)
		{
			ZOOM_SDK_NAMESPACE::StartParam startParam;
			startParam.userType = ZOOM_SDK_NAMESPACE::SDK_UT_WITHOUT_LOGIN;

			ZOOM_SDK_NAMESPACE::StartParam4WithoutLogin& RestAPIUserStartParam = startParam.param.withoutloginStart;

			RestAPIUserStartParam.userID = userRealID.c_str();
			RestAPIUserStartParam.userToken = userFinalToken.c_str();
			RestAPIUserStartParam.userZAK = userZaktoken.c_str();
			RestAPIUserStartParam.userName = userScreenName.c_str();
			RestAPIUserStartParam.zoomuserType =ZOOM_SDK_NAMESPACE:: ZoomUserType_APIUSER;
			RestAPIUserStartParam.meetingNumber = uPMI;

			if (SDKInterfaceWrap::GetInst().IsSelectCustomizedUIMode() && m_parentFrame)
			{
				CSDKDemoAppEvent* pAppEvent = m_parentFrame->GetAppEvent();
				if(pAppEvent)
					pAppEvent->InitCustomizedUI();
			}

			if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == m_RestAPIUserWorkFlow.RestAPIStartMeeting(startParam))
			{
				bNeedWaiting = true;
			}
		}
		if(!bNeedWaiting)
		{
			m_parentFrame->ShowErrorMessage(L"Rest API start meeting failed");
			m_parentFrame->SetCurrentPage(m_WithoutLoginRestAPIPage);
			m_parentFrame->SwitchToWaitingPage(NULL, false);
		}
	}

	if(hmacHelper)
		delete hmacHelper;
	if(zoomHttpHelper)
		delete zoomHttpHelper;

}

void CSDKRestAPIUserUIGroup::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult)
{

	switch (status)
	{
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_RECONNECTING:
		if (SDKInterfaceWrap::GetInst().IsSelectCustomizedUIMode())
		{
			CSDKDemoAppEvent* pAppEvent = m_parentFrame->GetAppEvent();
			if(pAppEvent)
				pAppEvent->InitCustomizedUI();
		}
		break;
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_CONNECTING:
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_DISCONNECTING:
		break;
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_ENDED:
		{
			if(m_parentFrame)
				m_parentFrame->GetAppEvent()->onSwitchToLoginUI(SwitchToLoginUIType_MeetingEND);

		}
		break;
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_FAILED:
		{
			if(m_parentFrame)
			{
				m_parentFrame->SetCurrentPage(m_WithoutLoginRestAPIPage);
				m_parentFrame->ShowErrorMessage(L"Rest API start meeting failed");
			}
		}
		break;
	case ZOOM_SDK_NAMESPACE::MEETING_STATUS_INMEETING:
		{
			if(m_parentFrame)
				m_parentFrame->GetAppEvent()->onShowLoggedInUI(Demo_Meeting_RestAPI_Start);
		}
	default:
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class CSDKLoginUIMgr
CSDKLoginUIMgr::CSDKLoginUIMgr()
{
	m_pAppEvent = NULL;
	m_waitingPage = NULL;
	m_waitingLabelUI = NULL;
	m_gifWaiting = NULL;
	m_currentPage = NULL;
	m_btnLoginWithEmail = NULL;
	m_btnRestAPI = NULL;
	m_btnLoginWithSSO = NULL;
	m_btnJoinMeetingOnly = NULL;
	m_panel_login_content = NULL;
	m_email_login_page = NULL;
	m_sso_login_page = NULL;
	m_restApi_login_page = NULL;
	m_only_join_page = NULL;
}

CSDKLoginUIMgr::~CSDKLoginUIMgr()
{
	m_pAppEvent = NULL;
	m_waitingPage = NULL;
	m_waitingLabelUI = NULL;
	m_gifWaiting = NULL;
	m_currentPage = NULL;
	m_btnLoginWithEmail = NULL;
	m_btnRestAPI = NULL;
	m_btnLoginWithSSO = NULL;
	m_btnJoinMeetingOnly = NULL;
	m_panel_login_content = NULL;
	m_email_login_page = NULL;
	m_sso_login_page = NULL;
	m_restApi_login_page = NULL;
	m_only_join_page = NULL;
	m_LoginCBHandler.SetUIEvent(NULL);
}

void CSDKLoginUIMgr::SetEvent(CSDKDemoAppEvent* pAppEvent)
{
	m_pAppEvent = pAppEvent;
}

void CSDKLoginUIMgr::InitWindow()
{
	m_LoginWithEmailUIGroup.InitWindow(m_PaintManager, this);
	m_LoginWithSSOUIGroup.InitWindow(m_PaintManager, this);
	m_WithoutLoginStartJoinMeetingUIGroup.InitWindow(m_PaintManager,this);
	m_RestAPIUserUIGroup.InitWindow(m_PaintManager,this);
	RECT rc = { 0 };
	if( !::GetClientRect(m_hWnd, &rc) ) return;
	rc.right = rc.left + 524;
	rc.bottom = rc.top + 376;
	if( !::AdjustWindowRectEx(&rc, GetWindowStyle(m_hWnd), (!(GetWindowStyle(m_hWnd) & WS_CHILD) && (::GetMenu(m_hWnd) != NULL)), GetWindowExStyle(m_hWnd)) ) return;
	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	::SetWindowPos(m_hWnd, NULL, (ScreenX - (rc.right - rc.left)) / 2, 
		(ScreenY - (rc.bottom - rc.top)) / 2, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_SHOWWINDOW);


	m_waitingPage = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(_T("waiting")));
	m_waitingLabelUI = static_cast<CLabelUI* >(m_PaintManager.FindControl(_T("waiting_label")));
	m_gifWaiting = static_cast<CGifAnimUI*>(m_PaintManager.FindControl(_T("gif_waiting"))); 
	m_btnLoginWithEmail = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("tabbtn_login_with_email")));
	m_btnRestAPI = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("tabbtn_login_with_RestAPI")));
	m_btnLoginWithSSO = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("tabbtn_login_with_SSO")));
	m_btnJoinMeetingOnly = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("tabbtn_JoinMeetingOnly")));

	m_panel_login_content = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(L"panel_Login_Content"));
	m_email_login_page = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(L"panel_Login_With_Email"));
	m_sso_login_page = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(L"panel_Login_With_SSO"));
	m_restApi_login_page = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(L"panel_RestAPI_Without_Login"));
	m_only_join_page = static_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(L"panel_Join_Meeting_Only"));

	m_currentPage = m_email_login_page;
	SwitchToWaitingPage(L"", false);

	m_LoginCBHandler.SetUIEvent(this);
}

void CSDKLoginUIMgr::Notify(TNotifyUI& msg)
{
	if(msg.sType == _T("click"))
	{
		if(msg.pSender == m_btnLoginWithEmail)
		{
			SwitchToPage(login_UseEmail_Page);
		}
		else if (msg.pSender == m_btnLoginWithSSO)
		{
			SwitchToPage(login_UseSSO_Page);
		}
		else if (msg.pSender == m_btnJoinMeetingOnly)
		{
			SwitchToPage(login_JoinMeetingOnly_Page);
		}
		else if (msg.pSender == m_btnRestAPI)
		{
			SwitchToPage(login_RestAPI_Page);
		}
		else if (m_currentPage == m_email_login_page)
		{
			m_LoginWithEmailUIGroup.Notify(msg);
		}
		else if (m_currentPage == m_sso_login_page)
		{
			m_LoginWithSSOUIGroup.Notify(msg);
		}
		else if (m_currentPage == m_restApi_login_page)
		{
			m_RestAPIUserUIGroup.Notify(msg);
		}
		else if(m_currentPage == m_only_join_page)
		{
			m_WithoutLoginStartJoinMeetingUIGroup.Notify(msg);
		}
		else
		{
			m_LoginWithEmailUIGroup.Notify(msg);
			m_LoginWithSSOUIGroup.Notify(msg);
			m_WithoutLoginStartJoinMeetingUIGroup.Notify(msg);
			m_RestAPIUserUIGroup.Notify(msg);
		}
	}
}

LRESULT CSDKLoginUIMgr::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT CSDKLoginUIMgr::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if (m_pAppEvent)
	{
		m_pAppEvent->onQuitApp();
	}
	return 0;
}

LRESULT CSDKLoginUIMgr::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_LoginWithSSOUIGroup.UninitWindow();
	m_LoginWithSSOUIGroup.UninitWindow();
	m_WithoutLoginStartJoinMeetingUIGroup.UninitWindow();
	m_RestAPIUserUIGroup.UninitWindow();																									  
	return 0;
}

void CSDKLoginUIMgr::SwitchToWaitingPage(const wchar_t* waiting_message, bool show)
{
	if (m_currentPage && m_panel_login_content)
	{
		m_panel_login_content->SetVisible(!show);
		m_LoginWithSSOUIGroup.m_login_bottom->SetVisible(!show);
	}
	if (waiting_message && m_waitingLabelUI)
	{
		m_waitingLabelUI->SetText(waiting_message);
	}

	if (m_waitingPage)
	{
		m_waitingPage->SetVisible(show);
		if (m_gifWaiting)
		{
			show ? m_gifWaiting->PlayGif() : m_gifWaiting->StopGif();
		}
	}
}

void CSDKLoginUIMgr::ShowErrorMessage(const wchar_t* error_message)
{
	if (error_message)
		::MessageBox(NULL, error_message, L"error", MB_OK);
}

void CSDKLoginUIMgr::SwitchToPage(loginTabPage nPage)
{
	m_LoginWithEmailUIGroup.Hide();
	m_LoginWithSSOUIGroup.Hide();
	m_WithoutLoginStartJoinMeetingUIGroup.Hide();
	m_RestAPIUserUIGroup.Hide();
	switch(nPage)
	{
		case login_UseEmail_Page:
			m_LoginWithEmailUIGroup.Show();
			break;
		case login_RestAPI_Page:
			m_RestAPIUserUIGroup.Show();
			break;
		case login_UseSSO_Page:
			m_LoginWithSSOUIGroup.Show();
			break;
		case login_JoinMeetingOnly_Page:
			m_WithoutLoginStartJoinMeetingUIGroup.Show();
			break;
		default:
			break;
	}
}

CSDKDemoAppEvent* CSDKLoginUIMgr::GetAppEvent()
{
	return m_pAppEvent;
}

bool CSDKLoginUIMgr::LogOut()
{
	return m_LoginWithEmailUIGroup.LogOut();
}

void CSDKLoginUIMgr::ChangeUIforLoginFailed()
{
	if (m_panel_login_content)
	{
		m_panel_login_content->SetVisible(true);
	}
	SwitchToWaitingPage(L"",false);
	ShowErrorMessage(CSDKMessInfo::GetInst().GetErrorMessInfo());

}

void CSDKLoginUIMgr::ChangeUIforJoinFailed()
{
	if(m_panel_login_content)
	{
		m_panel_login_content->SetVisible(true);
	}
	SwitchToWaitingPage(L"",false);
}

void CSDKLoginUIMgr::NotifyAuthDone()
{
	ZOOM_SDK_NAMESPACE::IAuthService* auth_service = SDKInterfaceWrap::GetInst().GetAuthService();
	if (auth_service
		&& ZOOM_SDK_NAMESPACE::LOGIN_IDLE != auth_service->GetLoginStatus())
	{
		SwitchToWaitingPage(L"auto login...", true);
	}
}
/////////////////////////////////////////////////////////////////
CSDKLoginCBHandler::CSDKLoginCBHandler()
{
	m_parentFrame = NULL;
}

CSDKLoginCBHandler::~CSDKLoginCBHandler()
{
	m_parentFrame = NULL;
	SDKInterfaceWrap::GetInst().UnListenAuthServiceEvent(this);
}

void CSDKLoginCBHandler::SetUIEvent(CSDKLoginUIMgr* main_frame_)
{
	m_parentFrame = main_frame_;
	main_frame_ ? SDKInterfaceWrap::GetInst().ListenAuthServiceEvent(this) : SDKInterfaceWrap::GetInst().UnListenAuthServiceEvent(this);
}

void CSDKLoginCBHandler::onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo)
{
	if (ZOOM_SDK_NAMESPACE::LOGIN_SUCCESS == ret)
	{
		TCHAR szlog[MAX_PATH] = {0};
		wsprintf(szlog,_T("userName:%s\r\nLoginType:%d loggin success"),pAccountInfo->GetDisplayName(),pAccountInfo->GetLoginType());
		OutputDebugString(szlog);
		if(m_parentFrame && m_parentFrame->GetAppEvent())
		{
			m_parentFrame->GetAppEvent()->onShowLoggedInUI();
		}
	}
	if (ZOOM_SDK_NAMESPACE::LOGIN_FAILED == ret)
	{

		if(m_parentFrame && m_parentFrame->GetAppEvent())
		{
			m_parentFrame->GetAppEvent()->onLoginFailed();
		}
	}
}

void CSDKLoginCBHandler::onLogout()
{
}

void CSDKLoginCBHandler::onZoomIdentityExpired()
{
}

