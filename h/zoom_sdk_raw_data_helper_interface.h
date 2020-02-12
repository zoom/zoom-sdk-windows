#ifndef _ZOOM_SDK_RAW_DATA_HELPER_INTERFACE_H_
#define _ZOOM_SDK_RAW_DATA_HELPER_INTERFACE_H_
#include "zoom_sdk_platform.h"
BEGIN_ZOOM_RAWDATA_NAMESPACE
class IAudioRawDataChannel;
class IVideoRawDataChannel;
class IShareRawDataChannel;
/*! \enum SDKRawDataError
    \brief SDK raw data error types.
    Here are more detailed structural descriptions.
*/
enum SDKRawDataError
{
	SDKRawDataError_SUCCESS,///<Success.
	SDKRawDataError_UNINITIALIZED,///<Not initialized before the usage.
	SDKRawDataError_MALLOC_FAILED,///<Memory allocation failed.
	SDKRawDataError_WRONGUSAGE,///<Incorrect usage of the feature.
	SDKRawDataError_INVALID_PARAM,///<Invalid parameter.
	SDKRawDataError_NOT_IN_MEETING,///<Not in meeting.
	SDKRawDataError_NO_LICENSE,///<The user has no raw data license.
	
	SDKRawDataError_VIDEO_MODULE_NOT_READY,///<The video module is not ready.
	SDKRawDataError_VIDEO_MODULE_ERROR,///<Video module is in error.
	SDKRawDataError_VIDEO_DEVICE_ERROR,///<Video device is in error.
	SDKRawDataError_NO_VIDEO_DATA,///<There is no raw data of video.

	SDKRawDataError_SHARE_MODULE_NOT_READY,///<The sharing module is not ready.
	SDKRawDataError_SHARE_MODULE_ERROR,///<Sharing module is in error.
	SDKRawDataError_NO_SHARE_DATA,///<There is no raw data of sharing.

	SDKRawDataError_AUDIO_MODULE_NOT_READY,///<The audio module is not ready.
	SDKRawDataError_AUDIO_MODULE_ERROR,///<Audio module is in error.
	SDKRawDataError_NO_AUDIO_DATA,///<There is no raw data of audio.
};
#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

/// \brief Determine if the user has raw data license.
/// \return If the user has license, the function returns SDKRawDataError_SUCCESS, otherwise SDKRawDataError_NO_LICENSE.
/// To get extended error information, see \link SDKRawDataError \endlink enum.
ZOOMSDK_MODULE_API SDKRawDataError HasRawDataLicense();

/// \brief Retrieve the audio raw data channel.
/// \param pp_channel A pointer to the pointer to IAudioRawDataChannel. For more details, see \link IAudioRawDataChannel \endlink.
/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
ZOOMSDK_MODULE_API SDKRawDataError RetrieveAudioRawDataChannel(IAudioRawDataChannel** pp_channel);

/// \brief Retrieve the video raw data channel.
/// \param pp_channel A pointer to the pointer to IVideoRawDataChannel. For more details, see \link IVideoRawDataChannel \endlink.
/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
ZOOMSDK_MODULE_API SDKRawDataError RetrieveVideoRawDataChannel(IVideoRawDataChannel** pp_channel);

/// \brief Retrieve the share raw data channel.
/// \param pp_channel A pointer to the pointer to IShareRawDataChannel. For more details, see \link IShareRawDataChannel \endlink.
/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
ZOOMSDK_MODULE_API SDKRawDataError RetrieveShareRawDataChannel(IShareRawDataChannel** pp_channel);

#ifdef __cplusplus
};
#endif //__cplusplus

/*! \enum RawDataMemoryMode
    \brief Raw data memory mode types.
    Here are more detailed structural descriptions.
*/
enum RawDataMemoryMode
{
	RawDataMemoryMode_Stack,///<Stack mode. Do not copy new buffer.
	RawDataMemoryMode_Heap,///<Heap mode. Copy new buffer.
};
/*! \enum RawDataResolution
    \brief The resolution of video/share raw data.
    Here are more detailed structural descriptions.
*/
enum RawDataResolution
{
	RawDataResolution_90,///<The resolution is 90p.
	RawDataResolution_180,///<The resolution is 180p.
	RawDataResolution_360,///<The resolution is 360p.
	RawDataResolution_720,///<The resolution is 720p.
#if (defined _WIN32) || (defined __MACOS__)
	RawDataResolution_1080,///<The resolution is 1080p.
#endif
};
/// \brief The YUV raw data handler interface.
class YUVRawDataI420
{
public:
	/// \brief Determine if the reference count can be increased.
	/// \return TRUE indicates to the reference count can be increased.
	virtual bool CanAddRef() = 0;
	
	/// \brief Add one to the reference count.
	/// \return If the function succeeds, the return value is TRUE.
	virtual bool AddRef() = 0;
	
