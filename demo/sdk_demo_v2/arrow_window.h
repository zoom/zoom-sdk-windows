#pragma once
#include "sdk_util.h"
#include "UIlib.h"
#include "Resource.h"

#include "custom_ui_mgr.h"
#include "sdk_demo_app_common.h"

//#define DEFAULT_ARROW_HEIGHT 35
#define DEFAULT_ARROW_HEIGHT 25

class CCustomizeInMeetingUIMgr;

class CArrowWindow : 
	public CWindowWnd, 
	public INotifyUI
{
public:
	CArrowWindow(CCustomizeInMeetingUIMgr* pCustomizeUI);
	~CArrowWindow();

	virtual void Notify( TNotifyUI& msg);
	bool IsWindow();
	bool DestroyWindow();
	HWND GetParent() {return m_hParentWnd;}
	void SetParent(HWND hParentWnd);

	virtual LPCTSTR		GetWindowClassName() const   {   return _T("zSDKDemoUI");  }
	//UINT GetClassStyle() const { return UI_WNDSTYLE_CHILD | CS_DBLCLKS ;  };
	UINT GetClassStyle() const { return UI_CLASSSTYLE_CHILD | CS_DBLCLKS ; };
	virtual UINT		GetSkinRes()				 {	 return IDXML_ARROW_BAR_FRAME_UI; }	
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }
	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND)   {}
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void EnableUsingButton(ArrowButtonType btnType, bool bEnable = false);
	void HandleSizeChanged(RECT newRC);
private:
	void DoButtonClick(ArrowButtonType btnType);
private:
	CCustomizeInMeetingUIMgr* m_pCustomizeUI;
	CPaintManagerUI m_PaintManager;
	CHorizontalLayoutUI* m_containerBottomButtons;
	CButtonUI* m_btnArrowPre;
	CButtonUI* m_btnArrowNext;
	HWND m_hParentWnd;

};

