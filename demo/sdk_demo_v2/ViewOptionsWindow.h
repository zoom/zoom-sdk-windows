#pragma once
#include "resource.h"
#include "UIlib.h"
#include "sdk_util.h"

using namespace DuiLib;

class AnnotateBarWindow;

class ViewOptionsWindow:
	public CWindowWnd ,
	public INotifyUI
{
public:
	ViewOptionsWindow(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* pShareRender);
	~ViewOptionsWindow();

	virtual LPCTSTR		GetWindowClassName() const { return _T("zSDKDemoUI"); }
	UINT                GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; }
	virtual UINT		GetSkinRes() { return IDXML_VIEW_OPTIONS_WINDOW_UI; }
	UILIB_RESOURCETYPE  GetResourceType() const { return UILIB_RESOURCE; }

	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND) {}

	virtual void		Notify( TNotifyUI& msg );
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

private:
	void ShowAnnotateBarWindow();

private:
	CPaintManagerUI m_PaintManager;
	CButtonUI* m_btnRequestRemoteControl;
	CButtonUI* m_btnGiveupRemoteControl;
	CButtonUI* m_btnAnnotate;
	ZOOM_SDK_NAMESPACE::ICustomizedAnnotationController* m_customerAnnoCtrl;
	ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* m_customerAnnoObj;
	ZOOM_SDK_NAMESPACE::ICustomizedShareRender* m_pShareRender;
	AnnotateBarWindow* m_pAnnotateBarWindow;
	bool m_bShowAnnoWin;
};