// MyRuleEngine1.h : Declaration of the CMyRuleEngine1

#ifndef __MYRULEENGINE1_H_
#define __MYRULEENGINE1_H_

#include "resource.h"       // main symbols
#include "RuleNode.h"

/////////////////////////////////////////////////////////////////////////////
// CMyRuleEngine1
class ATL_NO_VTABLE CMyRuleEngine1 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyRuleEngine1, &CLSID_MyRuleEngine1>,
	public IMyRuleEngine1
{
public:
	CMyRuleEngine1(); 
	~CMyRuleEngine1();

DECLARE_REGISTRY_RESOURCEID(IDR_MYRULEENGINE1)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMyRuleEngine1)
	COM_INTERFACE_ENTRY(IMyRuleEngine1)
END_COM_MAP()

protected:
	RuleNode* m_pRuleRoot;
	RuleNode* CreateNode(wchar_t *nodeName);
	RuleNode* ProcessNode(IXMLDOMNodePtr pNode);

// IMyRuleEngine1
public:
	STDMETHOD(Process)(/*[in]*/ IUnknown* pDoc, /*[out, retval]*/ VARIANT_BOOL* isSuccessful);
	STDMETHOD(CompileRule)(/*[in]*/ VARIANT xmlSource, /*[out, retval]*/ VARIANT_BOOL *isSuccessful);

};

#endif //__MYRULEENGINE1_H_
