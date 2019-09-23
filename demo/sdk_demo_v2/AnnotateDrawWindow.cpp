#include "stdafx.h"
#include "AnnotateDrawWindow.h"

AnnotateDrawWindow::AnnotateDrawWindow(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pAnnoObj)
{
	m_customerAnnoObj = pAnnoObj;

	m_btnCrookedLine     = NULL;
	m_btnAutoLineLine    = NULL;
	m_btnAutoRectangle   = NULL;
	m_btnAutoEllipseLine = NULL;
	m_btnHighlightLine   = NULL;
	m_btnAutoArrow       = NULL;
	m_btnRectangleFill   = NULL;
	m_btnEllipseFill     = NULL;
	m_btnRhombus         = NULL;
	m_btnDoubleArrow        = NULL;
	m_btnAutoRectanglePiece = NULL;
	m_btnAutoEllipsePiece   = NULL;
}

AnnotateDrawWindow::~AnnotateDrawWindow()
{
	if (::IsWindow(m_hWnd)){
		::DestroyWindow(m_hWnd);
	}
}

void AnnotateDrawWindow::MoveWindowPosTo(HWND hwOwner)
{
	RECT rcOwner;
	if (::GetWindowRect(hwOwner, &rcOwner)){
		RECT rc = { 0 };
		if (::GetWindowRect(m_hWnd, &rc)) {
			::SetWindowPos(m_hWnd, NULL, rcOwner.left + 220, rcOwner.bottom, rc.right-rc.left, rc.bottom-rc.top, SWP_HIDEWINDOW);
		}
	}
}

void AnnotateDrawWindow::InitWindow()
{
	m_btnCrookedLine     = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_crooked_line"));
	m_btnAutoLineLine    = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_autoLine_line"));
	m_btnAutoRectangle   = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_autoRectangle"));;
	m_btnAutoEllipseLine = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_autoEllipse_line"));;
	m_btnHighlightLine   = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_highlightLine"));;
	m_btnAutoArrow       = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_autoArrow"));;
	m_btnRectangleFill   = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_rectangleFill"));;
	m_btnEllipseFill     = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_ellipsefill"));;
	m_btnRhombus         = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_rhombus"));;
	m_btnDoubleArrow        = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_doubleArrow"));;
	m_btnAutoRectanglePiece = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_autoRectanglePiece"));;
	m_btnAutoEllipsePiece   = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_autoEllipsePiece"));;
}

void AnnotateDrawWindow::Notify( TNotifyUI& msg )
{
	if (msg.sType ==_T("click"))
	{
		if (msg.pSender == m_btnCrookedLine){
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_PEN);
		} else if (msg.pSender == m_btnAutoLineLine){
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_LINE);
		} else if (msg.pSender == m_btnAutoRectangle){
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_RECTANGLE);
		} else if (msg.pSender == m_btnAutoEllipseLine){
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_ELLIPSE);
		} else if (msg.pSender == m_btnHighlightLine){
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_HIGHLIGHTER);
		} else if (msg.pSender == m_btnAutoArrow){
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_ARROW);
		} else if (msg.pSender == m_btnRectangleFill){
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_RECTANGLE_SEMI_FILL);
		} else if (msg.pSender == m_btnEllipseFill){
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_ELLIPSE_SEMI_FILL);
		} else if (msg.pSender == m_btnRhombus){
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_DIAMOND);
		} else if (msg.pSender == m_btnDoubleArrow){
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_DOUBLE_ARROW);
		} else if (msg.pSender == m_btnAutoRectanglePiece){
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_RECTANGLE_FILL);
		} else if (msg.pSender == m_btnAutoEllipsePiece){
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_AUTO_ELLIPSE_FILL);
		}
	}
}

LRESULT AnnotateDrawWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT AnnotateDrawWindow::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return true;
}

LRESULT AnnotateDrawWindow::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return true;
}