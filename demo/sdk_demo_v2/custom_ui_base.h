#pragma once
#include "sdk_util.h"
#include <string>
#include <map>
#include "resource.h"
class IUIVideoContanier
{
public:
	virtual void onVideoContanierDestroy() = 0;
};

class IUIShareRender
{
public:
	virtual void onShareRenderDestroy() = 0;
};

class ICutomizedUIOwnWndInterface
{
protected:
	ICutomizedUIOwnWndInterface()
	{
		m_hOwnerHwnd = NULL;
	}

	virtual void onSize(RECT& rc) = 0;
	virtual void onDestroyed() = 0;
	virtual void onMove() = 0;

	static LRESULT _stdcall my_wnd_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (WM_SIZE == uMsg)
		{
			ICutomizedUIOwnWndInterface* cb_ = (ICutomizedUIOwnWndInterface*)::GetProp(hwnd, _T("resize_cb"));
			if (cb_)
			{
				RECT rc_;
				::GetClientRect(hwnd, &rc_);
				cb_->onSize(rc_);
			}
		}
		else if (WM_DESTROY == uMsg)
		{
			ICutomizedUIOwnWndInterface* cb_ = (ICutomizedUIOwnWndInterface*)::GetProp(hwnd, _T("resize_cb"));
			if (cb_)
			{
				cb_->onDestroyed();
			}
		}
		else if (WM_MOVE == uMsg)
		{
			ICutomizedUIOwnWndInterface* cb_ = (ICutomizedUIOwnWndInterface*)::GetProp(hwnd, _T("resize_cb"));
			if (cb_)
			{
				cb_->onMove();
			}
		}
		else if (WM_CLOSE == uMsg)
		{
			return TRUE;
		}
		else if (WM_GETMINMAXINFO == uMsg)
		{

			MINMAXINFO* p =(MINMAXINFO*)lParam;
			if (p)
			{
				p->ptMinTrackSize.x = 1000;
				p->ptMinTrackSize.y = 647;
			}

			return TRUE;
		}


		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

#define MAIN_WND_BK_COLOR (RGB(51, 88, 168))
	BOOL register_window_class(HINSTANCE hInstance)
	{
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= my_wnd_proc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_LOGO));
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= CreateSolidBrush(MAIN_WND_BK_COLOR);//(HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName = _T("zoom_sdk_demo_ui");
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON_LOGO));
		BOOL ret = 0 != RegisterClassEx(&wcex) ? TRUE : FALSE;;
		return ret;
	}

	void adjust_wnd_pos(int width, int height, HWND hwnd)
	{
		RECT rc;
		rc.left = 0;
		rc.right = width;
		rc.top = 0;
		rc.bottom = height;
		DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);
		DWORD dwExStyle = ::GetWindowLong(hwnd, GWL_EXSTYLE);
		::AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);
		int cx = rc.right - rc.left;
		int cy = rc.bottom - rc.top;
		int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

		::SetWindowPos(hwnd, NULL, (nScreenWidth-cx)/2, (nScreenHeight-cy)/2, cx, cy, SWP_NOZORDER|SWP_NOOWNERZORDER);
	}

	HWND create_owner_hwnd(ICutomizedUIOwnWndInterface* cb_, int width_, int height_)
	{
		DWORD dwStyle = WS_OVERLAPPEDWINDOW;
		dwStyle &= (~WS_MAXIMIZEBOX);
		//dwStyle &= (~WS_THICKFRAME);
		if (NULL == m_hOwnerHwnd || !::IsWindow(m_hOwnerHwnd))
		{
			HINSTANCE hmod = GetModuleHandle(NULL);
			register_window_class(hmod);
			m_hOwnerHwnd = CreateWindowEx( 
				0,     
				_T("zoom_sdk_demo_ui"),
				_T("zoom_sdk_demo_ui"), 
				dwStyle,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				GetDesktopWindow(),
				NULL,
				hmod,
				NULL 
				);
		}

		if (NULL == m_hOwnerHwnd)
		{
			DWORD err = GetLastError();
			return NULL;
		}

		::SetProp(m_hOwnerHwnd, _T("resize_cb"), cb_);
		::SetWindowLong(m_hOwnerHwnd, GWL_STYLE, dwStyle);
		adjust_wnd_pos(width_, height_, m_hOwnerHwnd);
		ShowWindow(m_hOwnerHwnd, SW_SHOW);

		return m_hOwnerHwnd;
	}

	void destroy_owner_wnd()
	{
		
		if (::IsWindow(m_hOwnerHwnd))
			::DestroyWindow(m_hOwnerHwnd);
		
		m_hOwnerHwnd = NULL;
	}

protected:
	HWND m_hOwnerHwnd;
};

class IWrapCustomizedVideoContainerEvent : public ZOOM_SDK_NAMESPACE::ICustomizedVideoContainerEvent
{
public:
	virtual void onVideoContainerWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	virtual void onRenderUserChanged(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement, unsigned int userid) = 0;
	virtual void onRenderDataTypeChanged(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement, ZOOM_SDK_NAMESPACE::VideoRenderDataType dataType) = 0;
	virtual void onLayoutNotification(RECT wnd_client_rect) = 0;
	virtual void onVideoRenderElementDestroyed(ZOOM_SDK_NAMESPACE::IVideoRenderElement* pElement) = 0;
private:
	void onWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		onVideoContainerWindowMsgNotification(uMsg, wParam, lParam);
	}
};
class IWrapCustomizedShareRenderEvent : public ZOOM_SDK_NAMESPACE::ICustomizedShareRenderEvent
{
public:
	virtual void onShareRenderWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	virtual void onSharingContentStartRecving() = 0;
	virtual void onSharingSourceUserIDNotification(unsigned int userid) = 0;
private:
	void onWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		onShareRenderWindowMsgNotification(uMsg, wParam, lParam);
	}
};
