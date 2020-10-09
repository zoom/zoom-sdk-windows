#include "stdafx.h"
#include "AnnotateBarWindow.h"
#include "AnnotateFormatWindow.h"
#include "AnnotateDrawWindow.h"
#include "AnnotateStampWindow.h"
#include "AnnotateSpolightWindow.h"
#include "AnnotateClearWindow.h"

AnnotateBarWindow::AnnotateBarWindow(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* pShareRender)
{
	m_btnMouse  = NULL;
	m_btnSelect = NULL;
	m_btnText   = NULL;
	m_btnDraw   = NULL;
	m_btnStamp  = NULL;
	m_btnSpotlight = NULL;
	m_btnArrow  = NULL;
	m_btnEraser = NULL;
	m_btnFormat = NULL;
	m_btnUndo   = NULL;
	m_btnRedo   = NULL;
    m_btnClearAll = NULL;
	m_btnSave     = NULL;

	m_pAnnotateFormatWindow = NULL;
	m_pAnnotateDrawWindow   = NULL;
	m_pAnnotateStampWindow  = NULL;
	m_pAnnotateSpolightWindow = NULL;
	m_pAnnotateClearWindow    = NULL;

	m_customerAnnoCtrl = NULL;
	m_customerAnnoObj  = NULL;
	m_pShareRender = pShareRender;
}

AnnotateBarWindow::~AnnotateBarWindow()
{
	if (m_customerAnnoCtrl){
		if (m_customerAnnoObj){
			m_customerAnnoCtrl->DestroyAnnoObj(m_customerAnnoObj);
		}
	}
	if (m_pAnnotateClearWindow){
		delete m_pAnnotateClearWindow;
		m_pAnnotateClearWindow = NULL;
	}
	if (m_pAnnotateSpolightWindow){
		delete m_pAnnotateSpolightWindow;
		m_pAnnotateSpolightWindow = NULL;
	}
	if (m_pAnnotateFormatWindow){
		delete m_pAnnotateFormatWindow;
		m_pAnnotateFormatWindow = NULL;
	}
	if (m_pAnnotateDrawWindow){
		delete m_pAnnotateDrawWindow;
		m_pAnnotateDrawWindow = NULL;
	}
	if (m_pAnnotateStampWindow){
		delete m_pAnnotateStampWindow;
		m_pAnnotateStampWindow = NULL;
	}
	if(::IsWindow(m_hWnd)){
		::DestroyWindow(m_hWnd);
	}
}

void AnnotateBarWindow::MoveWindowPosTo(HWND hwOwner)
{
	RECT rc;
	RECT rcOwner;

	if (::GetWindowRect(hwOwner, &rcOwner)){
		if (::GetWindowRect(m_hWnd, &rc)) {
			::SetWindowPos(m_hWnd, NULL, rcOwner.left, rcOwner.bottom, rc.right-rc.left, rc.bottom-rc.top, SWP_HIDEWINDOW);
		}
	}
}

void AnnotateBarWindow::InitWindow()
{
	m_btnMouse     = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_mouse"));
	m_btnSelect    = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_select"));
	m_btnText      = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_text"));
	m_btnDraw      = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_draw"));
	m_btnStamp     = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_stamp"));
	m_btnSpotlight = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_spotlight"));
	m_btnArrow     = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_arrow"));
	m_btnEraser    = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_eraser"));
	m_btnFormat    = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_format"));
	m_btnUndo      = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_undo"));
	m_btnRedo      = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_redo"));
	m_btnClearAll  = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_clear_all"));
	m_btnSave      = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_save"));

	if (m_pShareRender == NULL){
		m_btnArrow->SetEnabled(false);
	}else {
		m_btnSelect->SetEnabled(false);
		m_btnSpotlight->SetEnabled(false);
		m_btnSave->SetEnabled(false);
	}
}

void AnnotateBarWindow::onClickStamp(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pAnnoObj)
{
	if (m_pAnnotateStampWindow == NULL){
		m_pAnnotateStampWindow = new AnnotateStampWindow(pAnnoObj);
		m_pAnnotateStampWindow->Create(m_hWnd, _T("Stamp"), WS_OVERLAPPED, WS_EX_TOPMOST | WS_EX_TOOLWINDOW);
	}

	if (::IsWindowVisible(m_pAnnotateStampWindow->GetHWND())){
		m_pAnnotateStampWindow->ShowWindow(false);
	}else {
		m_pAnnotateStampWindow->MoveWindowPosTo(m_hWnd);
		m_pAnnotateStampWindow->ShowWindow(true);
		HideBrotherWindows(_T("Stamp"));
	}
}

