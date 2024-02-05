#include "okumagrd.h"
#include <iostream>

/*
ELF, CRACKLAB, 2023-2024
td_get_nc_data (+12)	lDataId	ulDataSize
    12	DWORD
    11	DWORD
    9	DWORD
    8	BYTE
    3	BYTE
    2	DWORD
    1	BYTE
td_set_nc_data (+16)
    10	DWORD
    7	QWORD
    4	strlen(password)
    2	DWORD
*/

//func declaration
void TEST_DWORD(ENUM_OK_ID DWORD_ID);
void TEST_BYTE( ENUM_OK_ID DWORD_ID);
void TEST_FILETIME(ENUM_OK_ID DWORD_ID);
void TEST_STRING(ENUM_OK_ID DWORD_ID);
int main()
{
    printf("Hello OKUMA! %-5i v2.0\n", 1);

    okumagrd_Init_first();
    DWORD le = okumagrd_last_error();
    if (le)
    {
        printf("[!] error during class init = %x\r\n", le);
        return le;
    }//end if (le) 
    
    //START 12
    TEST_DWORD(OKUMA_DWORD_12);
    TEST_DWORD(OKUMA_DWORD_11);
    TEST_DWORD(OKUMA_DWORD_10);
    TEST_DWORD(OKUMA_DWORD_9);
    TEST_BYTE (OKUMA_BYTE_8);
    TEST_FILETIME(OKUMA_FILETIME_7);
    //SKIP 6 ?? 
    //SKIP 5 ?? 
    TEST_STRING(OKUMA_PASSWORD_4);
    TEST_BYTE  (OKUMA_BYTE_3);
    TEST_DWORD (OKUMA_DWORD_2);
    TEST_BYTE  (OKUMA_BYTE_1);
    //END 0

    okumagrd_Release();
}

//or as template, of course...)
void TEST_DWORD( ENUM_OK_ID DWORD_ID)
{
    DWORD dword_dataprt = 0;
    signed int return_code = 0;
    ENUM_OK_ERRORS err_state = OKUMA_NOERROR;

    printf("+---------------------- [ -10%i -10%s ]-------------------------------------+\n", DWORD_ID, "DWORD" );

    return_code = get_nc_data__wrapper(DWORD_ID, (byte*)&dword_dataprt, sizeof(dword_dataprt), &err_state);
    printf("GET< %-20li -10%i -10%s\n", dword_dataprt, return_code, okumagrd_error_code_to_stringA(err_state));

    //set
        return_code = set_nc_data__wrapper(DWORD_ID, (byte*)&dword_dataprt, sizeof(dword_dataprt), &err_state);
        printf("SET> -20%li -10%i -10%s\n", dword_dataprt, return_code, okumagrd_error_code_to_stringA(err_state));
}

void TEST_BYTE(ENUM_OK_ID DWORD_ID)
{
    printf("+---------------------- [ %-5i %-5s ]-------------------------------------+\n", DWORD_ID, "BYTE");
    BYTE  byte_dataprt = 0;
    signed int return_code = 0;
    ENUM_OK_ERRORS err_state = OKUMA_NOERROR;

    return_code = get_nc_data__wrapper(DWORD_ID, &byte_dataprt, sizeof(byte_dataprt), &err_state);
    printf("GET< %-10i %-5i %-5s\n", byte_dataprt, return_code, okumagrd_error_code_to_stringA(err_state));
    //set
        return_code = set_nc_data__wrapper(DWORD_ID, &byte_dataprt, sizeof(byte_dataprt), &err_state);
        printf("SET> %-10i %-5i %-5s\n", byte_dataprt, return_code, okumagrd_error_code_to_stringA(err_state));
}

void TEST_FILETIME(ENUM_OK_ID DWORD_ID)
{
    printf("+---------------------- [ %-5i %-5s ]-------------------------------------+\n", DWORD_ID, "FILETIME");

    //(FILETIME)
    __int64  filetime_prt = 0;
    signed int return_code = 0;
    ENUM_OK_ERRORS err_state = OKUMA_NOERROR;
    
    return_code = get_nc_data__wrapper(DWORD_ID, (byte*)&filetime_prt, sizeof(filetime_prt), &err_state);
    printf("GET< %-10llu %-5i %-5s\n", filetime_prt, return_code, okumagrd_error_code_to_stringA(err_state));

        //set
        return_code = set_nc_data__wrapper(DWORD_ID, (byte*)&filetime_prt, sizeof(filetime_prt), &err_state);
        printf("SET> %-10llu %-5i %-5s\n", filetime_prt, return_code, okumagrd_error_code_to_stringA(err_state));
}

void TEST_STRING(ENUM_OK_ID DWORD_ID)
{
    printf("+---------------------- [ %-5i %-5s ]-------------------------------------+\n", DWORD_ID, "STRING");

    //(password)
    unsigned char password_string[DEF_PASSWORD_DEFAULT_LEN];
    signed int return_code = 0;
    ENUM_OK_ERRORS err_state = OKUMA_NOERROR;

    return_code = get_nc_data__wrapper(DWORD_ID, (byte*)&password_string, sizeof(password_string), &err_state);
    printf("GET< %-10s %-5i %-5s\n", password_string,return_code, okumagrd_error_code_to_stringA(err_state));
    
        //set
        return_code = set_nc_data__wrapper(DWORD_ID, (byte*)&password_string, sizeof(password_string), &err_state);
        printf("SET> %-10s %-5i %-5s\n", password_string, return_code, okumagrd_error_code_to_stringA(err_state));
}
