#pragma once

#include "UIlib.h"
#include <Windows.h>
using namespace DuiLib;

class ClosedCaptionDisplayUI:
	public CWindowWnd,
	public INotifyUI
{
public:
	ClosedCaptionDisplayUI(int x, int y);
	virtual ~ClosedCaptionDisplayUI();

public:
	virtual void Notify( TNotifyUI& msg){}
	virtual LPCTSTR GetWindowClassName() const { return _T("CSDKDemoUI"); }
	virtual LRESULT	HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void SetDisplayContent(const wchar_t* str);
	void HandleSizeChanged(HWND _hwnd);

private:
	void Init();

protected:
	CPaintManagerUI m_PaintManager;
	CControlUI* m_pLabel;
	int posx;
	int posy;
};

void  CALLBACK HideWnd(HWND   hwnd,UINT   uMsg,UINT   idEvent,DWORD   dwTime);