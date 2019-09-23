/*!
* \file customized_annotation.h
* \brief zoom customized annotation interface
* 
*/
#ifndef _ZOOM_CUSTOMIZED_ANNOTATION_H_
#define _ZOOM_CUSTOMIZED_ANNOTATION_H_
#include "..\zoom_sdk_def.h"
#include "..\meeting_service_components\meeting_annotation_interface.h"

BEGIN_ZOOM_SDK_NAMESPACE
class ICustomizedShareRender;

/*! \enum CustomizedShareAnnotationStatus
    \brief status of annotation
    A more detailed struct description.
*/ 
enum CustomizedShareAnnotationStatus
{
	CS_ANNO_READYTOUSE,//ready to use annotation
	CS_ANNO_CLOSE, //annotation shut down
};

/// \brief Annotation object callback event
///
class ICustomizedAnnotationObjEvent
{
public:
	/// \brief Notifies the app about annotation tool change
	virtual void onAnnotationObjToolChange(AnnotationToolType type_);
};

/// \brief Annotation object interface
///
class ICustomizedAnnotationObj
{
public:
	/// \brief Set Annotation object callback event
	/// \param pEvent A pointer to a ICustomizedAnnotationObjEvent* that receives annotation object event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(ICustomizedAnnotationObjEvent* event_) = 0;

	/// \brief Check can clear annotation
	/// \param type the type of clear annotation
	/// \return If can, the return value is SDKErr_Success.
	///If can't, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError CanClear(AnnotationClearType type) = 0;

	/// \brief Clear annotation
	/// \param type the type of clear annotation
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Clear(AnnotationClearType type) = 0;

	/// \brief Set annotation tool
	/// \param type the type of annotation tool
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetTool(AnnotationToolType type) = 0;

	/// \brief Set annotation color
	/// \param color the color of annotation tool
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetColor(unsigned long color) = 0;

	/// \brief Set annotation line width
	/// \param lineWidth the line width of annotation tool
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetLineWidth(long lineWidth) = 0;

	/// \brief Get annotation color
	/// \param color the current color of annotation tool
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GetCurColor(unsigned long& color) = 0;

	/// \brief Get annotation line width
	/// \param lineWidth the current line width of annotation tool
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GetCurLineWidth(long& lineWidth) = 0;

	/// \brief Get annotation tool type
	/// \param type the current type of annotation tool
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError GetCurTool(AnnotationToolType& type) = 0;

	/// \brief Undo Annotation
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Undo() = 0;

	/// \brief Redo Annotation
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError Redo() = 0;

	/// \brief Check can save snapshot
	/// \return If can, the return value is SDKErr_Success.
	///If can't, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError CanSaveSnapshot() = 0;

	/// \brief save snapshot
	/// \param path save path
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SaveSnapshot(const wchar_t* path) = 0;
	virtual ~ICustomizedAnnotationObj(){};
};

/// \brief Annotation controller callback event
///
class ICustomizedAnnotationControllerEvent
{
public:
	/// \brief Notifies the app about annotation object destroyed
	/// \param obj_ Specifies which annotation object destroyed
	virtual void onCustomizedAnnotationObjDestroyed(ICustomizedAnnotationObj* obj_) = 0;

	/// \brief Notifies the app about annotation status changed
	/// \param share_render_ Specifies annotation status of which share render changed
	/// \param status_ status
	virtual void onSharingShareAnnotationStatusChanged(ICustomizedShareRender* share_render_, CustomizedShareAnnotationStatus status_) = 0;
};

/// \brief Annotation controller interface
///
class ICustomizedAnnotationController
{
public:
	/// \brief Set Annotation controller callback event
	/// \param pEvent A pointer to a ICustomizedAnnotationControllerEvent* that receives annotation controller event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(ICustomizedAnnotationControllerEvent* event_) = 0;

	/// \brief Create annotation object
	/// \param view_share_render Specifies the owner of the annotation object, if create annotation for start sharing, pass NULL. 
	/// \param pp_obj A pointer to a ICustomizedAnnotationObj* that receives ICustomizedAnnotationObj Object. 
	/// \return If the function succeeds, the return value is SDKErr_Success, and ppMeetingService is not NULL
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \when you got onSharingShareAnnotationStatusChanged with CS_ANNO_READYTOUSE.
	virtual SDKError CreateAnnoObj(ICustomizedShareRender* view_share_render, ICustomizedAnnotationObj** pp_obj) = 0;

	/// \brief Destroy annotation object
	/// \param anno_obj A pointer to a ICustomizedAnnotationObj to be destroyed. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DestroyAnnoObj(ICustomizedAnnotationObj* anno_obj) = 0;
	virtual ~ICustomizedAnnotationController(){};
};
END_ZOOM_SDK_NAMESPACE
#endif