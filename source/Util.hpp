#pragma once

namespace Br4in
{

constexpr static auto IsWhitespace(const char c) -> bool
{
	return
		c == ' ' ||
		c == '\t' ||
		c == '\r' ||
		c == '\n' ||
		c == '\v' ||
		c == '\f';
}

constexpr static auto IsBrainfuck(const char c) -> bool
{
	return
		c == '<' ||
		c == '>' ||
		c == '+' ||
		c == '-' ||
		c == '.' ||
		c == ',' ||
		c == '[' ||
		c == ']';
}

}