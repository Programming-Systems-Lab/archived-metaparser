// MyREClient2.h : Declaration of the CMyREClient2

#ifndef __MYRECLIENT2_H_
#define __MYRECLIENT2_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyREClient2
class ATL_NO_VTABLE CMyREClient2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyREClient2, &CLSID_MyREClient2>,
	public IMyREClient2
{
public:
	CMyREClient2()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MYRECLIENT2)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMyREClient2)
	COM_INTERFACE_ENTRY(IMyREClient2)
END_COM_MAP()

// IMyREClient2
public:
	STDMETHOD(Process)();
};

#endif //__MYRECLIENT2_H_