	/// \brief Subtract one from the reference count.
	/// \return The current reference count. If the currrent reference count is 0, the SDK will delete this object instance.
	virtual int Release() = 0;
	
	/// \brief Get the y-data of the YUV raw data.
	/// \return A pointer to the y-data of the YUV raw data.
	virtual char* GetYBuffer() = 0;
	
	/// \brief Get the u-data of the YUV raw data.
	/// \return A pointer to the u-data of the YUV raw data.
	virtual char* GetUBuffer() = 0;
	
	/// \brief Get the v-data of the YUV raw data.
	/// \return A pointer to the v-data of the YUV raw data.
	virtual char* GetVBuffer() = 0;
	
	/// \brief Get the YUV raw data.
	/// \return A pointer to the YUV raw data.
	virtual char* GetBuffer() = 0;
	
	/// \brief Get the buffer length of the YUV raw data.
	/// \return The length of the YUV raw data.
	virtual unsigned int GetBufferLen() = 0;
	
	/// \brief Determine if the YUV raw data is limited range mode.
	/// \return TRUE indicates to the YUV raw data is limited range mode.
	virtual bool IsLimitedI420() = 0;
	
	/// \brief Get the stream width.
	/// \return The stream width.
	virtual unsigned int GetStreamWidth() =0;
	
	/// \brief Get the stream height.
	/// \return The stream height.
	virtual unsigned int GetStreamHeight() = 0;
	
	/// \brief Get the rotation angle of the local video device.
	/// \return If the function succeeds, the return is enumerated in LocalVideoDeviceRotation enum 
	virtual unsigned int GetRotation() = 0;
	
	/// \brief Get the source_id of the current YUV raw data.
	/// \return The source_id.
	virtual unsigned int GetSourceID() = 0;
	virtual ~YUVRawDataI420(){}
};

/// \brief The audio raw data handler interface.
class AudioRawData
{
public:
	/// \brief Determine if the reference count can be increased.
	/// \return TRUE indicates to the reference count can be increased.
	virtual bool CanAddRef() = 0;
	
	/// \brief Add one to the reference count.
	/// \return If the function succeeds, the return value is TRUE.
	virtual bool AddRef() = 0;
	
	/// \brief Subtract one from the reference count.
	/// \return The current reference count. If the currrent reference count is 0, the SDK will delete this object instance.
	virtual int Release() = 0;
	
	/// \brief Get the audio raw data.
	/// \return A pointer to the audio raw data.
	virtual char* GetBuffer() = 0;
	
	/// \brief Get the buffer length of the audio raw data.
	/// \return The length of the audio raw data.
	virtual unsigned int GetBufferLen() = 0;
	
	/// \brief Get the sample rate of the audio raw data.
	/// \return The sample rate of the audio raw data.
	virtual unsigned int GetSampleRate() = 0;
	
	/// \brief Get the channel number of the audio raw data.
	/// \return The channel number of the audio raw data.
	virtual unsigned int GetChannelNum() = 0;
	virtual ~AudioRawData(){}
};

/// \brief Audio raw data callback event.
class IAudioRawDataReceiver
{
public:
	virtual ~IAudioRawDataReceiver(){}
	
	/// \brief The callback event for receiving the mixed audio raw data.
	/// \param data_ The mixed audio raw data. A pointer to AudioRawData. For more details, see \link AudioRawData \endlink.
	virtual void onMixedAudioRawDataReceived(AudioRawData* data_) = 0;
	
	/// \brief The callback event for receiving the one way audio raw data.
	/// \param data_ The one way audio raw data. A pointer to AudioRawData. For more details, see \link AudioRawData \endlink.
	/// \param node_id The related user id of the audio raw data.
	virtual void onOneWayAudioRawDataReceived(AudioRawData* data_, unsigned int node_id) = 0;
};

/// \brief Audio raw data channel interface.
class IAudioRawDataChannel
{
public:
	/// \brief Start audio raw data channel for the service.
	/// \param mode Specifies the memory mode type. For more details, see \link RawDataMemoryMode \endlink.
	/// \param data_receiver A pointer to IAudioRawDataReceiver. Specifies the audio raw data receiver. For more details, see \link IAudioRawDataReceiver \endlink.
	/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
	virtual SDKRawDataError Start(RawDataMemoryMode mode, IAudioRawDataReceiver* data_receiver) = 0;
	
	/// \brief Stop audio raw data channel for the service.
	/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
	virtual SDKRawDataError Stop() = 0;
};

/// \brief The share_raw_data callback event.
class IShareRawDataReceiver
{
public:
	virtual ~IShareRawDataReceiver(){}
	
