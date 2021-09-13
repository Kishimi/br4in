#pragma once

#include <iostream>
#include <vector>

#include "Common.hpp"
#include "OpCode.hpp"

namespace Br4in
{

class Chunk final
{
public:
	auto Write(const Byte byte) -> void;
	auto DebugInstruction(const Byte instruction) const -> void;

	auto begin() const -> std::vector<Byte>::const_iterator;
	auto end() const -> std::vector<Byte>::const_iterator;

private:
	std::vector<Byte> byteCode;
};

}