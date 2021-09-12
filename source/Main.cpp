#include <fstream>
#include <iterator>
#include <cstring>

#include "VirtualMachine.hpp"
#include "Repl.hpp"

auto main(i32 argc, const char **argv) -> int
{
	if (argc == 1 || std::strcmp(argv[1], "-i") == 0)
	{
		Br4in::Repl();
		return 0;
	}

	std::ifstream file(argv[1]);
	std::string code(std::istreambuf_iterator<char>(file), {});

	Br4in::VirtualMachine virtualMachine;
	auto result = virtualMachine.Interpret(code);

	if (result != Br4in::InterpretResult::Success)
	{
		std::cout << "[Virtual Machine]: InterpretResult=";

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