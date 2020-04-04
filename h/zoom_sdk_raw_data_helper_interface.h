#ifndef _ZOOM_SDK_RAW_DATA_HELPER_INTERFACE_H_
#define _ZOOM_SDK_RAW_DATA_HELPER_INTERFACE_H_
#include "zoom_sdk_platform.h"
#include "zoom_sdk_raw_data_def.h"
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
    
    SDKRawDataError_PREPROCESS_RAWDATA_ERROR,
    SDKRawDataError_NO_DEVICE_RUNNING,
    SDKRawDataError_INIT_DEVICE,
    SDKRawDataError_VIRTUAL_DEVICE,
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

class YUVProcessDataI420
{
public:
    virtual unsigned int GetWidth() =0;
    virtual unsigned int GetHeight() = 0;
    
    virtual char* GetYBuffer(unsigned int lineNum = 0) = 0;
    virtual char* GetUBuffer(unsigned int lineNum = 0) = 0;
    virtual char* GetVBuffer(unsigned int lineNum = 0) = 0;
    
    virtual unsigned int GetYStride() = 0;
    virtual unsigned int GetUStride() = 0;
    virtual unsigned int GetVStride() = 0;
    
    virtual unsigned int GetRotation() = 0;
    virtual bool IsLimitedI420() = 0;
    virtual ~YUVProcessDataI420(){}
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
    
    virtual void onPreProcessRawData(YUVProcessDataI420* data_, IVector<unsigned long long >* recv_handle_list) = 0;
};

struct VideoCapabilityItem
{
    bool efficient;
    unsigned int width;
    unsigned int height;
    unsigned int frame;
    
    VideoCapabilityItem()
    {
        Reset();
    }
    
    VideoCapabilityItem(bool e, unsigned int w, unsigned int h, unsigned int f)
    {
        efficient = e;
        width = w;
        height = h;
        frame = f;
    }

	VideoCapabilityItem& operator=(const VideoCapabilityItem& ins)
	{
		efficient = ins.efficient;
		width = ins.width;
		height = ins.height;
		frame = ins.frame;
		return *this;
	}

	VideoCapabilityItem(const VideoCapabilityItem& ins)
	{
		*this = ins;  
	}

    void Reset()
    {
        efficient = false;
        width = 0;
        height = 0;
        frame = 0;
    }
};

class IVideoCapabilityHelper
{
public:
    virtual unsigned int GetMaxCapabilityCount() = 0;
    virtual VideoCapabilityItem GetCapability(unsigned int index) = 0;
    virtual bool SetCapability(unsigned int index, VideoCapabilityItem cap) = 0;
};

class IRawDataSender
{
public:
    virtual void SendRawData(char * data, unsigned int width, unsigned int height, unsigned int data_length, LocalVideoDeviceRotation rotation_flag = LOCAL_DEVICE_ROTATION_ACTION_UNKnown) = 0;
};

class IVirtualVideoSource
{
public:
    virtual void onInitialize(IRawDataSender *rawdata_sender, IVideoCapabilityHelper *capHelper) = 0;
    virtual void onPropertyChange(VideoCapabilityItem cap) = 0;
    virtual void onStartSend() = 0;
    virtual void onStopSend() = 0;
    virtual void onUninitialize() = 0;
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
    
    virtual SDKRawDataError RegisterRawDataPreProcessor(unsigned long long recver_handle) = 0;
    virtual SDKRawDataError UnRegisterRawDataPreProcessor(unsigned long long recver_handle) = 0;

    virtual SDKRawDataError SetExternalVideoSource(IVirtualVideoSource *video_srouce) = 0;
    
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

END_ZOOM_RAWDATA_NAMESPACE
#endif
