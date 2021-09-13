#pragma once

#include "Common.hpp"

namespace Br4in
{

namespace OpCode
{

enum Enum : Byte
{
	MovePtr,
	Increment,
	Decrement,
	Write,
	Read,
	JumpNext,
	JumpPrev
};

}

}