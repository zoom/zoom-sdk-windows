#ifndef _ZOOM_SDK_RAW_DATA_HELPER_INTERFACE_H_
#define _ZOOM_SDK_RAW_DATA_HELPER_INTERFACE_H_
#include "zoom_sdk_platform.h"
BEGIN_ZOOM_RAWDATA_NAMESPACE
class IAudioRawDataChannel;
class IVideoRawDataChannel;
class IShareRawDataChannel;
enum SDKRawDataError
{
	SDKRawDataError_SUCCESS,
	SDKRawDataError_UNINITIALIZED,
	SDKRawDataError_MALLOC_FAILED,
	SDKRawDataError_WRONGUSAGE,
	SDKRawDataError_INVALID_PARAM,
	SDKRawDataError_NOT_IN_MEETING,
	SDKRawDataError_NO_LICENSE,
	
	SDKRawDataError_VIDEO_MODULE_NOT_READY,
	SDKRawDataError_VIDEO_MODULE_ERROR,
	SDKRawDataError_VIDEO_DEVICE_ERROR,
	SDKRawDataError_NO_VIDEO_DATA,

	SDKRawDataError_SHARE_MODULE_NOT_READY,
	SDKRawDataError_SHARE_MODULE_ERROR,
	SDKRawDataError_NO_SHARE_DATA,

	SDKRawDataError_AUDIO_MODULE_NOT_READY,
	SDKRawDataError_AUDIO_MODULE_ERROR,
	SDKRawDataError_NO_AUDIO_DATA,
};
#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

ZOOMSDK_MODULE_API SDKRawDataError HasRawDataLicense();
ZOOMSDK_MODULE_API SDKRawDataError RetrieveAudioRawDataChannel(IAudioRawDataChannel** pp_channel);
ZOOMSDK_MODULE_API SDKRawDataError RetrieveVideoRawDataChannel(IVideoRawDataChannel** pp_channel);
ZOOMSDK_MODULE_API SDKRawDataError RetrieveShareRawDataChannel(IShareRawDataChannel** pp_channel);

#ifdef __cplusplus
};
#endif //__cplusplus

enum RawDataMemoryMode
{
	RawDataMemoryMode_Stack,
	RawDataMemoryMode_Heap,
};
enum RawDataResolution
{
	RawDataResolution_90,
	RawDataResolution_180,
	RawDataResolution_360,
	RawDataResolution_720,
#if (defined _WIN32) || (defined __MACOS__)
	RawDataResolution_1080,
#endif
};
class YUVRawDataI420
{
public:
	virtual bool CanAddRef() = 0;
	virtual bool AddRef() = 0;
	virtual int Release() = 0;
	virtual char* GetYBuffer() = 0;
	virtual char* GetUBuffer() = 0;
	virtual char* GetVBuffer() = 0;
	virtual char* GetBuffer() = 0;
	virtual unsigned int GetBufferLen() = 0;
	virtual bool IsLimitedI420() = 0;
	virtual unsigned int GetStreamWidth() =0;
	virtual unsigned int GetStreamHeight() = 0;
	virtual unsigned int GetRotation() = 0;
	virtual unsigned int GetSourceID() = 0;
	virtual ~YUVRawDataI420(){}
};

class AudioRawData
{
public:
	virtual bool CanAddRef() = 0;
	virtual bool AddRef() = 0;
	virtual int Release() = 0;
	virtual char* GetBuffer() = 0;
	virtual unsigned int GetBufferLen() = 0;
	virtual unsigned int GetSampleRate() = 0;
	virtual unsigned int GetChannelNum() = 0;
	virtual ~AudioRawData(){}
};

class IAudioRawDataReceiver
{
public:
	virtual ~IAudioRawDataReceiver(){}
	virtual void onMixedAudioRawDataReceived(AudioRawData* data_) = 0;
	virtual void onOneWayAudioRawDataReceived(AudioRawData* data_, unsigned int node_id) = 0;
};

class IAudioRawDataChannel
{
public:
	virtual SDKRawDataError Start(RawDataMemoryMode mode, IAudioRawDataReceiver* data_receiver) = 0;
	virtual SDKRawDataError Stop() = 0;
};

class IShareRawDataReceiver
{
public:
	virtual ~IShareRawDataReceiver(){}
	virtual void onShareRawDataReceived(YUVRawDataI420* data_, IVector<unsigned long long >* recv_handle_list) = 0;
	virtual void onSubscribedShareUserDataOn(IVector<unsigned long long >* recv_handle_list) = 0;
	virtual void onSubscribedShareUserDataOff(IVector<unsigned long long >* recv_handle_list) = 0;
	virtual void onSubscribedShareUserLeft(IVector<unsigned long long >* recv_handle_list) = 0;
};

class IShareRawDataChannel
{
public:
	virtual SDKRawDataError Start(RawDataMemoryMode mode, IShareRawDataReceiver* data_receiver) = 0;
	virtual SDKRawDataError Subscribe(unsigned int node_id, RawDataResolution size_, unsigned long long recver_handle) = 0;
	virtual SDKRawDataError UnSubscribe(unsigned int node_id, unsigned long long recver_handle) = 0;
	virtual SDKRawDataError Stop() = 0;
};

enum LocalVideoDeviceRotation
{
	LOCAL_DEVICE_ROTATION_ACTION_UNKnown,
	LOCAL_DEVICE_ROTATION_ACTION_0,
	LOCAL_DEVICE_ROTATION_ACTION_CLOCK90,
	LOCAL_DEVICE_ROTATION_ACTION_CLOCK180,
	LOCAL_DEVICE_ROTATION_ACTION_ANTI_CLOCK90
};

struct LocalVideoDeviceStatus
{
	bool working;
	LocalVideoDeviceRotation rotation;
	LocalVideoDeviceStatus()
	{
		rotation = LOCAL_DEVICE_ROTATION_ACTION_0;
		working = false;
	}
};

class IVideoRawDataReceiver
{
public:
	virtual ~IVideoRawDataReceiver(){}
	virtual void onDeviceRunning(void* device) = 0;
	virtual void onDeviceStop(void* device) = 0;
	virtual void onSubscribedVideoUserDataOn(IVector<unsigned long long >* recv_handle_list) = 0;
	virtual void onSubscribedVideoUserDataOff(IVector<unsigned long long >* recv_handle_list) = 0;
	virtual void onSubscribedVideoUserLeft(IVector<unsigned long long >* recv_handle_list) = 0;
	virtual void onVideoRawDataReceived(YUVRawDataI420* data_, IVector<unsigned long long >* recv_handle_list) = 0;
};

class IVideoRawDataChannel
{
public:
	virtual SDKRawDataError Start(RawDataMemoryMode mode, IVideoRawDataReceiver* data_receiver) = 0;

	virtual SDKRawDataError Subscribe(unsigned int node_id, RawDataResolution size_, unsigned long long recver_handle) = 0;
	virtual SDKRawDataError UnSubscribe(unsigned int node_id, unsigned long long recver_handle) = 0;
	virtual SDKRawDataError GetLocalDeviceStatus(void* device, LocalVideoDeviceStatus& status) = 0;
	virtual SDKRawDataError RotateLocalDevice(void* device, LocalVideoDeviceRotation& rotation_flag) = 0;
	virtual SDKRawDataError Stop() = 0;
};

END_ZOOM_RAWDATA_NAMESPACE
#endif
