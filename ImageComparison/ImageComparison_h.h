

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Dec 20 15:54:24 2016
 */
/* Compiler settings for ImageComparison.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

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


#ifndef __ImageComparison_h_h__
#define __ImageComparison_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IImageComparison_FWD_DEFINED__
#define __IImageComparison_FWD_DEFINED__
typedef interface IImageComparison IImageComparison;

#endif 	/* __IImageComparison_FWD_DEFINED__ */


#ifndef __ImageComparison_FWD_DEFINED__
#define __ImageComparison_FWD_DEFINED__

#ifdef __cplusplus
typedef class ImageComparison ImageComparison;
#else
typedef struct ImageComparison ImageComparison;
#endif /* __cplusplus */

#endif 	/* __ImageComparison_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __ImageComparison_LIBRARY_DEFINED__
#define __ImageComparison_LIBRARY_DEFINED__

/* library ImageComparison */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ImageComparison;

#ifndef __IImageComparison_DISPINTERFACE_DEFINED__
#define __IImageComparison_DISPINTERFACE_DEFINED__

/* dispinterface IImageComparison */
/* [uuid] */ 


EXTERN_C const IID DIID_IImageComparison;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5D2CAD12-44D1-4B35-A140-18671B6AA0D8")
    IImageComparison : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IImageComparisonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IImageComparison * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IImageComparison * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IImageComparison * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IImageComparison * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IImageComparison * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IImageComparison * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IImageComparison * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IImageComparisonVtbl;

    interface IImageComparison
    {
        CONST_VTBL struct IImageComparisonVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImageComparison_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IImageComparison_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IImageComparison_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IImageComparison_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IImageComparison_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IImageComparison_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IImageComparison_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IImageComparison_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ImageComparison;

#ifdef __cplusplus

class DECLSPEC_UUID("8B6CCAD6-AA1E-430F-8394-94DB52B83850")
ImageComparison;
#endif
#endif /* __ImageComparison_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


