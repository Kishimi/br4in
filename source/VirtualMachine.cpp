#include "VirtualMachine.hpp"

namespace Br4in
{

VirtualMachine::VirtualMachine(const u64 preallocatedMemorySize)
{
	memoryPointer = 0;
	memory.resize(preallocatedMemorySize);
}

auto VirtualMachine::Interpret(const Chunk &chunk) -> InterpretResult
{
	this->chunk = &chunk;
	return this->Run();
}

auto VirtualMachine::Interpret(const std::string &code) -> InterpretResult
{
	// lex
	Tokenizer tokenizer(code);
	auto tokens = tokenizer();

	if (tokenizer.HadError())
	{
		return InterpretResult::SyntaxError;
	}

	// parse
	Parser parser(tokens);
	auto unit = parser();

	if (parser.HadError())
	{
		return InterpretResult::ParseError;
	}

	// optimize
	Optimizer optimizer(unit);
	auto optimizedUnit = optimizer();

	// free memory of the unoptimized unit
	delete unit;

	// compile & run
	Compiler compiler;
	auto chunk = compiler(optimizedUnit);
	auto result = this->Interpret(chunk);

	if (result != InterpretResult::Success)
	{
		return result;
	}

	// free memory of the optimized unit
	delete optimizedUnit;

	return InterpretResult::Success;
}

auto VirtualMachine::GetMemory() -> std::vector<Byte>
{
	return memory;
}

auto VirtualMachine::Run() -> InterpretResult
{
	constexpr void* jumpTable[] = {
		&&OP_MOVE_PTR,
		&&OP_INCREMENT,
		&&OP_DECREMENT,
		&&OP_WRITE,
		&&OP_READ,
		&&OP_JUMP_NEXT,
		&&OP_JUMP_PREV
	};

	if (!chunk)
	{
		return InterpretResult::RuntimeError;
	}

	for (auto instruction = chunk->begin(); instruction < chunk->end(); instruction++)
	{
		#if DEBUG_TRACE_EXECUTION
		chunk->DebugInstruction(*instruction);
		#endif

		goto* jumpTable[static_cast<i32>(*instruction)];

		OP_MOVE_PTR:
		{
			const i8 moveAmount = *(++instruction);
			memoryPointer += moveAmount;

			#if DEBUG_TRACE_EXECUTION
			std::cout << "moveAmount: " << i32(moveAmount) << "\n";
			#endif

			if (memoryPointer >= memory.size())
			{
				for (u64 i = memory.size(); i < memoryPointer; i++)
				{
					memory.push_back(0);
				}
			}
		}
		goto BREAK;

		OP_INCREMENT:
		{
			const u32 incAmount = *(++instruction);
			this->AtMemoryPointer() += incAmount;
		}
		goto BREAK;

		OP_DECREMENT:
		{
			const u32 decAmount = *(++instruction);
			this->AtMemoryPointer() -= decAmount;
		}
		goto BREAK;

		OP_WRITE:
		{
			#if not DEBUG_TRACE_EXECUTION
			std::cout << this->AtMemoryPointer() << std::flush;
			#else
			std::cout << "Write: " << this->AtMemoryPointer() << "\n";
			#endif
		}
		goto BREAK;

		OP_READ:
		{
			std::cin >> this->AtMemoryPointer();
			std::cin.ignore();
		}
		goto BREAK;

		OP_JUMP_NEXT:
		{
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
		}
		goto BREAK;

		OP_JUMP_PREV:
		{
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
		}

		BREAK:
		if (memoryPointer >= memory.size())
		{
			std::cout << "[Virtual Machine]: RuntimeMemoryPointerCheck failed\n";
			return InterpretResult::RuntimeError;
		}

		#if DEBUG_TRACE_MEMORY
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

auto VirtualMachine::AtMemoryPointer() -> Byte&
{
	return memory[memoryPointer];
}

}