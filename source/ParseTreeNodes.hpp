#pragma once

#include <vector>

#include "Common.hpp"

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

class ParseTreeUnit final : public ParseTreeNode
{
public:
	~ParseTreeUnit();

public:
	auto Accept(Visitor *visitor) -> void override;
	auto AddNode(ParseTreeNode *node) -> void;

	auto begin() -> std::vector<ParseTreeNode*>::iterator;
	auto end() -> std::vector<ParseTreeNode*>::iterator;

private:
	std::vector<ParseTreeNode*> nodes;
};

class ParseTreeMove final : public ParseTreeNode
{
public:
	ParseTreeMove() = default;
	ParseTreeMove(const i32 moveAmount);

public:
	auto Accept(Visitor *visitor) -> void override;

public:
	i32 moveAmount = 0;
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