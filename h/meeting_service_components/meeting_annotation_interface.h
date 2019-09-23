/*!
* \file meeting_annotation_interface.h
* \brief Annotation of Meeting Service Interface.
* 
*/
#ifndef _MEETING_Annotation_INTERFACE_H_
#define _MEETING_Annotation_INTERFACE_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum AnnotationToolType
    \brief Type of annotation Tools.
    Here are more detailed structural descriptions.
*/
enum AnnotationToolType
{
	ANNOTOOL_NONE_DRAWING,///<Switch to mouse cursor.

	ANNOTOOL_PEN,///<Pen.
	ANNOTOOL_HIGHLIGHTER,///<Highlighter.
	ANNOTOOL_AUTO_LINE,///<A straight line changes automatically in pace with the mouse cursor.
	ANNOTOOL_AUTO_RECTANGLE,///<A rectangle changes automatically in pace with the mouse cursor.
	ANNOTOOL_AUTO_ELLIPSE,///<An ellipse changes automatically in pace with the mouse cursor.
	ANNOTOOL_AUTO_ARROW,///<An arrow changes automatically in pace with the mouse cursor.
	ANNOTOOL_AUTO_RECTANGLE_FILL,///<A filled rectangle.
	ANNOTOOL_AUTO_ELLIPSE_FILL,///<A filled ellipse.

	ANNOTOOL_SPOTLIGHT,///<Laser pointer.
	ANNOTOOL_ARROW,///<An arrow.

	ANNOTOOL_ERASER,///<An eraser.
};

/*! \enum AnnotationClearType
    \brief Clear types of annotation tools.
    Here are more detailed structural descriptions. 
*/
enum AnnotationClearType
{
	ANNOCLEAR_ALL,///<Clear all annotations.
	ANNOCLEAR_SELF,///<Clear only your own annotations.
	ANNOCLEAR_OTHER,///<Clear only the others' annotations.
};

class ICustomizedAnnotationController;
/// \brief Meeting annotation tools interface.
///
class IAnnotationController
{
public:
	/// \brief Determine if the annotation tools are disabled or not during the current meeting.
	/// \return FALSE indicates enabled while TRUE indicates disabled.
	/// \remarks Valid for both ZOOM style and user custom interface mode.
	virtual bool IsAnnoataionDisable() = 0;

	/// \brief Display annotation toolbar.
	/// \param viewtype Specify which view to display the toolbar. For more details, see \link SDKViewType \endlink enum.
	/// \param left Specify X-axis coordinate of the upper-left corner for the toolbar.
	/// \param top Specify Y-axis coordinate of the upper-left corner for the toolbar.
	/// \return If the function succeeds, the return value is SDKErr_Success. 
	///Otherwise failed. For extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid only for ZOOM style user interface mode.
	virtual SDKError StartAnnotation(SDKViewType viewtype, int left, int top) = 0;

	/// \brief Close the current annotation toolbar.
	/// \param viewtype Specify which view to close the toolbar. For more details, see \link SDKViewType \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. For extended error information, see \link SDKError \endlink enum.
	///  \remarks Valid only for ZOOM style user interface mode.
	virtual SDKError StopAnnotation(SDKViewType viewtype) = 0;

	/// \brief Choose annotation tool.
	/// \param viewtype Specify which view to display the toolbar. For more details, see \link SDKViewType \endlink enum.
	/// \param type Specify the annotation tool to be used.
	///For the definitions of the tools, see \link AnnotationToolType \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///  \remarks Valid only for ZOOM style user interface mode.
	virtual SDKError SetTool(SDKViewType viewtype, AnnotationToolType type) = 0;

	/// \brief Clear present annotations. 
	/// \param viewtype Specify on which view to clear the annotations. For more details, see \link SDKViewType \endlink enum.
	/// \param type Specify the ways to clear annotations. For the definitions of the tools, see \link AnnotationClearType \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///  \remarks Valid only for ZOOM style user interface mode.
	virtual SDKError Clear(SDKViewType viewtype, AnnotationClearType type) = 0;


	/// \brief Set the colors of annotation tools.
	/// \param viewtype The specified color is used on which view. For more details, see \link SDKViewType \endlink enum. 
	/// \param color Specify the color of the annotation tools in RGB format.  
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///  \remarks Valid only for ZOOM style user interface mode.
	virtual SDKError SetColor(SDKViewType viewtype, unsigned long color) = 0;

	/// \brief Set the line width of annotation tools.
	/// \param viewtype The specified line width is used on which view. For more details, see \link SDKViewType \endlink enum. 
	/// \param lineWidth Specify the line width to annotate.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///  \remarks Valid only for ZOOM style user interface mode.
	virtual SDKError SetLineWidth(SDKViewType viewtype, long lineWidth) = 0;
	
	/// \brief Undo the last annotation.
	/// \param viewtype Specify on which view to undo the last annotation. For more details, see \link SDKViewType \endlink enum. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///  \remarks Valid only for ZOOM style user interface mode.
	virtual SDKError Undo(SDKViewType viewtype) = 0;
	
	/// \brief Redo the last-undo annotation.
	/// \param viewtype Specify on which view to redo the last-undo annotation. For more details, see \link SDKViewType \endlink enum.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	///  \remarks Valid only for ZOOM style user interface mode.
	virtual SDKError Redo(SDKViewType viewtype) = 0;

	/// \brief Get the controller of annotation tools used in user custom interface mode.
	/// \return If the function succeeds, the return value is the controller of annotation tools used in user custom interface mode.
	///If the function fails, the return value is NULL.
	///  \remarks Valid only for user custom interface mode.
	virtual ICustomizedAnnotationController* GetCustomizedAnnotationController() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif