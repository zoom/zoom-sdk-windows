/*!
* \file meeting_annotation_interface.h
* \brief Annotation of Meeting Service Interface
* 
*/
#ifndef _MEETING_Annotation_INTERFACE_H_
#define _MEETING_Annotation_INTERFACE_H_
#include "..\zoom_sdk_def.h"

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum AnnotationToolType
    \brief Annotation Tool Type.
    A more detailed struct description.
*/
enum AnnotationToolType
{
	ANNOTOOL_NONE_DRAWING,///<switch to mouse 

	ANNOTOOL_PEN,
	ANNOTOOL_HIGHLIGHTER,
	ANNOTOOL_AUTO_LINE,
	ANNOTOOL_AUTO_RECTANGLE,
	ANNOTOOL_AUTO_ELLIPSE,
	ANNOTOOL_AUTO_ARROW,
	ANNOTOOL_AUTO_RECTANGLE_FILL,
	ANNOTOOL_AUTO_ELLIPSE_FILL,

	ANNOTOOL_SPOTLIGHT,
	ANNOTOOL_ARROW,

	ANNOTOOL_ERASER,///<earser
};

/*! \enum AnnotationClearType
    \brief Annotation Clear Type.
    A more detailed struct description.
*/
enum AnnotationClearType
{
	ANNOCLEAR_ALL,
	ANNOCLEAR_SELF,
	ANNOCLEAR_OTHER,
};

class ICustomizedAnnotationController;
/// \brief Meeting Annotation Controller Interface
///
class IAnnotationController
{
public:
	/// \brief The Annotation of the current meeting is disabled or not.
	/// \return Disabled or not.
	/// \support for zoom style and customized style ui mode
	virtual bool IsAnnoataionDisable() = 0;

	/// \brief start annotation
	/// \param viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \param left Specifies The left position of the annotation bar.
	/// \param top Specifies The top position of the annotation bar.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \only for zoom style ui mode
	virtual SDKError StartAnnotation(SDKViewType viewtype, int left, int top) = 0;

	/// \brief Stop current annotation
	/// \param viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \only for zoom style ui mode
	virtual SDKError StopAnnotation(SDKViewType viewtype) = 0;

	/// \brief Set Annotation Tool
	/// \param viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \param type The parameter to be used for annotation tool type, refer to AnnotationToolType. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \only for zoom style ui mode
	virtual SDKError SetTool(SDKViewType viewtype, AnnotationToolType type) = 0;

	/// \brief Clear Annotation
	/// \param viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \param type The parameter to be used for annotation earse operator type, refer to AnnotationClearType. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \only for zoom style ui mode
	virtual SDKError Clear(SDKViewType viewtype, AnnotationClearType type) = 0;


	/// \brief Set Annotation Color
	/// \param viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \param color The parameter to be used for annotation color, ABGR formats. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \only for zoom style ui mode
	virtual SDKError SetColor(SDKViewType viewtype, unsigned long color) = 0;

	/// \brief Set Annotation Line Width
	/// \param viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \param lineWidth The parameter to be used for annotation line width. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \only for zoom style ui mode
	virtual SDKError SetLineWidth(SDKViewType viewtype, long lineWidth) = 0;
	
	/// \brief Undo Annotation
	/// \param viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \only for zoom style ui mode
	virtual SDKError Undo(SDKViewType viewtype) = 0;
	
	/// \brief Redo Annotation
	/// \param viewtype Specifies which view you want to set, first monitor or second monitor.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// \only for zoom style ui mode
	virtual SDKError Redo(SDKViewType viewtype) = 0;

	/// \brief Get annotation controller for customized ui mode
	/// \return If the function succeeds, the return value is annotation controller interface of customized ui mode.
	///If the function fails, the return value is NULL.
	/// \only for customized style ui mode
	virtual ICustomizedAnnotationController* GetCustomizedAnnotationController() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif