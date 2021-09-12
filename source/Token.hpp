#pragma once

#include "Common.hpp"

namespace Br4in
{

class Token final
{
public:
	enum Type
	{
		None,

		Less, Greater,
		Plus, Minus,
		LBracket, RBracket,
		Dot, Comma,
		
		EndOfFile
	};

public:
	Byte literal;
	Type type;
};

}