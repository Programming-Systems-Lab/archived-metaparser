// MyREClient2.cpp : Implementation of CMyREClient2
#include "stdafx.h"
#include "Client2.h"
#include "MyREClient2.h"
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// CMyREClient2


STDMETHODIMP CMyREClient2::Process()
{
	// TODO: Add your implementation code here
	IMyRuleEngine1Ptr pTest = NULL;
	IXMLDOMDocument2Ptr pDoc = NULL;
	HRESULT hr1, hr2;

	hr1 = pTest.CreateInstance(__uuidof(MyRuleEngine1));
	hr2 = pDoc.CreateInstance(__uuidof(DOMDocument40));

	if(FAILED(hr1) || FAILED(hr2))
	{
		printf("CreateInstance failed!\n");
	}
	else
	{
		VARIANT_BOOL res = 
			pDoc->load("Q:\\Project\\xml\\Library.xml");
		if(res == VARIANT_FALSE)
		{
			printf("Loading not successful!\n");
			getchar();
			return 0;
		}
		::MessageBox(NULL, "Everything OK", "Error", MB_OK);

		/*
		_bstr_t location("//bo:Date[1]");		
		pDoc->setProperty(L"SelectionLanguage", L"XPath");
		pDoc->setProperty(L"SelectionNamespaces", L"xmlns:bo='http://www.book.org'");
		IXMLDOMNodeListPtr pNodeList = pDoc->selectNodes(location);
		printf("# of items selected: %ld\n", pNodeList->length);
		IXMLDOMSelectionPtr pSelection = pNodeList;
		IXMLDOMNodePtr pNode;
		printf("selection length is %ld\n", pSelection->length);
		pNode = pSelection->nextNode();
		if(pNode->nodeType == NODE_ELEMENT)
		{
			printf("node element\n");
			_bstr_t text(pNode->text);
			printf("using location: %s\n", (char *) text);
		}
		else if(pNode->nodeType == NODE_ATTRIBUTE)
		{
			printf("node attribute\n");
		}
		*/

		pTest->CompileRule("Q:\\Project\\xml\\ruleSet.xml");
		pTest->Process(pDoc.GetInterfacePtr());
	}
	pTest = NULL;
	pDoc = NULL;
	return S_OK;
}
