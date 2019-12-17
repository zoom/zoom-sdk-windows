#pragma once
#include "sdk_util.h"
#include "UIlib.h"
#include "resource.h"
#include "LOGIN_login_with_email_workflow.h"
#include "LOGIN_login_with_sso_workflow.h"
#include "LOGIN_join_meeting_only_workflow.h"
#include "LOGIN_restapi_without_login_workflow.h"
#include "sdk_demo_app_common.h"
/////////////////////////
enum loginTabPage
{
	login_UseEmail_Page = 0,
	login_RestAPI_Page,
	login_UseSSO_Page,
	login_JoinMeetingOnly_Page
};

class CSDKLoginFlowUIEvent;
class CSDKLoginUIMgr;
class CSDKLoginCBHandler;
class CSDKLoginWithEmailUIGroup
{
public:
	CSDKLoginWithEmailUIGroup();
	virtual ~CSDKLoginWithEmailUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKLoginUIMgr* main_frame_);
	void UninitWindow();
	void Show();
	void Hide();
	bool LogOut();
	void Notify( TNotifyUI& msg );

	void DoLoginWithEmailBtnClick();
		
protected:
	CVerticalLayoutUI* m_loginWithEmailPage;
	CRichEditUI*	   m_editUserAccount;
	CRichEditUI*	   m_editUserPassword;
	CButtonUI*		   m_btnLogin;
	CCheckBoxUI*       m_chkRemember;
	CSDKLoginUIMgr*	   m_parentFrame;
	CSDKLoginWithEmailFlow   m_loginEmailWorkFlow;
public:
	CVerticalLayoutUI* m_login_bottom;
};

class CSDKLoginWithSSOUIGroup
{
public:
	CSDKLoginWithSSOUIGroup();
	virtual ~CSDKLoginWithSSOUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKLoginUIMgr* main_frame_);
	void UninitWindow();
	void Show();
	void Hide();
	void Notify( TNotifyUI& msg );

	void DoLoginWithSSOBtnClick();

protected:
	CVerticalLayoutUI* m_loginWithSSOPage;
	CRichEditUI*	   m_editSSOtoken;
	CSDKLoginUIMgr*	   m_parentFrame;
	CSDKLoginWithSSOFlow   m_loginSSOWorkFlow;
	CButtonUI*		   m_btnLogin;
	CCheckBoxUI*       m_chkRemember;
public:
	CVerticalLayoutUI* m_login_bottom;
};

class CSDKLoginCBHandler : public ZOOM_SDK_NAMESPACE::IAuthServiceEvent
{
public:
	CSDKLoginCBHandler();
	virtual ~CSDKLoginCBHandler();
	void SetUIEvent(CSDKLoginUIMgr* main_frame_);
	virtual void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret) {};
	virtual void onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo);
	virtual void onLogout();
	virtual void onZoomIdentityExpired();
	virtual void onZoomAuthIdentityExpired() {}
protected:
	CSDKLoginUIMgr* m_parentFrame;
};

class CSDKWithoutLoginStartJoinMeetingUIGroup :public CSDKJoinMeetingOnlyFlowUIEvent
{
public:
	CSDKWithoutLoginStartJoinMeetingUIGroup();
	virtual ~CSDKWithoutLoginStartJoinMeetingUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKLoginUIMgr* main_frame_);
	void UninitWindow();
	void Show();
	void Hide();
	void Notify(TNotifyUI& msg);

	void DoWithoutLoginStartJoinMeetingBtnClick();
public:
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type) {};
	virtual void onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler) {};
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param) {};
  
protected:
	CVerticalLayoutUI* m_WithoutLoginStartJoinMeetingPage;
	CRichEditUI*	   m_editMeetingNumber;
	CRichEditUI*	   m_editScreenName;
	CRichEditUI*	   m_editMeetingPassword;
	CButtonUI*		   m_btnJoin;
	CCheckBoxUI*       m_chkRemember;
	CSDKLoginUIMgr*	   m_parentFrame;
	CSDKWithoutLoginStartJoinMeetingFlow  m_withoutLoginJoinMeetingWorkFlow;
	bool m_bInMeeting;
};

class CSDKRestAPIUserUIGroup : public CSDKRestAPIUserUIEvent
{
public:
	CSDKRestAPIUserUIGroup();
	virtual ~CSDKRestAPIUserUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKLoginUIMgr* main_frame_);
	void UninitWindow();
	void Show();
	void Hide();
	void Notify(TNotifyUI& msg);

	void DoWithoutLoginStartMeetingBtnClick();

public:
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);
	//handle the following status later. Just ignore them for a moment
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type) {};
	virtual void onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler) {};
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param) {};

private:
	CVerticalLayoutUI* m_WithoutLoginRestAPIPage;
	CRichEditUI*	   m_editRestAPIKey;
	CRichEditUI*	   m_editRestAPISecret;
	CRichEditUI*	   m_editEmail;
	CRichEditUI*	   m_editScreenName;

	CCheckBoxUI*  m_chkRemember;
	CButtonUI*		   m_btnStartMeeting;
	CSDKLoginUIMgr*  m_parentFrame;
	CSDKRestAPIUserWorkFlow  m_RestAPIUserWorkFlow;
	bool m_bInMeeting;
};

class CSDKLoginUIMgr : 
	public CWindowWnd, 
	public INotifyUI
{
public:
	CSDKLoginUIMgr();
	virtual ~CSDKLoginUIMgr();

	void SetEvent(CSDKDemoAppEvent* pAppEvent);
public:
	virtual LPCTSTR		GetWindowClassName() const   {   return _T("zSDKDemoUI");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; };
	virtual UINT		GetSkinRes()				 {	 return IDXML_LOGINFRAME_UI; };
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }

	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND) {}

	virtual void		Notify( TNotifyUI& msg );
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	void SwitchToWaitingPage(const wchar_t* waiting_message, bool show);
	void ShowErrorMessage(const wchar_t* error_message);
	void SwitchToPage(loginTabPage nPage);

	CSDKDemoAppEvent* GetAppEvent();
	void SetCurrentPage(CVerticalLayoutUI* current_) {m_currentPage = current_;}

	bool LogOut();
	void ChangeUIforLoginFailed();
	void ChangeUIforJoinFailed();

	void NotifyAuthDone();

protected:
	CPaintManagerUI m_PaintManager;
	CSDKLoginWithEmailUIGroup m_LoginWithEmailUIGroup;
	CSDKLoginWithSSOUIGroup m_LoginWithSSOUIGroup;
	CSDKWithoutLoginStartJoinMeetingUIGroup m_WithoutLoginStartJoinMeetingUIGroup;
	CSDKRestAPIUserUIGroup m_RestAPIUserUIGroup;
	CSDKLoginCBHandler     m_LoginCBHandler;
	CSDKDemoAppEvent* m_pAppEvent;
	CVerticalLayoutUI* m_waitingPage;
	CLabelUI*          m_waitingLabelUI;
	CGifAnimUI*		   m_gifWaiting;
	CVerticalLayoutUI* m_currentPage;

	COptionUI* m_btnLoginWithEmail;
	COptionUI* m_btnRestAPI;
	COptionUI* m_btnLoginWithSSO;
	COptionUI* m_btnJoinMeetingOnly;
	CVerticalLayoutUI* m_panel_login_content;

	CVerticalLayoutUI* m_email_login_page;
	CVerticalLayoutUI* m_sso_login_page;
	CVerticalLayoutUI* m_restApi_login_page;
	CVerticalLayoutUI* m_only_join_page;
};
