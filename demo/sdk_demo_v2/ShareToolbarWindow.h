#pragma once
#include "resource.h"
#include "UIlib.h"
#include "sdk_util.h"
#include "user_manager.h"

using namespace DuiLib;

class CCustomizeInMeetingUIMgr;
class AnnotateBarWindow;

class ShareToolbarWindow:
	public CWindowWnd ,
	public INotifyUI
{
public:
	ShareToolbarWindow(CCustomizeInMeetingUIMgr* pMainUI);
	~ShareToolbarWindow();

	virtual LPCTSTR		GetWindowClassName() const { return _T("zSDKDemoUI"); }
	UINT                GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; }
	virtual UINT		GetSkinRes() { return IDXML_SHARE_TOOLBAR_WINDOW_UI; }
	UILIB_RESOURCETYPE  GetResourceType() const { return UILIB_RESOURCE; }

	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND) {}

	virtual void		Notify( TNotifyUI& msg );
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	void UpdateUserList();
	HWND GetWindowHandle();

private:
	unsigned int GetSelectedUserID();
    void ShowAnnotateBarWindow();

private:
	CPaintManagerUI m_PaintManager;
	CCustomizeInMeetingUIMgr* m_pMainUI;
	CButtonUI* m_btnStopShare;
	CButtonUI* m_btnAnnotate;
	CButtonUI* m_btnGiveControlTo;
	CButtonUI* m_btnStopRemoteControl;
	CComboUI*  m_pComboxUsers;
	AnnotateBarWindow* m_pAnnotateBarWindow;
};