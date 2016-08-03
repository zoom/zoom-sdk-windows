// sdk_demo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <strsafe.h>
#include <string>
#include "sdk_demo.h"
#include "zoom_sdk.h"
#include "meeting_service_interface.h"
#include "auth_service_interface.h"
#include "setting_service_interface.h"
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	JoinMeetingDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	StartMonitorShareDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	StartAppShareDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	SetDefaultCameraDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK MuteDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
ZOOM_SDK_NAMESPACE::IMeetingService* g_pMeetService = NULL;
ZOOM_SDK_NAMESPACE::ISettingService* g_pSettingService = NULL;
UINT64 g_meetingNum = 0;
UINT64 g_userID = 0;
std::wstring g_monitorId;
std::wstring g_defCamera;
std::wstring g_lstCamera;
HWND	 g_hAppWnd = NULL;
HWND     g_demoWnd = NULL;
class CMeetingServiceEvent : public ZOOM_SDK_NAMESPACE::IMeetingServiceEvent
{
public:
	virtual void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0)
	{
		char szLog[MAX_PATH] = { 0 };
		sprintf(szLog, "meeting status:%d, details result:%d\r\n", status, iResult);
		OutputDebugStringA(szLog);

		if (ZOOM_SDK_NAMESPACE::MEETING_STATUS_INMEETING != status) 
		{
			g_lstCamera = L"";
			InvalidateRect(g_demoWnd, NULL, TRUE);
		}
	}
	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath)
	{
		char szLog[MAX_PATH] = { 0 };
		sprintf(szLog, "recording to mp4:%d, details result:%d%s\r\n", bsuccess, iResult);
		OutputDebugStringA(szLog);
		OutputDebugStringW(szPath);
	}

	virtual void onRecording2MP4Processing(int iPercentage)
	{
		char szLog[MAX_PATH] = { 0 };
		sprintf(szLog, "recording to mp4 processing:%d%%\r\n", iPercentage);
		OutputDebugStringA(szLog);
	}

	virtual void onUserJoin(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL)
	{
		if (lstUserID && g_pMeetService)
		{
			int count = lstUserID->GetCount();
			for (int i = 0; i < count; i++)
			{
				int userId = lstUserID->GetItem(i);
				ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = g_pMeetService->GetUserByUserID(userId);
				if (pUserInfo)
				{
					OutputDebugStringA("new user join:\r\n");
					OutputDebugStringW(pUserInfo->GetUserName());
					OutputDebugStringA("\r\n");
					char szUserID[64] = { 0 };
					sprintf(szUserID, "%d\r\n", pUserInfo->GetUserID());
					OutputDebugStringA(szUserID);
				}
			}
		}
	}

	virtual void onUserLeft(ZOOM_SDK_NAMESPACE::IList<unsigned int >* lstUserID, const wchar_t* strUserList = NULL)
	{
		if (lstUserID && g_pMeetService)
		{
			int count = lstUserID->GetCount();
			for (int i = 0; i < count; i++)
			{
				int userId = lstUserID->GetItem(i);
				{
					char szTmp[MAX_PATH] = { 0 };
					sprintf(szTmp, "user(id:%d) left the meeting\r\n", userId);
					OutputDebugStringA(szTmp);
				}
			}
		}
	}

	void onRemoteControlStatus(ZOOM_SDK_NAMESPACE::RemoteControlStatus status, unsigned int userId)
	{
		char szLog[MAX_PATH] = { 0 };
		sprintf(szLog, "onRemoteControlStatus:status=%d, userid=%d\r\n", status, userId);
		OutputDebugStringA(szLog);

		if (ZOOM_SDK_NAMESPACE::Remote_Control_Request == status)
		{
			if (g_pMeetService)
				g_pMeetService->GiveRemoteControlTo(userId);
		}
	}

	void onSharingStatus(ZOOM_SDK_NAMESPACE::SharingStatus status, unsigned int userId)
	{
		char szLog[MAX_PATH] = { 0 };
		sprintf(szLog, "onSharingStatus:status=%d, userid=%d\r\n", status, userId);
		OutputDebugStringA(szLog);
	}

	void onUserAudioStatusChange(ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::IUserAudioStatus* >* lstAudioStatusChange, const wchar_t* strAudioStatusList = NULL)
	{
		int count = lstAudioStatusChange->GetCount();
		for (int i = 0; i < count; i ++)
		{
			ZOOM_SDK_NAMESPACE::IUserAudioStatus* audioStatus = lstAudioStatusChange->GetItem(i);
			char sz[MAX_PATH] = { 0 };
			sprintf(sz, "userid:%d, status:%d\r\n", audioStatus->GetUserId(), audioStatus->GetStatus());
			OutputDebugStringA(sz);
		}
	}

	void onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status)
	{

	}

	void onChatMsgNotifcation(ZOOM_SDK_NAMESPACE::IChatMsgInfo* chatMsg, const wchar_t* ccc)
	{
		if (NULL == chatMsg)
			return;

		wchar_t szTmp[1024] = { 0 };
		wsprintf(szTmp, _T("%d:%s-->%d:%s::::%s\r\n"), chatMsg->GetSenderUserId(), chatMsg->GetSenderDisplayName(),
			chatMsg->GetReceiverUserId(), chatMsg->GetReceiverDisplayName(), chatMsg->GetContent());
		OutputDebugStringW(szTmp);
	}
};
CMeetingServiceEvent g_meetingEvent;

