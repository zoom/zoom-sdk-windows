/*!
* \file zoom_customized_ui.h
* \brief zoom customized ui interface
* 
*/
#ifndef _ZOOM_CUSTOMIZED_UI_H_
#define _ZOOM_CUSTOMIZED_UI_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
class ICustomizedUIMgr;
extern "C"
{
	/// \brief Create Customized UI Manager Interface
	/// \param ppCustomizedUIMgr A pointer to a ICustomizedUIMgr* that receives ICustomizedUIMgr Object. 
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppCustomizedUIMgr is not NULL
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	SDK_API SDKError CreateCustomizedUIMgr(ICustomizedUIMgr** ppCustomizedUIMgr);

	/// \brief Destroy Customized UI Manager Interface
	/// \param pCustomizedUIMgr A pointer to a ICustomizedUIMgr to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	SDK_API SDKError DestroyCustomizedUIMgr(ICustomizedUIMgr* pCustomizedUIMgr);
}

END_ZOOM_SDK_NAMESPACE
#endif