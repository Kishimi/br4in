#pragma once

#include <vector>

namespace Br4in
{

class Visitor;

class ParseTreeNode
{
public:
	virtual ~ParseTreeNode() = default;

public:
	virtual auto Accept(Visitor *visitor) -> void = 0;
};

class ParseTreeLMove final : public ParseTreeNode
{
public:
	auto Accept(Visitor *visitor) -> void override;
};

class ParseTreeRMove final : public ParseTreeNode
{
public:
	auto Accept(Visitor *visitor) -> void override;
};

class ParseTreeInc final : public ParseTreeNode
{
public:
	auto Accept(Visitor *visitor) -> void override;
};

class ParseTreeDec final : public ParseTreeNode
{
public:
	auto Accept(Visitor *visitor) -> void override;
};

class ParseTreeWrite final : public ParseTreeNode
{
public:
	auto Accept(Visitor *visitor) -> void override;
};

class ParseTreeRead final : public ParseTreeNode
{
public:
	auto Accept(Visitor *visitor) -> void override;
};

class ParseTreeLoop final : public ParseTreeNode
{
public:
	~ParseTreeLoop() override;

public:
	auto Accept(Visitor *visitor) -> void override;
	auto AddNode(ParseTreeNode *node) -> void;

	auto begin() -> std::vector<ParseTreeNode*>::iterator;
	auto end() -> std::vector<ParseTreeNode*>::iterator;

private:
	std::vector<ParseTreeNode*> nodes;
};

}