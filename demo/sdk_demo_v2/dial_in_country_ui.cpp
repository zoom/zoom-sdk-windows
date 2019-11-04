#include "stdafx.h"

#include "dial_in_country_ui.h"
#include "schedule_meeting_ui.h"


CDialInCountryUIMgr::CDialInCountryUIMgr(CSDKSheduleMeetingUIGroup* _main, ZOOM_SDK_NAMESPACE::IScheduleMeetingItem* _meeting_item)
{
	m_country_list = NULL;
	m_show_country_edit = NULL;
	m_inlude_free_num = false;
	m_save_change_btn = NULL;
	m_pScheduleMeetingItem = _meeting_item;
	m_audio_helper = NULL;
	m_main_ptr = _main;

	if (m_pScheduleMeetingItem)
	{
		m_audio_helper = m_pScheduleMeetingItem->GetQueryTelAudioInfoHelper();
	}

}

CDialInCountryUIMgr::~CDialInCountryUIMgr()
{
	m_country_list = NULL;
	m_show_country_edit = NULL;
	m_inlude_free_num = false;
	m_save_change_btn = NULL;
	m_pScheduleMeetingItem = NULL;
	m_audio_helper = NULL;
	m_main_ptr = NULL;
}

void CDialInCountryUIMgr::Notify( TNotifyUI& msg )
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_save_change_btn)
		{
			DoClickSaveChangeBtn();
		}
		
	}
	if (msg.sType == _T("selectchanged"))
	{
		UpdateShowList();
	}
	
}

void CDialInCountryUIMgr::InitWindow()
{
	RECT rc = { 0 };
	if( !::GetClientRect(m_hWnd, &rc) ) return;
	rc.right = rc.left + 440;
	rc.bottom = rc.top + 360;
	if( !::AdjustWindowRectEx(&rc, GetWindowStyle(m_hWnd), (!(GetWindowStyle(m_hWnd) & WS_CHILD) && (::GetMenu(m_hWnd) != NULL)), GetWindowExStyle(m_hWnd)) ) return;
	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	::SetWindowPos(m_hWnd, NULL, (ScreenX - (rc.right - rc.left)) / 2, 
		(ScreenY - (rc.bottom - rc.top)) / 2, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_SHOWWINDOW);

	m_country_list = dynamic_cast<CVerticalLayoutUI* >(m_PaintManager.FindControl(L"select_dial_in_country_list"));
	m_show_country_edit = dynamic_cast<CRichEditUI* >(m_PaintManager.FindControl(L"show_country_edit"));
	m_save_change_btn = dynamic_cast<CButtonUI* >(m_PaintManager.FindControl(L"modify_btn"));
	m_inlude_free_num = dynamic_cast<CCheckBoxUI* >(m_PaintManager.FindControl(L"free_phone_chk"));
	InitCountryListUI();
}

LRESULT CDialInCountryUIMgr::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
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
	else if (uMsg == WM_CLOSE)
	{
		ShowWindow(false);
		return lRes;
	}
	else if (uMsg == WM_DESTROY)
	{
		return lRes;
	}

	if( m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}



void CDialInCountryUIMgr::InitCountryListUI()
{
	
	if (NULL == m_audio_helper)
	{
		return;
	}
	ZOOM_SDK_NAMESPACE::IList<const wchar_t* >* pCountryList =m_audio_helper->GetAvailableDialinCountryCode();
	int nCount = pCountryList->GetCount();
	for (int i =0; i< nCount ; i++)
	{
		const wchar_t* pCountryCode = pCountryList->GetItem(i);
		AddElement(pCountryCode);
	}

	if(m_audio_helper->IsIncludeTollFree())
	{
		if (m_inlude_free_num)
		{
			m_inlude_free_num->Selected(true);
		}
	}

	ZOOM_SDK_NAMESPACE::IList<const wchar_t* >* pDefaultSelecteCountryList = NULL;
	if (m_audio_helper)
	{
		pDefaultSelecteCountryList = m_audio_helper->GetSelectedDialinCountryCode();
	}
	
	if (pDefaultSelecteCountryList)
	{
		nCount = pDefaultSelecteCountryList->GetCount();
		for (int i = 0; i < nCount ; i++)
		{
			CCheckBoxUI* pCtr = dynamic_cast<CCheckBoxUI* >(FindElement(pDefaultSelecteCountryList->GetItem(i)));
			if (pCtr)
			{
				pCtr->Selected(true);
			}
		}
	}



}

