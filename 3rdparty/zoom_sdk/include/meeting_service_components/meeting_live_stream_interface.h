/*!
* \file meeting_live_stream_interface.h
* \brief Meeting Service Live Streaming Interface.
* 
*/
#ifndef _MEETING_LIVE_STREAM_INTERFACE_H_
#define _MEETING_LIVE_STREAM_INTERFACE_H_
#include "..\zoom_sdk_def.h"

BEGIN_ZOOM_SDK_NAMESPACE

/*! \enum LiveStreamStatus
    \brief Status of live stream.
    Here are more detailed structural descriptions.
*/
enum LiveStreamStatus 
{
	LiveStreamStatus_None,///<Only for initialization.
	LiveStreamStatus_InProgress,///<In progress.
	LiveStreamStatus_Connecting,///<Be connecting.
	LiveStreamStatus_Start_Failed_Timeout,///<Connect timeout.
	LiveStreamStatus_Start_Failed,///<Failed to start live streaming. 
	LiveStreamStatus_Ended,///<Live stream ends.
};

/// \brief Live stream meeting controller callback event.
///
class IMeetingLiveStreamCtrlEvent
{
public:
	/// \brief Callback event that live stream status changes.
	/// \param status Live stream status. For more details, see \link LiveStreamStatus \endlink enum.
	virtual void onLiveStreamStatusChange(LiveStreamStatus status) = 0;
};

/// \brief Live stream of current meeting.
///
class IMeetingLiveStreamItem
{
public:
	/// \brief Get URL of the live stream meeting.
	/// \return If the function succeeds, the return value is the URL of the live stream meeting.
	virtual const wchar_t* GetLiveStreamURL() = 0;

	/// \brief Get the descriptions of live stream.
	/// \return If the function succeeds, the return value is the description of live stream.
	virtual const wchar_t* GetLiveStreamURLDescription() = 0;
	virtual ~IMeetingLiveStreamItem() {};
};

/// \brief Live stream meeting controller interface.
///
class IMeetingLiveStreamController
{
public:
	/// \brief Set live stream meeting callback event handler
	/// \param pEvent A pointer to the IMeetingLiveStreamCtrlEvent that receives live stream event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError SetEvent(IMeetingLiveStreamCtrlEvent* pEvent) = 0;

	/// \brief Determine if it is able to start live streaming.
	/// \return If it is enabled to start the live streaming, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError CanStartLiveStream() = 0;

	/// \brief Start live streaming.
	/// \param item_ A pointer to the IMeetingLiveStreamItem created via IMeetingLiveStreamController::GetSupportLiveStreamURL() API. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StartLiveStream(IMeetingLiveStreamItem* item_) = 0;

	/// \brief Start live streaming.
	/// \param streamingURL The URL of live streaming.
	/// \param streamingKey The key of live streaming. 
	/// \param broadcastURL The broadcast URL of live-stream.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	/// \remarks Get the parameters from the third party of live stream service
	virtual SDKError StartLiveStreamWithSteamingURL(const wchar_t* streamingURL, const wchar_t* streamingKey, const wchar_t* broadcastURL) = 0;

	/// \brief Stop live streaming.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///Otherwise failed. To get extended error information, see \link SDKError \endlink enum.
	virtual SDKError StopLiveStream() = 0;

	/// \brief Get the list of URL and associated information used by live streaming in the current meeting. 
	/// \return If the function succeeds, the return value is the meeting information to be live streamed.
	///Otherwise failed, the return value is NULL. For more details, see \link IMeetingLiveStreamItem \endlink.
	virtual IList<IMeetingLiveStreamItem* >* GetSupportLiveStreamURL() = 0;

	/// \brief Get live stream status of current meeting.
	/// \return If the function succeeds, the return value is the live stream status of current meeting.  
	///Otherwise failed. For more details, see \link LiveStreamStatus \endlink enum.
	virtual LiveStreamStatus GetCurrentLiveStreamStatus() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif