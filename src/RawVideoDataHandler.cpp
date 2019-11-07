#include "RawVideoDataHandler.h"
#include <windows.h>
#include "Parameters.h"

using ZOOM_RAWDATA_NAMESPACE::IVideoRawDataChannel;
using ZOOM_RAWDATA_NAMESPACE::RawDataMemoryMode;
using ZOOM_RAWDATA_NAMESPACE::SDKRawDataError;
using ZOOM_RAWDATA_NAMESPACE::YUVRawDataI420;
using std::ios;

RawVideoDataHandler::RawVideoDataHandler(IVideoRawDataChannel *pVideoChannel)
    : m_pVideoChannel(pVideoChannel) {
  std::wstring wszPath = wszRecordPath;
  wszPath.append(std::wstring(L"\\video.bin"));
  m_VideoFile.open(wszPath,
                   ios::out | ios::app | ios::binary);

  wszPath = wszRecordPath;
  wszPath.append(std::wstring(L"\\video.meta"));
  m_VideoMetaFile.open(wszPath,
                       ios::out | ios::app | ios::binary);
}

bool RawVideoDataHandler::Start() {
  SDKRawDataError err =
      m_pVideoChannel->Start(RawDataMemoryMode::RawDataMemoryMode_Heap, this);
  if (err != SDKRawDataError::SDKRawDataError_SUCCESS) {
    TCHAR szLog[MAX_PATH] = {0};
    wsprintf(szLog, _T("VideoChannel::Start:ret=%d\r\n"), err);
    OutputDebugString(szLog);
  }
  return err == SDKRawDataError::SDKRawDataError_SUCCESS;
}

void RawVideoDataHandler::onDeviceRunning(void *device) {
  TCHAR szLog[MAX_PATH] = {0};
  wsprintf(szLog, _T("Video::onDeviceRunning:device=%p\r\n"), device);
  OutputDebugString(szLog);
}

void RawVideoDataHandler::onDeviceStop(void *device) {
  TCHAR szLog[MAX_PATH] = {0};
  wsprintf(szLog, _T("Video::onDeviceStop:device=%p\r\n"), device);
  OutputDebugString(szLog);
}

void RawVideoDataHandler::onSubscribedVideoUserDataOn(
    IVector<unsigned long long> *recv_handle_list) {

  TCHAR szLog[MAX_PATH] = {0};
  int pos =
      wsprintf(szLog, _T("RawVideoDataHandler::onSubscribedVideoUserDataOn "));
  if (!recv_handle_list) {
    return;
  }

  for (int i = 0; i < recv_handle_list->GetCount(); i++) {
    pos +=
        wsprintf(szLog + pos, _T("%d "), (int)(recv_handle_list->GetItem(i)));
  }
  wsprintf(szLog + pos, _T("\r\n"));
  OutputDebugString(szLog);
}

void RawVideoDataHandler::onSubscribedVideoUserDataOff(
    IVector<unsigned long long> *recv_handle_list) {
  TCHAR szLog[MAX_PATH] = {0};
  int pos =
      wsprintf(szLog, _T("RawVideoDataHandler::onSubscribedVideoUserDataOff "));
  if (!recv_handle_list) {
    return;
  }

  for (int i = 0; i < recv_handle_list->GetCount(); i++) {
    pos +=
        wsprintf(szLog + pos, _T("%d "), (int)(recv_handle_list->GetItem(i)));
  }
  wsprintf(szLog + pos, _T("\r\n"));
  OutputDebugString(szLog);
}

void RawVideoDataHandler::onSubscribedVideoUserLeft(
    IVector<unsigned long long> *recv_handle_list) {
  TCHAR szLog[MAX_PATH] = {0};
  int pos =
      wsprintf(szLog, _T("RawVideoDataHandler::onSubscribedVideoUserLeft "));
  if (!recv_handle_list) {
    return;
  }

  for (int i = 0; i < recv_handle_list->GetCount(); i++) {
    pos +=
        wsprintf(szLog + pos, _T("%d "), (int)(recv_handle_list->GetItem(i)));
  }
  wsprintf(szLog + pos, _T("\r\n"));
  OutputDebugString(szLog);
}

void RawVideoDataHandler::onVideoRawDataReceived(
    YUVRawDataI420 *data, IVector<unsigned long long> *recv_handle_list) {
  TCHAR szLog[MAX_PATH] = {0};
  int pos = wsprintf(szLog, _T("RawVideoDataHandler::onVideoRawDataReceived "));
  if (!recv_handle_list) {
    return;
  }

  for (int i = 0; i < recv_handle_list->GetCount(); i++) {
    pos += wsprintf(szLog + pos, _T("%d"), (int)(recv_handle_list->GetItem(i)));
  }
  wsprintf(szLog + pos, _T("\r\n"));
  OutputDebugString(szLog);

  if (m_VideoFile.is_open() && data) {
    m_VideoFile.write(data->GetBuffer(), data->GetBufferLen());
    char meta[MAX_PATH] = {0};

    int pos = sprintf(
        meta, "len:%d,node_count:%d,source:%d,height:%d,width:%d\r\n",
        data->GetBufferLen(), recv_handle_list->GetCount(), data->GetSourceID(),
        data->GetStreamHeight(), data->GetStreamWidth());
    m_VideoMetaFile.write(meta, pos + 1);
  }
}

void RawVideoDataHandler::Stop() {
  if (m_pVideoChannel) {
    m_pVideoChannel->Stop();
    m_pVideoChannel = nullptr;
  }

  if (m_VideoFile.is_open()) {
    m_VideoFile.close();
  }
}

bool RawVideoDataHandler::Subscribe(
    unsigned int node_id, ZOOM_RAWDATA_NAMESPACE::RawDataResolution size_,
    unsigned long long recver_handle) {
  if (m_subscriptions.find(node_id) != m_subscriptions.end()) {
    return true;
  }
  TCHAR szLog[MAX_PATH] = {0};
  wsprintf(szLog, _T("RawVideoDataHandler::Subscribe %d\r\n", node_id));
  OutputDebugString(szLog);

  bool ret = m_pVideoChannel &&
             m_pVideoChannel->Subscribe(node_id, size_, recver_handle) ==
                 SDKRawDataError::SDKRawDataError_SUCCESS;

  if (ret) {
    m_subscriptions.insert(node_id);
  }

  return ret;
}

bool RawVideoDataHandler::UnSubscribe(unsigned int node_id,
                                      unsigned long long recver_handle) {
  if (m_subscriptions.find(node_id) == m_subscriptions.end()) {
    return true;
  }

  TCHAR szLog[MAX_PATH] = {0};
  wsprintf(szLog, _T("RawVideoDataHandler::UnSubscribe %d\r\n", node_id));
  OutputDebugString(szLog);

  bool ret = m_pVideoChannel &&
             m_pVideoChannel->UnSubscribe(node_id, recver_handle) ==
                 SDKRawDataError::SDKRawDataError_SUCCESS;

  if (ret) {
    m_subscriptions.erase(node_id);
  }

  return ret;
}
