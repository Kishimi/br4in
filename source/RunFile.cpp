#include "RunFile.hpp"

namespace Br4in
{

auto RunFile(const std::string &filename) -> void
{
	// load file contents
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cout << "[Error]: Couldn't open '" << filename << "'\n";
		return;
	}

	const std::string code(std::istreambuf_iterator<char>(file), {});

	// run
	VirtualMachine virtualMachine;
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
}

}