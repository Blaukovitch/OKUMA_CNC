//ELF, CRACKLAB, 2023
//TRANSDETECTAP.DLL [com object]
#pragma once

#include <windows.h>
#include <ole2.h>


class __declspec(uuid("{CE5E9000-0BB0-44CF-8DB9-4BC8C84A84B7}")) TransDetectIf;
EXTERN_C const CLSID CLSID_TransDetectIf;
EXTERN_C const IID IID_ITransDetectIf;

#if defined(__cplusplus)
extern "C++"
{
    MIDL_INTERFACE("02C34EDD-B584-4790-88D1-7F415AA6B77B")
     ITransDetectIf : public IUnknown
    {
    public:
        //GET (read)
        virtual signed int STDMETHODCALLTYPE  td_get_nc_data(unsigned int lDataId, byte* pDataPtr,  unsigned int ulDataSize, int* pErr_code) = 0;
        //SET (write)
        virtual signed int STDMETHODCALLTYPE  td_set_nc_data(unsigned int lDataId, byte* pDataPtr,  unsigned int ulDataSize, int* pErr_code) = 0;
    };
} // extern
#endif
