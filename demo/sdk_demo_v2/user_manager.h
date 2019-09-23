#pragma once
#include "sdk_util.h"
#include <vector>
#include <map>

class CSDKUserList
{
public:
	CSDKUserList();
	virtual ~CSDKUserList();

public:
	int GetCount();
	ZOOM_SDK_NAMESPACE::IUserInfo* GetItem(unsigned int index);
	void AddItem(ZOOM_SDK_NAMESPACE::IUserInfo* elem);
	ZOOM_SDK_NAMESPACE::IUserInfo* GetUserByID(unsigned int userID);
	ZOOM_SDK_NAMESPACE::IUserInfo* GetUserByName(std::wstring userName);
	void RemoveItemByID(unsigned int userid);
	void ClearAll();

protected:
	std::vector<ZOOM_SDK_NAMESPACE::IUserInfo*> m_pUserList;
	std::map<unsigned int, ZOOM_SDK_NAMESPACE::IUserInfo*> m_mapUserinfo;
};