class CAuthServiceEvent : public ZOOM_SDK_NAMESPACE::IAuthServiceEvent
{
public:
	/// \brief Authentication Result callback
	/// \param ret Authentication Result value. 
	virtual void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret)
	{
		char szLog[MAX_PATH] = { 0 };
		sprintf(szLog, "onAuthenticationReturn:%d\r\n", ret);
		OutputDebugStringA(szLog);
		MessageBoxA(NULL, szLog, "Authentication", MB_OK);
	}
};

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SDK_DEMO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	BOOL bSDKReady(FALSE);
	ZOOM_SDK_NAMESPACE::InitParam param_;
	ZOOM_SDK_NAMESPACE::IAuthService* pAuthService = NULL;
	CAuthServiceEvent authEvent;
	do 
	{
#error TODO:pass your domain
		param_.strWebDomain = _T("");
		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != ZOOM_SDK_NAMESPACE::InitSDK(param_))
			break;

		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != ZOOM_SDK_NAMESPACE::CreateAuthService(&pAuthService)
			|| NULL == pAuthService)
			break;

		pAuthService->SetEvent(&authEvent);
#error	TODO:pass your appKey and appSecret
		ZOOM_SDK_NAMESPACE::AuthParam authParam;
		authParam.appKey = L"";
		authParam.appSecret = L"";
		pAuthService->SDKAuth(authParam);

		if (ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS != ZOOM_SDK_NAMESPACE::CreateMeetingService(&g_pMeetService)
			|| NULL == g_pMeetService)
			break;

		g_pMeetService->SetEvent(&g_meetingEvent);
		bSDKReady = TRUE;

		if (NULL == g_pSettingService)
			ZOOM_SDK_NAMESPACE::CreateSettingService(&g_pSettingService);

		if (!InitInstance (hInstance, nCmdShow))
		{
			return FALSE;
		}

		hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SDK_DEMO));

		// Main message loop:
		while (GetMessage(&msg, NULL, 0, 0))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	} while (FALSE);

	if (bSDKReady)
	{
		ZOOM_SDK_NAMESPACE::DestroyAuthService(pAuthService);
		ZOOM_SDK_NAMESPACE::DestroyMeetingService(g_pMeetService);
		ZOOM_SDK_NAMESPACE::DestroySettingService(g_pSettingService);
		ZOOM_SDK_NAMESPACE::CleanUPSDK();
	}
	
	return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SDK_DEMO));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SDK_DEMO);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   g_demoWnd = hWnd;

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//

