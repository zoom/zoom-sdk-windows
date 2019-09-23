/*!
* \file customized_video_container.h
* \brief zoom customized video container interface
* 
*/
#ifndef _ZOOM_CUSTOMIZED_SHARE_RENDER_H_
#define _ZOOM_CUSTOMIZED_SHARE_RENDER_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum CustomizedViewShareMode
    \brief View mode of the share render.
    A more detailed struct description.
*/ 
enum CustomizedViewShareMode 
{
	CSM_FULLFILL, /// Stretch the sharing content to the whole window size
	CSM_LETTER_BOX /// Display the sharing content in the original ratio
};

/// \brief Share render callback event
///
class ICustomizedShareRenderEvent
{
public:
	/// \brief Notifies the app about sharing content start to receiving
	virtual void onSharingContentStartRecving() = 0;

	/// \brief Notifies the app about user id change of the share render
	/// \param userid the user id of the sharing sender 
	virtual void onSharingSourceUserIDNotification(unsigned int userid) = 0;

	/// \brief Passes message information to the app, message list as follow, 
	///WM_MOUSEMOVE
	///WM_MOUSEENTER
	///WM_MOUSELEAVE
	///WM_LBUTTONDOWN
	///WM_LBUTTONUP
	///WM_RBUTTONUP
	///WM_LBUTTONDBLCLK
	///WM_KEYDOWN
	virtual void onWindowMsgNotification(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};

/// \brief Share render interface
///
class ICustomizedShareRender
{
public:
	/// \brief Set Share render callback event
	/// \param pEvent A pointer to a ICustomizedShareRenderEvent* that receives share render event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(ICustomizedShareRenderEvent* pEvent) = 0;

	/// \brief Show share render
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Show() = 0;

	/// \brief Hide share render
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Hide() = 0;

	/// \brief Set the user id of who's sharing you want to view
	/// \param userid the user id of the sharing sender
	/// 1.you can call IMeetingShareController.GetViewableShareSourceList to fetch the send sharing user list
	/// 2.handle the IMeetingShareCtrlEvent.onSharingStatus callback event to know who start/stop sharing
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetUserID(unsigned int userid) = 0;

	/// \brief Get the user id of who's sharing is viewing.
	/// \return If the function succeeds, the return value is the user id.
	///If the function fails, the return value is 0.
	virtual unsigned int GetUserID() = 0;

	/// \brief Resize the share render
	/// \param rc that contains the client coordinates of the rectangle, relative to the upper-left corner of a parent window's client area. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Resize(RECT rc) = 0;

	/// \brief Set view mode of the share render
	/// \param mode refer the details of CustomizedViewShareMode 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetViewMode(CustomizedViewShareMode mode) = 0;

	/// \brief Get the handle of the render window.
	/// \return If the function succeeds, the return value is the handle of the window.
	///If the function fails, the return value is NULL.
	virtual HWND GetOwnerWnd() = 0;

	/// \brief Move the share render
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	///need to call this api when parent window got WM_MOVE windows message.
	virtual SDKError HandleWindowsMoveMsg() = 0;
	virtual ~ICustomizedShareRender(){}
};
END_ZOOM_SDK_NAMESPACE

#endif