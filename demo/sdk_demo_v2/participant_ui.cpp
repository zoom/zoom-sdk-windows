#include "stdafx.h"
#include "participant_ui.h"
#include <list>
#include "ParticipantPopMenu.h"

CPUserItemEx::CPUserItemEx()
{
	m_userId = 0;
	m_winUserInfo = NULL;
	m_lbName = NULL;
	m_lbHostInfo = NULL;
	m_lbVideo = NULL;
	m_lbAudio = NULL;
	m_ctrlBottomLine = NULL;
	m_pParticipantUIMgr = NULL;
	SetFixedHeight(PITEM_HEIGHT);
	m_pUser = NULL;

}

CPUserItemEx::~CPUserItemEx()
{
	OnSize -= MakeDelegate(this, &CPUserItemEx::OnSelfItemSize);
}

void CPUserItemEx::SetUIMgr(CParticipantUIMgr* pParticipantUIMgr)
{
	m_pParticipantUIMgr = pParticipantUIMgr;
	InitControls();
}
void CPUserItemEx::InitControls()
{
	m_winUserInfo = static_cast<CHorizontalLayoutUI*>(FindSubControl(_T("panel_userInfo")));
	m_lbName = static_cast<CLabelUI*>(FindSubControl(_T("lb_userName")));
	m_lbHostInfo = static_cast<CLabelUI*>(FindSubControl(_T("lb_userNameHostInfo")));
	m_lbVideo = static_cast<CLabelUI*>(FindSubControl(_T("lb_videoStatus")));
	m_lbAudio = static_cast<CLabelUI*>(FindSubControl(_T("lb_audioStatus")));
	m_ctrlBottomLine = static_cast<CControlUI*>(FindSubControl(_T("ctrl_bottom_line")));
	m_lbLowerHand = static_cast<CLabelUI* >(FindSubControl(_T("lb_raiseHand")));
	OnSize += MakeDelegate(this, &CPUserItemEx::OnSelfItemSize);
}


bool CPUserItemEx::IsSelected() const
{
	return __super::IsSelected();
}

bool CPUserItemEx::Select(bool bSelect)
{
	return __super::Select(bSelect);
}

unsigned int CPUserItemEx::GetUserID()
{
	return m_userId;
}

void CPUserItemEx::SetUserID(unsigned int userID)
{
	m_userId = userID;
	if(m_pParticipantUIMgr)
		m_pUser = m_pParticipantUIMgr->GetUserByID(m_userId);
	if(m_pUser)
		UpdateUserInfo();
}

void CPUserItemEx::UpdateName()
{
	if(!m_pUser || !m_lbHostInfo || !m_lbName)
		return;
	std::wstring strName = m_pUser->GetUserName();
	bool bHost = m_pUser->IsHost();
	if(m_lbName)
		m_lbName->SetText(strName.c_str());

	if (bHost && m_lbHostInfo)
	{
		m_lbHostInfo->SetText(_T("(Host)"));
		m_lbHostInfo->SetVisible(true);
	} 
	else 
	{
		m_lbHostInfo->SetVisible(false);
	} 
	OnSelfItemSize(NULL);
}

void CPUserItemEx::UpdateUserAudioStatus()
{
	if(!m_pUser || !m_lbAudio)
		return;
	bool bAudioStatus = m_pUser->IsAudioMuted();
	bool bPhoneUser = m_pUser->IsPurePhoneUser();
	std::wstring strUnmuteBk = bPhoneUser ? _T("res='btn_unmutePhone24x24.png' restype='ZPIMGRES' ")
		: _T("res='icon_unmute24x24.png' restype='ZPIMGRES' ");
	std::wstring strMuteBk = bPhoneUser ? _T("res='btn_mutePhone24x24.png' restype='ZPIMGRES' ")
		: _T("res='icon_mute24x24.png' restype='ZPIMGRES' ");

	if(bAudioStatus)
	{
		m_lbAudio->SetBkImage(strMuteBk.c_str());
	}
	else
	{
		m_lbAudio->SetBkImage(strUnmuteBk.c_str());
	}
	m_lbAudio->SetVisible(true);
	OnSelfItemSize(NULL);
}

