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
    \brief status of live stream
    A more detailed struct description.
*/
enum LiveStreamStatus 
{
	LiveStreamStatus_None,///< None
	LiveStreamStatus_InProgress,///< in progress
	LiveStreamStatus_Connecting,///< connecting
	LiveStreamStatus_Start_Failed_Timeout,///< connect live stream timeout
	LiveStreamStatus_Start_Failed,///< connect live stream failed
	LiveStreamStatus_Ended,///< ended
};

/// \brief Meeting live stream controller callback event
///
class IMeetingLiveStreamCtrlEvent
{
public:
	/// \brief live stream status changed callback
	/// \param status live stream status.
	virtual void onLiveStreamStatusChange(LiveStreamStatus status) = 0;
};

/// \brief Meeting live stream item of current meeting
///
class IMeetingLiveStreamItem
{
public:
	/// \brief Get url of live stream
	/// \return If the function succeeds, the return value is the url of live stream.
	virtual const wchar_t* GetLiveStreamURL() = 0;

	/// \brief Get description of live stream
	/// \return If the function succeeds, the return value is the description of live stream.
	virtual const wchar_t* GetLiveStreamURLDescription() = 0;
	virtual ~IMeetingLiveStreamItem() {};
};

/// \brief Meeting live stream controller interface
///
class IMeetingLiveStreamController
{
public:
	/// \brief Set meeting live stream callback event
	/// \param pEvent A pointer to a IMeetingLiveStreamCtrlEvent* that receives live stream event. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError SetEvent(IMeetingLiveStreamCtrlEvent* pEvent) = 0;

	/// \brief Check can start live stream or not
	/// \return If can start live stream, the return value is SDKErr_Success.
	///If can't, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError CanStartLiveStream() = 0;

	/// \brief Start live stream
	/// \param item_ A pointer to a IMeetingLiveStreamItem*, get this via GetSupportLiveStreamURL API. 
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StartLiveStream(IMeetingLiveStreamItem* item_) = 0;

	/// \brief Start live stream
	/// \param streamingURL url of live stream
	/// \param streamingKey key of live stream
	/// \param broadcastURL broadcast url of live stream
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	///you get these parameters from third party live stream service
	virtual SDKError StartLiveStreamWithSteamingURL(const wchar_t* streamingURL, const wchar_t* streamingKey, const wchar_t* broadcastURL) = 0;

	/// \brief Stop live stream
	/// \return If the function succeeds, the return value is SDKErr_Success.
	///If the function fails, the return value is not SDKErr_Success. To get extended error information, refer to SDKError enum.
	virtual SDKError StopLiveStream() = 0;

	/// \brief Get meeting live stream information list of current meeting
	/// \return the return value is current meeting all live stream information list.if not in meeting, return NULL.
	virtual IList<IMeetingLiveStreamItem* >* GetSupportLiveStreamURL() = 0;

	/// \brief Get live stream status of current meeting.
	/// \return If the function succeeds, the return value is the live stream status of current meeting, refer to LiveStreamStatus.
	virtual LiveStreamStatus GetCurrentLiveStreamStatus() = 0;
};
END_ZOOM_SDK_NAMESPACE
#endif