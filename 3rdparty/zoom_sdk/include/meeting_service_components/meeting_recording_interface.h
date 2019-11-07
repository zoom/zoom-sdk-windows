/*!
* \file meeting_recording_interface.h
* \brief Recording of Meeting Service Interface
* Valid for both ZOOM style and user custom interface mode.
*/
#ifndef _MEETING_Recording_INTERFACE_H_
#define _MEETING_Recording_INTERFACE_H_
#include "..\zoom_sdk_def.h"
#include <time.h>

BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum RecordingStatus
    \brief Recording status.
    Here are more detailed structural descriptions.
*/
enum RecordingStatus
{
	Recording_Start,///Start recording on local computer or on cloud.
	Recording_Stop,///Stop recording on local computer or on cloud.
	Recording_DiskFull,///There is no space to store for both local and cloud recording.
	Recording_Pause,///Pause recording on local or on cloud.
	Recording_Connecting,///Connecting, only for cloud recording.
};

class ICustomizedLocalRecordingLayoutHelper;
/// \brief Meeting recording callback event.
///
class IMeetingRecordingCtrlEvent
{
public:
	/// \brief Callback event of ending the conversion to MP4 format.
	/// \param bsuccess TRUE indicates to convert successfully. FALSE not.
	/// \param iResult This value is used to save the error code only when the convert fails.
	/// \param szPath If the conversion is successful, this value is used to save the path of the recording file. 
	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath) = 0;

	/// \brief Callback event of the process of the conversion to MP4 format.
	/// \param iPercentage Percentage of conversion process. Range from ZERO(0) to ONE HUNDREAD(100).
	virtual void onRecording2MP4Processing(int iPercentage) = 0;

	/// \brief Callback event that the status of local recording changes.
	/// \param status Value of recording status. For more details, see \link RecordingStatus \endlink enum.
	virtual void onRecordingStatus(RecordingStatus status) = 0;

	/// \brief Callback event that the status of cloud recording changes.
	/// \param status Value of recording status. For more details, see \link RecordingStatus \endlink enum.
	virtual void onCloudRecordingStatus(RecordingStatus status) = 0;

	/// \brief Callback event that the recording authority changes.
	/// \param bCanRec TRUE indicates to enable to record.
	virtual void onRecordPriviligeChanged(bool bCanRec) = 0;

	/// \brief Callback event that the local recording source changes in the custom user interface mode.
	/// \param layout_helper An object pointer to ICustomizedLocalRecordingLayoutHelper. For more details, see \link ICustomizedLocalRecordingLayoutHelper \endlink.
	///The layout_helper won't be released till the call ends. The user needs to complete the related layout before the call ends. 
	virtual void onCustomizedLocalRecordingSourceNotification(ICustomizedLocalRecordingLayoutHelper* layout_helper) = 0;
};

/// \brief Meeting recording controller interface.
///
class IMeetingRecordingController
{
public:
	/// \brief Set meeting recording callback event handler.
	/// \param pEvent A pointer to the IMeetingRecordingCtrlEvent that receives the recording event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IMeetingRecordingCtrlEvent* pEvent) = 0;

	/// \brief Start recording.
	/// \param [out] startTimestamp The timestamps when start recording.
	/// \param recPath Specifies the path of saving the recording. The SDK will try to create this path if the specified one does not exist. If the creation failed, an error code SDKERR_INVALID_PARAMETER returns. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StartRecording(time_t& startTimestamp, wchar_t* recPath) = 0;

	/// \brief Stop recording.
	/// \param [out] stopTimestamp The timestamps when stop recording.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StopRecording(time_t& stopTimestamp) = 0;

	/// \brief Determine if the specified user is enabled to start recording.
	/// \param cloud_recording TRUE indicates to determine whether to enable the cloud recording. FALSE local recording. 
	/// \param userid Specifies the user ID.
	/// \return If the value of cloud_recording is set to TRUE and the cloud recording is enabled, the return value is SDKErr_Success.
	///If the value of cloud_recording is set to FALSE and the local recording is enabled, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanStartRecording(bool cloud_recording, unsigned int userid) = 0;

	/// \brief Determine if the current user own the authority to change the recording permission of the others.
	/// \return If the user own the authority, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanAllowDisAllowLocalRecording() = 0;

	/// \brief Start cloud recording.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StartCloudRecording() = 0;

	/// \brief Stop cloud recording.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StopCloudRecording() = 0;

	/// \brief Determine if the user owns the authority to enable the local recording. 
	/// \param userid Specifies the user ID.
	/// \return If the specified user is enabled to start local recording, the return value is SDKErr_Success. 
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError IsSupportLocalRecording(unsigned int userid) = 0;

	/// \brief Give the specified user authority for local recording.
	/// \param userid Specifies the user ID.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError AllowLocalRecording(unsigned int userid) = 0;

	/// \brief Abrogate the authority of the specified user for local recoding.
	/// \param userid Specifies the user ID.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError DisAllowLocalRecording(unsigned int userid) = 0;

	/// \brief Send a request to enable the SDK to call IMeetingRecordingCtrlEvent::onCustomizedLocalRecordingSourceNotification().
	/// \return If the function succeeds, the return value is SDKErr_Success, and you will receive the onCustomizedLocalRecordingSourcenNotification callback event.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Valid only for custom style user interface mode only when recording.
	virtual SDKError RequestCustomizedLocalRecordingSource() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif