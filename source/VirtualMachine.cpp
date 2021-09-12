#include "VirtualMachine.hpp"

#define DEBUG_TRACE_EXECUTION 0

namespace Br4in
{

VirtualMachine::VirtualMachine()
{
	memory.reserve(BR4IN_VM_INITIAL_MEMORY_SIZE);
	memoryPointer = memory.begin();
}

auto VirtualMachine::Interpret(Chunk &chunk) -> InterpretResult
{
	this->chunk = &chunk;
	return this->Run();
}

auto VirtualMachine::Interpret(const std::string &code) -> InterpretResult
{
	Tokenizer tokenizer(code);
	auto tokens = tokenizer();

	if (tokenizer.HadError())
	{
		return InterpretResult::SyntaxError;
	}

	Parser parser(tokens);
	auto parseTrees = parser();

	if (parser.HadError())
	{
		return InterpretResult::ParseError;
	}

	Compiler compiler;
	for (auto parseTree : parseTrees)
	{
		auto chunk = compiler(parseTree);
		auto result = this->Interpret(chunk);

		if (result != InterpretResult::Success)
		{
			return result;
		}
	}

	// destroy the parse trees
	for (auto parseTree : parseTrees)
	{
		if (parseTree)
		{
			delete parseTree;
		}
	}

	return InterpretResult::Success;
}

auto VirtualMachine::Run() -> InterpretResult
{
	if (!chunk)
	{
		return InterpretResult::RuntimeError;
	}

	auto RuntimeMemoryPointerCheck = [&](auto pointer) -> bool
	{
		return pointer >= memory.begin() && pointer < memory.end();
	};

	memory.push_back(0);

	for (auto instruction = chunk->begin(); instruction < chunk->end(); instruction++)
	{
		#if DEBUG_TRACE_EXECUTION
		chunk->DebugInstruction(*instruction);
		#endif

		switch (*instruction)
		{
			case OpCode::MoveNext:
				memoryPointer++;

				if (memoryPointer == memory.end())
				{
					memory.push_back(0);
				}
				break;

			case OpCode::MovePrev:
				memoryPointer--;
				break;

			case OpCode::Increment:
				if (!RuntimeMemoryPointerCheck(memoryPointer))
				{
					std::cerr << "[RuntimeMemoryPointerCheck]: failed\n";
					return InterpretResult::RuntimeError;
				}

				(*memoryPointer)++;
				break;

			case OpCode::Decrement:
				if (!RuntimeMemoryPointerCheck(memoryPointer))
				{
					std::cerr << "[RuntimeMemoryPointerCheck]: failed\n";
					return InterpretResult::RuntimeError;
				}

				(*memoryPointer)--;
				break;

			case OpCode::Write:
				if (!RuntimeMemoryPointerCheck(memoryPointer))
				{
					std::cerr << "[RuntimeMemoryPointerCheck]: failed\n";
					return InterpretResult::RuntimeError;
				}

				std::cout << *memoryPointer << std::flush;
				break;

			case OpCode::Read:
				std::cin >> *memoryPointer;
				std::cin.ignore();
				break;

			case OpCode::JumpNext:
				if (!RuntimeMemoryPointerCheck(memoryPointer))
				{
					std::cerr << "[RuntimeMemoryPointerCheck]: failed\n";
					return InterpretResult::RuntimeError;
				}

				if (*memoryPointer == 0)
				{
					u32 scope = 1;
					while (*instruction != OpCode::JumpPrev || scope != 0)
					{
						instruction++;

						if (*instruction == OpCode::JumpNext)
						{
							scope++;
						}
						else if (*instruction == OpCode::JumpPrev)
						{
							scope--;
						}
					}
				}
				break;

			case OpCode::JumpPrev:
				if (!RuntimeMemoryPointerCheck(memoryPointer))
				{
					std::cout << "Check: " << std::distance(memory.begin(), memoryPointer) << "=" << memory.size() << "\n";
					std::cerr << "[RuntimeMemoryPointerCheck]: failed\n";
					return InterpretResult::RuntimeError;
				}

				if (*memoryPointer != 0)
				{
					u32 scope = 1;
					while (*instruction != OpCode::JumpNext || scope != 0)
					{
						instruction--;

						if (*instruction == OpCode::JumpNext)
						{
							scope--;
						}
						else if (*instruction == OpCode::JumpPrev)
						{
							scope++;
						}
					}
				}
				break;

			default:
				return InterpretResult::RuntimeError;
		}
	}

	return InterpretResult::Success;
}

}