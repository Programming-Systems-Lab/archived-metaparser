// MyMetaParserTest1.h : Declaration of the CMyMetaParserTest1

#ifndef __MYMETAPARSERTEST1_H_
#define __MYMETAPARSERTEST1_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CMyMetaParserTest1
class ATL_NO_VTABLE CMyMetaParserTest1 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyMetaParserTest1, &CLSID_MyMetaParserTest1>,
	public IMyMetaParserTest1
{
public:
	CMyMetaParserTest1()
	{
	}

DECLARE_CLASSFACTORY_AUTO_THREAD() 

DECLARE_REGISTRY_RESOURCEID(IDR_MYMETAPARSERTEST1)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMyMetaParserTest1)
	COM_INTERFACE_ENTRY(IMyMetaParserTest1)
END_COM_MAP()

private:
	IXMLDOMDocument2Ptr m_DOMPtr;
	IXMLDOMSchemaCollectionPtr m_SchemaPtr;
	IMyRuleEngine1Ptr m_RulePtr;
	typedef std::vector<_bstr_t> BSVector;
	BSVector m_ruleURIs;
	void GetRuleURI();

// IMyMetaParserTest1
public:
	STDMETHOD(Init)();
	STDMETHOD(Process)(/*[out, retval]*/ VARIANT_BOOL *isSuccessful);
	STDMETHOD(Parse)(/*[in]*/ VARIANT xmlSource, /*[out, retval]*/ VARIANT_BOOL *isSuccessful);

};

#endif //__MYMETAPARSERTEST1_H_
