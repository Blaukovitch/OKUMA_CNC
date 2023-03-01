#include "okumagrd.h"

/*
ELF, CRACKLAB, 2023
MY WRAPPER >> COM (TRANSDETECTAP.DLL)
*/

 ITransDetectIf* tdsIf = 0;
 HRESULT res = 0;
 DWORD LastError_CODE = 0;

void okumagrd_Init_first()
{
	::SetLastError(ERROR_SUCCESS);

	//COM Instance
	res = ::OleInitialize(NULL);
	res = ::CoCreateInstance(CLSID_TransDetectIf, NULL, CLSCTX_INPROC_SERVER, __uuidof(ITransDetectIf), (LPVOID*)&tdsIf);
	LastError_CODE = GetLastError();
	if (SUCCEEDED(res))
		tdsIf->AddRef();
}

DWORD okumagrd_last_error()
{
	return LastError_CODE;
}

void okumagrd_Release()
{
	if (SUCCEEDED(res))
		tdsIf->Release();
}

signed int get_nc_data__wrapper(ENUM_OK_ID lDataId, __out byte* pDataPtr, unsigned int ulDataSize, ENUM_OK_ERRORS* pErr_code)
{
	if (!tdsIf)
		return res;

	if (!pDataPtr)
		return res;

	register signed int ret = tdsIf->td_get_nc_data((unsigned int)lDataId, pDataPtr, ulDataSize, (int*)pErr_code);
	LastError_CODE = ::GetLastError();
	return ret;
}

signed int set_nc_data__wrapper(ENUM_OK_ID lDataId,      byte* pDataPtr, unsigned int ulDataSize, ENUM_OK_ERRORS* pErr_code)
{
	if (!tdsIf)
		return res;

	if (!pDataPtr)
		return res;

	register signed int ret = tdsIf->td_set_nc_data((unsigned int)lDataId, pDataPtr, ulDataSize, (int*)pErr_code);
	LastError_CODE = ::GetLastError();
	return ret;
}

const char* okumagrd_error_code_to_stringA(OKUMA_ERRORS Err_code)
{
	switch (Err_code)
	{
	case OKUMA_NOERROR: {return "NO_ERROR"; }
	case OKUMA_INVALID_ID: {return "DIALOGRD INTERNAL FATAL ERROR: Invalid ID"; }
	case OKUMA_ACCESS_REFUSE_READ_WRITE: {return "DIALOGRD INTERNAL FATAL ERROR: Access Refuse(Read/Write)"; }
	case OKUMA_SIZE_WRONG: {return "DIALOGRD INTERNAL FATAL ERROR: Size Wrong"; }
	default: {return "DIALOGRD INTERNAL FATAL ERROR: Fatal Error"; }
	}//end switch (Err_code)
	return "UNKNOWN";
}

const WCHAR* okumagrd_error_code_to_stringW(OKUMA_ERRORS Err_code)
{
	switch (Err_code)
	{
	case OKUMA_NOERROR: {return L"NO_ERROR"; }
	case OKUMA_INVALID_ID: {return L"DIALOGRD INTERNAL FATAL ERROR: Invalid ID"; }
	case OKUMA_ACCESS_REFUSE_READ_WRITE: {return L"DIALOGRD INTERNAL FATAL ERROR: Access Refuse(Read/Write)"; }
	case OKUMA_SIZE_WRONG: {return L"DIALOGRD INTERNAL FATAL ERROR: Size Wrong"; }
	default: {return L"DIALOGRD INTERNAL FATAL ERROR: Fatal Error"; }
	}//end switch (Err_code)
	return L"UNKNOWN";
}