void AnnotateBarWindow::onClickClear(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pAnnoObj)
{
	if (m_pShareRender){
		//share viewer
		m_customerAnnoObj->Clear(ZOOM_SDK_NAMESPACE::ANNOCLEAR_SELF);
		return;
	}

	if (m_pAnnotateClearWindow == NULL){
		m_pAnnotateClearWindow = new AnnotateClearWindow(pAnnoObj);
		m_pAnnotateClearWindow->Create(m_hWnd, _T("Clear"), WS_OVERLAPPED, WS_EX_TOPMOST | WS_EX_TOOLWINDOW);
	}

	if (::IsWindowVisible(m_pAnnotateClearWindow->GetHWND())){
		m_pAnnotateClearWindow->ShowWindow(false);
	}else {
		m_pAnnotateClearWindow->MoveWindowPosTo(m_hWnd);
		m_pAnnotateClearWindow->ShowWindow(true);
		HideBrotherWindows(_T("Clear"));
	}
}

void AnnotateBarWindow::onClickSpotlight(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pAnnoObj)
{
	if (m_pAnnotateSpolightWindow == NULL){
		m_pAnnotateSpolightWindow = new AnnotateSpolightWindow(pAnnoObj);
		m_pAnnotateSpolightWindow->Create(m_hWnd, _T("Spolight"), WS_OVERLAPPED, WS_EX_TOPMOST | WS_EX_TOOLWINDOW);
	}

	if (::IsWindowVisible(m_pAnnotateSpolightWindow->GetHWND())){
		m_pAnnotateSpolightWindow->ShowWindow(false);
	}else {
		m_pAnnotateSpolightWindow->MoveWindowPosTo(m_hWnd);
		m_pAnnotateSpolightWindow->ShowWindow(true);
		HideBrotherWindows(_T("Spolight"));
	}
}

void AnnotateBarWindow::onClickFormat(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pAnnoObj)
{
	if (m_pAnnotateFormatWindow == NULL){
		m_pAnnotateFormatWindow = new AnnotateFormatWindow(pAnnoObj);
		m_pAnnotateFormatWindow->Create(m_hWnd, _T("Format"), WS_OVERLAPPED, WS_EX_TOPMOST | WS_EX_TOOLWINDOW);
	}

	if (::IsWindowVisible(m_pAnnotateFormatWindow->GetHWND())){
		m_pAnnotateFormatWindow->ShowWindow(false);
	}else {
		m_pAnnotateFormatWindow->MoveWindowPosTo(m_hWnd);
		m_pAnnotateFormatWindow->ShowWindow(true);
		HideBrotherWindows(_T("Format"));
	}
}

void AnnotateBarWindow::onClickDraw(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pAnnoObj)
{
	if (m_pAnnotateDrawWindow == NULL){
		m_pAnnotateDrawWindow = new AnnotateDrawWindow(pAnnoObj);
		m_pAnnotateDrawWindow->Create(m_hWnd, _T("Draw"), WS_OVERLAPPED, WS_EX_TOPMOST | WS_EX_TOOLWINDOW);
	}

	if (::IsWindowVisible(m_pAnnotateDrawWindow->GetHWND())){
		m_pAnnotateDrawWindow->ShowWindow(false);
	}else {
		m_pAnnotateDrawWindow->MoveWindowPosTo(m_hWnd);
		m_pAnnotateDrawWindow->ShowWindow(true);
		HideBrotherWindows(_T("Draw"));
	}
}

