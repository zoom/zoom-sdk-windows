#include "stdafx.h"
#include "zoomHmacSHA256.h"

zoomHmacSHA256::zoomHmacSHA256()
{
	m_strKey = NULL;
	m_strSecret = NULL;
	m_strToken = NULL;
	//Hard-code the JWT header because we only support HMAC SHA256 algorithm
	//The header string should be {"alg":"HS256","typ":"JWT"}. 
	m_strJWTHeader = "{\"alg\":\"HS256\",\"typ\":\"JWT\"}";
	m_strJWTPayload = NULL;
	m_strToken = NULL;
	m_strMessageBody = NULL;
}

zoomHmacSHA256::~zoomHmacSHA256()
{
	if(m_strJWTPayload)
		free(m_strJWTPayload);
	if(m_strToken)
		free(m_strToken);
	if(m_strMessageBody)
		free( m_strMessageBody);
}

bool zoomHmacSHA256::SetRestAPIKey(char* strKey)
{
	if(NULL == strKey)
		return false;
	m_strKey = strKey;
	return true;
}
bool zoomHmacSHA256::SetTokenValidityPeriod(DWORD dwValidityPeriod)
{
	//hardcode the smallest period to be 30 seconds.
	if(dwValidityPeriod < ZOOM_SMALLEST_PERIOD_VALIDITY)
		return false;

	time_t	tmCurr = time(NULL);
	m_timeExpire = tmCurr + dwValidityPeriod;
	return true;

}
bool zoomHmacSHA256::SetRestAPISecret(char* strSecret)
{
	if(NULL == strSecret)
		return false;
	m_strSecret = strSecret;
	return true;
}

zoomCryptError zoomHmacSHA256::MakeToken()
{
	if(NULL == m_strKey)
		return ERROR_NO_API_KEY;
	if(NULL == m_strSecret)
		return ERROR_NO_API_SECRET;
	if(0 == m_timeExpire)
		return ERROR_NO_EXPIRED_TIME;
	
	zoomCryptError	err(ERROR_CRYPT_SUCCESS);

	HCRYPTPROV  hProv       = NULL;
	HCRYPTKEY   hKey        = NULL;
	HCRYPTHASH  hHmacHash   = NULL;
	PBYTE		pbSignature = NULL;
	PBYTE       pbHashDate      = NULL;
	DWORD       dwHashDataLen   = 0;
	PBYTE		pbBlobSecret = NULL;
	HMAC_INFO   HmacInfo;
	do
	{
		//Acquire a handle of the CSP with provider type PROV_RSA_AES
		if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, 0))
		{
			err = ERROR_ACQUIRE_CSP_FAILED;
			break;
		}

		//----Create the key used by CryptImportKey. So the REST API secret will be used as the 'key'.
		DWORD dwLengthSecret = strlen(m_strSecret);
		KEYBLOB keyBlob;
		keyBlob.hdr.bType = PLAINTEXTKEYBLOB;
		keyBlob.hdr.bVersion = CUR_BLOB_VERSION;
		keyBlob.hdr.reserved = 0;
		keyBlob.hdr.aiKeyAlg = CALG_RC2;  //use CALG_RC2
		keyBlob.cbKeySize = dwLengthSecret; 
		DWORD dwLengthStructBlob = sizeof(keyBlob);
		DWORD dwLengthFinalKey = dwLengthStructBlob+dwLengthSecret; 
		pbBlobSecret = (BYTE*)malloc(dwLengthFinalKey);
		memcpy(pbBlobSecret, &keyBlob,dwLengthStructBlob);
		memcpy(&pbBlobSecret[dwLengthStructBlob] ,m_strSecret ,dwLengthSecret); //append the secret to the end of the structure
		//----now we get the new key for CryptImportKey

		//import key for the CSP
		//using CRYPT_IPSEC_HMAC_KEY because the key size may be bigger than 16 bytes
		if(!CryptImportKey(hProv, pbBlobSecret, dwLengthFinalKey, 0, CRYPT_IPSEC_HMAC_KEY, &hKey))
		{
			err = ERROR_IMPORT_KEY_FAILED;
			break;
		}
		//create a hash object with algorithm CALG_HMAC
		if (!CryptCreateHash(hProv,	CALG_HMAC, hKey, 0,	&hHmacHash))
		{
			err = ERROR_CREATE_HASH_FAILED;
			break;
		}

		//set the param for the hash object
		ZeroMemory(&HmacInfo, sizeof(HmacInfo));
		HmacInfo.HashAlgid = CALG_SHA_256; //use SHA-256 algorithm
		if (!CryptSetHashParam(hHmacHash, HP_HMAC_INFO, (BYTE*)&HmacInfo, 0)) 
		{
			err = ERROR_SET_HASH_PARAM_FAILED;
			break;
		}
		
		//hash the data
		//make the message body first
		if( !MakeJWTHeader() || !MakeJWTPayload() || !MakeHmacMessage() )
		{
			err = ERROR_MAKE_HMAC_MESSAGEBODY_FAILED;
			break;
		}

		if (!CryptHashData(hHmacHash, (BYTE*)m_strMessageBody, strlen(m_strMessageBody), 0))
		{
			err = ERROR_HASH_DATE_FAILED;
			break;
		}

		// Referto known issue in the header file.
		if (!CryptGetHashParam(hHmacHash, HP_HASHSIZE, NULL, &dwHashDataLen, 0))		
		{
			err = ERROR_GET_HASH_SIZE_FAILED;
			break;
		}
		
		dwHashDataLen = ZOOM_ENCODE_DEFAULT_HASHLENGTH;
		pbHashDate = (BYTE*)malloc(dwHashDataLen);
		if(NULL == pbHashDate) 
		{
			err = ERROR_MALLOC_FOR_HASHBUF_FAILED;
			break;
		}

		if (!CryptGetHashParam(hHmacHash, HP_HASHVAL, pbHashDate, &dwHashDataLen, 0))
		{
			err = ERROR_GET_HASH_DATA_FAILED;
			break;
		}
		
		//Now we got the hash data. Make the final token
		Base64URLEncode((char*)pbHashDate, m_strJWTSignatureEncoded, dwHashDataLen);//use the really length of the buffer
		CombineFinalToken();

	}while(0);

	if (ERROR_SUCCESS != err)
	{
		if(hHmacHash)
			CryptDestroyHash(hHmacHash);
		if(hKey)
			CryptDestroyKey(hKey);
		if(hProv)
			CryptReleaseContext(hProv, 0);
		if(pbHashDate)
			free(pbHashDate);
		if(pbBlobSecret)
			free(pbBlobSecret);
	}
	
	return err;		
}

