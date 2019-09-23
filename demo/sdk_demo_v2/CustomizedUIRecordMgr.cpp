#include "stdafx.h"
#include "CustomizedUIRecordMgr.h"

CustomizedUIRecordMgr* CustomizedUIRecordMgr::s_recordMgrObj=NULL;

CustomizedUIRecordMgr::CustomizedUIRecordMgr()
{
	m_pRecordController = NULL;
}

CustomizedUIRecordMgr::~CustomizedUIRecordMgr()
{

}

CustomizedUIRecordMgr* CustomizedUIRecordMgr::GetInstance()
{
	if (!s_recordMgrObj){
		s_recordMgrObj = new CustomizedUIRecordMgr();
	}
	return s_recordMgrObj;
}

void CustomizedUIRecordMgr::GetRecordController()
{
	if (m_pRecordController){
		return;
	}

	ZOOM_SDK_NAMESPACE::IMeetingService* pMeetingService = SDKInterfaceWrap::GetInst().GetMeetingService();
	if ( !pMeetingService ){
		return;	
	}
	
	m_pRecordController = pMeetingService->GetMeetingRecordingController();
	if (!m_pRecordController){
		return;
	}

	ZOOM_SDK_NAMESPACE::SDKError rtn;
	rtn = m_pRecordController->SetEvent(this);
	if (rtn != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS){
		return;
	}

	//TODO: what time to call the api???
	/*
	rtn = m_pRecordController->RequestCustomizedLocalRecordingSource();
	if (rtn != ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS){
		return;
	}
	*/
}

bool CustomizedUIRecordMgr::StartRecording(time_t& startTimestamp)
{
	GetRecordController();
	if (!m_pRecordController){
		return false;
	}

	ZOOM_SDK_NAMESPACE::ISettingService* pSettingService = SDKInterfaceWrap::GetInst().GetSettingService();
	if (!pSettingService){
		return false;
	}
	ZOOM_SDK_NAMESPACE::IRecordingSettingContext* pRcdSetting = pSettingService->GetRecordingSettings();
	if (!pRcdSetting){
		return false;
	}
	wchar_t* pRcdPath = (wchar_t*)(pRcdSetting->GetRecordingPath());
	if (!pRcdPath){
		return false;
	}

	ZOOM_SDK_NAMESPACE::SDKError rtn = m_pRecordController->StartRecording(startTimestamp, pRcdPath); 
	if (rtn == ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS){
		return true;
	}else {
		return false;
	}
}

bool CustomizedUIRecordMgr::StopRecording(time_t& stopTimestamp)
{
	GetRecordController();
	
	if (!m_pRecordController){
		return false;
	}

	ZOOM_SDK_NAMESPACE::SDKError rtn = m_pRecordController->StopRecording(stopTimestamp);
	if (rtn == ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS){
		return true;
	}else {
		return false;
	}
}

bool CustomizedUIRecordMgr::StartCloudRecording()
{
	GetRecordController();

	if (!m_pRecordController){
		return false;
	}
	
	ZOOM_SDK_NAMESPACE::SDKError rtn;
	rtn = m_pRecordController->StartCloudRecording();
	if (rtn == ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS){
		return true;
	}else {
		return false;
	}
}

bool CustomizedUIRecordMgr::StopCloudRecording()
{
	GetRecordController();

	if (!m_pRecordController){
		return false;
	}

	ZOOM_SDK_NAMESPACE::SDKError rtn;
	rtn = m_pRecordController->StopCloudRecording();
	if (rtn == ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS){
		return true;
	}else {
		return false;
	}
}

bool CustomizedUIRecordMgr::CanIStartLocalRecording()
{
	return CanTheUserStartLocalRecording(0);
}

bool CustomizedUIRecordMgr::CanIStartCloudRecording()
{
	return CanTheUserStartCloudRecording(0);
}

/*
*Func:Determine if the specified user is enabled to start local recording.
*     when userid=0, the api determine current logined user!
*/
bool CustomizedUIRecordMgr::CanTheUserStartLocalRecording(unsigned int userid)
{
	GetRecordController();
	if (!m_pRecordController){
		return false;
	}

	ZOOM_SDK_NAMESPACE::SDKError rtn;
	rtn = m_pRecordController->CanStartRecording(false, userid);
	if (rtn == ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS){
		return true;
	}else {
		return false;
	}
}

