#pragma once
#include "sdk_util.h"
#include "UIlib.h"
#include "resource.h"
#include "init_auth_sdk_workflow.h"
#include "sdk_demo_app_common.h"
//#include "toolbar_manager.h"
/////////////////////////
class CSDKInitAuthUIMgr;
class CInitSDKUIGroup : public CInitSDKWorkFlowUIEvent
{
public:
	CInitSDKUIGroup();
	virtual ~CInitSDKUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKInitAuthUIMgr* main_frame_);
	void UninitWindow();
	void Show();
	void Hide();
	void Notify( TNotifyUI& msg );

	void DoInitBtnClick();
	virtual void onSDKInited(ZOOM_SDK_NAMESPACE::SDKError err);
protected:
	CVerticalLayoutUI* m_InitSDKPage;
	CButtonUI*		   m_btnInit;
	CRichEditUI*	   m_editWebDomain;
	CCheckBoxUI*	   m_chkCustomizedUI;
	CSDKInitAuthUIMgr*	   m_mainFrame;
	CInitSDKWorkFlow   m_initSDKWorkFlow;
};

class CAuthSDKUIGroup : public CAuthSDKWorkFlowUIEvent
{
public:
	CAuthSDKUIGroup();
	virtual ~CAuthSDKUIGroup();
	void InitWindow(CPaintManagerUI& ui_mgr, CSDKInitAuthUIMgr* main_frame_);
	void UninitWindow();
	void Show();
	void Hide();
	void Notify( TNotifyUI& msg );

	void DoAuthBtnClick();
	virtual void onSDKAuthed(ZOOM_SDK_NAMESPACE::AuthResult ret);
protected:
	CVerticalLayoutUI* m_AuthSDKPage;
	CButtonUI*		   m_btnAuth;
	std::wstring	   m_strOldValue;
	CRichEditUI*	   m_editSDKJWTToken;
	CSDKInitAuthUIMgr*	   m_mainFrame;
	CAuthSDKWorkFlow   m_AuthSDKWorkFlow;
};

///////////////////////////
class CSDKInitAuthUIMgr : 
	public CWindowWnd, 
	public INotifyUI
{
public:
	CSDKInitAuthUIMgr();
	virtual ~CSDKInitAuthUIMgr();
	void SetEvent(CSDKDemoAppEvent* pAppEvent);
public:
	virtual LPCTSTR		GetWindowClassName() const   {   return _T("zSDKDemoUI");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; };
	virtual UINT		GetSkinRes()				 {	 return IDXML_MAINFRAME_UI; }	
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }

	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND)   {}

	virtual void		Notify( TNotifyUI& msg );
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	void SwitchToWaitingPage(const wchar_t* waiting_message, bool show);
	void ShowErrorMessage(const wchar_t* error_message);
	void SwitchToAuthPage(bool show);

	CSDKDemoAppEvent* GetAppEvent();
	void SetCurrentPage(CVerticalLayoutUI* current_) {m_currentPage = current_;}
protected:
	CPaintManagerUI m_PaintManager;
	CInitSDKUIGroup m_InitSDKUIGroup;
	CAuthSDKUIGroup m_AuthSDKUIGroup;
	CSDKDemoAppEvent* m_pAppEvent;
	CVerticalLayoutUI* m_waitingPage;
	CLabelUI*          m_waitingLabelUI;
	CGifAnimUI*		   m_gifWaiting;
	CVerticalLayoutUI* m_currentPage;
};