#pragma once

#include "ParseTreeNodes.hpp"

namespace Br4in
{

class Optimizer final
{
public:
	Optimizer(const ParseTreeUnit *unit);

public:
	auto operator()() -> ParseTreeUnit*;

private:
	const ParseTreeUnit *unit = nullptr;
};

}