void AnnotateBarWindow::Notify( TNotifyUI& msg )
{
	if (msg.sType ==_T("click")){
		m_customerAnnoCtrl = SDKInterfaceWrap::GetInst().GetCustomizedAnnotationController(m_pShareRender);
		if (!m_customerAnnoCtrl) return;
		if (m_customerAnnoObj == NULL){
			m_customerAnnoCtrl->CreateAnnoObj(m_pShareRender, &m_customerAnnoObj);
			if (!m_customerAnnoObj) return;
		}

		//is annotation disable?
		bool bCan, bIs;
		ZOOM_SDK_NAMESPACE::SDKError err;
		bIs = m_customerAnnoObj->IsAnnoataionDisable();
		if (bIs) ::MessageBox(NULL, _T("IsAnnoataionDisable() true"),     _T("sdk demo"), MB_OK);
		
		//can do annotate?
		err = m_customerAnnoObj->CanDoAnnotation(bCan);
		if (err != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS)
		{
			::MessageBox(NULL, _T("CanDoAnnotation() error"), _T("sdk demo"), MB_OK);
			return;	
		}
		if (!bCan)
		{ 
			::MessageBox(NULL, _T("CanDoAnnotation() can not"), _T("sdk demo"), MB_OK);
			return;
		}

		if (msg.pSender == m_btnMouse)
		{
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_NONE_DRAWING);
		}
		else if (msg.pSender == m_btnSelect)
		{
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_PICKER);
		}
		else if (msg.pSender == m_btnText)
		{
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_TEXTBOX);
		}
		else if (msg.pSender == m_btnDraw)
		{
			onClickDraw(m_customerAnnoObj);
		}
		else if (msg.pSender == m_btnStamp)
		{
			onClickStamp(m_customerAnnoObj);
		}
		else if (msg.pSender == m_btnSpotlight)
		{
			onClickSpotlight(m_customerAnnoObj);
		}
		else if (msg.pSender == m_btnArrow)
		{
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_ARROW);
		}
		else if (msg.pSender == m_btnEraser)
		{
			m_customerAnnoObj->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_ERASER);
		}
		else if (msg.pSender == m_btnFormat)
		{
			onClickFormat(m_customerAnnoObj);
		}
		else if (msg.pSender == m_btnUndo)
		{
			m_customerAnnoObj->Undo();
		}
		else if (msg.pSender == m_btnRedo)
		{
			m_customerAnnoObj->Redo();
		}
		else if (msg.pSender == m_btnClearAll)
		{
			onClickClear(m_customerAnnoObj);
		}
		else if (msg.pSender == m_btnSave)
		{
			if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS == m_customerAnnoObj->CanSaveSnapshot())
				m_customerAnnoObj->SaveSnapshot(L"d:\\", ZOOM_SDK_NAMESPACE::SDK_ANNO_SAVE_PNG);
		}
	}
}

void AnnotateBarWindow::HideOwnedWindows()
{
	if (m_pAnnotateClearWindow){
		m_pAnnotateClearWindow->ShowWindow(false);
	}
	if (m_pAnnotateDrawWindow){
		m_pAnnotateDrawWindow->ShowWindow(false);
	}
	if (m_pAnnotateFormatWindow){
		m_pAnnotateFormatWindow->ShowWindow(false);
	}
	if (m_pAnnotateSpolightWindow){
		m_pAnnotateSpolightWindow->ShowWindow(false);
	}
	if (m_pAnnotateStampWindow){
		m_pAnnotateStampWindow->ShowWindow(false);
	}
}

void AnnotateBarWindow::HideBrotherWindows(LPTSTR pszShowStar)
{
	wstring wstrShowStar = pszShowStar;

	if (m_pAnnotateClearWindow    && (wstrShowStar != _T("Clear"))){
		m_pAnnotateClearWindow->ShowWindow(false);
	}
	if (m_pAnnotateDrawWindow     && (wstrShowStar != _T("Draw"))){
		m_pAnnotateDrawWindow->ShowWindow(false);
	}
	if (m_pAnnotateFormatWindow   && (wstrShowStar != _T("Format"))){
		m_pAnnotateFormatWindow->ShowWindow(false);
	}
	if (m_pAnnotateSpolightWindow && (wstrShowStar != _T("Spolight"))){
		m_pAnnotateSpolightWindow->ShowWindow(false);
	}
	if (m_pAnnotateStampWindow    && (wstrShowStar != _T("Stamp"))){
		m_pAnnotateStampWindow->ShowWindow(false);
	}
}

LRESULT AnnotateBarWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT AnnotateBarWindow::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	HideOwnedWindows();
	ShowWindow(false);
	return 1;
}

LRESULT AnnotateBarWindow::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 1;
}