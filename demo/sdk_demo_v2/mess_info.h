#pragma once
#include "sdk_util.h"
#include "stdafx.h"

class CSDKMessInfo
{
public:
	static CSDKMessInfo& GetInst();
	bool Init();
	void Cleanup();
	const wchar_t* GetErrorDescription();
	int GetErrorCode();
	const wchar_t* GetErrorType();
	wchar_t* GetErrorMessInfo();

private:
	CSDKMessInfo();
	~CSDKMessInfo();
	const ZOOM_SDK_NAMESPACE::IZoomLastError* m_pZoomLastError;
	const wchar_t* m_pErrorDescription;
	int m_nErrorCode;
	std::wstring m_sErrorType;
	wchar_t* m_pErrorMessInfo;
};