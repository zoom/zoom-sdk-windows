#include "stdafx.h"
#include "ParticipantPopMenu.h"
#include "CustomizedUIRecordMgr.h"

ParticipantPopMenu::ParticipantPopMenu()
{
	m_hPopMenu = ::CreatePopupMenu();
	if (m_hPopMenu)
	{
		::InsertMenu(m_hPopMenu,(-1),MF_BYPOSITION,ITEM_MENU_RECORD,TEXT("enable record"));
	}
}

ParticipantPopMenu::~ParticipantPopMenu()
{
	if (m_hPopMenu)
	{
		::DestroyMenu(m_hPopMenu);
		m_hPopMenu = NULL;
	}
}

void ParticipantPopMenu::PopMenu(HWND hwnd,int nX,int nY )
{
	if (m_hPopMenu && hwnd)
	{
		::TrackPopupMenu(m_hPopMenu,TPM_LEFTALIGN|TPM_RIGHTBUTTON,nX,nY,0,hwnd,NULL);
	}
}

void ParticipantPopMenu::PopMenu(HWND hwnd,const POINT& pt)
{
	PopMenu(hwnd,pt.x,pt.y);
}

void ParticipantPopMenu::SetUserID(unsigned int nUserID)
{
	m_nUserID = nUserID;

	if (CustomizedUIRecordMgr::GetInstance()->CanTheUserStartLocalRecording(m_nUserID)){
		::ModifyMenu(m_hPopMenu, 0, MF_BYPOSITION, ITEM_MENU_RECORD, TEXT("Disable Record"));
	}else {
		::ModifyMenu(m_hPopMenu, 0, MF_BYPOSITION, ITEM_MENU_RECORD, TEXT("Enable Record"));
	}
}

void ParticipantPopMenu::OnClickMenuItem(int nMenuItemId)
{
	switch (nMenuItemId)
	{
	case ITEM_MENU_RECORD:
		{
			if (!CustomizedUIRecordMgr::GetInstance()->CanIChangeOthersRecordingPermission()){
				::MessageBox(NULL, _T("you have no right to change others recording permission"), _T("winsdk demo"), MB_OK);
				return;		
			}

			if (CustomizedUIRecordMgr::GetInstance()->CanTheUserStartLocalRecording(m_nUserID)){
				CustomizedUIRecordMgr::GetInstance()->DisAllowLocalRecording(m_nUserID);
			}else {
				CustomizedUIRecordMgr::GetInstance()->AllowLocalRecording(m_nUserID);
			}
		}
		break;
	}
}