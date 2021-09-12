#include "Chunk.hpp"
#include "VirtualMachine.hpp"
#include "Tokenizer.hpp"
#include "Parser.hpp"
#include "Compiler.hpp"

auto main(i32 argc, const char **argv) -> int
{
	if (argc != 2)
	{
		std::cout << "Usage: br4in <bf-code>\n";
		return 1;
	}

	Br4in::VirtualMachine virtualMachine;
	auto result = virtualMachine.Interpret(argv[1]);

	if (result != Br4in::InterpretResult::Success)
	{
		std::cout << "[Error]: Virtual machine returned InterpretResult::";

		switch (result)
		{
			case Br4in::InterpretResult::SyntaxError:
				std::cout << "SyntaxError\n";
				break;

			case Br4in::InterpretResult::ParseError:
				std::cout << "ParseError\n";
				break;

			case Br4in::InterpretResult::RuntimeError:
				std::cout << "RuntimeError\n";
				break;
		}
	}

	return static_cast<i32>(result);
}