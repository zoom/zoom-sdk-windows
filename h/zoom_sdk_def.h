/*!
* \file zoom_sdk_def.h
* \brief ZOOM windows SDK Common Definition File.
* 
*/
#ifndef _ZOOM_SDK_DEF_H_
#define _ZOOM_SDK_DEF_H_
#include <tchar.h>
#define PLATFORM_IMPORT	__declspec(dllimport)  
#define PLATFORM_EXPORT	__declspec(dllexport)
#ifdef ZOOM_SDK_DLL_EXPORT
#define SDK_API PLATFORM_EXPORT
#elif defined ZOOM_SDK_DLL_IMPORT
#define SDK_API PLATFORM_IMPORT
#else
#define SDK_API
#endif

#define ZOOM_SDK_NAMESPACE ZOOMSDK
#define BEGIN_ZOOM_SDK_NAMESPACE namespace ZOOM_SDK_NAMESPACE {
#define END_ZOOM_SDK_NAMESPACE };
#define USING_ZOOM_SDK_NAMESPACE using namespace ZOOM_SDK_NAMESPACE;

BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum SDKError
    \brief SDK error types.
    Here are more detailed structural descriptions.
*/ 
enum SDKError
{
	SDKERR_SUCCESS = 0,///<Success.
	SDKERR_NO_IMPL,///<This feature is currently invalid. 
	SDKERR_WRONG_USEAGE,///<Incorrect usage of the feature. 
	SDKERR_INVALID_PARAMETER,///<Wrong parameter.
	SDKERR_MODULE_LOAD_FAILED,///<Loading module failed.
	SDKERR_MEMORY_FAILED,///<No memory is allocated. 
	SDKERR_SERVICE_FAILED,///<Internal service error.
	SDKERR_UNINITIALIZE,///<Not initialized before the usage.
	SDKERR_UNAUTHENTICATION,///<Not authorized before the usage.
	SDKERR_NORECORDINGINPROCESS,///<No recording in process.
	SDKERR_TRANSCODER_NOFOUND,///<Transcoder module is not found.
	SDKERR_VIDEO_NOTREADY,///<The video service is not ready.
	SDKERR_NO_PERMISSION,///<No permission.
	SDKERR_UNKNOWN,///<Unknown error.
	SDKERR_OTHER_SDK_INSTANCE_RUNNING,///<The other instance of the SDK is in process.
	SDKERR_INTELNAL_ERROR,///<SDK internal error.
	SDKERR_NO_AUDIODEVICE_ISFOUND,///<No audio device found.
	SDKERR_NO_VIDEODEVICE_ISFOUND,///<No video device found.
	SDKERR_TOO_FREQUENT_CALL,///<API calls too frequently.
	SDKERR_FAIL_ASSIGN_USER_PRIVILEGE, ///<User can't be assigned with new privilege.
	SDKERR_MEETING_DONT_SUPPORT_FEATURE,///<The current meeting doesn't support the feature.
	SDKERR_MEETING_NOT_SHARE_SENDER,///<The current user is not the presenter.
	SDKERR_MEETING_YOU_HAVE_NO_SHARE,///<There is no sharing.
	SDKERR_MEETING_VIEWTYPE_PARAMETER_IS_WRONG, ///<Incorrect ViewType parameters.
	SDKERR_MEETING_ANNOTATION_IS_OFF, ///<Annotation is disabled.
	SDKERR_SETTING_OS_DONT_SUPPORT, ///<Current OS doesn't support the setting.
	SDKERR_EMAIL_LOGIN_IS_DISABLED, ///<Email login is disable
	SDKERR_HARDWARE_NOT_MEET_FOR_VB, ///<Computer doesn't meet the minimum requirements to use virtual background feature.
};

/*! \enum SDK_LANGUAGE_ID
    \brief The text resource type used by the SDK.
    Here are more detailed structural descriptions.
*/
enum SDK_LANGUAGE_ID
{
	LANGUAGE_Unknow = 0,///<For initialization.
	LANGUAGE_English,///<In English.
	LANGUAGE_Chinese_Simplified,///<In simplified Chinese.
	LANGUAGE_Chinese_Traditional,///<In traditional Chinese.
	LANGUAGE_Japanese,///<In Japanese.
	LANGUAGE_Spanish,///<In Spanish.
	LANGUAGE_German,///<In German.
	LANGUAGE_French,///<In French.
	LANGUAGE_Portuguese,///<In Portuguese.
	LANGUAGE_Russian,///<In Russian.
	LANGUAGE_Korean,///<In Korean.
	LANGUAGE_Vietnamese,///<In Vietnamese.
	LANGUAGE_Italian,///<In Italian.
};