DWORD zoomHmacSHA256::GetTokenSize()
{
	if(m_strToken)
		return strlen(m_strToken);
	return 0;
}
char* zoomHmacSHA256::GetToken()
{
	return m_strToken;
}

bool zoomHmacSHA256::MakeJWTHeader()
{
	if(NULL == m_strJWTHeader)
		return false;
	
	Base64URLEncode(m_strJWTHeader, m_strJWTHeaderEncoded, strlen(m_strJWTHeader));
	return true;
}

bool zoomHmacSHA256::MakeJWTPayload()
{
	if(NULL == m_strKey || 0 ==m_timeExpire)
		return false;

	if(m_strJWTPayload)
		free(m_strJWTPayload);

	char strTmpExpiredTime[ZOOM_ENCODE_DEFAULT_BUFFER];
	_ui64toa_s(m_timeExpire, strTmpExpiredTime, ZOOM_ENCODE_DEFAULT_BUFFER, 10);

	/*follow code use a hardcode string to test	
	char* strHardcode = "123456789101";
	DWORD dwLengthHardcode=strlen(strHardcode);
	//strTmpExpiredTime = (char*)malloc(dwLengthHardcode);
	strcpy_s(strTmpExpiredTime, dwLengthHardcode, strHardcode);
	*/
	char* strFormat = "{\"iss\":\"\",\"exp\":\"\"}";
 	DWORD dwLenKey = strlen(m_strKey);
	DWORD dwLenExpiredTime = strlen(strTmpExpiredTime);
	DWORD dwLenFormat = strlen(strFormat);
	if(m_strJWTPayload)
		free(m_strJWTPayload);
	DWORD dwTotalLength = dwLenKey + dwLenExpiredTime + dwLenFormat + 1;
	m_strJWTPayload = (char*)malloc(dwTotalLength);
	if(NULL == m_strJWTPayload)
		return false;
	strcpy_s(m_strJWTPayload, dwTotalLength, "{\"iss\":\"");
	strcat_s(m_strJWTPayload, dwTotalLength, m_strKey);
	strcat_s(m_strJWTPayload, dwTotalLength, "\",\"exp\":\"");
	strcat_s(m_strJWTPayload, dwTotalLength, strTmpExpiredTime);
	strcat_s(m_strJWTPayload, dwTotalLength, "\"}");
	Base64URLEncode(m_strJWTPayload, m_strJWTPayloadEncoded, strlen(m_strJWTPayload));
	return true;
}

