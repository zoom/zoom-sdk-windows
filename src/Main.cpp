#include <iostream>
#include <memory>
#include "DemoUI.h"
#include <Windows.h>
#include <thread>

std::wstring wszMeetingID;
std::wstring wszUsername = L"Outreach";
std::wstring wszUserToken;
std::wstring wszAccessToken;
std::wstring wszUserID;
std::wstring wszSSOToken;
std::wstring wszEmail;
std::wstring wszPassword;
std::wstring wszSdkKey;
std::wstring wszSdkSecret;
std::wstring wszRecordPath = L"c:\\temp";
bool bLogging = false;

void doCloseGlobalEventHandleHack();

TCHAR *getCmdOption(TCHAR **begin, TCHAR **end, const std::wstring &option) {
  TCHAR **itr = std::find(begin, end, option);
  if (itr != end && ++itr != end) {
    return *itr;
  }
  return 0;
}

bool cmdOptionExists(TCHAR **begin, TCHAR **end, const std::wstring &option) {
  return std::find(begin, end, option) != end;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR cmd, int nCmdShow) {
  HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

  bool skipKillingHandle = false;
  int argc;
  LPWSTR *argv = CommandLineToArgvW(GetCommandLine(), &argc);

	// The following is the parameter parsing logic. Not every parameter
	// combination is valid. There are 3 ways to authenticate with zoom.

	// 1. Login as user - either through email(-e)/password(-p) or SSO token (-o).
	//    There is no way to control displayed user name (-u).

	// 2. Login as API user. No parameter needed. Displayed name can be changed. (-u)

	// 3. API user logs in on behalf of user. In this case, we need access token,
	//    i.e ZAK, (-a), user id (-i), user token (-t). Displayed name (-u) can be
	//    changed. Note that if ZAK or user token is invalid, the joining of
	//    meeting will still succeed as joined as a regular API user.

	// The following are sorted alphabetically.

  TCHAR *accessToken = getCmdOption(argv, argv + argc, L"-a");
  if (accessToken) {
    wszAccessToken = accessToken;
  }

  TCHAR *email = getCmdOption(argv, argv + argc, L"-e");
  if (email) {
    wszEmail = email;
  }

  TCHAR *userId = getCmdOption(argv, argv + argc, L"-i");
  if (userId) {
    wszUserID = userId;
  }

	// whether to turn on logging for debugging purpose
  if (cmdOptionExists(argv, argv + argc, L"-l")) {
    bLogging = true;
  }

	// meeting id must be present.
  TCHAR* meetingid = getCmdOption(argv, argv + argc, L"-m");
  if (!meetingid) {
    printf("must specify meeting id");
    return -1;
  }
  wszMeetingID = meetingid;

  TCHAR* ssoToken = getCmdOption(argv, argv + argc, L"-o");
  if (ssoToken) {
    wszSSOToken = ssoToken;
  }

  TCHAR* password = getCmdOption(argv, argv + argc, L"-p");
  if (password) {
    wszPassword = password;
  }

  TCHAR* recordingPath = getCmdOption(argv, argv + argc, L"-record_path");
  if (recordingPath) {
    wszRecordPath = recordingPath;
  }

	// whether to skip killing the global handle
  if (cmdOptionExists(argv, argv + argc, L"-s")) {
    skipKillingHandle = true;
  }

  TCHAR* sdkKey = getCmdOption(argv, argv + argc, L"-sdk_key");
  if (!sdkKey) {
    printf("must specify sdk key");
    return -1;
  }
  wszSdkKey = sdkKey;


  TCHAR* sdkSecret = getCmdOption(argv, argv + argc, L"-sdk_secret");
  if (!sdkSecret) {
    printf("must specify sdk secret");
    return -1;
  }
  wszSdkSecret = sdkSecret;


  TCHAR* userToken = getCmdOption(argv, argv + argc, L"-t");
  if (userToken) {
    wszUserToken = userToken;
  }

  // display name of the jonied user.
  TCHAR* username = getCmdOption(argv, argv + argc, L"-u");
  if (username) {
    wszUsername = username;
  }

  CDemoUI *demo = new CDemoUI();
  if (!demo->SDKInit(L"https://zoom.us")) {
    OutputDebugStringW(L"SDKInit failed");
  }

  if (!demo->SDKAuth()) {
    OutputDebugStringW(L"SDKAuth failed");
  }

  if (!skipKillingHandle) {
    doCloseGlobalEventHandleHack();
  }

  MSG msg;
  ZeroMemory(&msg, sizeof(msg));

  while (GetMessage(&msg, NULL, 0, 0)) {
    if (!msg.hwnd && msg.message >= WM_USER) {
      printf("null hwnd msg\n\r");
    }
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  demo->Leave();
}
