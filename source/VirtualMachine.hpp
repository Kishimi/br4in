#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "InterpretResult.hpp"
#include "Chunk.hpp"
#include "Tokenizer.hpp"
#include "Parser.hpp"
#include "Compiler.hpp"
#include "Common.hpp"

static constexpr auto BR4IN_VM_INITIAL_MEMORY_SIZE = 1 << 8;

namespace Br4in
{

class VirtualMachine final
{
public:
	VirtualMachine();

public:
	auto Interpret(const std::string &code) -> InterpretResult;
	auto Interpret(Chunk &chunk) -> InterpretResult;

private:
	auto Run() -> InterpretResult;

private:
	Chunk *chunk = nullptr;
	std::vector<sByte> memory;
	std::vector<sByte>::iterator memoryPointer;
};

}