bool zoomHmacSHA256::CombineFinalToken()
{
	if(NULL == m_strJWTHeaderEncoded || NULL == m_strJWTPayloadEncoded || NULL == m_strJWTSignatureEncoded)
		return false;
	DWORD dwLengthHeader = strlen(m_strJWTHeaderEncoded);
	DWORD dwLengthPayLoad = strlen(m_strJWTPayloadEncoded);
	DWORD dwLengthSignature = strlen(m_strJWTSignatureEncoded);
	if(m_strToken)
		free(m_strToken);
	DWORD dwTotalLength = dwLengthHeader+dwLengthPayLoad+dwLengthSignature+3;
	m_strToken = (char*)malloc(dwTotalLength); //2 is for 2 dots
	if(!m_strToken)
		return false;
	
	strcpy_s(m_strToken, dwTotalLength, m_strJWTHeaderEncoded);
	strcat_s(m_strToken, dwTotalLength, ".");
	strcat_s(m_strToken, dwTotalLength, m_strJWTPayloadEncoded);
	strcat_s(m_strToken, dwTotalLength, ".");
	strcat_s(m_strToken, dwTotalLength, m_strJWTSignatureEncoded);
	return true;
}

bool zoomHmacSHA256::MakeHmacMessage()
{
	if(NULL == m_strJWTHeaderEncoded || NULL == m_strJWTPayloadEncoded)
		return false;
	DWORD dwLengthHeader = strlen(m_strJWTHeaderEncoded);
	DWORD dwLengthPayLoad = strlen(m_strJWTPayloadEncoded);
	if(m_strMessageBody)
		free(m_strMessageBody);
	DWORD dwTotalLength = dwLengthHeader+dwLengthPayLoad+2;
	m_strMessageBody = (char*)malloc(dwTotalLength);
	if(!m_strMessageBody)
		return false;
	strcpy_s(m_strMessageBody, dwTotalLength, m_strJWTHeaderEncoded);
	strcat_s(m_strMessageBody, dwTotalLength, ".");
	strcat_s(m_strMessageBody, dwTotalLength, m_strJWTPayloadEncoded);
	return true;
}

char zoomHmacSHA256::Base64URLGetChar(BYTE num)
{
	return  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_="[num];
}

size_t zoomHmacSHA256::Base64URLEncode(const char *pSrc, char *pDest, size_t srclen)
{
	BYTE input[3], output[4];
	size_t i, index_src = 0, index_dest = 0;
	for(i = 0; i < srclen; i += 3)
	{
		//char [0]
		input[0] = pSrc[index_src++];
		output[0] = (BYTE)(input[0] >> 2);
		pDest[index_dest++] = Base64URLGetChar(output[0]);

		//char [1]
		if(index_src < srclen)
		{
			input[1] = pSrc[index_src++];
			output[1] = (BYTE)(((input[0] & 0x03) << 4) + (input[1] >> 4));
			pDest[index_dest++] = Base64URLGetChar(output[1]);
		}
		else
		{
			output[1] = (BYTE)((input[0] & 0x03) << 4);
			pDest[index_dest++] = Base64URLGetChar(output[1]);
			break;
		}

		//char [2]
		if(index_src < srclen)
		{
			input[2] = pSrc[index_src++];
			output[2] = (BYTE)(((input[1] & 0x0f) << 2) + (input[2] >> 6));
			pDest[index_dest++] = Base64URLGetChar(output[2]);
		}
		else
		{
			output[2] = (BYTE)((input[1] & 0x0f) << 2);
			pDest[index_dest++] = Base64URLGetChar(output[2]);
			break;
		}

		//char [3]
		output[3] = (BYTE)(input[2] & 0x3f);
		pDest[index_dest++] = Base64URLGetChar(output[3]);
	}
	//null-terminator
	pDest[index_dest] = 0;
	return index_dest;
}

bool zoomHmacSHA256::WcharToChar(const TCHAR *pSrc, char *pDest)
{  
	int iLength ;  
	iLength = WideCharToMultiByte(CP_ACP, 0, pSrc, -1, NULL, 0, NULL, NULL);  
	WideCharToMultiByte(CP_ACP, 0, pSrc, -1, pDest, iLength, NULL, NULL);  
	return true;
} 

bool zoomHmacSHA256::CharToWchar (const char *pSrc, TCHAR *pDest)
{  
	int iLength ;  
	iLength = MultiByteToWideChar(CP_ACP, 0, pSrc, strlen(pSrc), NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, pSrc, strlen(pSrc), pDest, iLength);
	if(NULL != &pDest[iLength])
		pDest[iLength] = '\0';
	return true;
}