#include "stdafx.h"
#include "RuleNode.h"

#define SIZE 9

wchar_t *nodeName[] =
{
	L"variable",
	L"condition",
	L"operator",
	L"or",
	L"and",
	L"action",
	L"complexRule",
	L"ruleset"
};

IXMLDOMDocument2Ptr RuleNode::m_pDoc = NULL;

_bstr_t RuleNode::ns;

nodeType RuleNode::GetType(wchar_t *t)
{
	for(int i = 0; i < SIZE; i++)
	{
		if(::wcscmp(nodeName[i], t) == 0)
			return (nodeType) i;
	}
	return NOSUCHTYPE;
}

bool RuleNode::IsEqual(_bstr_t a, char *b)
{
	_bstr_t tmp(b);
	return a == tmp;
}

RuleNode::~RuleNode()
{ 
	for(int i = 0; i < children.size(); i++)
	{
		if(0 != children[i])
		{
			delete children[i];
		}
	}
}

void RuleNode::AddChild(RuleNode* child)
{
	children.push_back(child);
}

void RuleNode::PrintNode(int indent)
{
	for(int i = 0; i < indent; i++)
		printf(" ");
	
	wprintf(L"%s\n", nodeName[type]);

	RuleNode *node;
	for(i = 0; i < children.size(); i++)
	{
		node = children[i];
		node->PrintNode(indent + 2);
	}
}

VariableNode::VariableNode()
{
	type = VARIABLE;
}

VariableNode::~VariableNode()
{

}

void VariableNode::PrintNode(int indent)
{
	//RuleNode::PrintNode(indent);
	printf("\n");
	wprintf(L"name: %s\n", (wchar_t *) name);
	wprintf(L"type: %d\n", valType);
	wprintf(L"location: %s\n", (wchar_t *) location);

	wprintf(L"value: ");
	switch(valType)
	{
	case n_INT:
		wprintf(L"%d\n", value.intValue);
		break;
	case n_REAL:
		wprintf(L"%f\n", value.realValue);
		break;
	case n_BOOL:
		if(value.boolValue == TRUE)
			wprintf(L"true\n");
		else 
			wprintf(L"false\n");
		break;
	case n_STR:
		if(0 != value.strValue)
			wprintf(L"%s\n", value.strValue);
		else
			wprintf(L"\n");
		break;
	}
	printf("\n");
}

nodeValue VariableNode::GetValue(valueType type, _bstr_t &val)
{
	nodeValue tmpValue;
	wchar_t *tmp;

	switch(type)
	{
	case n_INT:
		tmpValue.intValue = ::_wtoi((wchar_t *) val);
		break;
	case n_REAL:
		tmpValue.realValue = ::wcstod((wchar_t *) val, &tmp);
		break;
	case n_BOOL:
		if(IsEqual(val, "true"))
		{
			tmpValue.boolValue = TRUE;
		}
		else if(IsEqual(val, "false"))
		{
			tmpValue.boolValue = FALSE;
		}
		break;
	case n_STR:
		tmpValue.strValue = (wchar_t *) malloc((val.length() + 1) * sizeof(wchar_t));
		::wcscpy(tmpValue.strValue, (wchar_t *) val);
		break;
	default:
		printf("Unknown types!\n");
		break;
	}
	return tmpValue;
}

void VariableNode::SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes)
{
	_bstr_t n;
	_bstr_t v;

	long cItems = pAttributes->length;
	IXMLDOMNodePtr pNode;
	
	for(long i = 0; i < cItems; i++)
	{
		pAttributes->get_item(i, &pNode);
		n = pNode->GetnodeName();
		v = (_bstr_t) pNode->GetnodeValue();

		if(IsEqual(n, "name"))
		{
			name = v.copy();
		}
		else if(IsEqual(n, "type"))
		{
			if(IsEqual(v, "int"))
			{
				valType = n_INT;
				value.intValue = 0;
			}
			else if(IsEqual(v, "real"))
			{
				valType = n_REAL;
				value.realValue = 0.0;
			}
			else if(IsEqual(v, "bool"))
			{
				valType = n_BOOL;
				value.boolValue = FALSE;
			}
			else if(IsEqual(v, "string"))
			{
				valType = n_STR;
				value.strValue = 0;
			}
		}
		else if(IsEqual(n, "location"))
		{
			location = v.copy();
			printf("location is %s\n", (char *) location);
		}
		else if(IsEqual(n, "value"))
		{
			value = GetValue(valType, v);
		}
		//wprintf(L"name:\t%s\nvalue:\t%s\n", n, v);
	}
	PrintNode(0);
}

