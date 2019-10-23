#include <string>
#include "DemoUI.h"
#include "AuthServiceMgr.h"
#include "PreMeetingServiceMgr.h"
#include "MeetingServiceMgr.h"
#include "Parameters.h"
#define PROXY_DETECT_LOGIC
CDemoUI::CDemoUI() {
  m_pAuthServiceMgr = new CAuthServiceMgr(this);
  m_preMeetingServiceMgr = new CPreMeetingServiceMgr(this);
  m_pMeetingServiceMgr = new CMeetingServiceMgr(this);
  m_bStar = true;
  m_bSDKInit = false;
  m_pNetworkConnectionHelper = NULL;
}

CDemoUI::~CDemoUI() {
  if (m_pAuthServiceMgr) {
    delete m_pAuthServiceMgr;
    m_pAuthServiceMgr = NULL;
  }

  if (m_preMeetingServiceMgr) {
    delete m_preMeetingServiceMgr;
    m_preMeetingServiceMgr = NULL;
  }

  if (m_pMeetingServiceMgr) {
    delete m_pMeetingServiceMgr;
    m_pMeetingServiceMgr = NULL;
  }

  m_bStar = true;

  m_bSDKInit = false;
}

bool CDemoUI::SDKInit(const std::wstring &strWebDomain) {
  if (!m_pAuthServiceMgr || !strWebDomain.size())
    return false;

  m_strWebDomain = strWebDomain;

  if (!m_bSDKInit) {
    ZOOM_SDK_NAMESPACE::InitParam initParam;
    initParam.strWebDomain = m_strWebDomain.c_str();
    initParam.strSupportUrl = L"https://zoom.us";
    initParam.enableLogByDefault = bLogging;
#if (defined ENABLE_CUSTOMIZED_UI)
    initParam.obConfigOpts.optionalFeatures = ENABLE_CUSTOMIZED_UI_FLAG;
#endif
    m_bSDKInit = CSDKHelper::Init(initParam);
  }

  class CNetwrokHelperSink
      : public ZOOM_SDK_NAMESPACE::INetworkConnectionHandler {
  public:
    virtual void onProxyDetectComplete() {}
    virtual void onProxySettingNotification(
        ZOOM_SDK_NAMESPACE::IProxySettingHandler *handler) {
      // todo
    }
    virtual void onSSLCertVerifyNotification(
        ZOOM_SDK_NAMESPACE::ISSLCertVerificationHandler *handler) {
      if (handler)
        handler->Trust();
      // todo
    }

    CDemoUI *m_pDemo;
  };
  static CNetwrokHelperSink s_networksink;
  s_networksink.m_pDemo = this;
  ZOOM_SDK_NAMESPACE::CreateNetworkConnectionHelper(
      &m_pNetworkConnectionHelper);
  if (m_pNetworkConnectionHelper) {
    m_pNetworkConnectionHelper->RegisterNetworkConnectionHandler(
        &s_networksink);
  }

  return true;
}

bool CDemoUI::SDKAuth() {
  if (!m_pAuthServiceMgr)
    return false;

  if (wszSdkKey.length() <= 0 || wszSdkSecret.length() <= 0)
    return false;

  if (!m_bSDKInit) {
    return false;
  }

  ZOOM_SDK_NAMESPACE::AuthParam authParam;
  authParam.appKey = wszSdkKey.c_str();
  authParam.appSecret = wszSdkSecret.c_str();
  m_pAuthServiceMgr->Init();
  return m_pAuthServiceMgr->SDKAuth(authParam);
}

bool CDemoUI::APIUserStart(const std::wstring &strMeetingNumber,
                           const std::wstring &strUserToken,
                           const std::wstring &strUserName,
                           const std::wstring &strUserId,
                           const std::wstring &strAccessToken) {
  if (strMeetingNumber.length() <= 0 || strUserId.length() <= 0 ||
      strUserToken.length() <= 0 || strUserName.length() <= 0 ||
      strAccessToken.length() <= 0)
    return false;

  ZOOM_SDK_NAMESPACE::StartParam startParam;
  startParam.userType = ZOOM_SDK_NAMESPACE::SDK_UT_WITHOUT_LOGIN;
  ZOOM_SDK_NAMESPACE::StartParam4WithoutLogin &withoutLoginStartParam =
      startParam.param.withoutloginStart;

  withoutLoginStartParam.userID = strUserId.c_str();
  withoutLoginStartParam.userToken = strUserToken.c_str();
  withoutLoginStartParam.userZAK = strAccessToken.c_str();
  withoutLoginStartParam.meetingNumber = _wtoi64(strMeetingNumber.c_str());
  withoutLoginStartParam.userName = strUserName.c_str();
  withoutLoginStartParam.zoomuserType =
      ZOOM_SDK_NAMESPACE::ZoomUserType_APIUSER;

  return m_pMeetingServiceMgr->Start(startParam);
}

