#include "Repl.hpp"

namespace Br4in
{

auto Repl() -> void
{
	VirtualMachine virtualMachine;
	std::string input;

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

		auto result = virtualMachine.Interpret(input);

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