/*! \struct tagWndPosition
    \brief The position of the window. The coordinate of position is that of monitor when the parent window is null. If the the parent window is not null, the position coordinate is that of the parent window.
    Here are more detailed structural descriptions.
*/
typedef struct tagWndPosition 
{
	int left;///<Specifies the X-axis coordinate of the top-left corner of the window
	int top;///<Specifies the Y-axis coordinate of the top-left of the window.
	HWND hSelfWnd;///<Specifies the window handle of the window itself.
	HWND hParent;///<Specifies the window handle of the parent window. If the value is NULL, the position coordinate is the monitor coordinate.
	tagWndPosition()
	{
		left = 0;
		top = 0;
		hSelfWnd = NULL;
		hParent = NULL;
	}
}WndPosition;

/*! \enum CustomizedLanguageType
    \brief Custom resource type used by the SDK.
    Here are more detailed structural descriptions.
*/
enum CustomizedLanguageType
{
	CustomizedLanguage_None,///<No use of the custom resource.
	CustomizedLanguage_FilePath,///<Use the specified file path to assign the custom resource.
	CustomizedLanguage_Content,///<Use the specified content to assign the custom resource.
};

/*! \struct CustomizedLanguageType
    \brief The custom resource information used by the SDK.
    Here are more detailed structural descriptions.
*/ 
typedef struct tagCustomizedLanguageInfo
{
	const char* langName;///<Resource name.
	const char* langInfo;///<The value should be the full path of the resource file when the langType value is CustomizedLanguage_FilePath, including the file name. When the langType value is CustomizedLanguage_Content, the value saves the content of the resource.
	CustomizedLanguageType langType;///<Use the custom resource type.
	tagCustomizedLanguageInfo()
	{
		langName = NULL;
		langInfo = NULL;
		langType = CustomizedLanguage_None;
	}

}CustomizedLanguageInfo;

/*! \struct tagConfigurableOptions
    \brief SDK configuration options. 
	\remarks This structure is used only for the SDK initialization to configure the custom resource file and choose whether to use the UI mode.
    Here are more detailed structural descriptions.
*/
#define ENABLE_CUSTOMIZED_UI_FLAG (1 << 5)
typedef struct tagConfigurableOptions
{
	CustomizedLanguageInfo customizedLang;///The custom resource information.
	int optionalFeatures;///<Additional functional configuration. The function currently supports whether to use the custom UI mode only. When the value of the optionalFeatures&ENABLE_CUSTOMIZED_UI_FLAG is TRUE, it means the custom UI mode will be used. Otherwise the Zoom UI mode will be used.
	const wchar_t* sdkPathPostfix;
	tagConfigurableOptions()
	{
		optionalFeatures = 0;
		sdkPathPostfix = NULL;
	}

}ConfigurableOptions;

/*! \enum SDK_APP_Locale
    \brief SDK_APP locale type.
    Here are more detailed structural descriptions.
*/
enum SDK_APP_Locale
{
	SDK_APP_Locale_Default,
	SDK_APP_Locale_CN,
};

enum ZoomSDKRawDataMemoryMode 
{
	ZoomSDKRawDataMemoryModeStack,
	ZoomSDKRawDataMemoryModeHeap
};

enum ZoomSDKVideoRenderMode
{
	ZoomSDKVideoRenderMode_None = 0,
	ZoomSDKVideoRenderMode_Auto,
	ZoomSDKVideoRenderMode_D3D11EnableFLIP,
	ZoomSDKVideoRenderMode_D3D11,
	ZoomSDKVideoRenderMode_D3D9,
	ZoomSDKVideoRenderMode_GDI,
};

enum ZoomSDKRenderPostProcessing
{
	ZoomSDKRenderPostProcessing_None = 0,
	ZoomSDKRenderPostProcessing_Auto,
	ZoomSDKRenderPostProcessing_Enable,
	ZoomSDKRenderPostProcessing_Disable,
};

enum ZoomSDKVideoCaptureMethod
{
	ZoomSDKVideoCaptureMethod_None = 0,
	ZoomSDKVideoCaptureMethod_Auto,
	ZoomSDKVideoCaptureMethod_DirectSHow,
	ZoomSDKVideoCaptureMethod_MediaFoundation,
};