	/// \brief The callback event for receiving the share raw data.
	/// \param data_ The share raw data. A pointer to YUVRawDataI420. For more details, see \link YUVRawDataI420 \endlink.
	/// \param recv_handle_list The list of the render window handles.
	virtual void onShareRawDataReceived(YUVRawDataI420* data_, IVector<unsigned long long >* recv_handle_list) = 0;
	
	/// \brief The callback event for subscribed sharing user's data on.
	/// \param recv_handle_list The list of the render window handles.
	virtual void onSubscribedShareUserDataOn(IVector<unsigned long long >* recv_handle_list) = 0;
	
	/// \brief The callback event for subscribed sharing user's data off.
	/// \param recv_handle_list The list of the render window handles.
	virtual void onSubscribedShareUserDataOff(IVector<unsigned long long >* recv_handle_list) = 0;
	
	/// \brief The callback event for subscribed sharing user left meeting.
	/// \param recv_handle_list The list of the render window handles.
	virtual void onSubscribedShareUserLeft(IVector<unsigned long long >* recv_handle_list) = 0;
};

/// \brief Share_raw_data channel interface.
class IShareRawDataChannel
{
public:
	/// \brief Start the share_raw_data channel service.
	/// \param mode Specifies the memory mode type. For more details, see \link RawDataMemoryMode \endlink.
	/// \param data_receiver A pointer to IShareRawDataReceiver. Specifies the share_raw_data receiver. For more details, see \link IShareRawDataReceiver \endlink.
	/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
	virtual SDKRawDataError Start(RawDataMemoryMode mode, IShareRawDataReceiver* data_receiver) = 0;
	
	/// \brief Subscribe some user's share_raw_data.
	/// \param node_id Specifies the user's id.
	/// \param size_ Specifies the resolution of the raw data.
	/// \param recver_handle Specifies the render window handle related to the subscribing user.
	/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
	virtual SDKRawDataError Subscribe(unsigned int node_id, RawDataResolution size_, unsigned long long recver_handle) = 0;
	
	/// \brief Unsubscribe some user's share_raw_data.
	/// \param node_id Specifies the user's id.
	/// \param recver_handle Specifies the render window handle related to the unsubscribing user.
	/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
	virtual SDKRawDataError UnSubscribe(unsigned int node_id, unsigned long long recver_handle) = 0;
	
	/// \brief Stop the share_raw_data channel service.
	/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
	virtual SDKRawDataError Stop() = 0;
	
	/// \brief Enable the intermediate YUV raw data. Default value: FALSE
	/// \param enable TRUE indicates to enable the intermediate YUV raw data.
	/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
	virtual SDKRawDataError EnableIntermediateRawDataCB(bool enable) = 0;
};

/*! \enum LocalVideoDeviceRotation
    \brief The information category for local video device rotation angle.
    Here are more detailed structural descriptions.
*/
enum LocalVideoDeviceRotation
{
	LOCAL_DEVICE_ROTATION_ACTION_UNKnown,///<Unknown degrees.
	LOCAL_DEVICE_ROTATION_ACTION_0,///<0 degrees.
	LOCAL_DEVICE_ROTATION_ACTION_CLOCK90,///<90 degrees clockwise.
	LOCAL_DEVICE_ROTATION_ACTION_CLOCK180,///<180 degrees clockwise.
	LOCAL_DEVICE_ROTATION_ACTION_ANTI_CLOCK90///<90 degrees counterclockwise.
};

/*! \struct LocalVideoDeviceStatus
    \brief The status of the local video device.
    Here are more detailed structural descriptions.
*/
struct LocalVideoDeviceStatus
{
	bool working;///<Indicates whether the local video device is working.
	LocalVideoDeviceRotation rotation;///<The local video device's rotation angle
	LocalVideoDeviceStatus()
	{
		rotation = LOCAL_DEVICE_ROTATION_ACTION_0;
		working = false;
	}
};

/// \brief The video raw data callback event.
class IVideoRawDataReceiver
{
public:
	virtual ~IVideoRawDataReceiver(){}
	/// \brief The callback event for local video device started.
	/// \param device A pointer to void.
	virtual void onDeviceRunning(void* device) = 0;
	
	/// \brief The callback event for local video device stopped.
	/// \param device A pointer to void.
	virtual void onDeviceStop(void* device) = 0;
	
	/// \brief The callback event for subscribed user's video data on.
	/// \param recv_handle_list The list of the render window handles.
	virtual void onSubscribedVideoUserDataOn(IVector<unsigned long long >* recv_handle_list) = 0;
	
	/// \brief The callback event for subscribed user's video data off.
	/// \param recv_handle_list The list of the render window handles.
	virtual void onSubscribedVideoUserDataOff(IVector<unsigned long long >* recv_handle_list) = 0;
	
	/// \brief The callback event for the subscribed user left meeting.
	/// \param recv_handle_list The list of the render window handles.
	virtual void onSubscribedVideoUserLeft(IVector<unsigned long long >* recv_handle_list) = 0;
	