BOOL IsInMeeting(ZOOM_SDK_NAMESPACE::MeetingStatus status)
{
	BOOL bInMeeting(TRUE);
	if (ZOOM_SDK_NAMESPACE::MEETING_STATUS_IDLE == status
		|| ZOOM_SDK_NAMESPACE::MEETING_STATUS_ENDED == status)
	{
		bInMeeting = FALSE;
	}

	return bInMeeting;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_START:
			{
				if (g_pSettingService)
				{
					g_pSettingService->EnableAutoJoinAudio(true);
				}
				if (g_pMeetService
					&& !IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
#error	TODO:pass your user and meeting information 
					ZOOM_SDK_NAMESPACE::StartParam startParam;
					startParam.userID = L"";
					startParam.userToken = L"";
					startParam.userName = L"";
					startParam.meetingNumber = ;
					startParam.userType = ZOOM_SDK_NAMESPACE::SDK_UT_APIUSER;
					startParam.isDirectShareDesktop = true;
					g_pMeetService->Start(startParam);
				}
			}
			break;
		case IDM_JOIN:
			{
				if (g_pMeetService
					&& !IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DLG_JM), hWnd, JoinMeetingDlg);
					ZOOM_SDK_NAMESPACE::JoinParam joinParam;
					joinParam.meetingNumber = g_meetingNum;
					joinParam.userName = L"sdk demo";
					g_pMeetService->Join(joinParam);
				}
			}
			break;
		case IDM_LEAVE:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					g_pMeetService->Leave(ZOOM_SDK_NAMESPACE::LEAVE_MEETING);
				}
			}
			break;
		case IDM_END:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					g_pMeetService->Leave(ZOOM_SDK_NAMESPACE::END_MEETING);
				}
			}
			break;
		case ID_SDK_STARTREC:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					time_t startTime;
					g_pMeetService->StartRecording(startTime, L"c:\\dats1\\ddd");
				}
			}
			break;
		case ID_SDK_STOPREC:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					time_t stopTime;
					g_pMeetService->StopRecording(stopTime);
				}
			}
			break;
		case ID_SDK_MUTEVIDEO:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					g_pMeetService->MuteVideo();
				}
			}
			break;
		case ID_SDK_UNMUTEVIDEO:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					g_pMeetService->UnmuteVideo();
				}
			}
			break;
		case ID_SDK_STARTMONITORSHARE:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DLG_MONITORSHARE), hWnd, StartMonitorShareDlg);
					const wchar_t* monitorId_= g_monitorId.empty() ? NULL : g_monitorId.c_str();
					g_pMeetService->StartMonitorShare(monitorId_);
				}
			}
			break;
		case ID_SDK_STARTAPPSHARE:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DLG_APPSHARE), hWnd, StartAppShareDlg);
					g_pMeetService->StartAppShare(g_hAppWnd);
				}
			}
			break;
		case ID_SDK_STOPSHARE:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					g_pMeetService->StopShare();
				}
			}
			break;
		case ID_SDK_SHOWCHATDIALOG:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::IMeetingUIController* pUICtrl = g_pMeetService->GetUIController();
					if (pUICtrl)
					{
						ZOOM_SDK_NAMESPACE::ShowChatDlgParam param_;
						param_.rect.left = 0;
						param_.rect.top = 0;
						param_.rect.right = 200;
						param_.rect.bottom = 200;
						pUICtrl->ShowChatDlg(param_);
					}
				}
			}
			break;
		case ID_SDK_HIDECHATDIALOG:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::IMeetingUIController* pUICtrl = g_pMeetService->GetUIController();
					if (pUICtrl)
					{
						pUICtrl->HideChatDlg();
					}
				}
			}
			break;
		case ID_SDK_GETCAMERALIST:
			{
				std::wstring videoInfo(L"device info:\r\n");
				if (g_pSettingService)
				{
					ZOOM_SDK_NAMESPACE::IList<ZOOM_SDK_NAMESPACE::ICameraInfo* >* pList = g_pSettingService->GetCameraList();
					if (pList)
					{
						int count = pList->GetCount();
						for (int i = 0; i < count; i ++)
						{
							ZOOM_SDK_NAMESPACE::ICameraInfo* pInfo = pList->GetItem(i);
							if (pInfo)
							{
								videoInfo += L">>>>>>>>>>>>>>\r\ndevice id:";
								videoInfo += pInfo->GetDeviceId();
								videoInfo += L"\r\ndevice name:";
								videoInfo += pInfo->GetDeviceName();
								videoInfo += L"\r\n";
								videoInfo += L"<<<<<<<<<<<<<<\r\n";
							}
						}
					}
				}
				g_lstCamera = videoInfo;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		case ID_SDK_SETDEFCAMERA:
			{
				if (g_pSettingService)
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DLG_SETDEFCAMERA), hWnd, SetDefaultCameraDlg);

					g_pSettingService->SelectCamera(g_defCamera.c_str());
				}
			}
			break;
		case ID_SDK_ENTERFULLSCREEN:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::IMeetingUIController* pCtrl = g_pMeetService->GetUIController();
					if (pCtrl)
						pCtrl->EnterFullScreen(true, false);
				}
			}
			break;
		case ID_SDK_EXITFULLSCREEN:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::IMeetingUIController* pCtrl = g_pMeetService->GetUIController();
					if (pCtrl)
						pCtrl->ExitFullScreen(true, false);
				}
			}
			break;
		case ID_SDK_ENABLEDUALSCREENMODE:
			{
				if (g_pSettingService)
					g_pSettingService->EnableDualScreenMode(true);
			}
			break;
		case ID_SDK_DisableDualScreenMode:
			{
				if (g_pSettingService)
					g_pSettingService->EnableDualScreenMode(false);
			}
			break;
		case ID_SDK_SWITCHTOVIDEOWALL:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::IMeetingUIController* pCtrl = g_pMeetService->GetUIController();
					if (pCtrl)
						pCtrl->SwitchToVideoWall();
				}
			}
			break;
		case ID_SDK_SWITCHTOACTIVESPEAKER:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::IMeetingUIController* pCtrl = g_pMeetService->GetUIController();
					if (pCtrl)
						pCtrl->SwtichToAcitveSpeaker();
				}
			}
			break;
		case ID_SDK_SHOWSETTINGDIALOG:
			{
				ZOOM_SDK_NAMESPACE::ShowSettingDlgParam param;
				param.left = 0;
				param.top = 0;
				if (g_pSettingService)
					g_pSettingService->ShowSettingDlg(param);
			}
			break;
		case ID_SDK_HIDESETTINGDIALOG:
			{
				ZOOM_SDK_NAMESPACE::ShowSettingDlgParam param;
				if (g_pSettingService)
					g_pSettingService->HideSettingDlg();
			}
			break;
		case ID_SDK_LOCKMEETING:
			{
				if (g_pMeetService)
					g_pMeetService->LockMeeting();
			}
			break;
		case ID_SDK_UNLOCKMEETING:
			{
				if (g_pMeetService)
					g_pMeetService->UnlockMeeting();
			}
			break;
		case ID_SDK_STARTANNOTATION:
			{
				if (g_pMeetService)
					g_pMeetService->StartAnnotation(0, 0);
			}
			break;
		case ID_SDK_STOPANNOTATION:
			{
				if (g_pMeetService)
					g_pMeetService->StopAnnotation();
			}
			break;
		case ID_ANNOTATIONCTRL_SETPENTOOL:
			{
				ZOOM_SDK_NAMESPACE::IAnnotationController* pAnno(NULL);
				if (g_pMeetService)
					pAnno = g_pMeetService->GetAnnotationController();

				if (pAnno)
					pAnno->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_SPOTLIGHT);
			}
			break;
		case ID_ANNOTATIONCTRL_SETPENTOOL1:
			{
				ZOOM_SDK_NAMESPACE::IAnnotationController* pAnno(NULL);
				if (g_pMeetService)
					pAnno = g_pMeetService->GetAnnotationController();

				if (pAnno)
					pAnno->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_SPOTLIGHT);
			}
			break;
		case ID_ANNOTATIONCTRL_SETREDCOLOR:
			{
				ZOOM_SDK_NAMESPACE::IAnnotationController* pAnno(NULL);
				if (g_pMeetService)
					pAnno = g_pMeetService->GetAnnotationController();
				
				//argb
				if (pAnno)
					pAnno->SetColor(0xFFFF0000);
			}
			break;

		case ID_ANNOTATIONCTRL_SETLINEWIDTH:
			{
				ZOOM_SDK_NAMESPACE::IAnnotationController* pAnno(NULL);
				if (g_pMeetService)
					pAnno = g_pMeetService->GetAnnotationController();

				if (pAnno)
					pAnno->SetLineWidth(20);
			}
			break;

		case ID_ANNOTATIONCTRL_UNDO:
			{
				ZOOM_SDK_NAMESPACE::IAnnotationController* pAnno(NULL);
				if (g_pMeetService)
					pAnno = g_pMeetService->GetAnnotationController();

				if (pAnno)
					pAnno->Undo();
			}
			break;

		case ID_ANNOTATIONCTRL_REDO:
			{
				ZOOM_SDK_NAMESPACE::IAnnotationController* pAnno(NULL);
				if (g_pMeetService)
					pAnno = g_pMeetService->GetAnnotationController();

				if (pAnno)
					pAnno->Redo();
			}
			break;

		case ID_ANNOTATIONCTRL_SWITCHMOUSE:
			{
				ZOOM_SDK_NAMESPACE::IAnnotationController* pAnno(NULL);
				if (g_pMeetService)
					pAnno = g_pMeetService->GetAnnotationController();

				if (pAnno)
					pAnno->SetTool(ZOOM_SDK_NAMESPACE::ANNOTOOL_NONE_DRAWING);
			}
			break;

		case ID_ANNOTATIONCTRL_CLEARALL:
			{
				ZOOM_SDK_NAMESPACE::IAnnotationController* pAnno(NULL);
				if (g_pMeetService)
					pAnno = g_pMeetService->GetAnnotationController();

				if (pAnno)
					pAnno->Clear(ZOOM_SDK_NAMESPACE::ANNOCLEAR_ALL);
			}
			break;

		case ID_SDK_MOVEFLOATVIDEOWND:
			{
				ZOOM_SDK_NAMESPACE::IMeetingUIController* pUICtrl(NULL);
				if (g_pMeetService)
					pUICtrl = g_pMeetService->GetUIController();

				if (pUICtrl)
					pUICtrl->MoveFloatVideoWnd(0, 0);
			}
			break;
		case ID_REMOTECONTROL_REQUESTREMOTECONTROL:
			{
				if (g_pMeetService)
					g_pMeetService->RequestRemoteControl();
			}
			break;
		case ID_REMOTECONTROL_GIVEUPREMOTECONTROL:
			{
				if (g_pMeetService)
					g_pMeetService->GiveupRemoteControl();
			}
			break;
		case ID_REMOTECONTROL_CANCELREMOTECONTROL:
			{
				if (g_pMeetService)
					g_pMeetService->RevokeRemoteControl();
			}
			break;
		case ID_SDK_GETINVITEEMAILTEMPLATE:
			{
				if (g_pMeetService)
				{
					std::wstring strShow;

					const wchar_t* joinurl = g_pMeetService->GetJoinMeetingUrl();
					if (joinurl)
					{
						strShow += L"join url:\r\n";
						strShow += joinurl;
						strShow += L"\r\n";
					}

					const wchar_t* emailTitle = g_pMeetService->GetInviteEmailTitle();
					if (emailTitle)
					{
						strShow += L"email title:\r\n";
						strShow += emailTitle;
						strShow += L"\r\n";
					}

					const wchar_t* emailTem = g_pMeetService->GetInviteEmailTeamplate();
					if (emailTem)
					{
						strShow += L"email tem:\r\n";
						strShow += emailTem;
						strShow += L"\r\n";
					}

					::MessageBox(NULL, strShow.c_str(), L"info", MB_OK);
				}
			}
			break;
		case ID_UI_SHOWSHARINGFLOATTOOLBAR:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::IMeetingUIController* pCtrl = g_pMeetService->GetUIController();
					if (pCtrl)
						pCtrl->ShowSharingToolbar(true);
				}
			}
			break;
		case ID_UI_SHOWSHARINGFRAMEWND:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::IMeetingUIController* pCtrl = g_pMeetService->GetUIController();
