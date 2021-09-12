#include "Tokenizer.hpp"

namespace Br4in
{

Tokenizer::Tokenizer(const std::string &source)
	: source(source)
{
}

auto Tokenizer::operator()() -> std::vector<Token>
{
	Token next = { .type = Token::None };
	std::vector<Token> tokens;
	tokens.reserve(source.size());
	current = source.begin();
	hadError = false;

	// read all tokens
	while (next.type != Token::EndOfFile)
	{
		this->SkipWhitespace();

		next = this->ReadToken();
		tokens.push_back(next);
	}

	return tokens;
}

auto Tokenizer::HadError() const -> bool
{
	return hadError;
}

auto Tokenizer::SkipWhitespace() -> void
{
	while (!this->Eof() && std::isblank(*current))
	{
		current++;
	}
}

auto Tokenizer::Eof() const -> bool
{
	return current >= source.end();
}

auto Tokenizer::ReadToken() -> Token
{
	Token token;

	if (this->Eof())
	{
		token.literal = 0;
		token.type = Token::EndOfFile;
		return token;
	}

	const char c = *(current++);

	token.literal = c;
	token.type = Token::None;
	
	switch (c)
	{
		case '<':
			token.type = Token::Less;
			break;
		
		case '>':
			token.type = Token::Greater;
			break;

		case '+':
			token.type = Token::Plus;
			break;

		case '-':
			token.type = Token::Minus;
			break;

		case '[':
			token.type = Token::LBracket;
			break;

		case ']':
			token.type = Token::RBracket;
			break;
		
		case '.':
			token.type = Token::Dot;
			break;

		case ',':
			token.type = Token::Comma;
			break;
		
		default:
			std::cerr << "[Error]: Unexpected character " << c << "\n";
			hadError = true;
			break;
	}

	return token;
}

}