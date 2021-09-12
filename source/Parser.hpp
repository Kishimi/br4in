#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Common.hpp"
#include "Token.hpp"
#include "ParseTreeNodes.hpp"

namespace Br4in
{

class Parser final
{
public:
	Parser(const std::vector<Token> &tokens);

public:
	auto operator()() -> std::vector<ParseTreeNode*>;
	auto HadError() const -> bool;

private:
	auto Eof() const -> bool;

	auto Error(const std::string &message) -> void;
	auto Current() const -> Token::Type;
	auto Consume() -> Token::Type;
	auto Consume(const Token::Type expected, const std::string &error) -> Token::Type;

	auto ParseNext() -> ParseTreeNode*;
	auto ParseLoop() -> ParseTreeLoop*;

private:
	std::vector<Token> tokens;
	std::vector<Token>::iterator current;
	bool hadError = false;
};

}