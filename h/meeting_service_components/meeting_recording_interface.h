/*!
* \file meeting_recording_interface.h
* \brief Recording of Meeting Service Interface
* 
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
	Recording_Start,
	Recording_Stop,
	Recording_DiskFull,
};

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

	/// \brief self record privilige change callback
	/// \param bCanRec 
	virtual void onRecordPriviligeChanged(bool bCanRec) = 0;
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
};
END_ZOOM_SDK_NAMESPACE
#endif