void CPUserItemEx::UpdateUserVideoStatus()
{
	if(!m_pUser || !m_lbVideo)
		return;
	bool bVideoStatus = m_pUser->IsVideoOn();

	std::wstring strUnmuteBk =  _T("res='btn_sendvideo24x24.png' restype='ZPIMGRES' ");
	std::wstring strMuteBk = _T("res='btn_stopvideo24x24.png' restype='ZPIMGRES' ");

	if(bVideoStatus)
	{
		m_lbVideo->SetBkImage(strUnmuteBk.c_str());
	}
	else
	{
		m_lbVideo->SetBkImage(strMuteBk.c_str());
	}
	m_lbVideo->SetVisible(true);
	OnSelfItemSize(NULL);
}
void CPUserItemEx::UpdateUserLowerHandStatus()
{
	if(!m_pUser || !m_lbLowerHand)
		return;
	bool bRaiseHand = m_pUser->IsRaiseHand();
	if (bRaiseHand)
	{
		m_lbLowerHand->SetVisible();
	}
	else
	{
		m_lbLowerHand->SetVisible(false);
	}
}

void CPUserItemEx::UpdateUserInfo()
{
	UpdateName();
	UpdateItemInfo();
}

void CPUserItemEx::ResetItemInfo()
{
	m_pUser = NULL;
	m_userId = 0;
}

void CPUserItemEx::UpdateItemInfo()
{
	if (!m_pUser)
		return;
	UpdateUserAudioStatus();
	UpdateUserVideoStatus();
	UpdateUserLowerHandStatus();
	OnSelfItemSize(NULL);
}

bool CPUserItemEx::OnSelfItemSize(void* pParam)
{
	if (!m_lbName)
		return false;

	if (!m_lbHostInfo)
		return false;

	if (!m_lbVideo)
		return false;

	if (!m_lbAudio)
		return false;

	if (!m_pUser)
		return false;

	if (!m_pManager)
		return false;

	CRect rc = GetPos();
	int nWidthPanel = rc.right - rc.left;

	SIZE szNameText = CRenderEngine::GetTextSize(m_pManager->GetPaintDC(), m_pManager, m_lbName->GetText(), m_lbName->GetFont(), m_lbName->GetTextStyle());

	int nWidth = 0;

	if (m_lbHostInfo->IsVisible())
	{
		SIZE szHostInfoText = CRenderEngine::GetTextSize(m_pManager->GetPaintDC(), m_pManager, m_lbHostInfo->GetText(), m_lbHostInfo->GetFont(), m_lbHostInfo->GetTextStyle());
		CRect rcPadding = m_lbHostInfo->GetTextPadding();
		nWidth += (rcPadding.left + rcPadding.right);
		nWidth += szHostInfoText.cx;
	}

	if (m_lbAudio->IsVisible())
	{
		CRect rcPadding = m_lbAudio->GetPadding();
		nWidth += (rcPadding.left + rcPadding.right);
		nWidth += m_lbAudio->GetFixedWidth();
	}

	if (m_lbVideo->IsVisible())
	{
		CRect rcPadding = m_lbVideo->GetPadding();
		nWidth += (rcPadding.left + rcPadding.right);
		nWidth += m_lbVideo->GetFixedWidth();
	}

	int nNameWidth = nWidthPanel - 4 - 4 - nWidth - 60;

	int nRealWidth = szNameText.cx;
	if (nRealWidth > nNameWidth)
		nRealWidth = nNameWidth;
	m_lbName->SetFixedWidth(nRealWidth);
	return false;
}


//////////////////////////////////////////////////////////////////////////

CParticipantUIMgr::CParticipantUIMgr(CCustomizeInMeetingUIMgr* pCustomizeUI)
{
	m_hParentWnd = NULL;
	m_pCustomizeUI = pCustomizeUI;
	m_pUserListUI= NULL;
	m_pUserList = NULL;
	m_pPopMenu = NULL;
}

CParticipantUIMgr::~CParticipantUIMgr()
{
	m_hParentWnd = NULL;
	m_pCustomizeUI = NULL;
	if (m_pPopMenu){
		delete m_pPopMenu;
		m_pPopMenu=NULL;
	}
}

