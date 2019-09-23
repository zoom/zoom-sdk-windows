/*!
* \file ui_hook_interface.h
* \brief UI Hook Interface
* 
*/
#ifndef _UI_HOOK_INTERFACE_H_
#define _UI_HOOK_INTERFACE_H_

#include "zoom_sdk_def.h"
/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
enum UIHOOKHWNDTYPE
{
	UIHOOKWNDTYPE_USERDEFIEND,
	UIHOOKWNDTYPE_MAINWND,
	UIHOOKWNDTYPE_BOTTOMTOOLBAR,
};
/// \brief UI Hooker Callback Event
///
class IUIHookerEvent
{
public:
	/// \brief UI Action callback. this call back will be in work thread, not in main thread.
	/// \param type Windows type.refer to UIHOOKHWNDTYPE
	/// \param msg Contains message information
	virtual void onUIActionNotify(UIHOOKHWNDTYPE type, MSG msg) = 0;
};
/// \brief Embedded Browser Interface
///
class IUIHooker
{
public:
	/// \brief Set UI Hooker callback event
	/// \param pEvent A pointer to a IUIHookerEvent* that receives UI hooker event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IUIHookerEvent* pEvent) = 0;

	/// \brief Add or remove monitor windows message
	/// \param wndmsgid Windows message id, such as WM_CREATE.
	/// \bAdd Add or remove
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError MonitorWndMessage(unsigned int wndmsgid, bool bAdd = true) = 0;

	/// \brief Add or remove monitor windows
	/// \param classname Class name of monitor window
	/// \bAdd Add or remove
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError MonitorWnd(const wchar_t* classname, bool bAdd = true) = 0;

	/// \brief Start monitor
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Start() = 0;
	
	/// \brief Stop monitor
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Stop() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif