#include "stdafx.h"
#include "display_cc_ui.h"

ClosedCaptionDisplayUI::ClosedCaptionDisplayUI(int x, int y)
{
	m_pLabel = NULL;
	posx = x;
	posy = y;
}

ClosedCaptionDisplayUI::~ClosedCaptionDisplayUI()
{
	m_pLabel = NULL;
}

LRESULT ClosedCaptionDisplayUI::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	if( uMsg == WM_CREATE ) 
	{
		m_PaintManager.Init(m_hWnd);
		m_pLabel = new CLabelUI;
		m_PaintManager.AttachDialog(m_pLabel);
		Init();
		return lRes;
	}

	if (uMsg == WM_INITMENU)
	{
		return 0;
	}
	if( uMsg == WM_NCCALCSIZE)
	{
		return 0;
	}
	if( uMsg == WM_NCPAINT)
	{
		CWindowWnd::SendMessageW(WM_PAINT);
	}
	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

void ClosedCaptionDisplayUI::SetDisplayContent( const wchar_t* str )
{
	if (m_pLabel)
	{
		m_pLabel->SetText(str);
	}

	if (IsWindowVisible(m_hWnd))
	{
		SetTimer(m_hWnd,1, 2000, (TIMERPROC)HideWnd);
	}
	else
	{
		ShowWindow(true);
		SetTimer(m_hWnd,1, 2000, (TIMERPROC)HideWnd);
	}

}

void ClosedCaptionDisplayUI::Init()
{
	if (m_pLabel)
	{
		m_pLabel->SetBkColor(/*0xff3f3f3f*/0xff191919);
		m_pLabel->SetAttribute(L"textcolor",L"0xFFFFFFFFF");
		m_pLabel->SetAttribute(L"valign", L"top");
		m_pLabel->SetAttribute(L"textpadding", L"4,4,4,4");
		m_pLabel->SetAttribute(L"showhtml",L"true");
		m_pLabel->SetAttribute(L"multiline", L"true");
	}
	
	::SetLayeredWindowAttributes(m_hWnd, 0, 180, LWA_ALPHA);
	SetWindowLong(m_hWnd, GWL_STYLE, GetWindowLong(m_hWnd, GWL_STYLE) & ~WS_CAPTION);
	::SetWindowPos(m_hWnd,NULL,posx,posy,400,70,SWP_NOZORDER | SWP_HIDEWINDOW);


}

void ClosedCaptionDisplayUI::HandleSizeChanged(HWND _hwnd)
{
	if (IsWindow(_hwnd))
	{
		RECT rc ={0};
		GetWindowRect(_hwnd, &rc);
		int posx = (rc.left + rc.right - 400)/2;
		int posy = rc.bottom - 140;
		MoveWindow(m_hWnd, posx, posy, 400, 70, true);
	}
	
}

void  CALLBACK HideWnd(HWND   hwnd,UINT   uMsg,UINT   idEvent,DWORD   dwTime)
{
	ShowWindow(hwnd, false);
	KillTimer(hwnd,1);
}