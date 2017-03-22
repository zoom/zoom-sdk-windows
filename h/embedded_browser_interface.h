/*!
* \file embedded_browser_interface.h
* \brief Embedded Browser Interface
* 
*/
#ifndef _EMBEDDED_BROWSER_INTERFACE_H_
#define _EMBEDDED_BROWSER_INTERFACE_H_
#include "zoom_sdk_def.h"
/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE

/*! \enum NavigateError
    \brief Navigate error code.
    A more detailed struct description.
*/
enum NavigateError
{
	NavigateError_Success = 0,
	NavigateError_HttpStatus = 1,	//include all of below error code
	NavigateError_InvalidUrl,	//INET_E_INVALID_URL (0x800C0002L or -2146697214)
	NavigateError_NoSession,		//INET_E_NO_SESSION (0x800C0003L or -2146697213)
	NavigateError_CannotConnect,	//INET_E_CANNOT_CONNECT (0x800C0004L or -2146697212)
	NavigateError_ResourceNotFound,	//INET_E_RESOURCE_NOT_FOUND (0x800C0005L or -2146697211)
	NavigateError_ObjNotFound,		//INET_E_OBJECT_NOT_FOUND (0x800C0006L or -2146697210)
	NavigateError_DataNotAvailable,	//INET_E_DATA_NOT_AVAILABLE (0x800C0007L or -2146697209)
	NavigateError_DownloadFailure,	//INET_E_DOWNLOAD_FAILURE (0x800C0008L or -2146697208)
	NavigateError_ConnectionTimeout,	//INET_E_CONNECTION_TIMEOUT (0x800C000BL or -2146697205)
	NavigateError_CannotLoadData,	//INET_E_CANNOT_LOAD_DATA (0x800C000FL or -2146697201)
	NavigateError_BrowserContainerError,
	NavigateError_Others,				//includes all of below errors
};

/// \brief Embedded Browser Callback Event
///
class IEmbeddedBrowserEvent
{
public:
	/// \brief Fires before navigation occurs in the given object (on either a window element or a frameset element).
	/// \param url the URL to which the browser is navigating(UTF8).
	virtual void NotifyBeforeNavigate(const char* url) = 0;

	/// \brief Fires when a document is completely loaded and initialized.
	/// \param url that specifies the URL, UNC file name, or PIDL of the loaded document(UTF8).
	virtual void NotifyDocumentComplete(const char* url) = 0;

	/// \brief Fires when an error occurs during navigation.
	/// \param url the URL for which navigation failed(UTF8).
	/// \param err a status code corresponding to the error, if available. For a list of the possible status codes, see NavigateError.
	/// \param component_err Original error code
	virtual void NotifyNavigateError(const char* url, NavigateError err, int component_err) = 0;
};

/// \brief Embedded Browser Interface
///
class IEmbeddedBrowser
{
public:
	/// \brief Set Embedded Browser callback event
	/// \param pEvent A pointer to a IEmbeddedBrowserEvent* that receives Embedded Browser event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IEmbeddedBrowserEvent* pEvent) = 0;

	/// \brief Navigates to a resource identified by a URL or to a file identified by a full path.
	/// \param url the URL, full path, or UNC location and name of the resource to display(UTF8).
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Navigate(const char* url) = 0;

	/// \brief Resize the Embedded Browser window
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Resize() = 0;

	/// \brief Gets the URL of the resource that is currently displayed.
	/// \return the URL,If the resource is a folder or file on the network or local computer, the name is the full path of the folder or file in the Universal Naming Convention (UNC) format.
	virtual const char* GetURL() = 0;

	/// \brief Retrieves the path or title of the resource that is currently displayed.
	/// \return the location name.
	///If the resource is an HTML webpage, the name is the title of the document. 
	///If the resource is a folder or file on the network or local computer, the name is the full file system path of the folder or file in Universal Naming Convention (UNC) format.
	virtual const char* GetTitle() = 0;

	/// \brief Navigates the WebBrowser control to the previous page in the navigation history, if one is available.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GoBack() = 0;

	/// \brief Navigates the WebBrowser control to the next page in the navigation history, if one is available.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GoForward() = 0;

	/// \brief Reloads the document currently displayed in the WebBrowser control.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DoRefresh() = 0;

	/// \brief Cancels any pending navigation and stops any dynamic page elements, such as background sounds and animations.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DoStop() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif