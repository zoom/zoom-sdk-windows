/*!
* \file customized_annotation.h
* \brief ZOOM Custom Annotation Interface.
* 
*/
#ifndef _ZOOM_CUSTOMIZED_ANNOTATION_H_
#define _ZOOM_CUSTOMIZED_ANNOTATION_H_
#include "..\zoom_sdk_def.h"
#include "..\meeting_service_components\meeting_annotation_interface.h"

BEGIN_ZOOM_SDK_NAMESPACE
class ICustomizedShareRender;

/*! \enum CustomizedShareAnnotationStatus
    \brief Status of custom annotation toolbar. 
    Here are more detailed structural descriptions..
*/ 
enum CustomizedShareAnnotationStatus
{
	CS_ANNO_READYTOUSE,///<The toolbar has been created.
	CS_ANNO_CLOSE,///<The toolbar will be destroyed.  
};

enum SDKAnnoSaveType
{
	SDK_ANNO_SAVE_NONE = 0,
	SDK_ANNO_SAVE_PNG,
	SDK_ANNO_SAVE_PDF,
	SDK_ANNO_SAVE_PNG_MEMORY,
	SDK_ANNO_SAVE_PDF_MEMORY,
	SDK_ANNO_SAVE_BITMAP_MEMORY,
};
/// \brief Annotation object callback event.
///                                      
class ICustomizedAnnotationObjEvent
{
public:
	/// \brief Callback event that the annotation tool changes.
	/// \param type_ The type of annotation tool. For more details, see \link AnnotationToolType \endlink enum.
	virtual void onAnnotationObjToolChange(AnnotationToolType type_) = 0;
};

/// \brief Annotation object interface.
///
class ICustomizedAnnotationObj
{
public:
	/// \brief Set annotation object callback event handler.
	/// \param event_ A pointer to the ICustomizedAnnotationObjEvent that receives annotation object event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(ICustomizedAnnotationObjEvent* event_) = 0;

	/// \brief Determine if it is enabled to clear annotations by the specified way. 
	/// \param type Specify the annotation clear type. For more details, see \link AnnotationClearType \endlink enum.
	/// \return If the user owns the authority, the return value is SDKErr_Success.
	///Otherwise not. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanClear(AnnotationClearType type) = 0;

	/// \brief Clear the annotation with the specified type.
	/// \param type Specify the type to clear annotation. For more details, see \link AnnotationClearType \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Clear(AnnotationClearType type) = 0;

	/// \brief Set the tool to annotate.
	/// \param type Specify the type of the annotation tool. For more details, see \link AnnotationToolType \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetTool(AnnotationToolType type) = 0;

	/// \brief Set the color to annotate.
	/// \param color Specify the color to annotate, in RGB format.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetColor(unsigned long color) = 0;
	
	/// \brief Set the value of line width of annotation tool.
	/// \param lineWidth The line width of annotation tool.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetLineWidth(long lineWidth) = 0;

	/// \brief Get the color of current annotation tool.
	/// \param [out] color The color to annotate in RGB format.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError GetCurColor(unsigned long& color) = 0;

	/// \brief Get the value of line width of the current annotation tool.
	/// \param [out] lineWidth The width of the current annotation tool. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.										 
	virtual SDKError GetCurLineWidth(long& lineWidth) = 0;

	/// \brief Get the type of the current annotation tool.
	/// \param type Specify the type of the annotation tool. For more details, see \link AnnotationToolType \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError GetCurTool(AnnotationToolType& type) = 0;

	/// \brief Undo the last annotation.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Undo() = 0;

	/// \brief Redo the annotation that was undone. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError Redo() = 0;

	/// \brief Determine if it is enabled to save the screenshot.
	/// \return If the user owns the authority, the return value is SDKErr_Success.
	///Otherwise not. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanSaveSnapshot() = 0;

	/// \brief Save the screenshot in the specified path.
	/// \param path Specify the path to store the screenshot. If the specified path is wrong, the SDKERR_INVALID_PARAMETER will be returned. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SaveSnapshot(const wchar_t* path, SDKAnnoSaveType nType) = 0;

	/// \brief Determine if can do annotate.
	/// \param [out] bCan, true means can do annotate, false can not. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanDoAnnotation(bool& bCan) = 0;

	/// \brief Determine whether annotations are currently available.
	/// \return true available, false invalid.
	virtual bool IsAnnoataionDisable() = 0;

	virtual ~ICustomizedAnnotationObj(){};


};

/// \brief Annotation controller callback event
///
class ICustomizedAnnotationControllerEvent
{
public:
	/// \brief Callback of destroying the specified annotation object.
	/// \param obj_ Specify the annotation object to be destroyed. Once destroyed, it can no longer be used.
	virtual void onCustomizedAnnotationObjDestroyed(ICustomizedAnnotationObj* obj_) = 0;

	/// \brief Callback event when the annotation status changes.
	/// \param share_render_ The annotate status of share_render changes. For more details, see \link ICustomizedShareRender \endlink.
	/// \param status_ The changed status. For more details, see \link CustomizedShareAnnotationStatus \endlink.
	virtual void onSharingShareAnnotationStatusChanged(ICustomizedShareRender* share_render_, CustomizedShareAnnotationStatus status_) = 0;
};

/// \brief Annotation controller interface.
///
class ICustomizedAnnotationController
{
public:
	/// \brief Set annotation controller callback event handler.
	/// \param event_ A pointer to the ICustomizedAnnotationControllerEvent that receives annotation controller event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(ICustomizedAnnotationControllerEvent* event_) = 0;

	/// \brief An instance created on the specified render which is an object of ICustomizedShareRender created on the sharing window.
	/// \param view_share_render Specify the render to receive the shared content. The sharer should set the value to NULL.
	/// \param pp_obj A pointer to the ICustomizedAnnotationObj*.
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppMeetingService is not NULL
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks It is suggested to call this function if the value of status_ is CS_ANNO_READYTOUSE when you receive the ICustomizedAnnotationControllerEvent::onSharingShareAnnotationStatusChanged.
	virtual SDKError CreateAnnoObj(ICustomizedShareRender* view_share_render, ICustomizedAnnotationObj** pp_obj) = 0;

	/// \brief Destroy the specified annotation object.
	/// \param anno_obj Specify the annotation tool to be destroyed.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError DestroyAnnoObj(ICustomizedAnnotationObj* anno_obj) = 0;
	virtual ~ICustomizedAnnotationController(){};

}; 
END_ZOOM_SDK_NAMESPACE
#endif