/*
*Func:Determine if the specified user is enabled to start cloud recording.
*	  when userid=0, the api determine current logined user!
*/
bool CustomizedUIRecordMgr::CanTheUserStartCloudRecording(unsigned int userid)
{
	GetRecordController();
	if (!m_pRecordController){
		return false;
	}

	ZOOM_SDK_NAMESPACE::SDKError rtn;
	rtn = m_pRecordController->CanStartRecording(true, userid);
	if (rtn == ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS){
		return true;
	}else {
		return false;
	}
}

/*
*Func:Determine if the current user own the authority to change the recording permission of the others.
*     if you're the host/cohost, of course you can!
*/
bool CustomizedUIRecordMgr::CanIChangeOthersRecordingPermission()
{
	GetRecordController();
	if (!m_pRecordController){
		return false;
	}

	ZOOM_SDK_NAMESPACE::SDKError rtn;
	rtn = m_pRecordController->CanAllowDisAllowLocalRecording();
	if (rtn == ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS){
		return true;
	}
	return false;
}

/*
*Func:Determine If the specified user is enabled to start local recording
*     the api is invalid for current logined user!
*     not support: H32User/PureCallInUser/InSilentMode/RecordDisabled/ClientOSSupportRecord
*/
bool CustomizedUIRecordMgr::DoesTheUserSupportLocalRecording(unsigned int userid)
{
	GetRecordController();
	if (!m_pRecordController){
		return false;
	}

	ZOOM_SDK_NAMESPACE::SDKError rtn;
	rtn = m_pRecordController->IsSupportLocalRecording(userid);
	if (rtn == ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS){
		return true;
	}
	return false;
}

bool CustomizedUIRecordMgr::AllowLocalRecording(unsigned int userid)
{
	GetRecordController();
	if (!m_pRecordController){
		return false;
	}

	ZOOM_SDK_NAMESPACE::SDKError rtn;
	rtn = m_pRecordController->AllowLocalRecording(userid);
	if (rtn == ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS){
		return true;
	}
	return false;
}

bool CustomizedUIRecordMgr::DisAllowLocalRecording(unsigned int userid)
{
	GetRecordController();
	if (!m_pRecordController){
		return false;
	}

	ZOOM_SDK_NAMESPACE::SDKError rtn;
	rtn = m_pRecordController->DisAllowLocalRecording(userid);
	if (rtn == ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS){
		return true;
	}
	return false;
}

void CustomizedUIRecordMgr::onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath)
{
	TCHAR szMsg[256]={0};

	if (bsuccess){
		wnsprintf(szMsg, sizeof(szMsg)/sizeof(TCHAR), _T("convert to mp4 success->%s"), szPath);
		::MessageBox(NULL, szMsg, _T("winsdk demo"), MB_OK);
	}else {
		wnsprintf(szMsg, sizeof(szMsg)/sizeof(TCHAR), _T("iResult=%d"), iResult);
		::MessageBox(NULL, szMsg, _T("winsdk demo"), MB_OK);
	}
}

void CustomizedUIRecordMgr::onRecording2MP4Processing(int iPercentage)
{
	TCHAR szMsg[256]={0};
	wnsprintf(szMsg, sizeof(szMsg)/sizeof(TCHAR), _T("convent percent=%d"), iPercentage);
	//::MessageBox(NULL, szMsg, _T("winsdk demo"), MB_OK);
}

void CustomizedUIRecordMgr::onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status)
{	
	switch (status)
	{
	case ZOOM_SDK_NAMESPACE::Recording_Start:	
		::MessageBox(NULL, _T("recording start"), _T("winsdk demo"), MB_OK);
		break;
	case ZOOM_SDK_NAMESPACE::Recording_Stop:
		//::MessageBox(NULL, _T("recording stop"), _T("winsdk demo"), MB_OK);
		break;
	case ZOOM_SDK_NAMESPACE::Recording_Pause:
		::MessageBox(NULL, _T("recording pause"), _T("winsdk demo"), MB_OK);
		break;
	case ZOOM_SDK_NAMESPACE::Recording_Connecting:
		::MessageBox(NULL, _T("recording connecting"), _T("winsdk demo"), MB_OK);
		break;
	case ZOOM_SDK_NAMESPACE::Recording_DiskFull:
		::MessageBox(NULL, _T("recording diskfull"), _T("winsdk demo"), MB_OK);
		break;
	}
}

