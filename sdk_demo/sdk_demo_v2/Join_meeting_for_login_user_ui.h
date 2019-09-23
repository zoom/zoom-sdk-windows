#pragma once
#include "sdk_util.h"
#include "UIlib.h"
#include "resource.h"
#include "Join_meeting_for_login_user_workflow.h"
#include "LoggedIn_sdk_controller_ui.h"
#include "sdk_demo_app_common.h"

class CSDKJoinMeetingForLoginUserFlowUIEvent;
class CSDKJoinMeetingForLoginUserUIMgr;

class CSDKJoinMeetingForLoginUserUIGroup:public CSDKJoinMeetingForLoginUserFlowUIEvent
{
public:
	CSDKJoinMeetingForLoginUserUIGroup();
	virtual ~CSDKJoinMeetingForLoginUserUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKJoinMeetingForLoginUserUIMgr* main_frame_);
	void UninitWindow();
	void Show();
	void Hide();
	void Notify(TNotifyUI& msg);
	void DoJoinMeetingBtnClick();
	
public:
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);
	virtual void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type) {};
	virtual void onMeetingSecureKeyNotification(const char* key, int len, ZOOM_SDK_NAMESPACE::IMeetingExternalSecureKeyHandler* pHandler) {};
	virtual void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param) {};

protected:
 	CVerticalLayoutUI* m_JoinMeetingForLoginUserPage;
 	CRichEditUI*	   m_editMeetingNumber;
 	CRichEditUI*	   m_editScreenName;
 	CRichEditUI*	   m_editMeetingPassword;
 	CButtonUI*	   m_btnJoin;
	CSDKJoinMeetingForLoginUserUIMgr*  m_parentFrame;
	CSDKLoggedInUIMgr* m_pLoggedInUIMgr;
	CSDKJoinMeetingForLoginUserFlow m_joinMeetingForLoginUserWorkFlow;
	bool m_bJoinIn;
};
class CSDKJoinMeetingForLoginUserUIMgr : 
	public CWindowWnd, 
	public INotifyUI
{
public:
	CSDKJoinMeetingForLoginUserUIMgr();
	virtual ~CSDKJoinMeetingForLoginUserUIMgr();

	void SetEvent(CSDKDemoAppEvent* pAppEvent);
public:
	virtual LPCTSTR		GetWindowClassName() const   {   return _T("zSDKDemoUI");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; };
	virtual UINT		GetSkinRes()				 {	 return IDXML_JOIN_MEETING_FRAME_UI; }
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }

	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND) {}

	virtual void		Notify( TNotifyUI& msg );
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	void ShowErrorMessage(const wchar_t* error_message);

	CSDKDemoAppEvent* GetAppEvent();

protected:
	CPaintManagerUI m_PaintManager;
	CSDKJoinMeetingForLoginUserUIGroup m_JoinMeetingForLoginUserUIGroup;	
	CSDKDemoAppEvent* m_pAppEvent;
};