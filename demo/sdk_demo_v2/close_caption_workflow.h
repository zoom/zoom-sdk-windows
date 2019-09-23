#pragma once

#include "sdk_util.h"

class IClosedCaptionWorkflowEvent
{
public:
	virtual void onAssignedToSendCC(bool bAssigned) = 0;
	virtual void onClosedCaptionMsgReceived(const wchar_t* ccMsg, time_t time) = 0;

};
class CCloseCaptionWorkflow:public ZOOM_SDK_NAMESPACE::IClosedCaptionControllerEvent
{
public:
	CCloseCaptionWorkflow();
	virtual ~CCloseCaptionWorkflow();
	void SetEvent(IClosedCaptionWorkflowEvent* _event);

public:
	void Init();
	bool CanIAssignOthersToSendCC();//Query if it is able to assign others to send CC
	ZOOM_SDK_NAMESPACE::SDKError AssignCCPriviledge(unsigned int userid, bool bAssigned);//assign someone to send cc.
	bool CanBeAssignedToSendCC(unsigned int userid);//Query whether someone is assigned to send cc or not.
	bool CanSendClosedCaption();//Query if current user can send Close Caption.
	ZOOM_SDK_NAMESPACE::SDKError SendClosedCaption(const wchar_t* ccMsg);//send cc.
	const wchar_t* GetClosedCaptionUrlFor3rdParty();
	ZOOM_SDK_NAMESPACE::SDKError SaveCCHistory();
	const wchar_t* GetClosedCaptionSavePath();


public:
	virtual void onAssignedToSendCC(bool bAssigned);
	virtual void onClosedCaptionMsgReceived(const wchar_t* ccMsg, time_t time);
	
protected:
	ZOOM_SDK_NAMESPACE::IClosedCaptionController* m_close_caption_ctrl;

	IClosedCaptionWorkflowEvent* m_close_caption_workflow_event;
	bool m_bSupportCC;
};