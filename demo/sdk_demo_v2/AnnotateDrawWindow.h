#pragma once
#include "resource.h"
#include "UIlib.h"
#include "sdk_util.h"

using namespace DuiLib;

class AnnotateDrawWindow:
	public CWindowWnd ,
	public INotifyUI
{
public:
	AnnotateDrawWindow(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pShareRender);
	~AnnotateDrawWindow();

	virtual LPCTSTR		GetWindowClassName() const { return _T("zSDKDemoUI"); }
	UINT                GetClassStyle()      const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; }
	virtual UINT		GetSkinRes()               { return IDXML_ANNOTATE_DRAW_WINDOW_UI; }
	UILIB_RESOURCETYPE  GetResourceType()    const { return UILIB_RESOURCE; }

	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND) {}

	virtual void		Notify( TNotifyUI& msg );
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	void MoveWindowPosTo(HWND hWnd);

private:
	CPaintManagerUI m_PaintManager;
	ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* m_customerAnnoObj;
	CButtonUI* m_btnCrookedLine;
	CButtonUI* m_btnAutoLineLine;
	CButtonUI* m_btnAutoRectangle;
	CButtonUI* m_btnAutoEllipseLine;
	CButtonUI* m_btnHighlightLine;
	CButtonUI* m_btnAutoArrow;
	CButtonUI* m_btnRectangleFill;
	CButtonUI* m_btnEllipseFill;
	CButtonUI* m_btnRhombus;
	CButtonUI* m_btnDoubleArrow;
	CButtonUI* m_btnAutoRectanglePiece;
	CButtonUI* m_btnAutoEllipsePiece;
};