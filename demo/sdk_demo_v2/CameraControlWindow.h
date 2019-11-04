#pragma once
#include "resource.h"
#include "UIlib.h"
class CCustomizeInMeetingUIMgr;
using namespace DuiLib;

class CameraControlWindow:
	public CWindowWnd ,
	public INotifyUI
{
public:
	CameraControlWindow();
	CameraControlWindow(CCustomizeInMeetingUIMgr* pMainUI);
	~CameraControlWindow();

	virtual LPCTSTR		GetWindowClassName() const { return _T("zSDKDemoUI"); }
	UINT                GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; }
	virtual UINT		GetSkinRes() { return IDXML_CAMERA_CONTROL_UI; }
	UILIB_RESOURCETYPE  GetResourceType() const { return UILIB_RESOURCE; }

	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND) {}

	virtual void		Notify( TNotifyUI& msg );
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	
	bool DestroyWindow();

private:
	CPaintManagerUI m_PaintManager;
	CCustomizeInMeetingUIMgr* m_pMainUI;
	CButtonUI* m_btnZoomIn;
	CButtonUI* m_btnZoomOut;
	CButtonUI* m_btnLeft;
	CButtonUI* m_btnRight;
	CButtonUI* m_btnUp;
	CButtonUI* m_btnDown;
	CButtonUI* m_btnCheck;
};