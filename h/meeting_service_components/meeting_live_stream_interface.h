/*!
* \file meeting_sharing_interface.h
* \brief Sharing of Meeting Service Interface
* 
*/
#ifndef _MEETING_LIVE_STREAM_INTERFACE_H_
#define _MEETING_LIVE_STREAM_INTERFACE_H_
#include "..\zoom_sdk_def.h"

/// \brief Zoom SDK Namespace
/// 
///
BEGIN_ZOOM_SDK_NAMESPACE
/*! \enum LiveStreamStatus
    \brief Live stream status.
    A more detailed struct description.
*/
enum LiveStreamStatus 
{
	LiveStreamStatus_None,
	LiveStreamStatus_InProgress,
	LiveStreamStatus_Connecting,
	LiveStreamStatus_Start_Failed_Timeout,
	LiveStreamStatus_Start_Failed,
	LiveStreamStatus_Ended,
};

/// \brief Meeting live stream controller callback event
///
class IMeetingLiveStreamCtrlEvent
{
public:
	/// \brief Live stream status notify callback
	/// \param status Live stream status value.
	virtual void onLiveStreamStatusChange(LiveStreamStatus status) = 0;
};

/// \brief Meeting live stream information item Interface
///
class IMeetingLiveStreamItem
{
public:
	/// \brief Get live stream url
	/// \return If the function succeeds, the return value is the live stream url.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetLiveStreamURL() = 0;

	/// \brief Get description of live stream
	/// \return If the function succeeds, the return value is the description of live stream.
	///If the function fails, the return value is NULL.
	virtual const wchar_t* GetLiveStreamURLDescription() = 0;
	virtual ~IMeetingLiveStreamItem() {};
};

/// \brief Meeting live stream controller interface
///
class IMeetingLiveStreamController
{
public:
	/// \brief Set live stream controller callback event
	/// \param pEvent A pointer to a IMeetingLiveStreamCtrlEvent* that receives live stream event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingLiveStreamCtrlEvent* pEvent) = 0;

	/// \brief can start live stream or not.
	/// \return can start live stream or not.
	virtual SDKError CanStartLiveStream() = 0;

	/// \brief Start live stream.
	/// \param item_ the live stream item to start, you can get this from GetSupportLiveStreamURL
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StartLiveStream(IMeetingLiveStreamItem* item_) = 0;

	/// \brief Start live stream.
	/// \param streamingURL streaming url
	/// \param streamingKey streaming key
	/// \param broadcastURL broadcast url
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StartLiveStreamWithSteamingURL(const wchar_t* streamingURL, const wchar_t* streamingKey, const wchar_t* broadcastURL) = 0;

	/// \brief Stop live stream.
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StopLiveStream() = 0;

	/// \brief Get meeting live stream item list
	/// \return the return value is all live stream item list of current meeting.if don't have, return NULL.
	virtual IList<IMeetingLiveStreamItem* >* GetSupportLiveStreamURL() = 0;

	/// \brief Get current live stream status
	/// \return the status of current live stream.
	virtual LiveStreamStatus GetCurrentLiveStreamStatus() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif