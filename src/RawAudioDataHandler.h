#pragma once

#include <iostream>
#include <fstream>
#include "zoom_sdk_raw_data_helper_interface.h"

class RawAudioDataHandler
  : public ZOOM_RAWDATA_NAMESPACE::IAudioRawDataReceiver {
public:
  RawAudioDataHandler(
    ZOOM_RAWDATA_NAMESPACE::IAudioRawDataChannel* pAudioChannel);

  virtual ~RawAudioDataHandler() = default;

  // The data returned by this callback is the mixed audio raw data
  virtual void
    onMixedAudioRawDataReceived(ZOOM_RAWDATA_NAMESPACE::AudioRawData* data_);
  // The data returned by this callback is the audio raw data of a specified ID
  virtual void
    onOneWayAudioRawDataReceived(ZOOM_RAWDATA_NAMESPACE::AudioRawData* data_,
      unsigned int node_id);

  // true if it succeeds, false otherwise.
  bool Start();

  void Stop();

private:
  ZOOM_RAWDATA_NAMESPACE::IAudioRawDataChannel* m_pAudioChannel{ nullptr };
	std::ofstream m_AudioFile;
};
