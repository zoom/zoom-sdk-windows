#pragma once
#define PROXY_DETECT_LOGIC
#include "AuthServiceMgr.h"
#include "MeetingServiceMgr.h"
#include "zoom_sdk.h"
#include "network_connection_handler_interface.h"

class CAuthServiceMgr;
class CPreMeetingServiceMgr;
class CMeetingServiceMgr;
class CMessageWnd;

class CDemoUI : public IAuthServiceMgrEvent, public IMeetingserviceMgrEvent {
public:
  CDemoUI();
  virtual ~CDemoUI();

  //
  virtual void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret);
  virtual void onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS status,
                          ZOOM_SDK_NAMESPACE::IAccountInfo *pAccountInfo);
  virtual void onLogout() {}

  //
  virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status,
                                      int iResult = 0);
  virtual void onRecording2MP4Done(bool bsuccess, int iResult,
                                   const wchar_t *szPath){};
  virtual void onRecording2MP4Processing(int iPercentage){};
  virtual void onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int> *lstUserID,
                          const wchar_t *strUserList = NULL);
  virtual void onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int> *lstUserID,
                          const wchar_t *strUserList = NULL);
  virtual void onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status,
                               unsigned int userId);
  virtual void onUserAudioStatusChange(
      ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus *>
          *lstAudioStatusChange,
      const wchar_t *strAudioStatusList = NULL){};
  virtual void onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status){};
  virtual void onChatMsgNotifcation(ZOOM_SDK_NAMESPACE::IChatMsgInfo *chatMsg,
                                    const wchar_t *ccc){};
  virtual void
  onUserVideoStatusChange(unsigned int userId,
                          ZOOM_SDK_NAMESPACE::VideoStatus status){};
  virtual void onHostChangeNotification(unsigned int userId){};
  virtual void onSpotlightVideoChangeNotification(bool bSpotlight,
                                                  unsigned int userid){};
  virtual void onRecordPriviligeChanged(bool bCanRec){};
  virtual void onLowOrRaiseHandStatusChanged(bool bLow, unsigned int userid){};
  virtual void
  onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status,
                        unsigned int userId);
  virtual void onCustomizedLocalRecordingSourceNotification(
      ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper *layout_helper);

  bool NormalUserStart(const std::wstring &strMeetingNumber);

  bool SDKInit(const std::wstring &strWebDomain);
  bool SDKAuth();
  bool Login(const std::wstring &ssoToken, const std::wstring &email,
             const std::wstring &password);
  bool APIUserStart(const std::wstring &strMeetingNumber,
                    const std::wstring &strUserToken,
                    const std::wstring &strUserName,
                    const std::wstring &strUserId,
                    const std::wstring &strAccessToken);
  bool APIUserJoin(const std::wstring &strMeetingNumber,
                   const std::wstring &strUserToken,
                   const std::wstring &strUserName);
  bool Leave();
  bool End();
  bool MuteVideo();
  bool UnmuteVideo();
  bool MuteAudio(int userId);
  bool UnMuteAudio(int userId);
  LRESULT Destroy();

private:
  CAuthServiceMgr *m_pAuthServiceMgr;
  CPreMeetingServiceMgr *m_preMeetingServiceMgr;
  CMeetingServiceMgr *m_pMeetingServiceMgr;
  bool m_bStar;
  bool m_bSDKInit;
  std::wstring m_strWebDomain;
  ZOOM_SDK_NAMESPACE::INetworkConnectionHelper *m_pNetworkConnectionHelper;
};
