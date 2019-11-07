/*!
* \file customized_share_render.h
* \brief ZOOM Custom Video Share Render Interface.
* 
*/
#ifndef _ZOOM_CUSTOMIZED_SHARE_RENDER_H_
#define _ZOOM_CUSTOMIZED_SHARE_RENDER_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum CustomizedViewShareMode
    \brief View mode of shared render.
    Here are more detailed structural descriptions.
*/ 
enum CustomizedViewShareMode 
{
	CSM_FULLFILL,///View the shared content in full screen mode.
	CSM_LETTER_BOX,///View the shared content in original size.
};

/// \brief Share render callback event.
///
class ICustomizedShareRenderEvent
{
public:
	/// \brief Callback event the moment received the shared content.
	virtual void onSharingContentStartRecving() = 0;

	/// \brief Callback event of changed sender or the sharing closes when receiving the shared content.
	/// \param userid The new sender or the sender of new sharing content.
	virtual void onSharingSourceUserIDNotification(unsigned int userid) = 0;

	/// \brief Callback event when the App receives the window messages from the sharer. Here are the list of the window messages.
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

/// \brief Share render interface.
///
class ICustomizedShareRender
{
public:
	/// \brief Set the share render callback event handler.
	/// \param pEvent A pointer to the ICustomizedShareRenderEvent that receives the share render event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(ICustomizedShareRenderEvent* pEvent) = 0;

	/// \brief Show the shared content received.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Show() = 0;

	/// \brief Hide the shared content received.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Hide() = 0;

	/// \brief View the sharing content from the specified user ID.
	/// \param userid Specify the user ID that is sending the sharing content.
	/// \remarks Call the IMeetingShareController::GetViewableShareSourceList to get the list of users who are sending the sharing. 
	///Handle the IMeetingShareCtrlEvent::onSharingStatus callback event to know who starts/stops the sharing.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetUserID(unsigned int userid) = 0;

	/// \brief Get the ID of the user who's sending the sharing.
	/// \return If the function succeeds, the return value is the user ID. 
	///Otherwise failed, the return value is ZERO(0).
	virtual unsigned int GetUserID() = 0;

	/// \brief Reset the dialog size to view the sharing content.
	/// \param rc Specify the size of the window. The coordinate of the upper left corner of the window corresponds to the client area of the parent window. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Resize(RECT rc) = 0;

	/// \brief Set the view mode of watching the sharing.
	/// \param mode Specify the view mode. For more details, see \link CustomizedViewShareMode \endlink enum. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetViewMode(CustomizedViewShareMode mode) = 0;

	/// \brief Get the window handle of showing sharing content.
	/// \return If the function succeeds, the return value is the window handle.
	///Otherwise failed, the return value is NULL.
	virtual HWND GetOwnerWnd() = 0;

	/// \brief Redraw the window of showing the sharing.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///Call the function when the parent window gets WM_MOVE windows message.
	/// \remarks Call the function to complete the redraw work once received the ICustomizedShareRenderEvent::onWindowMsgNotification() callback event and dealt with WM_MOVE. Otherwise there maybe problem with the view.
	virtual SDKError HandleWindowsMoveMsg() = 0;
	virtual ~ICustomizedShareRender(){}
};
END_ZOOM_SDK_NAMESPACE

#endif