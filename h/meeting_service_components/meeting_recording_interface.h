/*!
* \file meeting_recording_interface.h
* \brief Recording of Meeting Service Interface
* \support for zoom style and customized style ui mode
*/
#ifndef _MEETING_Recording_INTERFACE_H_
#define _MEETING_Recording_INTERFACE_H_
#include "..\zoom_sdk_def.h"
#include <time.h>

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum RecordingStatus
    \brief Recording status.
    A more detailed struct description.
*/
enum RecordingStatus
{
	Recording_Start,			 //start, both for local & cloud recording
	Recording_Stop,				 //stop, both for local & cloud recording
	Recording_DiskFull,			 //error, both for local & cloud recording
	Recording_Pause,			 //pause, both for local & cloud recording
	Recording_Connecting,		 //connecting, only for cloud recording
};

class ICustomizedLocalRecordingLayoutHelper;
/// \brief Meeting recording callback event
///
class IMeetingRecordingCtrlEvent
{
public:
	/// \brief Once the mp4 conversion is complete, call back 
	/// \param bsuccess Success or not.
	/// \param iResult Details for error code if failed.
	/// \param szPath if success, will return the recording file path, Otherwise is NULL. 
	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath) = 0;

	/// \brief Notify the mp4 conversion processing
	/// \param iPercentage conversion process's percentage.
	virtual void onRecording2MP4Processing(int iPercentage) = 0;

	/// \brief Self Recording status notify callback
	/// \param status Recording status value.
	virtual void onRecordingStatus(RecordingStatus status) = 0;

	/// \brief Cloud Recording status notify callback
	/// \param status Recording status value.
	virtual void onCloudRecordingStatus(RecordingStatus status) = 0;

	/// \brief self record privilige change callback
	/// \param bCanRec 
	virtual void onRecordPriviligeChanged(bool bCanRec) = 0;

	/// \brief local recording source callback for customized ui mode
	/// \param layout_helper layout local recording helper.
	/// the layout_helper will be released after call end, please do layout before this call end.
	virtual void onCustomizedLocalRecordingSourceNotification(ICustomizedLocalRecordingLayoutHelper* layout_helper) = 0;
};

/// \brief Meeting recording controller interface
///
class IMeetingRecordingController
{
public:
	/// \brief Set meeting chat callback event
	/// \param pEvent A pointer to a IMeetingRecordingCtrlEvent* that receives recording event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingRecordingCtrlEvent* pEvent) = 0;

	/// \brief Start recording
	/// \param startTimestamp Start recording timestamp. 
	/// \param recPath Specifies where the recording is to be saved, if the path is not exist, return SDKERR_INVALID_PARAMETER error code.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StartRecording(time_t& startTimestamp, wchar_t* recPath) = 0;

	/// \brief Stop recording
	/// \param stopTimestamp Stop recording timestamp.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StopRecording(time_t& stopTimestamp) = 0;

	/// \brief Check Can Start recording or not
	/// \param cloud_recording cloud recording or not. 
	/// \param userid Specifies which user you want to check.
	/// \return If can start recording, the return value is SDKErr_Success.
	///If can't, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError CanStartRecording(bool cloud_recording, unsigned int userid) = 0;

	/// \brief Check Can allow or disallow other attendee to start local recording in the meeting
	/// \return If you can, the return value is SDKErr_Success.
	///If you can't, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError CanAllowDisAllowLocalRecording() = 0;

	/// \brief Start cloud recording
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StartCloudRecording() = 0;

	/// \brief Stop cloud recording
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StopCloudRecording() = 0;

	/// \brief Check support local recoding feature or not
	/// \param userid Specifies which user you want to check.
	/// \return If support recording, the return value is SDKErr_Success.
	///If don't support, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError IsSupportLocalRecording(unsigned int userid) = 0;

	/// \brief Allow to start local recoding
	/// \param userid Specifies which user you want to allow.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError AllowLocalRecording(unsigned int userid) = 0;

	/// \brief DisAllow to start local recoding
	/// \param userid Specifies which user you want to allow.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError DisAllowLocalRecording(unsigned int userid) = 0;

	/// \brief Request customized local recording source notification
	/// \return If the function succeeds, the return value is SDKErr_Success, and you will got the onCustomizedLocalRecordingSourcenNotification callback.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	/// only for customized style ui mode
	virtual SDKError RequestCustomizedLocalRecordingSource() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif