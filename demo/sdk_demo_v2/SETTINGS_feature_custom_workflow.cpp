#include "stdafx.h"
#include "SETTINGS_feature_custom_workflow.h"
CSDKFeatureCustomSettingsWorkFlow::CSDKFeatureCustomSettingsWorkFlow()
{
	m_pMeetingService = NULL;
	m_pMeetingConfiguration = NULL;
	m_pMeetingUIController = NULL;
	Init();
}
CSDKFeatureCustomSettingsWorkFlow::~CSDKFeatureCustomSettingsWorkFlow()
{
	m_pMeetingService = NULL;
	m_pMeetingConfiguration = NULL;
	m_pMeetingUIController = NULL;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKFeatureCustomSettingsWorkFlow::Init()
{
	if(NULL == m_pMeetingService)
	{
		m_pMeetingService = SDKInterfaceWrap::GetInst().GetMeetingService();
	}
	if(m_pMeetingService)
	{
		m_pMeetingConfiguration = m_pMeetingService->GetMeetingConfiguration();
		m_pMeetingUIController = m_pMeetingService->GetUIController();
	}
	if(m_pMeetingConfiguration && m_pMeetingUIController)
	{
		return ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
void CSDKFeatureCustomSettingsWorkFlow::SetMeetingUIPos(ZOOM_SDK_NAMESPACE::WndPosition pos)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->SetMeetingUIPos(pos);
	}
}
void CSDKFeatureCustomSettingsWorkFlow::SetFloatVideoPos(ZOOM_SDK_NAMESPACE::WndPosition pos)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->SetFloatVideoPos(pos);
	}
}

void CSDKFeatureCustomSettingsWorkFlow::EnableLButtonDBClick4SwitchFullScreenMode(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableLButtonDBClick4SwitchFullScreenMode(bEnable);
	}
}
ZOOM_SDK_NAMESPACE::SDKError CSDKFeatureCustomSettingsWorkFlow::EnableGrabShareWithoutReminder(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingConfiguration->EnableGrabShareWithoutReminder(bEnable);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
void CSDKFeatureCustomSettingsWorkFlow::EnableShareIOSDevice(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableShareIOSDevice(bEnable);
	}
}
void CSDKFeatureCustomSettingsWorkFlow::EnableShareWhiteBoard(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableShareWhiteBoard(bEnable);
	}
}
void CSDKFeatureCustomSettingsWorkFlow::ForceDisableMultiShare(bool bDisable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->ForceDisableMultiShare(bDisable);
	}
}
void CSDKFeatureCustomSettingsWorkFlow::DisableRemoteCtrlCopyPasteFeature(bool bDisable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->DisableRemoteCtrlCopyPasteFeature(bDisable);
	}
}
ZOOM_SDK_NAMESPACE::SDKError CSDKFeatureCustomSettingsWorkFlow::BackToMeeting()
{
	if(m_pMeetingUIController)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingUIController->BackToMeeting();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKFeatureCustomSettingsWorkFlow::EnterFullScreen(bool firstView, bool secondView)
{
	if(m_pMeetingUIController)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingUIController->EnterFullScreen(firstView,secondView);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKFeatureCustomSettingsWorkFlow::ExitFullScreen(bool firstView, bool secondView)
{
	if(m_pMeetingUIController)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingUIController->ExitFullScreen(firstView,secondView);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
void CSDKFeatureCustomSettingsWorkFlow::EnableAutoEndOtherMeetingWhenStartMeeting(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableAutoEndOtherMeetingWhenStartMeeting(bEnable);
	}
}
ZOOM_SDK_NAMESPACE::SDKError CSDKFeatureCustomSettingsWorkFlow::MoveFloatVideoWnd(int left, int top)
{
	if(m_pMeetingUIController)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingUIController->MoveFloatVideoWnd(left,top);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKFeatureCustomSettingsWorkFlow::SwitchFloatVideoToActiveSpkMod()
{
	if(m_pMeetingUIController)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingUIController->SwitchFloatVideoToActiveSpkMod();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKFeatureCustomSettingsWorkFlow::SwitchFloatVideoToGalleryMod()
{
	if(m_pMeetingUIController)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingUIController->SwitchFloatVideoToGalleryMod();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKFeatureCustomSettingsWorkFlow::SwitchToVideoWall()
{
	if(m_pMeetingUIController)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingUIController->SwitchToVideoWall();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKFeatureCustomSettingsWorkFlow::ShowPreOrNextPageVideo(bool bPageUp)
{
	if(m_pMeetingUIController)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingUIController->ShowPreOrNextPageVideo(bPageUp);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKFeatureCustomSettingsWorkFlow::SwtichToAcitveSpeaker()
{
	if(m_pMeetingUIController)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingUIController->SwtichToAcitveSpeaker();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
void CSDKFeatureCustomSettingsWorkFlow::EnableForceAutoStartMyVideoWhenJoinMeeting(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableForceAutoStartMyVideoWhenJoinMeeting(bEnable);
	}
}
void CSDKFeatureCustomSettingsWorkFlow::EnableForceAutoStopMyVideoWhenJoinMeeting(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableForceAutoStopMyVideoWhenJoinMeeting(bEnable);
	}
}
void CSDKFeatureCustomSettingsWorkFlow::EnableAutoAdjustSpeakerVolumeWhenJoinAudio(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableAutoAdjustSpeakerVolumeWhenJoinAudio(bEnable);
	}
}
void CSDKFeatureCustomSettingsWorkFlow::EnableAutoAdjustMicVolumeWhenJoinAudio(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableAutoAdjustMicVolumeWhenJoinAudio(bEnable);
	}
}
ZOOM_SDK_NAMESPACE::SDKError CSDKFeatureCustomSettingsWorkFlow::ShowParticipantsListWnd(bool bShow, HWND& hParticipantsListWnd)
{
	if(m_pMeetingUIController)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingUIController->ShowParticipantsListWnd(bShow,hParticipantsListWnd);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKFeatureCustomSettingsWorkFlow::ShowChatDlg(ZOOM_SDK_NAMESPACE::ShowChatDlgParam& param)
{
	if(m_pMeetingUIController)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingUIController->ShowChatDlg(param);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
ZOOM_SDK_NAMESPACE::SDKError CSDKFeatureCustomSettingsWorkFlow::HideChatDlg()
{
	if(m_pMeetingUIController)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingUIController->HideChatDlg();
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
void CSDKFeatureCustomSettingsWorkFlow::EnableClaimHostFeature(bool bEnable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->EnableClaimHostFeature(bEnable);
	}
}
void CSDKFeatureCustomSettingsWorkFlow::DisableSplitScreenModeUIElements(bool bDisable)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->DisableSplitScreenModeUIElements(bDisable);
	}
}
ZOOM_SDK_NAMESPACE::SDKError CSDKFeatureCustomSettingsWorkFlow::SwitchSplitScreenMode(bool bSplit)
{
	if(m_pMeetingUIController)
	{
		ZOOM_SDK_NAMESPACE::SDKError err = ZOOM_SDK_NAMESPACE::SDKERR_SUCCESS;
		err = m_pMeetingUIController->SwitchSplitScreenMode(bSplit);
		return err;
	}
	return ZOOM_SDK_NAMESPACE::SDKERR_UNINITIALIZE;
}
void CSDKFeatureCustomSettingsWorkFlow::PrePopulateWebinarRegistrationInfo(const wchar_t* email, const wchar_t* username)
{
	if(m_pMeetingConfiguration)
	{
		m_pMeetingConfiguration->PrePopulateWebinarRegistrationInfo(email,username);
	}
}