nodeValue VariableNode::Eval()
{
	_bstr_t bNull;
	
	if(location != bNull)
	{
		RuleNode::m_pDoc->setProperty(L"SelectionNamespaces", RuleNode::ns);
		RuleNode::m_pDoc->setProperty(L"SelectionLanguage", L"XPath");
		IXMLDOMNodeListPtr pNodeList = RuleNode::m_pDoc->selectNodes(location);
		printf("# of items selected: %ld\n", pNodeList->length);
		IXMLDOMSelectionPtr pSelection = pNodeList;
		IXMLDOMNodePtr pNode;
		pNode = pSelection->nextNode();
		if(pNode->nodeType == NODE_ELEMENT)
		{
			_bstr_t text(pNode->text);
			value = GetValue(valType, text);
			printf("using location: %s\n", (char *) text);
		}
		else if(pNode->nodeType == NODE_ATTRIBUTE)
		{
			_bstr_t text = (_bstr_t) pNode->GetnodeValue();
			value = GetValue(valType, text);
		}
	}
	return value;
}

ConditionNode::ConditionNode()
{
	type = CONDITION;
}

void ConditionNode::PrintNode(int indent)
{
	RuleNode::PrintNode(indent);
}

nodeValue ConditionNode::Eval()
{
	//printf("Eval\n");
	VariableNode *v1, *v2;
	OperatorNode *o;
	int opCode;

	v1 = (VariableNode *) children[0];
	o = (OperatorNode *) children[1];
	v2 = (VariableNode *) children[2];
	
	opCode = o->Eval().intValue;

	value.boolValue = FALSE;

	switch(opCode)
	{
	case EQ:
		if(Eq(v1, v2))
		{
			value.boolValue = TRUE;
		}
		break;
	case NE:
		if(Ne(v1, v2))
		{
			value.boolValue = TRUE;
		}
		break;
	case GT:
		if(Gt(v1, v2))
		{
			value.boolValue = TRUE;
		}
		break;
	case GTE:
		if(Gte(v1, v2))
		{
			value.boolValue = TRUE;
		}
		break;
	case LT:
		if(Lt(v1, v2))
		{
			value.boolValue = TRUE;
		}
		break;
	case LTE:
		if(Lte(v1, v2))
		{
			value.boolValue = TRUE;
		}
		break;
	}
	
	if(value.boolValue == TRUE)
	{
		::MessageBox(NULL, "condition evaluated to true", "result", MB_OK);
	}

	return value;
}

void ConditionNode::SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes)
{

}

bool ConditionNode::Eq(VariableNode *a, VariableNode *b)
{
	if(a->valType == n_INT && b->valType == n_INT)
	{
		return a->Eval().intValue == b->Eval().intValue;
	}
	else if(a->valType == n_INT && b->valType == n_REAL)
	{
		return a->Eval().intValue == b->Eval().realValue;
	}
	else if(a->valType == n_REAL && b->valType == n_INT)
	{
		return a->Eval().realValue == b->Eval().intValue;
	}
	else if(a->valType == n_REAL && b->valType == n_REAL)
	{
		return a->Eval().realValue == b->Eval().realValue;
	}
	else if(a->valType == n_BOOL && b->valType == n_BOOL)
	{
		return a->Eval().boolValue == b->Eval().boolValue;
	}
	else if(a->valType == n_STR && b->valType == n_STR)
	{
		return ::wcscmp(a->Eval().strValue, b->Eval().strValue) == 0;
	}

	return FALSE;
}

bool ConditionNode::Ne(VariableNode *a, VariableNode *b)
{	
	return !Eq(a, b);
}

bool ConditionNode::Gt(VariableNode *a, VariableNode *b)
{
	if(a->valType == n_INT && b->valType == n_INT)
	{
		return a->Eval().intValue > b->Eval().intValue;
	}
	else if(a->valType == n_INT && b->valType == n_REAL)
	{
		return a->Eval().intValue > b->Eval().realValue;
	}
	else if(a->valType == n_REAL && b->valType == n_INT)
	{
		return a->Eval().realValue > b->Eval().intValue;
	}
	else if(a->valType == n_REAL && b->valType == n_REAL)
	{
		return a->Eval().realValue > b->Eval().realValue;
	}
	else if(a->valType == n_STR && b->valType == n_STR)
	{
		return ::wcscmp(a->Eval().strValue, b->Eval().strValue) == 1;
	}

	return FALSE;
}

bool ConditionNode::Gte(VariableNode *a, VariableNode *b)
{
	return !Lt(a, b);
}