bool CDemoUI::APIUserJoin(const std::wstring &strMeetingNumber,
                          const std::wstring &strUserToken,
                          const std::wstring &strUserName) {
  if (!m_pMeetingServiceMgr)
    return false;

  if (strMeetingNumber.length() <= 0 || strUserName.length() <= 0)
    return false;

  ZOOM_SDK_NAMESPACE::JoinParam joinParam;
  joinParam.userType = ZOOM_SDK_NAMESPACE::SDK_UT_APIUSER;
  ZOOM_SDK_NAMESPACE::JoinParam4APIUser &apiParam = joinParam.param.apiuserJoin;
  apiParam.meetingNumber = _wtoi64(strMeetingNumber.c_str());
  apiParam.userName = strUserName.c_str();
  apiParam.psw = strUserToken.c_str();

  return m_pMeetingServiceMgr->Join(joinParam);
}

bool CDemoUI::Leave() {
  if (m_pMeetingServiceMgr == NULL)
    return false;

  return m_pMeetingServiceMgr->Leave();
}

bool CDemoUI::End() {
  if (m_pMeetingServiceMgr == NULL)
    return false;

  return m_pMeetingServiceMgr->End();
}

bool CDemoUI::MuteVideo() {
  if (m_pMeetingServiceMgr == NULL)
    return false;

  return m_pMeetingServiceMgr->MuteVideo();
}

bool CDemoUI::UnmuteVideo() {
  if (m_pMeetingServiceMgr == NULL)
    return false;

  return m_pMeetingServiceMgr->UnmuteVideo();
}

bool CDemoUI::MuteAudio(int userId) {
  if (m_pMeetingServiceMgr == NULL)
    return false;

  return m_pMeetingServiceMgr->MuteAudio(userId);
}

bool CDemoUI::UnMuteAudio(int userId) {
  if (m_pMeetingServiceMgr == NULL)
    return false;

  return m_pMeetingServiceMgr->UnMuteAudio(userId);
}

LRESULT CDemoUI::Destroy() {
  // Destroy Meeting Service.
  if (m_pMeetingServiceMgr)
    m_pMeetingServiceMgr->UnInit();

  // Destroy Auth Service and clean up SDK
  if (m_pAuthServiceMgr) {
    m_pAuthServiceMgr->LogOut();
    m_pAuthServiceMgr->UnInit();
    if (m_pNetworkConnectionHelper) {
      ZOOM_SDK_NAMESPACE::DestroyNetworkConnectionHelper(
          m_pNetworkConnectionHelper);
      m_pNetworkConnectionHelper = NULL;
    }
    CSDKHelper::UnInit();
  }
  return 0;
}

bool CDemoUI::Login(const std::wstring &ssoToken, const std::wstring &email,
                    const std::wstring &password) {
  if (!m_pAuthServiceMgr)
    return false;

  ZOOM_SDK_NAMESPACE::LoginParam param;
  param.ut.ssoLogin.bRememberMe = false;
  if (!ssoToken.empty()) {
    param.ut.ssoLogin.ssoToken = ssoToken.c_str();
    param.loginType = ZOOM_SDK_NAMESPACE::LoginType::LoginType_SSO;
  } else if (!email.empty() && !password.empty()) {
    param.ut.emailLogin.userName = email.c_str();
    param.ut.emailLogin.password = password.c_str();
  } else {
    return false;
  }
  return m_pAuthServiceMgr->Login(param);
}

void CDemoUI::onLoginRet(ZOOM_SDK_NAMESPACE::LOGINSTATUS status,
                         ZOOM_SDK_NAMESPACE::IAccountInfo *pAccountInfo) {
  switch (status) {
  case ZOOM_SDK_NAMESPACE::LOGIN_SUCCESS: {
    if (m_preMeetingServiceMgr) {
      m_preMeetingServiceMgr->Init();
      if (!NormalUserStart(wszMeetingID)) {
        OutputDebugStringW(L"NormalUserStart failed");
      }
    }
  } break;
  case ZOOM_SDK_NAMESPACE::LOGIN_PROCESSING: {
    OutputDebugStringW(L"LOGIN_PROCESSING");
  } break;
  case ZOOM_SDK_NAMESPACE::LOGIN_FAILED: {
    OutputDebugStringW(L"LOGIN_FAILED");
  } break;
  }
}

