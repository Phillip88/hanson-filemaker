

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Thu Nov 15 11:27:20 2012
 */
/* Compiler settings for .\NbbfC.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __NbbfC_i_h__
#define __NbbfC_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICreate_FWD_DEFINED__
#define __ICreate_FWD_DEFINED__
typedef interface ICreate ICreate;
#endif 	/* __ICreate_FWD_DEFINED__ */


#ifndef __Create_FWD_DEFINED__
#define __Create_FWD_DEFINED__

#ifdef __cplusplus
typedef class Create Create;
#else
typedef struct Create Create;
#endif /* __cplusplus */

#endif 	/* __Create_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICreate_INTERFACE_DEFINED__
#define __ICreate_INTERFACE_DEFINED__

/* interface ICreate */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICreate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("77711067-7683-4A37-B239-67289449CD7D")
    ICreate : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ LONG lID1,
            /* [in] */ LONG lID2,
            /* [in] */ LONG lID3,
            /* [retval][out] */ BSTR *pbstrKey) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICreateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICreate * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICreate * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICreate * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICreate * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICreate * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICreate * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICreate * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            ICreate * This,
            /* [in] */ LONG lID1,
            /* [in] */ LONG lID2,
            /* [in] */ LONG lID3,
            /* [retval][out] */ BSTR *pbstrKey);
        
        END_INTERFACE
    } ICreateVtbl;

    interface ICreate
    {
        CONST_VTBL struct ICreateVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICreate_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICreate_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICreate_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICreate_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICreate_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICreate_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICreate_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICreate_Create(This,lID1,lID2,lID3,pbstrKey)	\
    ( (This)->lpVtbl -> Create(This,lID1,lID2,lID3,pbstrKey) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICreate_INTERFACE_DEFINED__ */



#ifndef __NbbfCLib_LIBRARY_DEFINED__
#define __NbbfCLib_LIBRARY_DEFINED__

/* library NbbfCLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_NbbfCLib;

EXTERN_C const CLSID CLSID_Create;

#ifdef __cplusplus

class DECLSPEC_UUID("668B80D2-A842-4065-9AB1-9AF4BDC18C1A")
Create;
#endif
#endif /* __NbbfCLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


