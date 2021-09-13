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

	auto begin() const -> std::vector<ParseTreeNode*>::const_iterator;
	auto end() const -> std::vector<ParseTreeNode*>::const_iterator;

private:
	std::vector<ParseTreeNode*> nodes;
};

class ParseTreeMove final : public ParseTreeNode
{
public:
	ParseTreeMove() = default;
	ParseTreeMove(const uByte moveAmount);

public:
	auto Accept(Visitor *visitor) -> void override;

public:
	uByte moveAmount = 0;
};

class ParseTreeInc final : public ParseTreeNode
{
public:
	auto Accept(Visitor *visitor) -> void override;

public:
	uByte incAmount = 1;
};

class ParseTreeDec final : public ParseTreeNode
{
public:
	auto Accept(Visitor *visitor) -> void override;

public:
	uByte decAmount = 1;
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