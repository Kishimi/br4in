#pragma once

#include "ParseTreeNodes.hpp"

namespace Br4in
{

class Visitor
{
public:
	virtual ~Visitor() = default;

public:
	virtual auto Visit(ParseTreeUnit *node) -> void = 0;
	virtual auto Visit(ParseTreeMove *node) -> void = 0;
	virtual auto Visit(ParseTreeInc *node) -> void = 0;
	virtual auto Visit(ParseTreeDec *node) -> void = 0;
	virtual auto Visit(ParseTreeWrite *node) -> void = 0;
	virtual auto Visit(ParseTreeRead *node) -> void = 0;
	virtual auto Visit(ParseTreeLoop *loop) -> void = 0;
};

}