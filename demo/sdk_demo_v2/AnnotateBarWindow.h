#pragma once
#include "resource.h"
#include "UIlib.h"
#include "sdk_util.h"

using namespace DuiLib;

class AnnotateFormatWindow;
class AnnotateDrawWindow;
class AnnotateStampWindow;
class AnnotateSpolightWindow;
class AnnotateClearWindow;

class AnnotateBarWindow:
	public CWindowWnd ,
	public INotifyUI
{
public:
	AnnotateBarWindow(ZOOM_SDK_NAMESPACE::ICustomizedShareRender* pShareRender);
	~AnnotateBarWindow();

	virtual LPCTSTR		GetWindowClassName() const { return _T("zSDKDemoUI"); }
	UINT                GetClassStyle()      const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS ; }
	virtual UINT		GetSkinRes()               { return IDXML_ANNOTATE_BAR_WINDOW_UI; }
	UILIB_RESOURCETYPE  GetResourceType()    const { return UILIB_RESOURCE; }

	virtual void		InitWindow();
	virtual void		OnFinalMessage(HWND) {}

	virtual void		Notify( TNotifyUI& msg );
	virtual LRESULT		HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	void MoveWindowPosTo(HWND hwOwner);
	void HideOwnedWindows();

private:
	void onClickClear(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pAnnoObj);
	void onClickSpotlight(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pAnnoObj);
	void onClickFormat(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pAnnoObj);
	void onClickDraw(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pAnnoObj);
	void onClickStamp(ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* pAnnoObj);
	void HideBrotherWindows(LPTSTR pszShowStar);

private:
	CPaintManagerUI m_PaintManager;
	CButtonUI* m_btnMouse;
	CButtonUI* m_btnSelect;
	CButtonUI* m_btnText;
	CButtonUI* m_btnDraw;
	CButtonUI* m_btnStamp;
	CButtonUI* m_btnSpotlight;
	CButtonUI* m_btnArrow;
	CButtonUI* m_btnEraser;
	CButtonUI* m_btnFormat;
	CButtonUI* m_btnUndo;
	CButtonUI* m_btnRedo;
	CButtonUI* m_btnClearAll;
	CButtonUI* m_btnSave;
	AnnotateFormatWindow* m_pAnnotateFormatWindow;
	AnnotateDrawWindow*   m_pAnnotateDrawWindow;
	AnnotateStampWindow*  m_pAnnotateStampWindow;
	AnnotateSpolightWindow* m_pAnnotateSpolightWindow;
	AnnotateClearWindow*  m_pAnnotateClearWindow;
	ZOOM_SDK_NAMESPACE::ICustomizedAnnotationController* m_customerAnnoCtrl;
	ZOOM_SDK_NAMESPACE::ICustomizedAnnotationObj* m_customerAnnoObj;
	ZOOM_SDK_NAMESPACE::ICustomizedShareRender* m_pShareRender;
};