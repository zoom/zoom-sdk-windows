#include "stdafx.h"
#include "AnnotateFormatWindow.h"

AnnotateFormatWindow::AnnotateFormatWindow(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pAnnoObj)
{
	m_customerAnnoObj = pAnnoObj;
	m_btnColor1 = NULL;
	m_btnColor2 = NULL;
	m_btnColor3 = NULL;
	m_btnColor4 = NULL;
	m_btnColor5 = NULL;
	m_btnColor6 = NULL;
	m_btnColor7 = NULL;
	m_btnColor8 = NULL;
	m_btnColor9 = NULL;
	m_btnColor10 = NULL;
	m_btnColor11 = NULL;
	m_btnColor12 = NULL;
	m_btnColor13 = NULL;
	m_btnColor14 = NULL;
	m_btnColor15 = NULL;
	m_btnColor16 = NULL;

	m_btnLineThin = NULL;
	m_btnLineThick = NULL;
	m_btnLineThicker = NULL;
	m_btnLineThickest = NULL;

	m_btnFontSet = NULL;
}

AnnotateFormatWindow::~AnnotateFormatWindow()
{
	if (::IsWindow(m_hWnd)){
		::DestroyWindow(m_hWnd);
	}
}

void AnnotateFormatWindow::MoveWindowPosTo(HWND hwOwner)
{
	RECT rcOwner;
	if (::GetWindowRect(hwOwner, &rcOwner)){
		RECT rc = { 0 };
		if (::GetWindowRect(m_hWnd, &rc)) {
			::SetWindowPos(m_hWnd, NULL, rcOwner.left + 570, rcOwner.bottom, rc.right-rc.left, rc.bottom-rc.top, SWP_HIDEWINDOW);
		}
	}
}

void AnnotateFormatWindow::InitWindow()
{
	m_btnColor1 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_color1"));
	m_btnColor2 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_color2"));
	m_btnColor3 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_color3"));
	m_btnColor4 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_color4"));
	m_btnColor5 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_color5"));
	m_btnColor6 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_color6"));
	m_btnColor7 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_color7"));
	m_btnColor8 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_color8"));
	m_btnColor9 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_color9"));
	m_btnColor10 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_color10"));
	m_btnColor11 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_color11"));
	m_btnColor12 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_color12"));
	m_btnColor13 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_color13"));
	m_btnColor14 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_color14"));
	m_btnColor15 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_color15"));
	m_btnColor16 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_color16"));

	m_btnLineThin = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_line_thin"));
	m_btnLineThick = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_line_thick"));
	m_btnLineThicker = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_line_thicker"));
	m_btnLineThickest = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_line_thickest"));
}

void AnnotateFormatWindow::onClickColor(int nColorIndex)
{
	unsigned long nColorValue;

	switch (nColorIndex)
	{
	case 1:
	    //yellow
		nColorValue = RGB(255, 255, 0);
		break;
	case 2:
		//orange
		nColorValue = RGB(255, 102, 0);
		break;
	case 3:
		//red
		nColorValue = RGB(255, 0, 0);
		break;
	case 4:
		nColorValue = RGB(96, 57, 19);
		break;
	case 5:
		nColorValue = RGB(246, 150, 121);
		break;
	case 6:
		nColorValue = RGB(236, 0, 140);
		break;
	case 7:
		nColorValue = RGB(146, 39, 143);
		break;
	case 8:
		nColorValue = RGB(0, 0, 0);
		break;
	case 9:
		nColorValue = RGB(0, 165, 255);
		break;
	case 10:
		nColorValue = RGB(0, 0, 255);
		break;
	case 11:
		nColorValue = RGB(0, 33, 87);
		break;
	case 12:
		nColorValue = RGB(149, 149, 149);
		break;
	case 13:
		nColorValue = RGB(137, 204, 0);
		break;
	case 14:
		nColorValue = RGB(0, 255, 0);
		break;
	case 15:
		nColorValue = RGB(0, 114, 54);
		break;
	case 16:
		nColorValue = RGB(255, 255, 255);
		break;
	}
	
	m_customerAnnoObj->SetColor(nColorValue);
}

void AnnotateFormatWindow::Notify( TNotifyUI& msg )
{
	if (msg.sType ==_T("click"))
	{
		if (msg.pSender == m_btnColor1){
			onClickColor(1);
		}else if (msg.pSender == m_btnColor2){
			onClickColor(2);
		}else if (msg.pSender == m_btnColor3){
			onClickColor(3);
		}else if (msg.pSender == m_btnColor4){
			onClickColor(4);
		}else if (msg.pSender == m_btnColor5){
			onClickColor(5);
		}else if (msg.pSender == m_btnColor6){
			onClickColor(6);
		}else if (msg.pSender == m_btnColor7){
			onClickColor(7);
		}else if (msg.pSender == m_btnColor8){
			onClickColor(8);
		}else if (msg.pSender == m_btnColor9){
			onClickColor(9);
		}else if (msg.pSender == m_btnColor10){
			onClickColor(10);
		}else if (msg.pSender == m_btnColor11){
			onClickColor(11);
		}else if (msg.pSender == m_btnColor12){
			onClickColor(12);
		}else if (msg.pSender == m_btnColor13){
			onClickColor(13);
		}else if (msg.pSender == m_btnColor14){
			onClickColor(14);
		}else if (msg.pSender == m_btnColor15){
			onClickColor(15);
		}else if (msg.pSender == m_btnColor16){
			onClickColor(16);
		}else if (msg.pSender == m_btnLineThin) { //TODO, param value???
			m_customerAnnoObj->SetLineWidth(1);
		}else if (msg.pSender == m_btnLineThick){
			m_customerAnnoObj->SetLineWidth(3);
		}else if (msg.pSender == m_btnLineThicker){
			m_customerAnnoObj->SetLineWidth(5);
		}else if (msg.pSender == m_btnLineThickest){
			m_customerAnnoObj->SetLineWidth(7);
		}else if (msg.pSender == m_btnFontSet){
			//m_customerAnnoObj->SetFont(); //TODO, no interface?????
		}
	}
}

LRESULT AnnotateFormatWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		this->ShowWindow(false);
		return lRes;
	}
	else if (uMsg == WM_DESTROY)
	{
		OnDestroy(uMsg, wParam, lParam, bHandled);		
	}
	else if (uMsg == WM_NCDESTROY)
	{
		//delete this;
		//window obj pointer = NULL
	}

	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT AnnotateFormatWindow::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return true;
}

LRESULT AnnotateFormatWindow::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return true;
}