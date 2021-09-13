#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Config.hpp"
#include "InterpretResult.hpp"
#include "Chunk.hpp"
#include "Tokenizer.hpp"
#include "Parser.hpp"
#include "Compiler.hpp"
#include "Common.hpp"
#include "Util.hpp"

namespace Br4in
{

class VirtualMachine final
{
public:
	VirtualMachine();

public:
	auto Interpret(const std::string &code) -> InterpretResult;
	auto Interpret(Chunk &chunk) -> InterpretResult;

	auto GetMemory() -> std::vector<sByte>;

private:
	auto Run() -> InterpretResult;
	
	auto AtMemoryPointer() -> sByte&;

private:
	Chunk *chunk = nullptr;
	std::vector<sByte> memory;
	u64 memoryPointer;
};

}