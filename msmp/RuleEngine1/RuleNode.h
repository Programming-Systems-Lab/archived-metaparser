#if !defined(RULE_NODE_H)
#define RULE_NODE_H

#include <vector>

enum nodeType 
{  
	VARIABLE, 
	CONDITION,
	OPERATOR,
	OR,
	AND,
	ACTION,
	COMPLEXRULE,
	RULESET, 
	NOSUCHTYPE
};

enum valueType
{
	n_INT,
	n_REAL,
	n_BOOL,
	n_STR
};

enum operatorType
{
	EQ,
	NE,
	GT,
	GTE,
	LT,
	LTE
};

typedef union _nodeValue
{
	int intValue;
	double realValue;
	bool boolValue;
	wchar_t* strValue;
} nodeValue;

class RuleNode 
{
public:
	RuleNode() { }
	virtual ~RuleNode();
	virtual void AddChild(RuleNode* child);	
	virtual void PrintNode(int indent);
	virtual nodeValue Eval() = 0;
	virtual void SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes) { }

	static nodeType GetType(wchar_t *t);
	static IXMLDOMDocument2Ptr m_pDoc;
	static _bstr_t ns;

	nodeType type;

protected:
	nodeValue value;
	_bstr_t name;
	typedef std::vector<RuleNode*> RuleNodeList;
	RuleNodeList children;

	bool IsEqual(_bstr_t a, char* b);
};
	
class VariableNode : public RuleNode
{
public:
	VariableNode();
	virtual ~VariableNode();
	virtual void PrintNode(int indent);
	virtual nodeValue Eval();
	virtual void SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes);
	
	valueType valType;

private:
	_bstr_t location;
protected:
	nodeValue GetValue(valueType type, _bstr_t &val);
};

class ConditionNode : public RuleNode
{
public:
	ConditionNode();
	virtual ~ConditionNode() { }
	virtual void PrintNode(int indent);
	virtual nodeValue Eval();
	virtual void SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes);
protected:
	bool Lte(VariableNode *a, VariableNode *b);
	bool Lt(VariableNode *a, VariableNode *b);
	bool Gte(VariableNode *a, VariableNode *b);
	bool Gt(VariableNode *a, VariableNode *b);
	bool Ne(VariableNode *a, VariableNode *b);
	bool Eq(VariableNode *a, VariableNode *b);
};

class OperatorNode : public RuleNode
{
public:
	OperatorNode();
	virtual ~OperatorNode() { }
	virtual void PrintNode(int indent);
	virtual nodeValue Eval();
	virtual void SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes);

private:
	operatorType opType;
};

class OrNode : public RuleNode
{
public:
	OrNode();
	virtual ~OrNode() { }
	virtual void PrintNode(int indent);
	virtual nodeValue Eval();
	virtual void SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes);
};

class AndNode : public RuleNode
{
public:
	AndNode();
	virtual ~AndNode() { }
	virtual void PrintNode(int indent);
	virtual nodeValue Eval();
	virtual void SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes);
};

class ActionNode : public RuleNode
{
public:
	ActionNode();
	virtual ~ActionNode() { }
	virtual void PrintNode(int indent);
	virtual nodeValue Eval();
	virtual void SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes);
};

class ComplexRuleNode : public RuleNode
{
public:
	ComplexRuleNode();
	virtual ~ComplexRuleNode() { }
	virtual void PrintNode(int indent);
	virtual nodeValue Eval();
	virtual void SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes);
};

class RuleSetNode : public RuleNode
{
public:
	RuleSetNode();
	virtual ~RuleSetNode() { }
	virtual void PrintNode(int indent);
	virtual nodeValue Eval();
	virtual void SetAttributes(IXMLDOMNamedNodeMapPtr pAttributes);
};

#endif