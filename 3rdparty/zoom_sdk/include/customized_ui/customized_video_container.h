/*!
* \file customized_video_container.h
* \brief ZOOM Custom Video Container Interface. 
* 
*/
#ifndef _ZOOM_CUSTOMIZED_VIDEO_CONTAINER_H_
#define _ZOOM_CUSTOMIZED_VIDEO_CONTAINER_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/*! \enum VideoRenderElementType
    \brief Type of the video render element.
    Here are more detailed structural descriptions.
*/ 
enum VideoRenderElementType
{
	VideoRenderElement_None,///<For initiation.
	VideoRenderElement_PRVIEW,///<Preview type, see \link IPreviewVideoRenderElement \endlink.
	VideoRenderElement_ACTIVE,///<Active type, see \link IActiveVideoRenderElement \endlink.
	VideoRenderElement_NORMAL,///<Normal type, see \link INormalVideoRenderElement \endlink.
};

/*! \enum VideoRenderDataType
    \brief Data type of the video render element.
    Here are more detailed structural descriptions.
*/ 
enum VideoRenderDataType
{
	VideoRenderData_None,///<For initiation.
	VideoRenderData_Video,///<Data type including the video data.
	VideoRenderData_Avatar,///<Data type without video data.
	VideoRenderData_ScreenName,///<Data type of screen name only.
};

/// \brief The base class for the video element interface.
///
class IVideoRenderElement
{
public:
	/// \brief Get the type of the video render element.
	/// \return If the function succeeds, the return value is the type of the render element. For more details, see \link VideoRenderElementType \endlink enum.
	///Otherwise failed, the return value is VideoRenderElement_None.
	virtual VideoRenderElementType GetType() = 0;

	/// \brief Get the area where the current render element is.
	/// \return A RECT structure. The value in the structure corresponding to the coordinate system is the client area of the video container.
	///The client coordinates corresponds to the client area of the upper-left corner of the parent window.
	virtual RECT     GetPos() = 0;

	/// \brief Specify a new display area of the current render element.
	/// \param pos Specify a new area through RECT structure. The value in the structure corresponding to the coordinate system is that of the client area of the video main window. 
	/// \return If the function succeeds, the return value is SDKERR_SUCCESS. Otherwise failed,see \link SDKError \endlink enum.
	virtual SDKError SetPos(RECT pos) = 0;

	/// \brief Show the render element.
	/// \return If the function succeeds, the return value is SDKERR_SUCCESS. Otherwise failed,see \link SDKError \endlink enum.
	virtual SDKError Show() = 0;

	/// \brief Hide the render element.
	/// \return If the function succeeds, the return value is SDKERR_SUCCESS. Otherwise failed,see \link SDKError \endlink enum.
	virtual SDKError Hide() = 0;

	/// \brief Get the user ID corresponding to the current render element.
	/// \return The ID of the user.
	virtual unsigned int GetCurrentRenderUserId() = 0;

	/// \brief Get the data type of the current render element. 
	/// \return The data type of the current render elements. For more details, see \link VideoRenderDataType \endlink enum.
	virtual VideoRenderDataType GetCurrentRenderDataType() = 0;

	/// \brief Set the visibility of the screen name on the current render element. 
	/// \param enable_show TRUE indicates to show the screen name.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError EnableShowScreenNameOnVideo(bool enable_show) = 0;
	virtual ~IVideoRenderElement(){}
};

/// \brief The interface to preview the video render element of the participant who joins the meeting before the host.
/// 
class IPreviewVideoRenderElement : public IVideoRenderElement
{
public:
	/// \brief Start previewing.
	/// \return If the function succeeds, the return value is SDKERR_SUCCESS. Otherwise failed,see \link SDKError \endlink enum.
	virtual SDKError Start() = 0;

	/// \brief Stop previewing.
	/// \return If the function succeeds, the return value is SDKERR_SUCCESS. Otherwise failed,see \link SDKError \endlink enum.
	virtual SDKError Stop() = 0;
	virtual ~IPreviewVideoRenderElement(){}
};

/// \brief The active video render element interface in the meeting.
/// 
class IActiveVideoRenderElement : public IVideoRenderElement
{
public:
	/// \brief Display the data of the current active user. 
	/// \return If the function succeeds, the return value is SDKERR_SUCCESS. Otherwise failed,see \link SDKError \endlink enum 
	virtual SDKError Start() = 0;

