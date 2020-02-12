/*!
* \file network_connection_handler_interface.h
* \brief Network Connection Message Notification Handler.
* 
*/

#ifndef _NETWORK_CONNECTION_HANDLER_H_
#define _NETWORK_CONNECTION_HANDLER_H_

BEGIN_ZOOM_SDK_NAMESPACE

/*! \struct tagProxySettings
    \brief The proxy that the user want to use according to the net environment.
    Here are more detailed structural descriptions.
*/
typedef struct tagProxySettings
{
	const wchar_t* proxy;///<The proxy ip address and port that user want to use, should be organized like ip:port, such as '255.255.255.255:8080'. Use ';' to separate multi proxies.
	bool auto_detect;///<TRUE indicates automatic detection.
	tagProxySettings()
	{
		proxy = NULL;
		auto_detect = false;
	}
}ProxySettings;

/// \brief Proxy setting information callback interface.
///
class IProxySettingHandler
{
public:
	virtual ~IProxySettingHandler(){};
	/// \brief Get the address of the proxy host.
	/// Return the address of the proxy host.
	virtual const wchar_t* GetProxyHost() = 0;
	/// \brief Get the proxy port.
	///Return The value of the proxy port.
	virtual unsigned int GetProxyPort() = 0;
	/// \brief Get the description of the proxy.
	///Return The description of the proxy.
	virtual const wchar_t* GetProxyDescription() = 0;

	/// \brief Input the username and password when using the proxy.
	/// \param userName The username when using the proxy.
	/// \param psw The password when using the proxy.
	virtual void InputUsernamePassword(const wchar_t* userName, const wchar_t* psw) = 0;

	/// \brief Cancel the process to input the username and password of the proxy.
	virtual void Cancel() = 0;

};

/// \brief Verification of the SSL certificate callback interface.
///
class ISSLCertVerificationHandler
{
public:
	virtual ~ISSLCertVerificationHandler(){};

	/// \brief Get the value of whom the SSL certificate is issued to.
	virtual const wchar_t* GetCertIssuedTo() = 0;
	
	/// \brief Get the value that who issues the SSL certificate.
	virtual const wchar_t* GetCertIssuedBy() = 0;
	
	/// \brief Get the serial number of the SSL certificate.
	virtual const wchar_t* GetCertSerialNum() = 0;
	
	/// \brief get the SSL certificate's fingerprint
	virtual const wchar_t* GetCertFingerprint() = 0;

	/// \brief The SSL certificate is trusted.
	virtual void Trust() = 0;
	/// \brief The SSL certificate is not trusted.
	virtual void Cancel() = 0;

};

/// \brief The network connection handler callback event.
///
class INetworkConnectionHandler
{
public:
	/// \brief Notification callback of completing the proxy detection.
	virtual void onProxyDetectComplete() = 0;
	/// \brief The callback will be triggered if the proxy requests to input the username and password.
	/// \remarks Use the handler to configure the related information. For more details, see \link IProxySettingHandler \endlink. 
	///The handler will be destroyed once the function calls end.
	virtual void onProxySettingNotification(IProxySettingHandler* handler) = 0;
	
	/// \brief The callback will be triggered when the SSL is verified.
	/// \remarks Use the handler to check the related information. For more details, see \link ISSLCertVerificationHandler \endlink.
	///The handler will be destroyed once the function calls end.
	virtual void onSSLCertVerifyNotification(ISSLCertVerificationHandler* handler) = 0;
};

/// \brief The network connection helper interface.
///
class INetworkConnectionHelper
{
public:
	/// \brief Set the callback handler to receive the INetworkConnectionHandler.
	/// \param pNetworkHandler The SDK will invoke the handler once received this type of message. For more details, see \link INetworkConnectionHandler \endlink.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError RegisterNetworkConnectionHandler(INetworkConnectionHandler* pNetworkHandler) = 0;

	/// \brief Unregister the callback handler which is used to receive the INetworkConnectionHandler.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError UnRegisterNetworkConnectionHandler() = 0;

	/// \brief Set the proxy that the user want to use according to your net environment.
	/// \praam proxy_setting The proxy ip address and port that user want to use, should be organized like ip:port, such as '255.255.255.255:8080'. Using ';' to separate multi proxies.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError ConfigureProxy(ProxySettings& proxy_setting) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif