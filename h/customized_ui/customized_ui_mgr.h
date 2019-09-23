/*!
* \file customized_ui_mgr.h
* \brief zoom customized ui mgr interface
* 
*/
#ifndef _ZOOM_CUSTOMIZED_UI_MGR_H_
#define _ZOOM_CUSTOMIZED_UI_MGR_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
class ICustomizedVideoContainer;
class ICustomizedShareRender;

/// \brief Customized UI manager callback event
///
class ICustomizedUIMgrEvent
{
public:
	/// \brief Notifies the app about the video container destroyed message
	/// \param pContainer specify which video container will be destroyed  
	virtual void onVideoContainerDestroyed(ICustomizedVideoContainer* pContainer) = 0;

	/// \brief Notifies the app about the share render destroyed message
	/// \param pContainer specify which share render will be destroyed 
	virtual void onShareRenderDestroyed(ICustomizedShareRender* pRender) = 0;
};


/// \brief Customized UI manager interface
///
class ICustomizedUIMgr
{
public:
	/// \brief Check license
	/// \return If has license, the return value is SDKErr_Success.
	///If no license, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError HasLicense() = 0;

	/// \brief Set customized ui manager callback event
	/// \param pEvent A pointer to a ICustomizedUIMgrEvent* that receives customized ui manager event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(ICustomizedUIMgrEvent* pEvent) = 0;

	/// \brief Create video container Interface
	/// \param ppContainer A pointer to a ICustomizedVideoContainer* that receives ICustomizedVideoContainer Object. 
	/// \param hParentWnd specify the parent window of the video container.
	/// \param rc specify the position of a video render element's client area.
	/// client coordinates are relative to the upper-left corner of a parent window's client area
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppEmbeddedBrowser is not NULL
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError CreateVideoContainer(ICustomizedVideoContainer** ppContainer, HWND hParentWnd, RECT rc) = 0;

	/// \brief Destroy video container Interface
	/// \param pContainer A pointer to a ICustomizedVideoContainer to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DestroyVideoContainer(ICustomizedVideoContainer* pContainer) = 0;

	/// \brief Destroy all video containers
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DestroyAllVideoContainer() = 0;

	/// \brief Create share render Interface
	/// \param ppRender A pointer to a ICustomizedShareRender* that receives ICustomizedShareRender Object. 
	/// \param hParentWnd specify the parent window of the share render.
	/// \param rc specify the position of a share render's client area.
	/// client coordinates are relative to the upper-left corner of a parent window's client area
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppEmbeddedBrowser is not NULL
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError CreateShareRender(ICustomizedShareRender** ppRender, HWND hParentWnd, RECT rc) = 0;

	/// \brief Destroy share render Interface
	/// \param pRender A pointer to a ICustomizedShareRender to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DestroyShareRender(ICustomizedShareRender* pRender) = 0;

	/// \brief Destroy all share render
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DestroyAllShareRender() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif