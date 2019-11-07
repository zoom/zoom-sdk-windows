/*!
* \file embedded_browser_interface.h
* \brief Embedded Browser Interface.
* 
*/
#ifndef _EMBEDDED_BROWSER_INTERFACE_H_
#define _EMBEDDED_BROWSER_INTERFACE_H_
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/*! \enum NavigateError
    \brief Navigation error code.
    Here are more detailed structural descriptions.
*/
enum NavigateError
{
	NavigateError_Success = 0,///<Navigation successful.
	NavigateError_HttpStatus = 1,///<HTTP requests some related errors.
	NavigateError_InvalidUrl,///<INET_E_INVALID_URL (0x800C0002L or -2146697214)
	NavigateError_NoSession,///<INET_E_NO_SESSION (0x800C0003L or -2146697213)
	NavigateError_CannotConnect,///<INET_E_CANNOT_CONNECT (0x800C0004L or -2146697212)
	NavigateError_ResourceNotFound,///<INET_E_RESOURCE_NOT_FOUND (0x800C0005L or -2146697211)
	NavigateError_ObjNotFound,///<INET_E_OBJECT_NOT_FOUND (0x800C0006L or -2146697210)
	NavigateError_DataNotAvailable,///<INET_E_DATA_NOT_AVAILABLE (0x800C0007L or -2146697209)
	NavigateError_DownloadFailure,///<INET_E_DOWNLOAD_FAILURE (0x800C0008L or -2146697208)
	NavigateError_ConnectionTimeout,///<INET_E_CONNECTION_TIMEOUT (0x800C000BL or -2146697205)
	NavigateError_CannotLoadData,///<INET_E_CANNOT_LOAD_DATA (0x800C000FL or -2146697201)
	NavigateError_BrowserContainerError,///<Browser container error.
	NavigateError_Others,///<Some other issues.
};

/// \brief Embedded Browser Callback Event.
///
class IEmbeddedBrowserEvent
{
public:
	/// \brief The callback event will be triggered before the embedded browser starts to navigate.
	/// \param url The URL used by embedded browser in UTF8 encoding format.
	virtual void NotifyBeforeNavigate(const char* url) = 0;

	/// \brief The callback event will be triggered once the embedded browser receives all the information.
	/// \param url The URL used by embedded browser in UTF8 encoding format.
	virtual void NotifyDocumentComplete(const char* url) = 0;

	/// \brief The callback event will be triggered the moment an error occurs while the embedded browser visits the website.
	/// \param url The URL used by embedded browser in UTF8 encoding format.
	/// \param err Specifies the error information. For more details, see \link NavigateError \endlink enum.
	/// \param component_err Original error code.
	virtual void NotifyNavigateError(const char* url, NavigateError err, int component_err) = 0;
};

/// \brief Embedded Browser Interface.
///
class IEmbeddedBrowser
{
public:
	/// \brief Set embedded browser callback event handler.
	/// \param pEvent A pointer to the IEmbeddedBrowserEvent that receives Embedded Browser event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IEmbeddedBrowserEvent* pEvent) = 0;

	/// \brief Start to navigate.
	/// \param url The URL to browser or the full path of file to be visited, or the full path of file to be opened in UTF8 encoding format.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Navigate(const char* url) = 0;

	/// \brief Resize the embedded browser window to cover the client area of the parent window.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Resize() = 0;

	/// \brief Gets the URL matched to the present displayed content or get the full path of file, or the full path containing the file name.
	/// \return The URL matched to the present displayed content or the full path of file, or the full path containing the file name.
	virtual const char* GetURL() = 0;

	/// \brief Get the title of the present displayed content.
	/// \return The title of the present displayed content.
	///If the resource is a HTML web-page, the name is the title of the document. 
	///If the resource is a folder or file on the network or local computer, the name is the full path of folder or file in Universal Naming Convention (UNC) format. 
	virtual const char* GetTitle() = 0;

	/// \brief Navigate to the previous page by the web control if exists navigation history. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError GoBack() = 0;

	/// \brief Navigate to the next page by the web control if exists navigation history. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError GoForward() = 0;

	/// \brief Reloads the present document displayed on the web browser. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError DoRefresh() = 0;

	/// \brief Cancel all pending navigations or dynamic elements, such as background sounds and animations. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError DoStop() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif