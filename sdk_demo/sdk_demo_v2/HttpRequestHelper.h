#include <iostream>
#include <Windows.h>
#include <wininet.h>

#pragma comment(lib, "wininet.lib")


enum infoType
{
	info_user_token = 0,
	info_user_zak,
	info_user_basic

};

class CZoomHttpRequestHelper
{
public:
	CZoomHttpRequestHelper();
	~CZoomHttpRequestHelper();
	void SetRestAPIAccessToken(wchar_t* strAccessToken);
	void SetUserEmail(wchar_t* strUserEmail);
	bool MakeAPIUrlTokens();
	const wchar_t* GetSDKURLUserToken() {return m_strAPIURLUserToken;}
	const wchar_t* GetSDKURLZakToken() {return m_strAPIURLZakToken;}
	const wchar_t* GetSDKURLUserID() {return m_strUserID;}
	const UINT64 GetSDKUserPMI() {return m_userPMI;}
	void SetRestAPIDomain(wchar_t* strDomain);
	 
private:
	void getResponse();
	bool getAPIUserInfo(infoType nType);
	bool WcharToChar(const TCHAR * tchar_, char * char_);
	bool CharToWchar (const char * char_, TCHAR * tchar_); 
	bool GetTokenFromFile(infoType nType);
	bool GetUserBasicInfoFromFile();
	void DeleteTempFile(wchar_t* strFileDelete);
private:
	wchar_t* m_strDomain;
	wchar_t* m_strUserEmail; //the account that user login
	wchar_t* m_strAccessToken;
	wchar_t*  m_strMeetingStartUrl;
	wchar_t m_strAPIURLUserToken[1024];
	wchar_t m_strAPIURLZakToken[1024];
	wchar_t m_strUserID[32];
	UINT64 m_userPMI;
};
