/*!
* \file zoom_sdk_def.h
* \brief  Zoom Windows SDK Common Defines File
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

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum SDKError
    \brief Init SDK Parameter.
    A more detailed struct description.
*/ 
enum SDKError
{
	SDKERR_SUCCESS = 0,///< Success Result
	SDKERR_NO_IMPL,///< Not support this feature now 
	SDKERR_WRONG_USEAGE,///< Wrong useage about this feature 
	SDKERR_INVALID_PARAMETER,///< Wrong parameter 
	SDKERR_MODULE_LOAD_FAILED,///< Load module failed 
	SDKERR_MEMORY_FAILED,///< No memory allocated 
	SDKERR_SERVICE_FAILED,///< Internal service error 
	SDKERR_UNINITIALIZE,///< Not initialize before use 
	SDKERR_UNAUTHENTICATION,///< Not Authentication before use
	SDKERR_NORECORDINGINPROCESS,///< No recording in process
	SDKERR_TRANSCODER_NOFOUND,///< can't find transcoder module
	SDKERR_VIDEO_NOTREADY,///< Video service not ready
	SDKERR_NO_PERMISSION,///< No premission to do this
	SDKERR_UNKNOWN,///< Unknown error 
};

enum SDK_LANGUAGE_ID
{
	LANGUAGE_Unknow = 0,
	LANGUAGE_English,
	LANGUAGE_Chinese_Simplified,
	LANGUAGE_Chinese_Traditional,
};

typedef struct tagWndPosition 
{
	int left;
	int top;
	tagWndPosition()
	{
		left = 0;
		top = 0;
	}
}WndPosition;

/*! \struct tagInitParam
    \brief Init SDK Parameter.
    A more detailed struct description.
*/
typedef struct tagInitParam  
{
	const wchar_t* strWebDomain;///< Web Domain
	const wchar_t* strBrandingName;///< Branding name
	const wchar_t* strSupportUrl;///< Support Url
	void* hResInstance;///< resource moudle handle
	unsigned int uiWindowIconSmallID;///< windows small icon file path
	unsigned int uiWindowIconBigID;///< windows small icon file path
	SDK_LANGUAGE_ID emLanguageID;///< sdk language ID
	tagInitParam()
	{
		strWebDomain = NULL;
		strBrandingName = NULL;
		strSupportUrl = NULL;
		hResInstance = (void*)-1;
		uiWindowIconSmallID = 0;
		uiWindowIconBigID = 0;
		emLanguageID = LANGUAGE_Unknow;
	}
}InitParam;
template<class T>
class IList
{
public:
	virtual ~IList(){};
	virtual int GetCount() = 0;
	virtual T   GetItem(int index) = 0;
};
END_ZOOM_SDK_NAMESPACE

#endif