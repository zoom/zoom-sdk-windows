#pragma once

#include <iostream>
#include <fstream>
#include <set>
#include "zoom_sdk_raw_data_helper_interface.h"

class RawVideoDataHandler
    : public ZOOM_RAWDATA_NAMESPACE::IVideoRawDataReceiver {
public:
  RawVideoDataHandler(
      ZOOM_RAWDATA_NAMESPACE::IVideoRawDataChannel *pVideoChannel);

  virtual ~RawVideoDataHandler() = default;

  // The specified device starts running and the parameter is the pointer of the
  // device, given by the callback function. This callback is used to notifying
  // the user that SDK starts getting video data on a device. Usually, it is
  // used for the preview screen before actually join a meeting.
  void onDeviceRunning(void *device) override;

  // The callback for the event when the specified device stops running.
  void onDeviceStop(void *device) override;

  // The callback for the event when the video of the subscriber is on. The
  // parameter is a list of all pointers that are subscribing to watch the
  // subscriber's video
  void
  onSubscribedVideoUserDataOn(IVector<unsigned long long> *recv_handle_list) override;

  // The callback for the event when the video of the subscriber is off. The
  // parameter is a list of all pointers that are subscribing to watch the
  // subscriber's video
  void
  onSubscribedVideoUserDataOff(IVector<unsigned long long> *recv_handle_list) override;

  // The callback for the event when the subscriber leaves the meeting. The
  // parameter is a list of all pointers that are subscribing to watch the
  // subscriber's video
  void
  onSubscribedVideoUserLeft(IVector<unsigned long long> *recv_handle_list) override;

  // The callback for receiving raw video data. The first parameter is the raw
  // data in YUV420 format, and the second parameter is a list of all pointers
  // that are subscribing to watch the subscriber's video
  void
  onVideoRawDataReceived(ZOOM_RAWDATA_NAMESPACE::YUVRawDataI420 *data_,
                         IVector<unsigned long long> *recv_handle_list) override;

  // true if it succeeds, false otherwise.
  bool Start();

  void Stop();


  bool Subscribe(unsigned int node_id, ZOOM_RAWDATA_NAMESPACE::RawDataResolution size_, unsigned long long recver_handle);
  bool UnSubscribe(unsigned int node_id, unsigned long long recver_handle);


private:
  std::set<unsigned int> m_subscriptions;
  ZOOM_RAWDATA_NAMESPACE::IVideoRawDataChannel* m_pVideoChannel{ nullptr };
  std::ofstream m_VideoFile;
  std::ofstream m_VideoMetaFile;
};