CControlUI* CParticipantUIMgr::CreateControl(LPCTSTR pstrClass)
{
	//if need circular image, we can write a new class to do it
	if (_tcscmp(pstrClass, DUILIB_PUSERITEM_UI) == 0)
		return new CPUserItemEx();
	return NULL;
}

void CParticipantUIMgr::InitWindow()
{
	RECT rc = { 0 };
	if( !::GetClientRect(m_hWnd, &rc) ) 
		return;
	rc.bottom = rc.top + DEFAULT_PARTICIPANT_HEIGHT;
	if( !::AdjustWindowRectEx(&rc, GetWindowStyle(m_hWnd), false, GetWindowExStyle(m_hWnd)) ) return;
	::SetWindowPos(m_hWnd, NULL, rc.left,rc.top, rc.right-rc.left,DEFAULT_PARTICIPANT_HEIGHT, SWP_SHOWWINDOW);
	m_pUserListUI = static_cast<CListUI* >(m_PaintManager.FindControl(_T("puserlist")));
	m_pUserListUI->SetContextMenuUsed(true);
	//m_pUserListUI->SetItemRSelected(true);
}


LRESULT CParticipantUIMgr::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;

	if( uMsg == WM_CREATE ) 
	{
		m_PaintManager.Init(m_hWnd);
		CDialogBuilder builder;
		STRINGorID xml(GetSkinRes());
		CControlUI* pRoot = builder.Create(xml, _T("xml"), 0, &m_PaintManager);
		ASSERT(pRoot && "Failed to parse XML");

		m_PaintManager.AttachDialog(pRoot);
		m_PaintManager.AddNotifier(this);
		InitWindow(); 
		return lRes;
	}
	else if (uMsg == WM_COMMAND)
	{
		m_pPopMenu->OnClickMenuItem(LOWORD(wParam));
	}

	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

void CParticipantUIMgr::Notify(TNotifyUI& msg)
{	
	if (msg.sType == DUI_MSGTYPE_MENU)
	{
		int nCurSel = m_pUserListUI->GetCurSel();
		CPUserItemEx* pItem = static_cast<CPUserItemEx*>(m_pUserListUI->GetItemAt(nCurSel));
		unsigned int nUserId = pItem->GetUserID();

		ZOOM_SDK_NAMESPACE::IUserInfo* pUserInfo = GetUserByID(nUserId);
		if (pUserInfo->IsHost()){ 
			return;
		}

		if (!m_pPopMenu){
			m_pPopMenu = new ParticipantPopMenu();
		}
		m_pPopMenu->SetUserID(nUserId);
		POINT pt; ::GetCursorPos(&pt);
		m_pPopMenu->PopMenu(m_hWnd, pt);
	}
}

bool CParticipantUIMgr::IsWindow()
{
	return ::IsWindow(m_hWnd) ? true:false;
}

bool CParticipantUIMgr::DestroyWindow()
{
	if(IsWindow())
	{
		return ::DestroyWindow(m_hWnd) ? true:false;
	}
	return false;
}

void CParticipantUIMgr::SetParent(HWND hParentWnd)
{
	m_hParentWnd = hParentWnd;
}

void CParticipantUIMgr::HandleUserChanged(SDKUserChangedType changedType)
{
	GetUserList();
	switch(changedType)	
	{
	case SDK_USER_JOIN:
	case SDK_USER_UPDATE:
		UpdateListItem();
		break;
	case SDK_USER_LEFT:
		RemoveListItem();
		break;
	default:
		break;
	}
}

void CParticipantUIMgr::GetUserList()
{
	if(m_pCustomizeUI)
		m_pUserList = m_pCustomizeUI->GetUserList();
	
	ResetWindowTitle();
}