typedef struct tagZoomSDKRenderOptions
{
	ZoomSDKVideoRenderMode    videoRenderMode;
	ZoomSDKRenderPostProcessing renderPostProcessing;
	ZoomSDKVideoCaptureMethod videoCaptureMethod;
	tagZoomSDKRenderOptions()
	{
		videoRenderMode = ZoomSDKVideoRenderMode_None;
		renderPostProcessing = ZoomSDKRenderPostProcessing_Auto;
		videoCaptureMethod = ZoomSDKVideoCaptureMethod_Auto;
	}
}ZoomSDKRenderOptions;

typedef struct tagRawDataOptions
{
	bool enableRawdataIntermediateMode; ///<false -- YUV420data, true -- intermediate data
	ZoomSDKRawDataMemoryMode  videoRawdataMemoryMode;
	ZoomSDKRawDataMemoryMode  shareRawdataMemoryMode;
	ZoomSDKRawDataMemoryMode  audioRawdataMemoryMode;
	tagRawDataOptions()
	{
		enableRawdataIntermediateMode = false;
		videoRawdataMemoryMode = ZoomSDKRawDataMemoryModeStack;
		shareRawdataMemoryMode = ZoomSDKRawDataMemoryModeStack;
		audioRawdataMemoryMode = ZoomSDKRawDataMemoryModeStack;
	}
}RawDataOptions;

/*! \struct tagInitParam
    \brief Initialize the SDK Parameter.
    Here are more detailed structural descriptions.
*/
typedef struct tagInitParam  
{
	const wchar_t* strWebDomain;///<Web domain.
	const wchar_t* strBrandingName;///<Branding name.
	const wchar_t* strSupportUrl;///<Support URL.
	void* hResInstance;///<Resource module handle.
	unsigned int uiWindowIconSmallID;///<The ID of the small icon on the window.
	unsigned int uiWindowIconBigID;///<The ID of the big Icon on the window.
	SDK_LANGUAGE_ID emLanguageID;///<The ID of the SDK language.
	bool enableGenerateDump; ///<Enable generate dump file if the app crashed.
	bool enableLogByDefault;///<Enable log feature.
	unsigned int uiLogFileSize; ///<Size of a log file in M(megabyte). The default size is 5M. There are 5 log files in total and the file size varies from 1M to 50M. 
	ConfigurableOptions obConfigOpts;///<The configuration options of the SDK.
	SDK_APP_Locale locale;
	bool permonitor_awareness_mode;
	ZoomSDKRenderOptions renderOpts;
	RawDataOptions rawdataOpts;
	tagInitParam()
	{
		strWebDomain = NULL;
		strBrandingName = NULL;
		strSupportUrl = NULL;
		hResInstance = (void*)-1;
		uiWindowIconSmallID = 0;
		uiWindowIconBigID = 0;
		emLanguageID = LANGUAGE_Unknow;
		enableGenerateDump = false;
		enableLogByDefault = false;
		uiLogFileSize = 5;
		locale = SDK_APP_Locale_Default;
		permonitor_awareness_mode = true;
	}
}InitParam;

/*! \enum LastErrorType
    \brief The last error types of the SDK.
    Here are more detailed structural descriptions.
*/
enum LastErrorType
{
	LastErrorType_None,///<No error.
	LastErrorType_Auth,///<Error during verification.
	LastErrorType_Login,///<Error during login.
	LastErrorType_Meeting,///<The associated error with the meeting.
	LastErrorType_System,///<The associated error with the SDK bottom layer.
};

/// \brief Error mechanism interface provided by the SDK
///This feature is gradually improved, so some errors may not be supported.
class IZoomLastError
{
public:
	/// \brief Get the last error type.
	/// \return If the function succeeds, the error type will be returned. For more details, see \link LastErrorType \endlink enum.
	virtual LastErrorType GetErrorType() const = 0 ;
	/// \brief Get the last error code.
	/// \return If the function succeeds, the error code will be returned.
	virtual UINT64 GetErrorCode() const = 0;

	/// \brief Get the description for the last error.
	/// \return If the function succeeds, the error description will be returned. If there is no error, it will return an empty string of length zero(0).
	virtual const wchar_t* GetErrorDescription() const = 0;
	virtual ~IZoomLastError(){};
};
template<class T>
class IList
{
public:
	virtual ~IList(){};
	virtual int GetCount() = 0;
	virtual T   GetItem(int index) = 0;
};
#define SDK_NULL_AUDIO_FILE_HANDLE (0xffffffff)
const RECT _SDK_TEST_VIDEO_INIT_RECT = {0,0,0,0};

END_ZOOM_SDK_NAMESPACE

#endif