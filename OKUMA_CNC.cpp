#include "okumagrd.h"
#include <iostream>

/*
ELF, CRACKLAB, 2023
*/

//func declaration
void TEST_DWORD(ENUM_OK_ID DWORD_ID);

int main()
{
    printf("Hello OKUMA! %-5i\r\n", 2);

    okumagrd_Init_first();
    DWORD le = okumagrd_last_error();
    if (le)
    {
        printf("[!] error during class init = %x\r\n", le);
        return le;
    }//end if (le) 
    
    TEST_DWORD(0);

    okumagrd_Release();
}

//or as template, of course...)
void TEST_DWORD( ENUM_OK_ID DWORD_ID)
{
    DWORD dword_dataprt = 0;
    signed int return_code = 0;
    ENUM_OK_ERRORS err_state = OKUMA_NOERROR;

    printf("+---------------------- [ %i %s ]-------------------------------------+\n", DWORD_ID, "DWORD" );

    return_code = get_nc_data__wrapper(DWORD_ID, (byte*)&dword_dataprt, sizeof(dword_dataprt), &err_state);
    printf("GET< %li %i %s\n", dword_dataprt, return_code, okumagrd_error_code_to_stringA(err_state));

    //set
        return_code = set_nc_data__wrapper(DWORD_ID, (byte*)&dword_dataprt, sizeof(dword_dataprt), &err_state);
        printf("SET> %li %i %s\n", dword_dataprt, return_code, okumagrd_error_code_to_stringA(err_state));
}


