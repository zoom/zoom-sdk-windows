#include "RawAudioDataHandler.h"
#include <windows.h>
#include "Parameters.h"

using ZOOM_RAWDATA_NAMESPACE::IAudioRawDataChannel;
using ZOOM_RAWDATA_NAMESPACE::RawDataMemoryMode;
using ZOOM_RAWDATA_NAMESPACE::SDKRawDataError;
using ZOOM_RAWDATA_NAMESPACE::AudioRawData;
using std::ios;

namespace {
void LogAudioRawData(AudioRawData *data) {
  TCHAR szLog[MAX_PATH] = {0};

  bool canAddRef = data ? data->CanAddRef() : false;
  unsigned int bufLen = data ? data->GetBufferLen() : 0;
  unsigned int sampleRate = data ? data->GetSampleRate() : 0;
  unsigned int channelNum = data ? data->GetChannelNum() : 0;
  char *buffer = data ? data->GetBuffer() : nullptr;

  wsprintf(szLog, _T("data=%p, len: %d, rate: %d, chanNum: %d, buf:%p\r\n"),
           data, bufLen, sampleRate, channelNum, buffer);
  OutputDebugString(szLog);
}
}

RawAudioDataHandler::RawAudioDataHandler(IAudioRawDataChannel *pAudioChannel)
    : m_pAudioChannel(pAudioChannel) {
  std::wstring wszPath = wszRecordPath;
  wszPath.append(std::wstring(L"\\audio.bin"));
	m_AudioFile.open(wszPath, ios::out | ios::app | ios::binary);
}

bool RawAudioDataHandler::Start() {
  SDKRawDataError err =
      m_pAudioChannel->Start(RawDataMemoryMode::RawDataMemoryMode_Stack, this);
  if (err != SDKRawDataError::SDKRawDataError_SUCCESS) {
    TCHAR szLog[MAX_PATH] = {0};
    wsprintf(szLog, _T("AudioChannel::Start:ret=%d\r\n"), err);
    OutputDebugString(szLog);
  }
  return err == SDKRawDataError::SDKRawDataError_SUCCESS;
}

void RawAudioDataHandler::onMixedAudioRawDataReceived(AudioRawData *data) {
  TCHAR szLog[MAX_PATH] = {0};
  wsprintf(szLog, _T("MixedAudio "));
  OutputDebugString(szLog);

  LogAudioRawData(data);
	if (m_AudioFile.is_open() && data) {
		m_AudioFile.write(data->GetBuffer(), data->GetBufferLen());
	}
}

void RawAudioDataHandler::onOneWayAudioRawDataReceived(AudioRawData *data,
                                                       unsigned int node_id) {
  TCHAR szLog[MAX_PATH] = {0};
  wsprintf(szLog, _T("OneWay::node_id=%d\r\n"), node_id);
  OutputDebugString(szLog);

  LogAudioRawData(data);
}

void RawAudioDataHandler::Stop() {
	if (m_AudioFile.is_open()) {
		m_AudioFile.close();
	}
  if (m_pAudioChannel) {
    m_pAudioChannel->Stop();
  }
  m_pAudioChannel = nullptr;
}
