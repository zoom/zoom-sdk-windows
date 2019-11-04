#include "stdafx.h"
#include "user_manager.h"

//////////////////////////////////////////////////////////////////////////
CSDKUserList::CSDKUserList()
{

}

CSDKUserList::~CSDKUserList()
{
	ClearAll();
}

int CSDKUserList::GetCount()
{
	return m_pUserList.size();
}

ZOOM_SDK_NAMESPACE::IUserInfo* CSDKUserList::GetItem( unsigned int index )
{
	if(index >= 0 && index < m_pUserList.size())
		return m_pUserList[index];
	else
		return NULL;
}

void CSDKUserList::AddItem( ZOOM_SDK_NAMESPACE::IUserInfo* elem )
{
	//if(m_pUserList.capacity() > m_pUserList.size())
	if(m_pUserList.capacity() < m_pUserList.max_size())
	{
		if (NULL == elem)
			return;
		map<unsigned int, ZOOM_SDK_NAMESPACE::IUserInfo*>::iterator iterMap_ = m_mapUserinfo.find(elem->GetUserID());
		if(m_mapUserinfo.end() != iterMap_)
			return;
		m_pUserList.push_back(elem);
		m_mapUserinfo.insert(std::pair<unsigned int, ZOOM_SDK_NAMESPACE::IUserInfo*>(elem->GetUserID(), elem));
	}
}

void CSDKUserList::RemoveItemByID( unsigned int userID )
{

	std::vector<ZOOM_SDK_NAMESPACE::IUserInfo*>::iterator iter_ = m_pUserList.begin();
	for (;m_pUserList.end() != iter_; iter_++)
	{
		//if(userID == (*iter_)->GetUserID())
		if ((*iter_) == m_mapUserinfo[userID])
		{
			m_pUserList.erase(iter_);
			map<unsigned int, ZOOM_SDK_NAMESPACE::IUserInfo*>::iterator iterMap_ = m_mapUserinfo.find(userID);			
			m_mapUserinfo.erase(iterMap_);
			return;
		}
	}
}

void CSDKUserList::ClearAll()
{
	if(!m_pUserList.empty())
		m_pUserList.clear();
	if(!m_mapUserinfo.empty())
		m_mapUserinfo.clear();
}

ZOOM_SDK_NAMESPACE::IUserInfo* CSDKUserList::GetUserByID( unsigned int userID )
{
	int nCount = GetCount();
	for(int i = 0; i<nCount; ++i)
	{
		if (userID == m_pUserList[i]->GetUserID())
			return m_pUserList[i];
	}
	return NULL;
}

ZOOM_SDK_NAMESPACE::IUserInfo* CSDKUserList::GetUserByName( std::wstring userName )
{
	int nCount = GetCount();
	for(int i = 0; i<nCount; ++i)
	{
		const wchar_t* user_name = m_pUserList[i]->GetUserName();
		if( StrCmpCW(userName.c_str(), user_name) == 0)
			return m_pUserList[i];
	}
	return NULL;
}