#include "Chunk.hpp"
#include "VirtualMachine.hpp"
#include "Tokenizer.hpp"
#include "Parser.hpp"
#include "Compiler.hpp"

auto main() -> int
{
	Br4in::VirtualMachine virtualMachine;
	auto result = virtualMachine.Interpret("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.");

	if (result != Br4in::InterpretResult::Success)
	{
		std::cerr << "[Error]: Virtual machine returned InterpretResult::";

		switch (result)
		{
			case Br4in::InterpretResult::SyntaxError:
				std::cerr << "SyntaxError\n";
				break;

			case Br4in::InterpretResult::ParseError:
				std::cerr << "ParseError\n";
				break;

			case Br4in::InterpretResult::RuntimeError:
				std::cerr << "RuntimeError\n";
				break;
		}
	}

	return static_cast<i32>(result);
}