bool ConditionNode::Lt(VariableNode *a, VariableNode *b)
{
	if(a->valType == n_INT && b->valType == n_INT)
	{
		return a->Eval().intValue < b->Eval().intValue;
	}
	else if(a->valType == n_INT && b->valType == n_REAL)
	{
		return a->Eval().intValue < b->Eval().realValue;
	}
	else if(a->valType == n_REAL && b->valType == n_INT)
	{
		return a->Eval().realValue < b->Eval().intValue;
	}
	else if(a->valType == n_REAL && b->valType == n_REAL)
	{
		return a->Eval().realValue < b->Eval().realValue;
	}
	else if(a->valType == n_STR && b->valType == n_STR)
	{
		return ::wcscmp(a->Eval().strValue, b->Eval().strValue) == -1;
	}

	return FALSE;
}

bool ConditionNode::Lte(VariableNode *a, VariableNode *b)
{
	return !Gt(a, b);
}

OperatorNode::OperatorNode()
{
	type = OPERATOR;
}

void OperatorNode::PrintNode(int indent)
{
	RuleNode::PrintNode(indent);
}

void OperatorNode::SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes)
{
	_bstr_t n;
	_bstr_t v;

	long cItems = pAttributes->length;
	IXMLDOMNodePtr pNode;
	
	for(long i = 0; i < cItems; i++)
	{
		pAttributes->get_item(i, &pNode);
		n = pNode->GetnodeName();
		v = (_bstr_t) pNode->GetnodeValue();

		if(IsEqual(n, "type"))
		{
			if(IsEqual(v, "EQ"))
			{
				opType = EQ;
			}
			else if(IsEqual(v, "NE"))
			{
				opType = NE;
			}
			else if(IsEqual(v, "GT"))
			{
				opType = GT;
			}
			else if(IsEqual(v, "GTE"))
			{
				opType = GTE;
			}
			else if(IsEqual(v, "LT"))
			{
				opType = LT;
			}
			else if(IsEqual(v, "LTE"))
			{
				opType = LTE;
			}
		}
	}
}

nodeValue OperatorNode::Eval()
{
	value.intValue = opType;
	return value;
}

OrNode::OrNode()
{
	type = OR;
}

void OrNode::PrintNode(int indent)
{
	RuleNode::PrintNode(indent);
}

nodeValue OrNode::Eval()
{
	value.boolValue = FALSE;

	for(int i = 0; i < children.size(); i++)
	{
		if(children[i]->Eval().boolValue == TRUE)
		{
			value.boolValue = TRUE;
			break;
		}
	}

	return value;
}

void OrNode::SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes)
{

}

AndNode::AndNode()
{
	type = AND;
}

void AndNode::PrintNode(int indent)
{
	RuleNode::PrintNode(indent);
}

nodeValue AndNode::Eval()
{
	value.boolValue = TRUE;

	for(int i = 0; i < children.size(); i++)
	{
		if(children[i]->Eval().boolValue == FALSE)
		{
			value.boolValue = FALSE;
			break;
		}
	}
	return value;
}

void AndNode::SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes)
{

}

ComplexRuleNode::ComplexRuleNode()
{
	type = COMPLEXRULE;
}

void ComplexRuleNode::PrintNode(int indent)
{
	RuleNode::PrintNode(indent);
}

nodeValue ComplexRuleNode::Eval()
{
	value.boolValue = FALSE;

	if(children[0]->Eval().boolValue == TRUE)
	{
		value.boolValue = TRUE;
	}
	return value;
}

void ComplexRuleNode::SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes)
{

}

ActionNode::ActionNode()
{
	type = VARIABLE;
}

void ActionNode::PrintNode(int indent)
{
	RuleNode::PrintNode(indent);
}

nodeValue ActionNode::Eval()
{
	value.boolValue = TRUE;
	return value;
}

void ActionNode::SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes)
{

}

RuleSetNode::RuleSetNode()
{
	type = RULESET;
}

void RuleSetNode::PrintNode(int indent)
{
	RuleNode::PrintNode(indent);
}

nodeValue RuleSetNode::Eval()
{
	value.boolValue = FALSE;

	for(int i = 0; i < children.size(); i++)
	{
		children[i]->Eval();
	}

	return value;
}

void RuleSetNode::SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes)
{
	_bstr_t n;
	_bstr_t v;

	long cItems = pAttributes->length;
	IXMLDOMNodePtr pNode;
	
	for(long i = 0; i < cItems; i++)
	{
		pAttributes->get_item(i, &pNode);
		n = pNode->GetnodeName();
		v = (_bstr_t) pNode->GetnodeValue();
		if(IsEqual(n, "namespace"))
		{
			RuleNode::ns = v;
		}
	}
}