	/// \brief The callback event for receiving the video raw data.
	/// \param data_ The video raw data. A pointer to YUVRawDataI420. For more details, see \link YUVRawDataI420 \endlink.
	/// \param recv_handle_list The list of the render window handles.
	virtual void onVideoRawDataReceived(YUVRawDataI420* data_, IVector<unsigned long long >* recv_handle_list) = 0;
};

/// \brief Video raw data channel interface.
class IVideoRawDataChannel
{
public:
	/// \brief Start the video raw data channel service.
	/// \param mode Specifies the memory mode type. For more details, see \link RawDataMemoryMode \endlink.
	/// \param data_receiver A pointer to IVideoRawDataReceiver. Specifies the video raw data receiver. For more details, see \link IVideoRawDataReceiver \endlink.
	/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
	virtual SDKRawDataError Start(RawDataMemoryMode mode, IVideoRawDataReceiver* data_receiver) = 0;

	/// \brief Subscribe some user's video raw data.
	/// \param node_id Specifies the user's id.
	/// \param size_ Specifies the resolution of the raw data.
	/// \param recver_handle Specifies the render window handle related to the subscribing user.
	/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
	virtual SDKRawDataError Subscribe(unsigned int node_id, RawDataResolution size_, unsigned long long recver_handle) = 0;
	
	/// \brief Unsubscribe some user's video raw data.
	/// \param node_id Specifies the user's id.
	/// \param recver_handle Specifies the render window handle related to the unsubscribing user.
	/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
	virtual SDKRawDataError UnSubscribe(unsigned int node_id, unsigned long long recver_handle) = 0;
	
	/// \brief Get the status of the local video device.
	/// \param device Specifies the local video device.
	/// \param [out] status If the function succeeds, the parameter will save the status of the local video device. For more details, see \link LocalVideoDeviceStatus \endlink structure.
	/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
	virtual SDKRawDataError GetLocalDeviceStatus(void* device, LocalVideoDeviceStatus& status) = 0;
	
	/// \brief Rotate the local video device.
	/// \param device Specifies the local video device.
	/// \param rotation_flag Specifies the rotation angle of the local video device. For more details, see \link LocalVideoDeviceRotation \endlink.
	/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
	virtual SDKRawDataError RotateLocalDevice(void* device, LocalVideoDeviceRotation& rotation_flag) = 0;
	
	/// \brief Stop the video raw data channel service.
	/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
	virtual SDKRawDataError Stop() = 0;
	
	/// \brief Get the preview/running device.
	/// \param preview Determine getting the preview_device or running_device.
	/// \return the preview/running device.
	virtual void* GetRunningDevice(bool preview) = 0;
	
	/// \brief Enable the intermediate YUV raw data. Default value: FALSE
	/// \param enable TRUE indicates to enable the intermediate YUV raw data.
	/// \return If the function succeeds, the return value is SDKRawDataError_SUCCESS.
	///Otherwise failed. To get extended error information, see \link SDKRawDataError \endlink enum.
	virtual SDKRawDataError EnableIntermediateRawDataCB(bool enable) = 0;
};

/// \brief I420 YUV raw data converter interface.
class IYUVRawDataI420Converter
{
public:
	/// \brief Convert the intermediate YUV raw data to YUV raw data.
	/// \return The YUV raw data. A pointer to YUVRawDataI420. For more details, see \link YUVRawDataI420 \endlink.
	virtual YUVRawDataI420* ConvertToYUV() = 0;
	
	/// \brief Convert the intermediate YUV raw data to YUV raw data via external buffer.
	/// \param buffer Specifies the external buffer.
	/// \param size_ Specifies the size of the YUV raw data.
	/// \return The YUV raw data. A pointer to YUVRawDataI420. For more details, see \link YUVRawDataI420 \endlink.
	virtual YUVRawDataI420* ConvertToYUVViaExternalBuffer(char* buffer_, int size_) = 0;
	
	/// \brief Fill data to the pixel buffer if expanding the size of the intermediate YUV raw data.
	/// \param ybuffer_ Specifies the y-data of intermediate YUV raw data.
	/// \param ybuffer_pre_row_bytes Specifies the width of the y-data.
	/// \param uvbuffer_ Specifies the uv-data of intermediate YUV raw data.
	/// \param uvbuffer_pre_row_bytes Specifies the width of the uv-data.
	/// \param width Specifies the new width to extended.
	/// \param height Specifies the new height to extended.
	virtual void FillToPixelBuffer(char* ybuffer_, int ybuffer_pre_row_bytes, char* uvbuffer_, int uvbuffer_pre_row_bytes,int width, int height) = 0;

	virtual ~IYUVRawDataI420Converter(){}
};

END_ZOOM_RAWDATA_NAMESPACE
#endif
