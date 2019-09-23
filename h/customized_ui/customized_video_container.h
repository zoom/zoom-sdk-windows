/*!
* \file customized_video_container.h
* \brief zoom customized video container interface
* 
*/
#ifndef _ZOOM_CUSTOMIZED_VIDEO_CONTAINER_H_
#define _ZOOM_CUSTOMIZED_VIDEO_CONTAINER_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/*! \enum VideoRenderElementType
    \brief Type of the video render element.
    A more detailed struct description.
*/ 
enum VideoRenderElementType
{
	VideoRenderElement_None, /// none
	VideoRenderElement_PRVIEW, /// for IPreviewVideoRenderElement
	VideoRenderElement_ACTIVE, /// for IActiveVideoRenderElement
	VideoRenderElement_NORMAL, /// for INormalVideoRenderElement
};

/*! \enum VideoRenderDataType
    \brief Data type of the video render element.
    A more detailed struct description.
*/ 
enum VideoRenderDataType
{
	VideoRenderData_None,/// none
	VideoRenderData_Video,/// video data
	VideoRenderData_Avatar,/// avatar (no video data)
	VideoRenderData_ScreenName,/// screen name (no video data and no avatar)
};

/// \brief base class of the video element interface
///
class IVideoRenderElement
{
public:
	/// \brief Get the type of the video render.
	/// \return If the function succeeds, the return value is the render type.refer VideoRenderElementType
	///If the function fails, the return value is VideoRenderElement_None.
	virtual VideoRenderElementType GetType() = 0;

	/// \brief Retrieves the coordinates of a video render element's client area.
	/// \return a RECT structure that receives the client coordinates.
	/// client coordinates are relative to the upper-left corner of a video container's client area
	virtual RECT     GetPos() = 0;

	/// \brief Changes the position of a video render element's client area.
	/// \param pos specify the position of a video render element's client area.
	virtual SDKError SetPos(RECT pos) = 0;

	/// \brief Show video element
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Show() = 0;

	/// \brief Hide video element
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Hide() = 0;

	/// \brief Get the user id of the video element.
	/// \return The user id specify which user was viewing.
	virtual unsigned int GetCurrentRenderUserId() = 0;

	/// \brief Get the render data type of the video element.
	/// \return The data type of the video element
	virtual VideoRenderDataType GetCurrentRenderDataType() = 0;

	/// \brief Enable show screen name on video or not.
	/// \param enable_show enable or not.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError EnableShowScreenNameOnVideo(bool enable_show) = 0;
	virtual ~IVideoRenderElement(){}
};

/// \brief preview video element interface(pre-meeting)
/// 
class IPreviewVideoRenderElement : public IVideoRenderElement
{
public:
	/// \brief Start to preview
	virtual SDKError Start() = 0;

	/// \brief Stop to preview
	virtual SDKError Stop() = 0;
	virtual ~IPreviewVideoRenderElement(){}
};

/// \brief active video element interface(in-meeting)
/// 
class IActiveVideoRenderElement : public IVideoRenderElement
{
public:
	/// \brief Start to view the active user's video/avatar/screen name data
	virtual SDKError Start() = 0;

	/// \brief Stop to view the active user's video/avatar/screen name data
	virtual SDKError Stop() = 0;
	virtual ~IActiveVideoRenderElement(){}
};

/// \brief normal video element interface(in-meeting)
/// 
class INormalVideoRenderElement : public IVideoRenderElement
{
public:
	/// \brief Subscribe the user's video/avatar/screen name data
	/// \param userid specify which user you want to view
	virtual SDKError Subscribe(unsigned int userid) = 0;

	/// \brief Unsubscribe the user's video/avatar/screen name data
	/// \param userid specify which user you want to unsubscribe
	/// if you want to switch to other user, just call Subscribe with the other user id
	/// if you want to recycle the video element, please call this API before the Hide API
	virtual SDKError Unsubscribe(unsigned int userid) = 0;
	virtual ~INormalVideoRenderElement(){}
};

/// \brief Video container callback event
///
class ICustomizedVideoContainerEvent
{
public:
	/// \brief Notifies the app about user id change of the video render element
	/// \param pElement specify which render element's user id changed  
	/// \param userid the new user id of the video render element  
	virtual void onRenderUserChanged(IVideoRenderElement* pElement, unsigned int userid) = 0;

	/// \brief Notifies the app about render data type change of the video render element
	/// \param pElement specify which render element's data type changed  
	/// \param dataType the new render data type of the video render element 
	virtual void onRenderDataTypeChanged(IVideoRenderElement* pElement, VideoRenderDataType dataType) = 0;

	/// \brief Notifies the app about size change of the video container
	/// when receive this message, need to layout all video elements of the video container
	/// \param rc the new video container position that contains the client coordinates of the rectangle, relative to the upper-left corner of a parent window's client area. 
	virtual void onLayoutNotification(RECT wnd_client_rect) = 0;

	/// \brief Notifies the app about the video render element destroyed message
	/// \param pElement specify which render element will be destroyed  
	virtual void onVideoRenderElementDestroyed(IVideoRenderElement* pElement) = 0;

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

/// \brief Video container interface
///
class ICustomizedVideoContainer
{
public:
	/// \brief Set video container callback event
	/// \param pEvent A pointer to a ICustomizedVideoContainerEvent* that receives video container event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(ICustomizedVideoContainerEvent* pEvent) = 0;
	
	/// \brief Create video render element Interface
	/// \param ppElement A pointer to a IVideoRenderElement* that receives IVideoRenderElement Object. 
	/// \param type_ type of the IVideoRenderElement
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppEmbeddedBrowser is not NULL
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError CreateVideoElement(IVideoRenderElement** ppElement, VideoRenderElementType type_) = 0;

	/// \brief Destroy video render element Interface
	/// \param ppElement A pointer to a IVideoRenderElement to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DestroyVideoElement(IVideoRenderElement* ppElement) = 0;

	/// \brief Destroy all video render elements
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DestroyAllVideoElement() = 0;

	/// \brief Show video container
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Show() = 0;

	/// \brief Hide video container
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Hide() = 0;

	/// \brief Resize the video container
	/// \param rc that contains the client coordinates of the rectangle, relative to the upper-left corner of a parent window's client area. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Resize(RECT rc) = 0;

	/// \brief get the video element list of the video container.
	/// \return If the function succeeds, the return value is the video element list.
	///If the function fails, the return value is NULL.
	virtual IList<IVideoRenderElement* >* GetVideoElementList() = 0;

	virtual ~ICustomizedVideoContainer(){}
};
END_ZOOM_SDK_NAMESPACE
#endif