void CustomizedUIRecordMgr::onCloudRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status)
{
	wstring wstrMsg;

	switch (status)
	{
	case ZOOM_SDK_NAMESPACE::Recording_Start:
		wstrMsg = _T("recording start");
		break;
	case ZOOM_SDK_NAMESPACE::Recording_Stop:
		wstrMsg = _T("recording stop");
		break;
	case ZOOM_SDK_NAMESPACE::Recording_Pause:
		wstrMsg = _T("recording pause");
		break;
	case ZOOM_SDK_NAMESPACE::Recording_Connecting:
		wstrMsg = _T("recording connecting");
		break;
	case ZOOM_SDK_NAMESPACE::Recording_DiskFull:
		wstrMsg = _T("recording diskfull");
		break;
	}
	::MessageBox(NULL, wstrMsg.c_str(), _T("winsdk demo"), MB_OK);
}

void CustomizedUIRecordMgr::onRecordPriviligeChanged(bool bCanRec)
{
	if (bCanRec)
		::MessageBox(NULL, _T("you can record now."),     _T("winsdk demo"), MB_OK);
	else 
		::MessageBox(NULL, _T("you can not record now."), _T("winsdk demo"), MB_OK);
}

void CustomizedUIRecordMgr::onCustomizedLocalRecordingSourceNotification(ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper* layout_helper)
{
	if (layout_helper)
	{

		int support_layout = layout_helper->GetSupportLayout();
		if (ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_SHARE_AND_VIDEO & support_layout)
		{
			layout_helper->SelectRecordingLayoutMode(ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_SHARE_AND_VIDEO);
			if (layout_helper->IsSendSharingSourceAvailable())
			{
				layout_helper->SelectSendSharingSource();
			}
			else
			{
				ZOOM_SDK_NAMESPACE::IList<unsigned int >* lst_recv_share = layout_helper->GetValidRecvSharingSourceList();
				int count_recv_share = lst_recv_share ? lst_recv_share->GetCount() : 0;
				if (count_recv_share > 0)
				{
					layout_helper->SelectRecvSharingSource(lst_recv_share->GetItem(0));
				}
			}

			ZOOM_SDK_NAMESPACE::IList<unsigned int >* lst_video = layout_helper->GetValidVideoSourceList();
			int count_video = lst_video ? lst_video->GetCount() : 0;
			if (count_video > 0)
			{
				for (int i = 0; i < min(count_video, 5); i++)
				{
					unsigned int user_id = lst_video->GetItem(i);
					layout_helper->AddVideoSourceToRecList(user_id);
				}
			}

			if (layout_helper->HasActiveVideoSource())
			{
				layout_helper->SelectActiveVideoSource();
			}
		}
		else if (ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_ONLY_SHARE & support_layout)
		{
			layout_helper->SelectRecordingLayoutMode(ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_ONLY_SHARE);
			if (layout_helper->IsSendSharingSourceAvailable())
			{
				layout_helper->SelectSendSharingSource();
			}
			else
			{
				ZOOM_SDK_NAMESPACE::IList<unsigned int >* lst_recv_share = layout_helper->GetValidRecvSharingSourceList();
				int count_recv_share = lst_recv_share ? lst_recv_share->GetCount() : 0;
				if (count_recv_share > 0)
				{
					layout_helper->SelectRecvSharingSource(lst_recv_share->GetItem(0));
				}
			}
		}
		else if (ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_VIDEO_WALL & support_layout)
		{
			layout_helper->SelectRecordingLayoutMode(ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_VIDEO_WALL);
			ZOOM_SDK_NAMESPACE::IList<unsigned int >* lst_video = layout_helper->GetValidVideoSourceList();
			int count_video = lst_video ? lst_video->GetCount() : 0;
			if (count_video > 0)
			{
				for (int i = 0; i < min(count_video, 5); i++)
				{
					unsigned int user_id = lst_video->GetItem(i);
					layout_helper->AddVideoSourceToRecList(user_id);
				}
			}

			if (layout_helper->HasActiveVideoSource())
			{
				layout_helper->SelectActiveVideoSource();
			}
		}
		else if (ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_ACTIVE_VIDEO_ONLY & support_layout)
		{
			layout_helper->SelectRecordingLayoutMode(ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_ACTIVE_VIDEO_ONLY);
			if (layout_helper->HasActiveVideoSource())
			{
				layout_helper->SelectActiveVideoSource();
			}
		}
		else if (ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_ONLY_AUDIO & support_layout)
		{
			layout_helper->SelectRecordingLayoutMode(ZOOM_SDK_NAMESPACE::RECORDING_LAYOUT_MODE_ONLY_AUDIO);
		}
	}
}