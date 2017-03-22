#pragma once

#include "UIlib.h"
#include "resource.h"

using namespace DuiLib;

class CMessageWnd : public CWindowWnd, public INotifyUI/*public WindowImplBase*/
{
public:
	CMessageWnd();	
	virtual ~CMessageWnd();

public:
	virtual LPCTSTR		GetWindowClassName() const   {   return _T("MessageWnd");  }
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; };
	//virtual CDuiString	GetSkinFile()                {   return _T("DemoUI.xml");  }
	//virtual CDuiString	GetSkinFolder()              {   return _T("");  }
	virtual UINT		GetSkinRes()				 {	 return IDXML_MESSAGE_WND; }
	UILIB_RESOURCETYPE GetResourceType() const{	return UILIB_RESOURCE; }

	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND /*hWnd*/) { /*delete this;*/ }

	virtual void		Notify( TNotifyUI& msg );
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

public:
	std::wstring GetInputVal();
	void SetLabelText(std::wstring strLabelText);

private:
	void InitAllControls();
	void ResetAllControls();

protected:
	CPaintManagerUI m_PaintManager;

private:
	CRichEditUI*			m_editInputVal;
	CLabelUI*				m_lableInputVal;
	CButtonUI*				m_btnOK;

	std::wstring			m_strInputVal;
	std::wstring			m_strLabelText;
};