bool CDemoUI::NormalUserStart(const std::wstring &strMeetingNumber) {
  if (!m_pMeetingServiceMgr)
    return false;

  if (strMeetingNumber.length() <= 0)
    return false;

  ZOOM_SDK_NAMESPACE::StartParam startParam;
  startParam.userType = ZOOM_SDK_NAMESPACE::SDK_UT_NORMALUSER;
  ZOOM_SDK_NAMESPACE::StartParam4NormalUser &normalParam =
      startParam.param.normaluserStart;
  normalParam.meetingNumber = _wtoi64(strMeetingNumber.c_str());

  return m_pMeetingServiceMgr->Start(startParam);
}

void CDemoUI::onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret) {
  TCHAR szLog[MAX_PATH] = {0};
  wsprintf(szLog, _T("onAuthenticationReturn:ret=%d\r\n"), ret);
  OutputDebugString(szLog);

  if (m_pMeetingServiceMgr)
    m_pMeetingServiceMgr->Init();

  if (!wszSSOToken.empty() || !wszEmail.empty()) {
    if (!Login(wszSSOToken, wszEmail, wszPassword)) {
      OutputDebugStringW(L"SSO Login failed");
    }
  } else if (!wszUserID.empty() && !wszAccessToken.empty() &&
             !wszUserToken.empty()) {
    if (!APIUserStart(wszMeetingID, wszUserToken, wszUsername, wszUserID,
                      wszAccessToken)) {
      OutputDebugStringW(L"APIUserStart failed");
    }
  } else if (!APIUserJoin(wszMeetingID, L"", wszUsername)) {
    OutputDebugStringW(L"APIUserJoin failed");
  }
}

void CDemoUI::onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status,
                                     int iResult /*= 0*/) {
  TCHAR szLog[MAX_PATH] = {0};
  wsprintf(szLog, _T("status=%d, result:%d\r\n"), status, iResult);
  OutputDebugString(szLog);
}

void CDemoUI::onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status,
                              unsigned int userId) {
#if (defined ENABLE_CUSTOMIZED_UI)
  m_inMeetingUI.onSharingStatus(status, userId);
#endif
}

void CDemoUI::onRemoteControlStatus(
    ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId) {
#if (defined ENABLE_CUSTOMIZED_UI)
  m_inMeetingUI.onRemoteControlStatus(status, userId);
#endif
}

void CDemoUI::onCustomizedLocalRecordingSourceNotification(
    ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper *layout_helper) {
#if (defined ENABLE_CUSTOMIZED_UI)
  m_inMeetingUI.HandleCustomizedLocalRecordingSourceNotification(layout_helper);
#endif
}

void CDemoUI::onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int> *lstUserID,
                         const wchar_t *strUserList /*= NULL*/) {
  if (lstUserID && m_pMeetingServiceMgr) {
    int count = lstUserID->GetCount();
    for (int i = 0; i < count; i++) {
      int userId = lstUserID->GetItem(i);
      ZOOM_SDK_NAMESPACE::IUserInfo *pUserInfo =
          m_pMeetingServiceMgr->GetUserByUserID(userId);
      if (pUserInfo) {
        TCHAR szUserID[MAX_PATH] = {0};
        wsprintf(szUserID, _T("%d"), pUserInfo->GetUserID());
      }
    }
  }
#if (defined ENABLE_CUSTOMIZED_UI)
  m_inMeetingUI.onUserJoin(lstUserID, strUserList);
#endif
}

void CDemoUI::onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int> *lstUserID,
                         const wchar_t *strUserList /*= NULL*/) {
  if (lstUserID) {
    int count = lstUserID->GetCount();
    for (int i = 0; i < count; i++) {
      TCHAR szUserID[MAX_PATH] = {0};
      wsprintf(szUserID, _T("%d"), lstUserID->GetItem(i));

      TCHAR szLog[MAX_PATH] = {0};
      wsprintf(szLog, _T("onUserLeft:userid (%d) left the meeting\r\n"),
               lstUserID->GetItem(i));
      OutputDebugString(szLog);
    }
  }
#if (defined ENABLE_CUSTOMIZED_UI)
  m_inMeetingUI.onUserLeft(lstUserID, strUserList);
#endif
}
