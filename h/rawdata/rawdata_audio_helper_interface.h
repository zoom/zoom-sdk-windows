#ifndef _RAWDATA_AUDIO_HELPER_INTERFACE_H_
#define _RAWDATA_AUDIO_HELPER_INTERFACE_H_
#include "../zoom_sdk_def.h"

class AudioRawData;

BEGIN_ZOOM_SDK_NAMESPACE
class IZoomSDKAudioRawDataDelegate
{
public:
	~IZoomSDKAudioRawDataDelegate(){}
	virtual void onMixedAudioRawDataReceived(AudioRawData* data_) = 0;
	virtual void onOneWayAudioRawDataReceived(AudioRawData* data_, uint32_t node_id) = 0;
};

class IZoomSDKAudioRawDataHelper
{
public:
	virtual ~IZoomSDKAudioRawDataHelper(){}
	virtual SDKError subscribe(IZoomSDKAudioRawDataDelegate* pDelegate) = 0;
	virtual SDKError unSubscribe() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif