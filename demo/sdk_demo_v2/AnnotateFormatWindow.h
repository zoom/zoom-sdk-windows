#pragma once
#include "resource.h"
#include "UIlib.h"
#include "sdk_util.h"

using namespace DuiLib;

class AnnotateFormatWindow:
	public CWindowWnd ,
	public INotifyUI
{
public:
	AnnotateFormatWindow(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pShareRender);
	~AnnotateFormatWindow();

	virtual LPCTSTR		GetWindowClassName() const { return _T("zSDKDemoUI"); }
	UINT                GetClassStyle()      const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; }
	virtual UINT		GetSkinRes()               { return IDXML_ANNOTATE_FORMAT_WINDOW_UI; }
	UILIB_RESOURCETYPE  GetResourceType()    const { return UILIB_RESOURCE; }

	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND) {}

	virtual void		Notify( TNotifyUI& msg );
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	void MoveWindowPosTo(HWND hWnd);

private:
	void onClickColor(int nColorIndex);

private:
	CPaintManagerUI m_PaintManager;
	CButtonUI* m_btnColor1;
	CButtonUI* m_btnColor2;
	CButtonUI* m_btnColor3;
	CButtonUI* m_btnColor4;
	CButtonUI* m_btnColor5;
	CButtonUI* m_btnColor6;
	CButtonUI* m_btnColor7;
	CButtonUI* m_btnColor8;
	CButtonUI* m_btnColor9;
	CButtonUI* m_btnColor10;
	CButtonUI* m_btnColor11;
	CButtonUI* m_btnColor12;
	CButtonUI* m_btnColor13;
	CButtonUI* m_btnColor14;
	CButtonUI* m_btnColor15;
	CButtonUI* m_btnColor16;
	CButtonUI* m_btnLineThin;
	CButtonUI* m_btnLineThick;
	CButtonUI* m_btnLineThicker;
	CButtonUI* m_btnLineThickest;
	CCheckBoxUI* m_chkboxBold;
	CCheckBoxUI* m_chkboxItalic;
	CComboUI* m_cmbFontSize;
	CButtonUI* m_btnFontSet;
	ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* m_customerAnnoObj;
};