/*!
* \file auth_service_interface.h
* \brief Authentication Service Interface
* 
*/
#ifndef _AUTH_SERVICE_INTERFACE_H_
#define _AUTH_SERVICE_INTERFACE_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/*! \enum AuthResult
    \brief SDK Authentication Result.
    Here are more detailed structural descriptions.
*/
enum AuthResult
{
	AUTHRET_SUCCESS,///<Authentication is successful.
	AUTHRET_KEYORSECRETEMPTY,///<The key or secret to authenticate is empty.
	AUTHRET_KEYORSECRETWRONG,///<The key or secret to authenticate is wrong.
	AUTHRET_ACCOUNTNOTSUPPORT,///<The user account does not support.
	AUTHRET_ACCOUNTNOTENABLESDK,///<The user account is not enabled for SDK.
	AUTHRET_UNKNOWN,///<Unknown error.
	AUTHRET_SERVICE_BUSY,///<Service is busy.
	AUTHRET_NONE,///<Initial status.
	AUTHRET_OVERTIME,///<Time out.
	AUTHRET_NETWORKISSUE,///<Network issues.
};

/*! \enum LOGINSTATUS
    \brief Login status.
    Here are more detailed structural descriptions.
*/
enum LOGINSTATUS
{
	LOGIN_IDLE,///<Unlogged in.
	LOGIN_PROCESSING,///<In process of login.
	LOGIN_SUCCESS,///<Login successful.
	LOGIN_FAILED,///<Login failed.
};

/*! \struct tagAuthParam
    \brief SDK Authentication parameter.
    Here are more detailed structural descriptions.
*/
typedef struct tagAuthParam
{
	const wchar_t* appKey;///<APP Key string.
	const wchar_t* appSecret;///<APP Secret string.
	tagAuthParam()
	{
		appKey = NULL;
		appSecret = NULL;
	}
}AuthParam;

/*! \enum LoginType
	\brief User login type.
	Here are more detailed structural descriptions.
*/
enum LoginType
{
	LoginType_Unknown,///<Unknown type.
	LoginType_Email,///<Login with work mailbox.
	LoginType_SSO,///<Login with SSO token.
};

/*! \struct tagLoginParam4Email
    \brief SDK parameter for login via email.
    Here are more detailed structural descriptions.
*/
typedef struct tagLoginParam4Email
{
	const wchar_t* userName;///<Username. It is usually working mailbox or other mailbox.
	const wchar_t* password;///<Account password.
	bool bRememberMe;///<True indicates to save the information for next login.
}LoginParam4Email;

/*! \struct tagLoginParam4SSO
    \brief SDK parameter for login via SSO.
    Here are more detailed structural descriptions.
*/
typedef struct tagLoginParam4SSO
{
	const wchar_t* ssoToken;///<Account SSO token when logging.
	bool bRememberMe; ///<True indicates to save the information for next login.
}LoginParam4SSO;

/*! \struct tagLoginParam
    \brief Account login parameter.
    Here are more detailed structural descriptions.
*/
typedef struct tagLoginParam
{
	LoginType loginType; ///<Type of login.
	union
	{
		LoginParam4Email emailLogin;///<Login with mailbox.
		LoginParam4SSO ssoLogin;///<Login with SSO token.
	}ut;

	tagLoginParam()
	{
		loginType = LoginType_Email;
		memset(&ut, 0, sizeof(ut));
		
	}
}LoginParam;

/// \brief Account information interface.
///
class IAccountInfo
{
public:
	/// \brief Get the screen name of user.
	/// \return The return value is the displayed username. If there is no screen name of user, the return value is a string of length ZERO(0).
	virtual const wchar_t* GetDisplayName() = 0;

	/// \brief Get login type.
	/// \return The return value is the account login type. For more details, see \link LoginType \endlink enum.
	virtual LoginType GetLoginType() = 0;
	virtual ~IAccountInfo(){};
};

/// \brief Authentication service callback event.
///
class IAuthServiceEvent
{
public:
	/// \brief Authentication result callback.
	/// \param ret Authentication result value.  For more details, see \link AuthResult \endlink enum.
	virtual void onAuthenticationReturn(AuthResult ret) = 0;

	/// \brief Callback of login result.
	/// \param ret Login status. see \link LOGINSTATUS \endlink enum.
	/// \param pAccountInfo Valid when the ret is LOGINRET_SUCCESS. Otherwise NULL.
	virtual void onLoginRet(LOGINSTATUS ret, IAccountInfo* pAccountInfo) = 0;
	
	/// \brief Logout result callback.
	virtual void onLogout() = 0;

	/// \brief Zoom identity has expired, please re-login or generate a new zoom access token via REST Api.
	virtual void onZoomIdentityExpired() = 0;
};

class IDirectShareServiceHelper;
class IOutlookPluginIntegrationHelper;
/// \brief Authentication Service Interface.
///
class IAuthService
{
public:
	/// \brief Set the authentication service callback event handler.
	/// \param pEvent A pointer to receive authentication event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IAuthServiceEvent* pEvent) = 0;

	/// \brief SDK Authentication.
	/// \param authParam The parameter to be used for authentication SDK, see \link AuthParam \endlink structure. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SDKAuth(AuthParam& authParam) = 0;

	/// \brief Get authentication status.
	/// \return The return value is authentication status. To get extended error information, see \link AuthResult \endlink enum.
	virtual AuthResult GetAuthResult() = 0;

	/// \brief Get SDK identity.
	/// \return The SDK identity.
	virtual const wchar_t* GetSDKIdentity() = 0;

	/// \brief Account login.
	/// \param param For the parameter to be used for account login, see \link LoginParam \endlink structure. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///You need to call this APIs after IAuthServiceEvent::onAuthenticationReturn() return SDKErr_Success.
	virtual SDKError Login(LoginParam& param) = 0;
	
	/// \brief Account logout.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError LogOut() = 0;

	/// \brief Get login account information.
	/// \return If you has logged in your account successfully, the return value is a pointer to IAccountInfo, otherwise is NULL.
	virtual IAccountInfo* GetAccountInfo() = 0;

	/// \brief Get login status.
	/// \return The return value is login status. To get extended error information, see \link LOGINSTATUS \endlink enum.
	virtual LOGINSTATUS GetLoginStatus() = 0;

	/// \brief Get Outlook plugin integration helper interface. 
	/// \return If you logged in your account successfully, the return value is the object pointer to IOutlookPluginIntegrationHelper. Otherwise is NULL.
	virtual IOutlookPluginIntegrationHelper* GetOutlookPluginHeler() = 0;

	/// \brief Get direct share service helper interface. 
	/// \return If you logged in your account successfully, the return value is the object pointer IDirectShareServiceHelper. Otherwise is NULL.
	virtual IDirectShareServiceHelper* GetDirectShareServiceHeler() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif
