#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Common.hpp"
#include "Token.hpp"

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
	auto SkipWhitespace() -> void;
	auto Eof() const -> bool;

	auto ReadToken() -> Token;

private:
	std::string source;
	std::string::iterator current;
	bool hadError = false;
};

}