/*!
* \file zoom_sdk.h
* \brief ZOOM SDK.
* 
*/

#ifndef _ZOOM_SDK_H_
#define _ZOOM_SDK_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
extern "C"
{
	class IMeetingService;
	class IAuthService;
	class ISettingService;
	class ICalenderService;
	class IPreMeetingService;
	class INetworkConnectionHelper;
	
	/// \brief Initialize ZOOM SDK.
	/// \param [out] initParam Initialize the parameter of ZOOM SDK. For more details, see \link InitParam \endlink structure.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	SDK_API SDKError InitSDK(InitParam& initParam);


	SDK_API SDKError SwitchDomain(const wchar_t* new_domain, bool bForce);
	/// \brief Create meeting service interface.
	/// \param ppMeetingService An object pointer to the IMeetingService*. 
	/// \return If the function succeeds, the return value is SDKErr_Success while the value of ppMeetingService is not NULL.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	SDK_API SDKError CreateMeetingService(IMeetingService** ppMeetingService);

	/// \brief Destroy the specified meeting service Interface.
	/// \param pMeetingService A pointer to the IMeetingService to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	SDK_API SDKError DestroyMeetingService(IMeetingService* pMeetingService);

	/// \brief Create authentication service interface.
	/// \param ppAuthService An object pointer to the IAuthService*. 
	/// \return If the function succeeds, the return value is SDKErr_Success while the value of ppAuthService is not NULL.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	SDK_API SDKError CreateAuthService(IAuthService** ppAuthService);

	/// \brief Destroy the specified authentication service interface.
	/// \param pAuthService A pointer to the IAuthService to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	SDK_API SDKError DestroyAuthService(IAuthService* pAuthService);

	/// \brief Create setting service interface.
	/// \param ppSettingService An object pointer to the ISettingService*. 
	/// \return If the function succeeds, the return value is SDKErr_Success while the value of ppSettingService is not NULL.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	SDK_API SDKError CreateSettingService(ISettingService** ppSettingService);

	/// \brief Destroy the specified setting service interface.
	/// \param pSettingService A pointer to the ISettingService to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	SDK_API SDKError DestroySettingService(ISettingService* pSettingService);

	/// \brief Create calender service interface.
	/// \param ppCalenderService An object pointer to the ICalenderService*. 
	/// \return If the function succeeds, the return value is SDKErr_Success while the value of ppCalenderService is not NULL.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	SDK_API SDKError CreateCalenderService(ICalenderService** ppCalenderService);

	/// \brief Destroy the specified account service interface.
	/// \param pCalenderService A pointer to the ICalenderService to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	SDK_API SDKError DestroyCalenderService(ICalenderService* pCalenderService);

	/// \brief Create pre-meeting service interface.
	/// \param ppPreMeetingService An object pointer to the IPreMeetingService*. 
	/// \return If the function succeeds, the return value is SDKErr_Success while the value of ppCalenderService is not NULL.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	SDK_API SDKError CreatePreMeetingService(IPreMeetingService** ppPreMeetingService);

	/// \brief Destroy the specified pre-meeting service Interface
	/// \param pPreMeetingService A pointer to the IPreMeetingService to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	SDK_API SDKError DestroyPreMeetingService(IPreMeetingService* pPreMeetingService);

	/// \brief Create network connection helper interface.
	/// \param ppNetworkHelper An object pointer to the INetworkConnectionHelper*. 
	/// \return If the function succeeds, the return value is SDKErr_Success while the value of ppNetworkHelper is not NULL.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	SDK_API SDKError CreateNetworkConnectionHelper(INetworkConnectionHelper** ppNetworkHelper);

	/// \brief Destroy the specified network connection helper interface.
	/// \param pNetworkHelper A pointer to the INetworkConnectionHelper to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	SDK_API SDKError DestroyNetworkConnectionHelper(INetworkConnectionHelper* pNetworkHelper);

	/// \brief Clean up ZOOM SDK.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	SDK_API SDKError CleanUPSDK();

	/// \brief Get the version of ZOOM SDK.
	/// \return The version of ZOOM SDK.
	SDK_API const wchar_t* GetVersion();

	/// \brief Get ZOOM last error interface.
	/// \return If the function succeeds, the return value is an interface of ZOOM last error.
	///If the function fails or there is no error, the return value is NULL.
	/// For more information, see \link IZoomLastError  \endlink
	SDK_API const IZoomLastError* GetZoomLastError();
}

END_ZOOM_SDK_NAMESPACE
#endif