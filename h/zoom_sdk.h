/*!
* \file zoom_sdk.h
* \brief  Zoom Windows SDK
* 
*/

#ifndef _ZOOM_SDK_H_
#define _ZOOM_SDK_H_
#include "zoom_sdk_def.h"
/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
extern "C"
{
	class IMeetingService;
	class IAuthService;
	class ISettingService;
	class ICalenderService;
	/// \brief Initialize Zoom SDK
	/// \param initParam Initialize Zoom SDK Parameter
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	SDK_API SDKError InitSDK(InitParam& initParam);

	/// \brief Create Meeting Service Interface
	/// \param ppMeetingService A pointer to a IMeetingService* that receives IMeetingService Object. 
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppMeetingService is not NULL
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	SDK_API SDKError CreateMeetingService(IMeetingService** ppMeetingService);

	/// \brief Destroy Meeting Service Interface
	/// \param pMeetingService A pointer to a IMeetingService to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	SDK_API SDKError DestroyMeetingService(IMeetingService* pMeetingService);

	/// \brief Create Authentication Service Interface
	/// \param ppAuthService A pointer to a IAuthService* that receives IAuthService Object. 
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppAuthService is not NULL
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	SDK_API SDKError CreateAuthService(IAuthService** ppAuthService);

	/// \brief Destroy Authentication Service Interface
	/// \param pAuthService A pointer to a IAuthService to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	SDK_API SDKError DestroyAuthService(IAuthService* pAuthService);

	/// \brief Create Setting Service Interface
	/// \param ppSettingService A pointer to a ISettingService* that receives ISettingService Object. 
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppSettingService is not NULL
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	SDK_API SDKError CreateSettingService(ISettingService** ppSettingService);

	/// \brief Destroy Setting Service Interface
	/// \param pSettingService A pointer to a ISettingService to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	SDK_API SDKError DestroySettingService(ISettingService* pSettingService);

	/// \brief Create Calender Service Interface
	/// \param ppCalenderService A pointer to a ICalenderService* that receives ICalenderService Object. 
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppCalenderService is not NULL
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	SDK_API SDKError CreateCalenderService(ICalenderService** ppCalenderService);

	/// \brief Destroy Calender Service Interface
	/// \param pCalenderService A pointer to a ICalenderService to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	SDK_API SDKError DestroyCalenderService(ICalenderService* pCalenderService);

	/// \brief Clean up Zoom SDK
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	SDK_API SDKError CleanUPSDK();
}

END_ZOOM_SDK_NAMESPACE
#endif