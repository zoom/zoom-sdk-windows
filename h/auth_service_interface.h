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
	AUTHRET_SERVICE_BUSY,///< service busy
	AUTHRET_NONE,///< Initial status
};

/*! \enum LOGINSTATUS
    \brief Login status.
    A more detailed struct description.
*/
enum LOGINSTATUS
{
	LOGIN_IDLE,///< Not login
	LOGIN_PROCESSING,///< Login in processing
	LOGIN_SUCCESS,///< Login success
	LOGIN_FAILED,///< Login failed
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

/*! \enum LoginType
\brief type of user login.
A more detailed struct description.
*/
enum LoginType
{
	LoginType_Unknown,
	LoginType_Email,///<Login with work email
	LoginType_SSO,///<Login with SSO token
};

typedef struct tagLoginParam4Email
{
	const wchar_t* userName;///< Account name. email or something else
	const wchar_t* password;///< Account password
	bool bRememberMe;
}LoginParam4Email;

typedef struct tagLoginParam4SSO
{
	const wchar_t* ssoToken;///< Account SSO token when Login
	bool bRememberMe;
}LoginParam4SSO;

/*! \struct tagLoginParam
    \brief Account login Parameter.
    A more detailed struct description.
*/
typedef struct tagLoginParam
{
	LoginType loginType;
	union
	{
		LoginParam4Email emailLogin;
		LoginParam4SSO ssoLogin;
	}ut;

	tagLoginParam()
	{
		loginType = LoginType_Email;
		memset(&ut, 0, sizeof(ut));
		
	}
}LoginParam;

/// \brief Account information Interface
///
class IAccountInfo
{
public:
	/// \brief Get account display name
	/// \return The return value is account display name.
	virtual const wchar_t* GetDisplayName() = 0;

	/// \brief Get login type
	/// \return The return value is account login type.
	virtual LoginType GetLoginType() = 0;
	virtual ~IAccountInfo(){};
};

/// \brief Authentication Service Callback Event
///
class IAuthServiceEvent
{
public:
	/// \brief Authentication Result callback
	/// \param ret Authentication Result value. 
	virtual void onAuthenticationReturn(AuthResult ret) = 0;

	/// \brief Login Result callback
	/// \param ret Login status. refer LOGINSTATUS.
	/// \param pAccountInfo if the ret is LOGINRET_SUCCESS, it is not NULL value, otherwise is NULL
	virtual void onLoginRet(LOGINSTATUS ret, IAccountInfo* pAccountInfo) = 0;
	
	/// \brief Logout Result callback
	virtual void onLogout() = 0;

	/// \brief Zoom identity expired, please re-login or generate new zoom access token via REST api
	virtual void onZoomIdentityExpired() = 0;
};

/// \brief Authentication Service Interface
///
class IAuthService
{
public:
	/// \brief Set authentication service callback event
	/// \param pEvent A pointer to a IAuthServiceEvent* that receives authentication event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IAuthServiceEvent* pEvent) = 0;

	/// \brief Authentication sdk
	/// \param authParam The parameter to be used for authentication sdk, refer to AuthParam. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SDKAuth(AuthParam& authParam) = 0;

	/// \brief Get authentication status
	/// \return The return value is  authentication status.To get extended error information, refer to AuthResult enum
	virtual AuthResult GetAuthResult() = 0;

	/// \brief Get SDK identity
	/// \return the SDK identity.
	virtual const wchar_t* GetSDKIdentity() = 0;

	// \brief Account login
	/// \param param The parameter to be used for account login, refer to LoginParam. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	///you need to call this APIs after onAuthenticationReturn return success status.
	virtual SDKError Login(LoginParam& param) = 0;
	
	// \brief Account logout
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError LogOut() = 0;

	// \brief Get login account information.
	/// \return If you has login your account success, the return value is the account information, otherwise is NULL.
	virtual IAccountInfo* GetAccountInfo() = 0;

	/// \brief Get login status
	/// \return The return value is login status.To get extended error information, refer to LOGINSTATUS enum
	virtual LOGINSTATUS GetLoginStatus() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif
