#pragma once

#include "ParseTreeNodes.hpp"
#include "Visitor.hpp"
#include "OpCode.hpp"
#include "Chunk.hpp"

namespace Br4in
{

class Compiler final : public Visitor
{
public:
	auto operator()(ParseTreeNode *node) -> Chunk;

	auto Visit(ParseTreeUnit *node) -> void override;
	auto Visit(ParseTreeMove *node) -> void override;
	auto Visit(ParseTreeInc *node) -> void override;
	auto Visit(ParseTreeDec *node) -> void override;
	auto Visit(ParseTreeWrite *node) -> void override;
	auto Visit(ParseTreeRead *node) -> void override;
	auto Visit(ParseTreeLoop *node) -> void override;

private:
	Chunk chunk;
};

}