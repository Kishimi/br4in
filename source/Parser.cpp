#include "Parser.hpp"

using namespace std::string_literals;

namespace Br4in
{

Parser::Parser(const std::vector<Token> &tokens)
	: tokens(tokens)
{
}

auto Parser::operator()() -> ParseTreeUnit*
{
	auto unit = new ParseTreeUnit();
	current = tokens.begin();
	hadError = false;

	while (auto next = this->ParseNext())
	{
		unit->AddNode(next);
	}

	this->Consume(Token::EndOfFile, "Expected EOF");

	return unit;
}

auto Parser::HadError() const -> bool
{
	return hadError;
}

auto Parser::Eof() const -> bool
{
	return current >= tokens.end();
}

auto Parser::Error(const std::string &message) -> void
{
	hadError = true;
	std::cout << "[Error on line" << current->line << "]: " << message << "\n";
}

auto Parser::Current() const -> Token::Type
{
	return current->type;
}

auto Parser::Consume() -> Token::Type
{
	return (current++)->type;
}

auto Parser::Consume(const Token::Type expected, const std::string &error) -> Token::Type
{
	if (this->Eof())
	{
		this->Error(error);
		return Token::EndOfFile;
	}
	else if (current->type != expected)
	{
		this->Error(error);
		return current->type;
	}

	return (current++)->type;
}

auto Parser::ParseNext() -> ParseTreeNode*
{
	if (this->Eof())
	{
		return nullptr;
	}
	else if (this->Current() == Token::EndOfFile)
	{
		return nullptr;
	}

	auto current = this->Consume();

	switch (current)
	{
		case Token::Less:
			return new ParseTreeMove(-1);

		case Token::Greater:
			return new ParseTreeMove(1);

		case Token::Plus:
			return new ParseTreeInc();
		
		case Token::Minus:
			return new ParseTreeDec();

		case Token::Dot:
			return new ParseTreeWrite();

		case Token::Comma:
			return new ParseTreeRead();

		case Token::LBracket:
			return this->ParseLoop();

		default:
			this->Error("Unexpected token '"s + (this->current - 1)->literal + "'");
			return nullptr;
	}
}

auto Parser::ParseLoop() -> ParseTreeLoop*
{
	auto loop = new ParseTreeLoop();

	while (!this->Eof() && this->Current() != Token::RBracket)
	{
		loop->AddNode(this->ParseNext());
	}

	this->Consume(Token::RBracket, "Expected ']'");

	return loop;
}

}