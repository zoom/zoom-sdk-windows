#pragma once
#include "stdafx.h"
#include <stdio.h>
//#include <mbstring.h>
//#include <windows.h>
#include <stdlib.h>
#include <wincrypt.h>
#include <atltime.h>

#pragma comment(lib, "Crypt32.lib")
/*---------------------------------------
 The zoomHmacSHA256 class uses Window Crypt API to create a token for REST API authentication.
It only supports the HMAC SHA256 algorithm.
 Note: This class only supports the windows versions above windows 2000.
 Known Issue: The calling of the API CryptGetHashParam() with the parameter
	HP_HASHSIZE doesn't work. The return buffer size is always 4. However, the 
	second calling of the API can return the correct size of the hash data. So,
	just hard-code a bigger buffer to retrieve the hash data.

 
 Since it is used for a demo. Not too much error handlers and protections are made.
*/

#define ZOOM_SMALLEST_PERIOD_VALIDITY 30 //the smallest period of validity
#define ZOOM_ENCODE_DEFAULT_BUFFER 64
#define ZOOM_ENCODE_BIGGEST_BUFFER 256
#define ZOOM_ENCODE_DEFAULT_HASHLENGTH 64

enum zoomCryptError
{
	ERROR_CRYPT_SUCCESS = 0,
	ERROR_NO_API_KEY,
	ERROR_NO_API_SECRET,
	ERROR_NO_EXPIRED_TIME,
	ERROR_EXPIRED_TIME_ILLEGAL,
	ERROR_ACQUIRE_CSP_FAILED,
	ERROR_IMPORT_KEY_FAILED,
	ERROR_CREATE_HASH_FAILED,
	ERROR_SET_HASH_PARAM_FAILED,
	ERROR_HASH_DATE_FAILED,
	ERROR_GET_HASH_SIZE_FAILED,
	ERROR_GET_HASH_DATA_FAILED,
	ERROR_MALLOC_FOR_HASHBUF_FAILED,
	ERROR_MAKE_PAYLOAD_FIALED,
	ERROR_MAKE_HMAC_MESSAGEBODY_FAILED,
};


//self-define a structure KEYBLOB for importing a key used by HMAC(the key here is corresponding to REST API secret)
typedef struct tagKeyBlob
{
	BLOBHEADER hdr;
	DWORD cbKeySize;
}KEYBLOB;


class zoomHmacSHA256
{
public:
	zoomHmacSHA256();
	~zoomHmacSHA256();

	bool SetRestAPIKey(char* strKey);
	bool SetTokenValidityPeriod(DWORD dwValidityPeriod); //period of validity. Unit is second.
	bool SetRestAPISecret(char* strSecret);

	zoomCryptError MakeToken();
	char* GetToken();
	DWORD GetTokenSize();

	char Base64URLGetChar(BYTE num);
	size_t Base64URLEncode(const char *pSrc, char *pDest, size_t srclen);
	bool CharToWchar (const char *pSrc, TCHAR *pDest);
	bool WcharToChar(const TCHAR *pSrc, char *pDest);

private:
	bool MakeJWTHeader();
	bool MakeJWTPayload();
	bool CombineFinalToken();
	bool MakeHmacMessage();

private:
	char* m_strKey;
	char* m_strSecret;
	char* m_strToken;
	char* m_strMessageBody;
	char* m_strJWTHeader;
	char* m_strJWTPayload;
	char m_strJWTHeaderEncoded[ZOOM_ENCODE_DEFAULT_BUFFER];
	char m_strJWTPayloadEncoded[ZOOM_ENCODE_BIGGEST_BUFFER];
	char m_strJWTSignatureEncoded[ZOOM_ENCODE_DEFAULT_BUFFER];
	time_t m_timeExpire;
	
};