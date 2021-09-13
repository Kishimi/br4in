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