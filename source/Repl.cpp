#include "Repl.hpp"

namespace Br4in
{

auto Repl() -> void
{
	VirtualMachine virtualMachine;
	Compiler compiler;
	std::string input;

	std::cout << "Br4in [v" << Version() << "], a brainfuck interpreter written by Kishimi/Ruarq in C++\n";

	while (true)
	{
		std::cout << ">>> ";
		std::getline(std::cin, input);

		if (input == "quit" || input == "q" || input == "exit")
		{
			break;
		}
		else if (input == "memory_view")
		{
			u32 currentByte = 0;
			const u32 viewWidth = 16;
			auto memory = virtualMachine.GetMemory();

			std::cout << "==== memory view ====";
			for (auto byte : memory)
			{
				if (currentByte % viewWidth == 0)
				{
					std::cout << "\n";
				}

				if (IsWhitespace(byte) || byte == 0)
				{
					std::cout << ".";
				}
				else
				{
					std::cout << byte;
				}

				currentByte++;
			}
			std::cout << "\n=====================\n";

			continue;
		}

		Tokenizer tokenizer(input);
		tokenizer.ReplMode();
		auto tokens = tokenizer();

		Parser parser(tokens);
		auto parseTrees = parser();

		InterpretResult result;

		for (auto parseTree : parseTrees)
		{
			auto chunk = compiler(parseTree);
			result = virtualMachine.Interpret(chunk);

			if (result != InterpretResult::Success)
			{
				break;
			}
		}

		if (result != InterpretResult::Success)
		{
			std::cout << "[Virtual Machine]: InterpretResult=";
		}
		else
		{
			std::cout << "\n";
		}

		switch (result)
		{
			case InterpretResult::SyntaxError: std::cout << "SyntaxError\n"; break;
			case InterpretResult::ParseError: std::cout << "ParseError\n"; break;
			case InterpretResult::RuntimeError: std::cout << "RuntimeError\n"; break;
		}
	}
}

}