// 					if (pCtrl)
// 						pCtrl->ShowSharingFrameWnd(true);
				}
			}
			break;
		case ID_UI_SWITCHFLOATVIDEOTOACTIVE:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::IMeetingUIController* pCtrl = g_pMeetService->GetUIController();
					pCtrl->SwitchFloatVideoToActiveSpkMod();
				}
			}
			break;
		case ID_UI_SWITCHFLOATVIDEOTOLIST:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::IMeetingUIController* pCtrl = g_pMeetService->GetUIController();
					pCtrl->SwitchFloatVideoToGalleryMod();
				}
			}
			break;
		case ID_UI_SHOWFLOATACTMODMAX:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::IMeetingUIController* pCtrl = g_pMeetService->GetUIController();
					pCtrl->ChangeFloatoActiveSpkVideoSize(true);
				}
			}
			break;
		case ID_UI_SHOWFLOATACTMODMIN:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::IMeetingUIController* pCtrl = g_pMeetService->GetUIController();
					pCtrl->ChangeFloatoActiveSpkVideoSize(false);
				}
			}
			break;
		case ID_UI_HIDEBOTTOMTOOLBAR:
			{
				static bool bShow(true);
				bShow = !bShow;
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::IMeetingUIController* pCtrl = g_pMeetService->GetUIController();
					pCtrl->ShowBottomFloatToolbarWnd(bShow);

					HWND hFristView(NULL), hSecondView(NULL);
					pCtrl->GetMeetingUIWnd(hFristView, hSecondView);
				}
			}
			break;
		case ID_UI_GETALLUSEOUTPUTDEBUGSTR:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::IList<unsigned int >* lst = g_pMeetService->GetParticipantsList();
					int count_ = lst->GetCount();
					for (int i = 0; i < count_; i ++)
					{
						int userID = lst->GetItem(i);
						ZOOM_SDK_NAMESPACE::IUserInfo* pUser = g_pMeetService->GetUserByUserID(userID);
						if (pUser)
						{
							const wchar_t* strZoomId = pUser->GetEmail();
							OutputDebugStringW(strZoomId);
							OutputDebugStringA("\r\n");
						}
					}
				}
			}
			break;
		case ID_UI_G:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					const wchar_t* strTopic = g_pMeetService->GetMeetingTopic();
					OutputDebugStringW(strTopic);
					OutputDebugStringA("\r\n");
				}
			}
			break;
		case ID_UI_SHOWUSERLIST:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::IMeetingUIController* pCtrl = g_pMeetService->GetUIController();
					HWND hWnd(NULL);
					pCtrl->ShowParticipantsListWnd(true, hWnd);
				}
			}
			break;
		case ID_UI_HIDEUSERLIST:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::IMeetingUIController* pCtrl = g_pMeetService->GetUIController();
					HWND hWnd(NULL);
					pCtrl->ShowParticipantsListWnd(false, hWnd);
				}
			}
			break;
		case ID_UI_MUTE:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DLG_MUTE), hWnd, MuteDlg);
					g_pMeetService->MuteAudio(g_userID);
				}
			}
			break;
		case ID_SDK2_TURNOFFAEROMODE:
			{
				if (g_pSettingService)
				{
					g_pSettingService->TurnOffAeroModeInSharing(true);
				}
			}
			break;
		case ID_SDK2_GET:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					ZOOM_SDK_NAMESPACE::ConnectionQuality connQu = g_pMeetService->GetMeetingConnQuality();
					char sz[60] = { 0 };
					sprintf(sz, "ConnectionQuality =%d\r\n", connQu);
					OutputDebugStringA(sz);
				}
			}
			break;
		case ID_SDK2_GETCURREMOTE:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					unsigned int userID;
					g_pMeetService->GetCurrentRemoteController(userID);
					char sz[60] = { 0 };
					sprintf(sz, "current remote controller =%d\r\n", userID);
					OutputDebugStringA(sz);
				}
			}
			break;
		case ID_SDK2_SENDHELLOTOALL:
			{
				if (g_pMeetService
					&& IsInMeeting(g_pMeetService->GetMeetingStatus()))
				{
					g_pMeetService->SendChatTo(0, _T("hello"));
// 					static bool bBlock = true;
// 					g_pMeetService->BlockWindowFromScreenshare(bBlock, (HWND)0x000C1B02);
// 					bBlock = !bBlock;
				}
			}
			break;
		case IDM_ABOUT:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			}
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		//TextOutW(hdc, 0, 0, g_lstCamera.c_str(), g_lstCamera.size());
		RECT rect;
		GetClientRect(hWnd, &rect);
		DrawTextW(hdc, g_lstCamera.c_str(), -1, &rect, DT_WORDBREAK);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK JoinMeetingDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			g_meetingNum = (UINT)GetDlgItemInt(hDlg, IDC_EDIT_METNUM, NULL, FALSE);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK MuteDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			g_userID = (UINT)GetDlgItemInt(hDlg, IDC_EDIT_METNUM, NULL, FALSE);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK	StartMonitorShareDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			wchar_t szTmp[MAX_PATH] = { 0 };
			GetDlgItemTextW(hDlg, IDC_EDIT_MONITORNUM, szTmp, MAX_PATH);
			g_monitorId = szTmp;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK	StartAppShareDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			g_hAppWnd = (HWND)GetDlgItemInt(hDlg, IDC_EDIT_APPHWND, NULL, FALSE);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK SetDefaultCameraDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			wchar_t szTmp[MAX_PATH] = { 0 };
			GetDlgItemTextW(hDlg, IDC_EDIT_CAMERAID, szTmp, MAX_PATH);
			EndDialog(hDlg, LOWORD(wParam));
			g_defCamera = szTmp;
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
