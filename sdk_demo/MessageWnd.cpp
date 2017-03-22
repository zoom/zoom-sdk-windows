#include "MessageWnd.h"

CMessageWnd::CMessageWnd()
{
	m_strLabelText = _T("");
	m_strInputVal = _T("");
}

CMessageWnd::~CMessageWnd()
{
	m_strLabelText = _T("");
	m_strInputVal = _T("");
}

void CMessageWnd::InitWindow()
{
	InitAllControls();
}

void CMessageWnd::InitAllControls()
{
	m_lableInputVal = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lb_input_val")));
	m_editInputVal = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("edit_input_val")));
	m_btnOK = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_ok")));
	
	if (m_lableInputVal)
		m_lableInputVal->SetText(m_strLabelText.c_str());

	if (m_editInputVal)
		m_editInputVal->SetFocus();
}

void CMessageWnd::ResetAllControls()
{
	m_lableInputVal = NULL;
	m_editInputVal = NULL;
	m_btnOK = NULL;
}

void CMessageWnd::SetLabelText(std::wstring strLabelText)
{
	m_strLabelText = strLabelText;
}

std::wstring CMessageWnd::GetInputVal()
{
	return m_strInputVal;
}

void CMessageWnd::Notify( TNotifyUI& msg )
{
	if(msg.sType == _T("click"))
	{
		if(msg.pSender == m_btnOK)
		{
			if (m_editInputVal)
			{
				m_strInputVal = m_editInputVal->GetText().GetData();
			}

			PostMessage(WM_CLOSE, 0, 0);
		}
	}
}

LRESULT CMessageWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

		return lRes;
	}

	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CMessageWnd::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	if (IsWindow(GetHWND()))
		DestroyWindow(GetHWND());
	bHandled = FALSE;
	return 0;
}

LRESULT CMessageWnd::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	ResetAllControls();
	bHandled = FALSE;
	return 0;
}