#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "Config.hpp"
#include "InterpretResult.hpp"
#include "Chunk.hpp"
#include "Tokenizer.hpp"
#include "Parser.hpp"
#include "Compiler.hpp"
#include "Common.hpp"
#include "Util.hpp"
#include "Optimizer.hpp"

namespace Br4in
{

class VirtualMachine final
{
public:
	VirtualMachine(const u64 preallocatedMemorySize = std::numeric_limits<i16>::max());

public:
	auto Interpret(const std::string &code) -> InterpretResult;
	auto Interpret(const Chunk &chunk) -> InterpretResult;

	auto GetMemory() -> std::vector<Byte>;

private:
	auto Run() -> InterpretResult;
	auto AtMemoryPointer() -> Byte&;

private:
	const Chunk *chunk = nullptr;
	std::vector<Byte> memory;
	u64 memoryPointer;
};

}