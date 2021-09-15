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

		if (tokenizer.HadError())
		{
			continue;
		}

		Parser parser(tokens);
		auto unit = parser();

		if (parser.HadError())
		{
			continue;
		}

		InterpretResult result = InterpretResult::UnkownError;

		auto chunk = compiler(unit);
		result = virtualMachine.Interpret(chunk);

		delete unit;
		unit = nullptr;

		if (result != InterpretResult::Success)
		{
			std::cout << "[Virtual Machine]: InterpretResult=";

			switch (result)
			{
				case InterpretResult::SyntaxError: std::cout << "SyntaxError\n"; break;
				case InterpretResult::ParseError: std::cout << "ParseError\n"; break;
				case InterpretResult::RuntimeError: std::cout << "RuntimeError\n"; break;
				default: std::cout << "Unknown\n"; break;
			}
		}
		else
		{
			std::cout << "\n";
		}
	}
}

}