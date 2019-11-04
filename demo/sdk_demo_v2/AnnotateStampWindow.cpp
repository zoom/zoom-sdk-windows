#include "stdafx.h"
#include "AnnotateStampWindow.h"

AnnotateStampWindow::AnnotateStampWindow(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pAnnoObj)
{
	m_customerAnnoObj = pAnnoObj;
	m_btnArrow = NULL;
	m_btnCheck = NULL;
	m_btnX = NULL; 
	m_btnStar = NULL;
	m_btnHeart = NULL;
	m_btnQm = NULL;
}

AnnotateStampWindow::~AnnotateStampWindow()
{
	if (::IsWindow(m_hWnd)){
		::DestroyWindow(m_hWnd);
	}
}

void AnnotateStampWindow::MoveWindowPosTo(HWND hwOwner)
{
	RECT rcOwner;
	if (::GetWindowRect(hwOwner, &rcOwner)){
		RECT rc = { 0 };
		if (::GetWindowRect(m_hWnd, &rc)) {
			::SetWindowPos(m_hWnd, NULL, rcOwner.left + 290, rcOwner.bottom, rc.right-rc.left, rc.bottom-rc.top, SWP_HIDEWINDOW);
		}
	}
}

void AnnotateStampWindow::InitWindow()
{
	m_btnArrow = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_arrow"));
	m_btnCheck = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_check"));
	m_btnX     = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_x")); 
	m_btnStar  = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_star"));
	m_btnHeart = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_heart"));
	m_btnQm    = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_qm")); 
}

void AnnotateStampWindow::Notify( TNotifyUI& msg )
{
	if (msg.sType ==_T("click"))
	{
		if (m_customerAnnoObj == NULL){
			return;
		}
		ZOOM_SDK_NAMESPACE::AnnotationToolType annoToolType;
		if (msg.pSender == m_btnArrow){
			annoToolType = ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_STAMP_ARROW;
		} else if (msg.pSender == m_btnCheck){
			annoToolType = ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_STAMP_CHECK;
		} else if (msg.pSender == m_btnX){
			annoToolType = ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_STAMP_X;
		} else if (msg.pSender == m_btnStar){
			annoToolType = ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_STAMP_STAR;
		} else if (msg.pSender == m_btnHeart){
			annoToolType = ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_STAMP_HEART;
		} else if (msg.pSender == m_btnQm){
			annoToolType = ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_STAMP_QM;
		}
		m_customerAnnoObj->SetTool(annoToolType);
	}
}

LRESULT AnnotateStampWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT AnnotateStampWindow::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 1;
}

LRESULT AnnotateStampWindow::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 1;
}