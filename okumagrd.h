//ELF, CRACKLAB, 2023
#pragma once
#include "TRANSDETECTAP.h"

#define DEF_PASSWORD_DEFAULT_LEN 30

#ifndef _INC_OKUMA_GRD
#define _INC_OKUMA_GRD

//OKUMA ID commands to get/set OLE method
typedef enum OKUMA_ID
{
	OKUMA_UNKNOWN = 0,
	OKUMA_BYTE_1,
	OKUMA_DWORD_2,
	OKUMA_BYTE_3,
	OKUMA_PASSWORD_4,
	//not define
	OKUMA_NOTDEFINE_5,
	OKUMA_NOTDEFINE_6,

	OKUMA_FILETIME_7,
	OKUMA_BYTE_8,
	OKUMA_DWORD_9,
	OKUMA_DWORD_10,
	OKUMA_DWORD_11,
	OKUMA_DWORD_12,
}ENUM_OK_ID;

//OKUMA error enum
typedef enum OKUMA_ERRORS
{
	OKUMA_NOERROR = 0,
	OKUMA_INVALID_ID = -1,
	OKUMA_ACCESS_REFUSE_READ_WRITE = -2,
	OKUMA_SIZE_WRONG = -3
}ENUM_OK_ERRORS;

//COM object
extern ITransDetectIf* tdsIf;
//com methods call result
extern HRESULT res;
//LastError after call
extern DWORD LastError_CODE;

// * * * OLE init/release - first/system error control * * *//
//OLE Init FIRST
extern	void okumagrd_Init_first();
//OLE Release
extern	void okumagrd_Release();
//system error control
extern	DWORD okumagrd_last_error();

// * * * COM METHODS WRAPPER * * * //
//READ (GET) from CNC
extern	signed int get_nc_data__wrapper(ENUM_OK_ID lDataId, byte* pDataPtr, unsigned int ulDataSize, ENUM_OK_ERRORS* pErr_code);
//WRITE (SET) to CNC
extern	signed int set_nc_data__wrapper(ENUM_OK_ID lDataId, byte* pDataPtr, unsigned int ulDataSize, ENUM_OK_ERRORS* pErr_code);

// * * * COM ERROR RET CODES * * * //
//Decode Err_code to string (ASCII)
extern	const char* okumagrd_error_code_to_stringA(OKUMA_ERRORS Err_code);
//Decode Err_code to string (wide char)
extern	const WCHAR* okumagrd_error_code_to_stringW(OKUMA_ERRORS Err_code);
	
#endif