	/// \brief Hide the data of the current active user. 
	/// \return If the function succeeds, the return value is SDKERR_SUCCESS. Otherwise failed,see \link SDKError \endlink enum 
	virtual SDKError Stop() = 0;
	virtual ~IActiveVideoRenderElement(){}
};

/// \brief Normal video render element interface in the meeting. 
/// 
class INormalVideoRenderElement : public IVideoRenderElement
{
public:
	/// \brief Show the data of the specified user through normal render mode.
	/// \param userid Specify the user ID.
	virtual SDKError Subscribe(unsigned int userid) = 0;

	/// \brief Unsubscribe the data of the specified user.
	/// \param userid Specify the ID of user that you want to unsubscribe his data.
	/// \remarks Call Subscribe with the other ID if you want to view his data.
	///Call the function to stop receiving the data before calling the parent class Hide() function if you no longer want to see the data of the specified user.
	virtual SDKError Unsubscribe(unsigned int userid) = 0;
	virtual ~INormalVideoRenderElement(){}
};

/// \brief Callback event of custom video container. 
///
class ICustomizedVideoContainerEvent
{
public:
	/// \brief The callback will be triggered if the video render element corresponding to the user changes.
	/// \param pElement The video render element corresponding to the user who is changed.
	/// \param userid Specify the ID of new user.
	virtual void onRenderUserChanged(IVideoRenderElement* pElement, unsigned int userid) = 0;

	/// \brief The callback will be triggered if the video render element corresponding to data type changes.
	/// \param pElement The video render elements corresponding to data type that is changed. 
	/// \param dataType Specify a new render data type. For more details, see \link VideoRenderDataType \endlink enum. 
	virtual void onRenderDataTypeChanged(IVideoRenderElement* pElement, VideoRenderDataType dataType) = 0;

	/// \brief The callback will be triggered if the size of video container changes. 
	///The user should redeploy the video render elements displayed once received the callback event.
	/// \param wnd_client_rect Specify a new display area. The coordinate value of the structure is that of the parent window of the video container.
	virtual void onLayoutNotification(RECT wnd_client_rect) = 0;

	/// \brief The callback will be triggered before the video render element is destroyed.
	/// \param pElement Specify the video render element to be destroyed.
	/// \remarks The specified video render element will be destroyed once the function calls end. The user should complete the operations to the related video render element.
	virtual void onVideoRenderElementDestroyed(IVideoRenderElement* pElement) = 0;

	/// \brief The SDK will pass the window messages to users via the callback. Here are the messages.
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

/// \brief Video container interface.
///
class ICustomizedVideoContainer
{
public:
	/// \brief Set video container callback event handler.
	/// \param pEvent A pointer to the ICustomizedVideoContainerEvent that receives video container callback event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(ICustomizedVideoContainerEvent* pEvent) = 0;
	
	/// \brief Create a video render element.
	/// \param [out] ppElement Once the function succeeds, the parameter will store the pointer to the video render element.
	/// \param type_ Specify the type of the video render element to be created.
	/// \return If the function succeeds, the return value is SDKErr_Success, the return value of ppElement is not NULL.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CreateVideoElement(IVideoRenderElement** ppElement, VideoRenderElementType type_) = 0;

	/// \brief Destroy a video render element.
	/// \param ppElement Specify the video render element to be destroyed.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError DestroyVideoElement(IVideoRenderElement* ppElement) = 0;

	/// \brief Destroy all the video render element.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError DestroyAllVideoElement() = 0;

	/// \brief Show the video container.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Show() = 0;

	/// \brief Hide the video container.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Hide() = 0;

	/// \brief Resize the video container in the specified area.
	/// \param rc Specify a new display area. The coordinate value of the structure is that of the parent window of video container.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Resize(RECT rc) = 0;

	/// \brief Get the list of video render elements in the current container.
	/// \return If the function succeeds, the return value is the list that stores the video render element.
	///Otherwise failed, the return list is blank.
	virtual IList<IVideoRenderElement* >* GetVideoElementList() = 0;

	virtual ~ICustomizedVideoContainer(){}
};
END_ZOOM_SDK_NAMESPACE
#endif