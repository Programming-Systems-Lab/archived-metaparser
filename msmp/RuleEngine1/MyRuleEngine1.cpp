// MyRuleEngine1.cpp : Implementation of CMyRuleEngine1
#include "stdafx.h"
#include "RuleEngine1.h"
#include "MyRuleEngine1.h"
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// CMyRuleEngine1

CMyRuleEngine1::CMyRuleEngine1()
{
	m_pRuleRoot = 0; 
}

CMyRuleEngine1::~CMyRuleEngine1()
{
	if(0 != m_pRuleRoot)
	{
		delete m_pRuleRoot;
	}
}

STDMETHODIMP CMyRuleEngine1::CompileRule(VARIANT xmlSource, VARIANT_BOOL *isSuccessful)
{
	// TODO: Add your implementation code here
	printf("In CompileRule!\n");
	*isSuccessful = VARIANT_TRUE;

	IXMLDOMDocument2Ptr pDoc;
	HRESULT hr;

	hr = pDoc.CreateInstance(__uuidof(DOMDocument40));

	if(!FAILED(hr))
	{
		VARIANT_BOOL code = pDoc->load(xmlSource);
		if(code == VARIANT_TRUE)
		{
			printf("Parsed Successfully!\n");
			IXMLDOMNodePtr pTmpNode;
			pDoc->childNodes->get_item(1, &pTmpNode);
			m_pRuleRoot = ProcessNode(pTmpNode);
		}
	}
	return S_OK;
}

RuleNode* CMyRuleEngine1::ProcessNode(IXMLDOMNodePtr pNode)
{
	RuleNode *rNode = 0;
	
	printf("nodename is %s\n", (char *) pNode->nodeName);
	
	rNode = CreateNode(pNode->nodeName);
	rNode->SetAttributes(pNode->attributes);

	if(pNode->hasChildNodes() == VARIANT_TRUE)
	{
		IXMLDOMNodeListPtr nodesPtr = pNode->childNodes;
		long length = nodesPtr->length;
		//printf("length is %d\n", length);
		IXMLDOMNodePtr nodePtr = NULL;
		for(long i = 0; i < length; i++)
		{
			nodesPtr->get_item(i, &nodePtr);
			rNode->AddChild(ProcessNode(nodePtr));
		}
	}

	return rNode;
}

RuleNode* CMyRuleEngine1::CreateNode(wchar_t *nodeName)
{
	nodeType type = RuleNode::GetType(nodeName);

	switch(type)
	{
	case VARIABLE:
		return new VariableNode();
	case CONDITION:
		return new ConditionNode();
	case OPERATOR:
		return new OperatorNode();
	case OR:
		return new OrNode();
	case AND:
		return new AndNode();
	case ACTION:
		return new ActionNode();
	case COMPLEXRULE:
		return new ComplexRuleNode();
	case RULESET:
		return new RuleSetNode();
	}

	return 0;
}

STDMETHODIMP CMyRuleEngine1::Process(IUnknown *pDoc, VARIANT_BOOL *isSuccessful)
{
	// TODO: Add your implementation code here
	*isSuccessful = VARIANT_FALSE;
	try 
	{
		IXMLDOMDocument2* pTmpDoc;
		HRESULT hr = pDoc->QueryInterface(__uuidof(IXMLDOMDocument2), (void **)&pTmpDoc);
		if(SUCCEEDED(hr))
		{
			RuleNode::m_pDoc.Attach(pTmpDoc);
			m_pRuleRoot->Eval();
			//::MessageBox(NULL, "Evaluated to true", "Message", MB_OK);
			*isSuccessful = VARIANT_TRUE;
		}
		else
		{
			printf("QueryInterface failed!\n");
		}
	}
	catch(_com_error &e)
	{
		printf("exception: %s\n", (char *) e.Description());
	}
	return S_OK;
}
