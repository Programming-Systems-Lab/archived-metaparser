
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Sun Jan 13 21:38:49 2002
 */
/* Compiler settings for Q:\Project\Visual Studio\RuleEngine1\RuleEngine1.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __RuleEngine1_h__
#define __RuleEngine1_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMyRuleEngine1_FWD_DEFINED__
#define __IMyRuleEngine1_FWD_DEFINED__
typedef interface IMyRuleEngine1 IMyRuleEngine1;
#endif 	/* __IMyRuleEngine1_FWD_DEFINED__ */


#ifndef __MyRuleEngine1_FWD_DEFINED__
#define __MyRuleEngine1_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyRuleEngine1 MyRuleEngine1;
#else
typedef struct MyRuleEngine1 MyRuleEngine1;
#endif /* __cplusplus */

#endif 	/* __MyRuleEngine1_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IMyRuleEngine1_INTERFACE_DEFINED__
#define __IMyRuleEngine1_INTERFACE_DEFINED__

/* interface IMyRuleEngine1 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMyRuleEngine1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("26E2C9EB-E8F4-4340-8E31-9E80666407DD")
    IMyRuleEngine1 : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CompileRule( 
            /* [in] */ VARIANT xmlSource,
            /* [retval][out] */ VARIANT_BOOL *isSuccessful) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Process( 
            /* [in] */ IUnknown *pDoc,
            /* [retval][out] */ VARIANT_BOOL *isSuccessful) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyRuleEngine1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyRuleEngine1 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyRuleEngine1 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyRuleEngine1 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CompileRule )( 
            IMyRuleEngine1 * This,
            /* [in] */ VARIANT xmlSource,
            /* [retval][out] */ VARIANT_BOOL *isSuccessful);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Process )( 
            IMyRuleEngine1 * This,
            /* [in] */ IUnknown *pDoc,
            /* [retval][out] */ VARIANT_BOOL *isSuccessful);
        
        END_INTERFACE
    } IMyRuleEngine1Vtbl;

    interface IMyRuleEngine1
    {
        CONST_VTBL struct IMyRuleEngine1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyRuleEngine1_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyRuleEngine1_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyRuleEngine1_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMyRuleEngine1_CompileRule(This,xmlSource,isSuccessful)	\
    (This)->lpVtbl -> CompileRule(This,xmlSource,isSuccessful)

#define IMyRuleEngine1_Process(This,pDoc,isSuccessful)	\
    (This)->lpVtbl -> Process(This,pDoc,isSuccessful)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMyRuleEngine1_CompileRule_Proxy( 
    IMyRuleEngine1 * This,
    /* [in] */ VARIANT xmlSource,
    /* [retval][out] */ VARIANT_BOOL *isSuccessful);


void __RPC_STUB IMyRuleEngine1_CompileRule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMyRuleEngine1_Process_Proxy( 
    IMyRuleEngine1 * This,
    /* [in] */ IUnknown *pDoc,
    /* [retval][out] */ VARIANT_BOOL *isSuccessful);


void __RPC_STUB IMyRuleEngine1_Process_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMyRuleEngine1_INTERFACE_DEFINED__ */



#ifndef __RULEENGINE1Lib_LIBRARY_DEFINED__
#define __RULEENGINE1Lib_LIBRARY_DEFINED__

/* library RULEENGINE1Lib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_RULEENGINE1Lib;

EXTERN_C const CLSID CLSID_MyRuleEngine1;

#ifdef __cplusplus

class DECLSPEC_UUID("A82F0487-A246-4BF1-A9D7-DB87A087155B")
MyRuleEngine1;
#endif
#endif /* __RULEENGINE1Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


