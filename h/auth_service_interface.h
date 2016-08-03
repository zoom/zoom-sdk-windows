/*!
* \file auth_service_interface.h
* \brief Authentication Service Interface
* 
*/
#ifndef _AUTH_SERVICE_INTERFACE_H_
#define _AUTH_SERVICE_INTERFACE_H_
#include "zoom_sdk_def.h"
/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE

/*! \enum AuthResult
    \brief SDK Authentication result.
    A more detailed struct description.
*/
enum AuthResult
{
	AUTHRET_SUCCESS,///< Auth Success 
	AUTHRET_KEYORSECRETEMPTY,///< Key or Secret is empty
	AUTHRET_KEYORSECRETWRONG,///< Key or Secret is wrong
	AUTHRET_ACCOUNTNOTSUPPORT,///< Client Account does not support
	AUTHRET_ACCOUNTNOTENABLESDK,///< Client account does not enable SDK
	AUTHRET_UNKNOWN,///< Auth Unknown error
};

/*! \struct tagAuthParam
    \brief SDK Authentication Parameter.
    A more detailed struct description.
*/
typedef struct tagAuthParam
{
	const wchar_t* appKey;///< APP Key string
	const wchar_t* appSecret;///< APP Secret string
	tagAuthParam()
	{
		appKey = NULL;
		appSecret = NULL;
	}
}AuthParam;

/// \brief Authentication Service Callback Event
///
class IAuthServiceEvent
{
public:
	/// \brief Authentication Result callback
	/// \param ret Authentication Result value. 
	virtual void onAuthenticationReturn(AuthResult ret) = 0;
};

/// \brief Authentication Service Interface
///
class IAuthService
{
public:
	/// \brief Set authentication service callback event
	/// \param pEvent A pointer to a IAuthServiceEvent* that receives meeting event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IAuthServiceEvent* pEvent) = 0;

	/// \brief Authentication sdk
	/// \param authParam The parameter to be used for authentication sdk, refer to AuthParam. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SDKAuth(AuthParam& authParam) = 0;

	/// \brief Get authentication status
	/// \return the return value is  authentication status.To get extended error information, refer to AuthResult enum
	virtual AuthResult GetAuthResult() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif
