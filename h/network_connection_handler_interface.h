/*!
* \file network_connection_handler_interface.h
* \brief  network connection message notification handler
* 
*/

#ifndef _NETWORK_CONNECTION_HANDLER_H_
#define _NETWORK_CONNECTION_HANDLER_H_
/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/// \brief Proxy setting information callback interface
///
class IProxySettingHandler
{
public:
	virtual ~IProxySettingHandler(){};
	/// \brief Return value of the Proxy-Host
	virtual const wchar_t* GetProxyHost() = 0;
	/// \brief Return value of the Proxy-Port
	virtual unsigned int GetProxyPort() = 0;
	/// \brief Return value of the Proxy-Description
	virtual const wchar_t* GetProxyDescription() = 0;

	/// \brief Input the username and password of this proxy for continue connect.
	virtual void InputUsernamePassword(const wchar_t* userName, const wchar_t* psw) = 0;

	/// \brief cancel to input the username and password of this proxy
	virtual void Cancel() = 0;

};

/// \brief the SSL Certificate Verification callback interface
///
class ISSLCertVerificationHandler
{
public:
	virtual ~ISSLCertVerificationHandler(){};

	// \brief Return the value of SSL certificate is issued to
	virtual const wchar_t* GetCertIssuedTo() = 0;
	// \brief Return the value of SSL certificate is issued by
	virtual const wchar_t* GetCertIssuedBy() = 0;
	// \brief Return the SSL certificate's serial number
	virtual const wchar_t* GetCertSerialNum() = 0;
	/// \brief Return the ssl certificate's fingerprint
	virtual const wchar_t* GetCertFingerprint() = 0;

	// \brief trust this SSL certificate
	virtual void Trust() = 0;
	// \brief don't trust this SSL certificate
	virtual void Cancel() = 0;

};

/// \brief the network connection handler callback event
///
class INetworkConnectionHandler
{
public:
	/// \brief must prompt the user for their username and password of the proxy,when receive this message
	virtual void onProxySettingNotification(IProxySettingHandler* handler) = 0;
	/// \brief must prompt the user for the SSL Certificate Verification,when receive this message
	virtual void onSSLCertVerifyNotification(ISSLCertVerificationHandler* handler) = 0;
};

/// \brief the network connection helper interface
///
class INetworkConnectionHelper
{
public:
	/// \brief Register a handler for a network connection message notification.
	/// \param pNetworkHandler Handler which will be invoked for when this message type is received.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError RegisterNetworkConnectionHandler(INetworkConnectionHandler* pNetworkHandler) = 0;

	/// \brief Unregister a handler for a network connection message notification.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError UnRegisterNetworkConnectionHandler() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif