// MyMetaParserTest1.cpp : Implementation of CMyMetaParserTest1
#include "stdafx.h"
#include "ComMetaParserTest1.h"
#include "MyMetaParserTest1.h"
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// CMyMetaParserTest1


STDMETHODIMP CMyMetaParserTest1::Parse(VARIANT xmlSource, VARIANT_BOOL *isSuccessful)
{
	// TODO: Add your implementation code here
	BSTR bstrValue;
	long l;
	//char buf[128];

	*isSuccessful = m_DOMPtr->load(xmlSource);

	if(*isSuccessful == VARIANT_TRUE)
	{
		m_SchemaPtr = m_DOMPtr->namespaces;
		l = m_SchemaPtr->length;
	
		for(long iIndex = 0; iIndex < l; iIndex++)
		{
			m_SchemaPtr->get_namespaceURI(iIndex, &bstrValue);
			::MessageBoxW(NULL, bstrValue, L"Namespaces", MB_OK);
		}
		/*
		m_DOMPtr->setProperty(L"SelectionLanguage", _variant_t(L"XPath"));

		IXMLDOMNodeListPtr pNodeList;
		pNodeList = m_DOMPtr->selectNodes(L"//Book");
		IXMLDOMSelectionPtr pSelection;
		pSelection = pNodeList;
		long length;
		length = pSelection->length;
		sprintf(buf, "%d", length);
		MessageBox(NULL, buf, "Length", MB_OK);
		*/
	}	
	return S_OK;
}

STDMETHODIMP CMyMetaParserTest1::Process(VARIANT_BOOL *isSuccessful)
{
	// TODO: Add your implementation code here
	*isSuccessful = VARIANT_FALSE;
	GetRuleURI();
	for(int i = 0; i < m_ruleURIs.size(); i++)
	{
		m_RulePtr->CompileRule(_variant_t(m_ruleURIs[i]));
		m_RulePtr->Process(m_DOMPtr.GetInterfacePtr());
	}
	return S_OK;
}

void CMyMetaParserTest1::GetRuleURI()
{
	_bstr_t uri("Q:\\Project\\xml\\ruleSet.xml");
	m_ruleURIs.push_back(uri);
}

STDMETHODIMP CMyMetaParserTest1::Init()
{
	// TODO: Add your implementation code here
	CoInitialize(NULL);

	HRESULT hr1, hr2;

	hr1 = m_DOMPtr.CreateInstance(__uuidof(DOMDocument40));
	hr2 = m_RulePtr.CreateInstance(__uuidof(MyRuleEngine1));

	if(FAILED(hr1))
	{
		//error handling
		::MessageBox(NULL, "Dom parser cannot be loaded", "Error", MB_OK);
	}
	if(FAILED(hr2))
	{
		::MessageBox(NULL, "RuleEngine cannot be loaded", "Error", MB_OK);
	}
	return S_OK;
}
