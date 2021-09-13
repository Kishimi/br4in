#include "Tokenizer.hpp"

using namespace std::string_literals;

namespace Br4in
{

Tokenizer::Tokenizer(const std::string &source)
	: source(source)
{
}

auto Tokenizer::operator()() -> std::vector<Token>
{
	Token next = { .literal = 0, .type = Token::None };
	std::vector<Token> tokens;
	tokens.reserve(source.size());
	current = source.begin();
	hadError = false;
	line = 1;

	if (!replMode)
	{
		this->SkipComment();
	}

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

auto Tokenizer::ReplMode() -> void
{
	replMode = true;
}

auto Tokenizer::Eof() const -> bool
{
	return current >= source.end();
}

auto Tokenizer::Current() const -> char
{
	return *current;
}

auto Tokenizer::Consume() -> char
{
	return *(current++);
}

auto Tokenizer::Error(const std::string &message) -> void
{
	hadError = true;

	std::cout << "[Error on line " << line << "]: " << message << "\n";
}

auto Tokenizer::SkipComment() -> void
{
	this->SkipWhitespace();

	if (this->Current() == '[')
	{
		i32 scope = 1;
		while (!this->Eof() && (this->Current() != ']' || scope != 0))
		{
			const auto prev = this->Consume();
			if (prev == '\n')
			{
				line++;
			}

			if (this->Current() == '[')
			{
				scope++;
			}
			else if (this->Current() == ']')
			{
				scope--;
			}
		}

		if (this->Eof())
		{
			this->Error("Unterminated comment, expected ']' but found EOF");
		}

		// skip ']'
		this->Consume();
	}
}

auto Tokenizer::SkipWhitespace() -> void
{
	while (!this->Eof() && IsWhitespace(this->Current()))
	{
		const char prev = this->Consume();
		if (prev == '\n')
		{
			line++;
		}
	}
}

auto Tokenizer::SkipNonBrainfuck() -> void
{
	while (!this->Eof() && !IsBrainfuck(this->Current()))
	{
		const char prev = this->Consume();
		if (prev == '\n')
		{
			line++;
		}
	}
}

auto Tokenizer::ReadToken() -> Token
{
	Token token;
	token.line = line;

	if (this->Eof())
	{
		token.literal = 0;
		token.type = Token::EndOfFile;
		return token;
	}

	const char c = this->Consume();

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
			this->Error("Unexpected character '"s + c + "'"s);
			break;
	}

	return token;
}

}