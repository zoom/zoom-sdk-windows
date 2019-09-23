#pragma  once

#include "stdafx.h"
#include "sdk_util.h"

class CustomizedUIRecordMgr : 
	public ZOOM_SDK_NAMESPACE::IMeetingRecordingCtrlEvent
{

public:
	static CustomizedUIRecordMgr* GetInstance();
	bool StartRecording(time_t& startTimestamp);
	bool StopRecording(time_t& stopTimestamp);
	bool StartCloudRecording();
	bool StopCloudRecording();

	bool CanTheUserStartLocalRecording(unsigned int userid);
	bool CanTheUserStartCloudRecording(unsigned int userid);
	bool CanIStartLocalRecording();
	bool CanIStartCloudRecording();
	bool CanIChangeOthersRecordingPermission();
	bool DoesTheUserSupportLocalRecording(unsigned int userid);

	bool AllowLocalRecording(unsigned int userid);
	bool DisAllowLocalRecording(unsigned int userid);
	
	virtual void onRecording2MP4Done(bool bsuccess, int iResult, const wchar_t* szPath);
	virtual void onRecording2MP4Processing(int iPercentage);
	virtual void onRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status);
	virtual void onCloudRecordingStatus(ZOOM_SDK_NAMESPACE::RecordingStatus status);
	virtual void onRecordPriviligeChanged(bool bCanRec);
	virtual void onCustomizedLocalRecordingSourceNotification(ZOOM_SDK_NAMESPACE::ICustomizedLocalRecordingLayoutHelper* layout_helper);

private:
	CustomizedUIRecordMgr();
	~CustomizedUIRecordMgr();
	void GetRecordController();

private:
	static CustomizedUIRecordMgr* s_recordMgrObj;
	time_t m_rcdStartTime; 
	ZOOM_SDK_NAMESPACE::IMeetingRecordingController* m_pRecordController;
};