
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Jan 14 20:50:21 2002
 */
/* Compiler settings for Q:\Project\Visual Studio\RuleEngine1\Client2\Client2.idl:
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

#ifndef __Client2_h__
#define __Client2_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMyREClient2_FWD_DEFINED__
#define __IMyREClient2_FWD_DEFINED__
typedef interface IMyREClient2 IMyREClient2;
#endif 	/* __IMyREClient2_FWD_DEFINED__ */


#ifndef __MyREClient2_FWD_DEFINED__
#define __MyREClient2_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyREClient2 MyREClient2;
#else
typedef struct MyREClient2 MyREClient2;
#endif /* __cplusplus */

#endif 	/* __MyREClient2_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IMyREClient2_INTERFACE_DEFINED__
#define __IMyREClient2_INTERFACE_DEFINED__

/* interface IMyREClient2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMyREClient2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4C31E4AC-A5B3-470F-99D5-00F9AD99B811")
    IMyREClient2 : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Process( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyREClient2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyREClient2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyREClient2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyREClient2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Process )( 
            IMyREClient2 * This);
        
        END_INTERFACE
    } IMyREClient2Vtbl;

    interface IMyREClient2
    {
        CONST_VTBL struct IMyREClient2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyREClient2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyREClient2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyREClient2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMyREClient2_Process(This)	\
    (This)->lpVtbl -> Process(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMyREClient2_Process_Proxy( 
    IMyREClient2 * This);


void __RPC_STUB IMyREClient2_Process_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMyREClient2_INTERFACE_DEFINED__ */



#ifndef __CLIENT2Lib_LIBRARY_DEFINED__
#define __CLIENT2Lib_LIBRARY_DEFINED__

/* library CLIENT2Lib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CLIENT2Lib;

EXTERN_C const CLSID CLSID_MyREClient2;

#ifdef __cplusplus

class DECLSPEC_UUID("68845DD2-120D-4E6F-9723-43579ADC6282")
MyREClient2;
#endif
#endif /* __CLIENT2Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