ZOOM_SDK_NAMESPACE::IList<const wchar_t* >* CDialInCountryUIMgr::GetSelectedDialinCountryCode()
{
	if (m_audio_helper)
	{
		return m_audio_helper->GetSelectedDialinCountryCode();
	}

	return NULL;
}

void CDialInCountryUIMgr::AddElement( LPCTSTR name )
{
	CCheckBoxUI* tmp = new CCheckBoxUI;
	if (tmp)
	{
		tmp->SetAttribute(L"name", name);
		tmp->SetAttribute(L"text", name);
		tmp->SetAttribute(L"width", L"200");
		tmp->SetAttribute(L"height", L"20");
		tmp->SetAttribute(L"textpadding", L"25,0,0,0");
		tmp->SetAttribute(L"align", L"left,singleline");
		tmp->SetAttribute(L"normalimage", L"res=\'checkbox_bk.png\' restype=\'ZPIMGRES\' source=\'0,0,18,18\' dest=\'2,2,20,20\'");
		tmp->SetAttribute(L"selectedimage", L"res=\'checkbox_bk.png\' restype=\'ZPIMGRES\' source=\'90,0,108,18\' dest=\'2,2,20,20\'");

	}
	if (m_country_list)
	{
		m_country_list->Add(tmp);
	}
}

void CDialInCountryUIMgr::DoClickSaveChangeBtn()
{		
	ZOOM_SDK_NAMESPACE::ISelectMeetingItemTelAudioHelper* pAudioHelper = NULL;
	if (m_pScheduleMeetingItem)
	{
		pAudioHelper = m_pScheduleMeetingItem->GetScheduleTelAudioHelper();
	}
	
	// remove all country
	ZOOM_SDK_NAMESPACE::IList<const wchar_t* >* pDefaultSelecteCountryList = NULL;
	if (m_audio_helper)
	{
		pDefaultSelecteCountryList = m_audio_helper->GetSelectedDialinCountryCode();
	}
	
	if (pDefaultSelecteCountryList)
	{
		int n = pDefaultSelecteCountryList->GetCount();
		for (int i = n-1; i >= 0 ; i--)
		{
			if (pDefaultSelecteCountryList)
			{
				ZOOM_SDK_NAMESPACE::SDKError err = pAudioHelper->RemoveDefaultDialInCountry(pDefaultSelecteCountryList->GetItem(i));
			}
			
		}
	}

	int nCount = 0;
	if (m_country_list)
	{
		nCount = m_country_list->GetCount();
	}
	//reselct country
	for (int i =0; i < nCount; i++)
	{
		CCheckBoxUI* pCtr = dynamic_cast<CCheckBoxUI* >(m_country_list->GetItemAt(i));
		if (pCtr && pAudioHelper)
		{
			if(pCtr->IsSelected())
			{
				pAudioHelper->SelectDefaultDialInCountry(pCtr->GetName().GetData());	
			}
		}
	}

	if (pAudioHelper && m_inlude_free_num)
	{
		pAudioHelper->EnableIncludeTollFree(m_inlude_free_num->IsSelected());
	}

	if (m_main_ptr)
	{
		m_main_ptr->InitDialInCountry();
	}
	ShowWindow(false);
}

void CDialInCountryUIMgr::UpdateShowList()
{
	if (m_show_country_edit)
	{
		m_show_country_edit->SetText(L"");
	}

	int nCount = 0;
	if (m_country_list)
	{
		nCount = m_country_list->GetCount();
	}
	for (int i =0; i < nCount; i++)
	{
		CCheckBoxUI* pCtr = dynamic_cast<CCheckBoxUI* >(m_country_list->GetItemAt(i));
		if (pCtr&&m_show_country_edit)
		{
			if(pCtr->IsSelected())
			{
				std::wstring country_code = std::wstring(pCtr->GetName().GetData())+L"\n";
				m_show_country_edit->AppendText(country_code.c_str());
			}
		}
	}

}


CControlUI* CDialInCountryUIMgr::FindElement( LPCTSTR name )
{
	if (m_country_list)
	{
		return m_country_list->FindSubControl(name);
	}
	return NULL;
}