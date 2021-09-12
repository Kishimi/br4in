#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Common.hpp"
#include "Token.hpp"
#include "Util.hpp"

namespace Br4in
{

class Tokenizer final
{
public:
	Tokenizer(const std::string &source);

public:
	auto operator()() -> std::vector<Token>;
	auto HadError() const -> bool;

private:
	auto Eof() const -> bool;

	auto SkipComment() -> void;
	auto SkipWhitespace() -> void;
	auto SkipNonBrainfuck() -> void;
	auto ReadToken() -> Token;

private:
	const std::string source;
	std::string::const_iterator current;
	bool hadError = false;
};

}