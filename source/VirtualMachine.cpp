#include "VirtualMachine.hpp"

namespace Br4in
{

VirtualMachine::VirtualMachine()
{
	memoryPointer = 0;
	memory.resize(1);
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

auto VirtualMachine::GetMemory() -> std::vector<sByte>
{
	return memory;
}

auto VirtualMachine::Run() -> InterpretResult
{
	if (!chunk)
	{
		return InterpretResult::RuntimeError;
	}

	auto RuntimeMemoryPointerCheck = [&](auto pointer) -> bool
	{
		return pointer < memory.size();
	};

	for (auto instruction = chunk->begin(); instruction < chunk->end(); instruction++)
	{
		#if DEBUG_TRACE_EXECUTION
		chunk->DebugInstruction(*instruction);
		#endif

		switch (*instruction)
		{
			case OpCode::MoveNext:
				memoryPointer++;

				if (memoryPointer >= memory.size())
				{
					memory.push_back(0);
				}
				break;

			case OpCode::MovePrev:
				memoryPointer--;
				break;

			case OpCode::Increment:
				this->AtMemoryPointer()++;
				break;

			case OpCode::Decrement:
				this->AtMemoryPointer()--;
				break;

			case OpCode::Write:
				#if not DEBUG_TRACE_EXECUTION
				std::cout << this->AtMemoryPointer() << std::flush;
				#else
				std::cout << "Write: " << this->AtMemoryPointer() << "\n";
				#endif

				break;

			case OpCode::Read:
				std::cin >> this->AtMemoryPointer();
				std::cin.ignore();
				break;

			case OpCode::JumpNext:
				if (this->AtMemoryPointer() == 0)
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
				if (this->AtMemoryPointer() != 0)
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

		if (!RuntimeMemoryPointerCheck(memoryPointer))
		{
			std::cout << "[Virtual Machine]: RuntimeMemoryPointerCheck failed\n";
			return InterpretResult::RuntimeError;
		}

		#if DEBUG_TRACE_EXECUTION
		std::cout << "=== memory view ===";
		u32 i = 0;
		const u32 memoryWidth = 16;
		for (auto byte : memory)
		{
			if (i % memoryWidth == 0)
			{
				std::cout << "\n";
			}

			// I want to avoid the memory output being broken by \n, \r, \t etc.
			if (!IsWhitespace(byte) && byte != 0)
			{
				std::cout << byte;
			}
			else
			{
				std::cout << ".";
			}

			i++;
		}
		std::cout << "\n===================\n";
		#endif
	}

	return InterpretResult::Success;
}

auto VirtualMachine::AtMemoryPointer() -> sByte&
{
	return memory[memoryPointer];
}

}