void CParticipantUIMgr::ResetWindowTitle()
{
	if(!m_pUserList)
		return;
	TCHAR strTitle[25] = {0};
	int nCount = m_pUserList->GetCount();
	if(nCount>1)
		wsprintf(strTitle,_T("  %s (%d)"), _T("Pariticipants"), nCount);
	else
		wsprintf(strTitle,_T("  %s"), _T("Pariticipant"));

	bool BRet = ::SetWindowText(m_hWnd, strTitle);
}
ZOOM_SDK_NAMESPACE::IUserInfo* CParticipantUIMgr::GetUserByID(unsigned int uID)
{
	if(m_pUserList)
		return m_pUserList->GetUserByID(uID);
	return NULL;
}

void CParticipantUIMgr::InitListUI()
{
	GetUserList();
	if (m_pUserList)
	{
		m_pUserListUI->RemoveAll();
		int nCount = m_pUserList->GetCount();
		for (int i=0; i<nCount; i++)
		{
			CDialogBuilder builder;
			STRINGorID xml(IDXML_MEETING_PARTICIPANT_LIST_UI);
			CPUserItemEx* pLine = static_cast<CPUserItemEx*>(builder.Create(xml, _T("XML"), this, &m_PaintManager));
			ZOOM_SDK_NAMESPACE::IUserInfo* pUser = m_pUserList->GetItem(i);
			if( pLine != NULL && pUser != NULL) 
			{
				pLine->SetFixedHeight(PITEM_HEIGHT);
				pLine->SetUIMgr(this);
				pLine->SetUserID(pUser->GetUserID());
				m_pUserListUI->Add(pLine);
			}
		}
	}
}

void CParticipantUIMgr::RemoveListItem()
{
	std::list<int> needRemoveList;
	bool bFound = false;
	unsigned int userID;
	if (m_pUserList && m_pUserListUI)
	{		
		int nCount = m_pUserListUI->GetCount();
		for (int i=nCount-1; i<nCount; i--)
		{
			CPUserItemEx* pItem = static_cast<CPUserItemEx*>(m_pUserListUI->GetItemAt(i));
			if (pItem)
			{
				userID = pItem->GetUserID();
				int nListCount = m_pUserList->GetCount();
				for(int j=0; j<nListCount; j++)
				{
					ZOOM_SDK_NAMESPACE::IUserInfo* pUser = m_pUserList->GetItem(j);
					if(!pUser)
						continue;
					if(userID == pUser->GetUserID())
					{
						bFound = true;
						break;
					}
				}
			}
			if(bFound)
				continue;
			else
			{
				bFound = false;
				needRemoveList.push_back(userID);

			}
		}
		if(!needRemoveList.empty())
		{
			std::list<int>::iterator iter_ = needRemoveList.begin();
			for (;needRemoveList.end() != iter_; iter_++)
			{
				int nRemovedPos = *iter_;
				if(nRemovedPos < m_pUserListUI->GetCount())
					m_pUserListUI->RemoveAt(nRemovedPos);
			}
		}
	}
}
void CParticipantUIMgr::UpdateListItem()
{
	bool bUpdated = false;
	if(m_pUserListUI)
	{	
		int nListCount = m_pUserList->GetCount();
		for(int i= 0; i<nListCount; i++)
		{
			ZOOM_SDK_NAMESPACE::IUserInfo* pUser = m_pUserList->GetItem(i);
			if(!pUser)
				continue;
			unsigned int userID = pUser->GetUserID();
			int nListUICount = m_pUserListUI->GetCount();
			for (int j=0; j<nListUICount; j++)
			{
				CPUserItemEx* pItem = static_cast<CPUserItemEx*>(m_pUserListUI->GetItemAt(j));
				//found
				if (pItem && userID == pItem->GetUserID())
				{
					pItem->UpdateItemInfo();
					bUpdated = true;
				}
			}

			if(!bUpdated)
			{
				CDialogBuilder builder;
				STRINGorID xml(IDXML_MEETING_PARTICIPANT_LIST_UI);
				CPUserItemEx* pNewItem = static_cast<CPUserItemEx*>(builder.Create(xml, _T("XML"), this, &m_PaintManager));
				if( pNewItem != NULL ) 
				{
					pNewItem->SetFixedHeight(PITEM_HEIGHT);
					pNewItem->SetUIMgr(this);
					pNewItem->SetUserID(userID);
					m_pUserListUI->Add(pNewItem);
				}	
			}
		}
	}
}

