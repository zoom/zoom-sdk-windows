/*!
* \file customized_resource_helper_interface.h
* \brief Customized Service Interface
* \Remarks You must call the functions first before calling ZOOM_SDK_NAMESPACE::InitSDK(), or no, they won't work.
*/
#ifndef _customiezed_resource_helper_interface_h
#define _customiezed_resource_helper_interface_h
#include "zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum SDKCustomizedStringType
	\brief Custom string type.
	Here are more detailed structural descriptions.
	\remarks Read the description of the each type carefully. You must follow the format to custom your own string. Wrong usage may cause unpredictable crash.
*/
enum SDKCustomizedStringType
{
	SDK_Customized_LiveStream_MenuString_LiveOn_String = 0,///<The new string must end up with "%s" so that the menu item can show correctly. This type is used to define a string to replace the menu item ON %S on live streaming. 
	SDK_Customized_LiveStream_MenuString_LiveView_String,///<The new string must end up with "%s" so that the menu item can show correctly. This type is used to define a string to replace the menu item VIEW STREAM ON %S on live streaming.
	SDK_Customized_LiveStream_MenuString_LiveStop_String,///<The new string must be a pure string so that it can show correctly. This type is used to define a string to replace the menu item STOP LIVE STREAM on live streaming.
	SDK_Customized_LiveStream_MenuString_CopyURL_String,///<The new string must be a pure string so that it can show correctly. This type is used to define a string to replace the menu item COPY STREAMING LINK on live streaming.
	SDK_Customized_Title_App,	///<The new string must be a pure string so that it can show correctly. This type is used to define a string to replace the title of the meeting video UI.
	SDK_Customized_Title_ZoomVideo,  ///<The new string must be the same format as "Zoom Participant ID: %s   Meeting ID: %s" so that it can show correctly. This type is used to define a string to replace the title of the meeting video UI.
	SDK_Customized_Title_FreeZoomVideo, ///<The new string must be the same format as "Zoom Participant ID: %s  %d-Minutes Meeting ID:%s" so that it can show correctly. This type is used to define a string to replace the title of the meeting video UI when the user is free user and in view-only status. 
	SDK_Customized_Title_ViewOnly_FreeZoomVideo, ///<The new string must be the same format as "Zoom %d-Minutes Meeting ID: %s" so that it can show correctly. This type is used to define a string to replace the title of the meeting video UI when the user is free user and in view-only status. 
};

/*! \enum SDKCustomizedURLType
	\brief Custom URL type.
	Here are more detailed structural descriptions.
	\remarks The URL must remain intact and should contain 'http' or https'.
*/
enum SDKCustomizedURLType
{
	SDKCustomizedURL_VITRULBG_HELP, ///<Set the custom help URL in the virtual background tab page.
	SDKCustomizedURL_VITRULBG_LEARN_MORE,///<Set the custom Learn More URL in the virtual background tab page.
	SDKCustomizedURL_SUPPORTURL, ///<Set the Support URL in the meeting.
};

/// \brief Customized resource helper interface.
class ICustomizedResourceHelper
{
public:
	///\brief Add the custom photo files, currently, support PNG and SVG formats.
	///\param key_ Resource ID corresponding to the custom resource.
	///\param absolute_resource_path The location of the customized resource file must be an absolute path and include the file name with suffix.
	/// \remarks You must call the function first before calling ZOOM_SDK_NAMESPACE::InitSDK(), or no, it won't work.
	virtual SDKError AddCustomizedPictureResource(const wchar_t* key_, const wchar_t* absolute_resource_path) = 0;
	/// \brief Use the custom string to replace the specified string item.
	/// \param customizedType Specify the string item type. For more information, see \link SDKCustomizedStringType \endlink enum.
	/// \param customizedString Specify the custom string.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks If customizedString is NULL or is not NULL but with length zero(0), the return value is SDKERR_INVALID_PARAMETER.
	/// \remarks You must call the function first before calling ZOOM_SDK_NAMESPACE::InitSDK(), or no, it won't work.
	virtual SDKError AddCustomizedStringResource(SDKCustomizedStringType customizedType, const wchar_t* customizedString) = 0;
	/// \brief Use the custom URL to replace the specified URL.
	/// \param customizedType Specify the URL type. For more information, see \link SDKCustomizedURLType \endlink enum.
	/// \param customizedUrl Specify the custom URL. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks If customizedUrl is NULL or is not NULL but with length zero(0), the return value is SDKERR_INVALID_PARAMETER.
	/// \remarks You must call the function first before calling ZOOM_SDK_NAMESPACE::InitSDK(), or no, it won't work.
	virtual SDKError AddCustomizedURLResource(SDKCustomizedURLType customizedType, const wchar_t* customizedUrl) = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif
