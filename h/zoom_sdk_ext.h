/*!
* \file zoom_sdk_ext.h
* \brief  Zoom Windows SDK
* 
*/

#ifndef _ZOOM_SDK_EXT_H_
#define _ZOOM_SDK_EXT_H_
#include "zoom_sdk_def.h"
/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
extern "C"
{
	class IEmbeddedBrowser;
	class IUIHooker;
	/// \brief Create Embedded Browser Interface
	/// \param ppEmbeddedBrowser A pointer to a IEmbeddedBrowser* that receives IEmbeddedBrowser Object. 
	/// \param hwnd parent window of the embedded browser. 
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppEmbeddedBrowser is not NULL
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	SDK_API SDKError CreateEmbeddedBrowser(IEmbeddedBrowser** ppEmbeddedBrowser, HWND hwnd);

	/// \brief Destroy Embedded Browser Interface
	/// \param pEmbeddedBrowser A pointer to a IEmbeddedBrowser to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	SDK_API SDKError DestroyEmbeddedBrowser(IEmbeddedBrowser* pEmbeddedBrowser);

	/// \brief Retrieve UI Hooker Interface
	/// \param ppUIHooker A pointer to a IUIHooker* that receives IUIHooker Object. 
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppEmbeddedBrowser is not NULL
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	SDK_API SDKError RetrieveUIHooker(IUIHooker** ppUIHooker);
}

END_ZOOM_SDK_NAMESPACE
#endif