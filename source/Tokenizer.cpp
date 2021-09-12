#include "Tokenizer.hpp"

#if defined DEBUG
#define DEBUG_PRINT_TOKENS 1
#endif

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

	this->SkipComment();

	// read all tokens
	while (next.type != Token::EndOfFile)
	{
		this->SkipWhitespace();
		this->SkipNonBrainfuck();

		next = this->ReadToken();
		tokens.push_back(next);
	}

	#if DEBUG_PRINT_TOKENS
	std::cout << "tokens={";
	for (auto token = tokens.begin(); token < tokens.end() - 1; token++)
	{
		std::cout << "'" << token->literal << "',";
	}
	std::cout << "'" << tokens.back().literal << "'";
	std::cout << "}\n";
	#endif

	return tokens;
}

auto Tokenizer::HadError() const -> bool
{
	return hadError;
}

auto Tokenizer::Eof() const -> bool
{
	return current >= source.end();
}

auto Tokenizer::SkipComment() -> void
{
	this->SkipWhitespace();

	if (*current == '[')
	{
		i32 scope = 1;

		current++;
		while (!this->Eof() && (*current != ']' || scope != 0))
		{
			current++;

			if (*current == '[')
			{
				scope++;
			}
			else if (*current == ']')
			{
				scope--;
			}
		}

		// skip ']'
		current++;

		if (this->Eof())
		{
			hadError = true;
			std::cout << "[Error]: Unterminated comment, expected ']' found EOF\n";
		}
	}
}

auto Tokenizer::SkipWhitespace() -> void
{
	while (!this->Eof() && IsWhitespace(*current))
	{
		current++;
	}
}

auto Tokenizer::SkipNonBrainfuck() -> void
{
	while (!this->Eof() && !IsBrainfuck(*current))
	{
		current++;
	}
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
			std::cout << "[Error]: Unexpected character '" << c << "'\n";
			hadError = true;
			break;
	}

	return token;
}

}