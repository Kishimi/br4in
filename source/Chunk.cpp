#include "Chunk.hpp"

namespace Br4in
{

auto Chunk::Write(const Byte byte) -> void
{
	byteCode.push_back(byte);
}

auto Chunk::DebugInstruction(const Byte instruction) -> void
{
	switch (instruction)
	{
		case OpCode::MovePtr:
			std::cout << "MovePtr\n";
			break;

		case OpCode::Increment:
			std::cout << "Increment\n";
			break;

		case OpCode::Decrement:
			std::cout << "Decrement\n";
			break;

		case OpCode::Write:
			std::cout << "Write\n";
			break;

		case OpCode::Read:
			std::cout << "Read\n";
			break;

		case OpCode::JumpNext:
			std::cout << "JumpNext\n";
			break;

		case OpCode::JumpPrev:
			std::cout << "JumpPrev\n";
			break;

		default:
			std::cout << "Unknown\n";
			break;
	}
}

auto Chunk::begin() const -> std::vector<Byte>::const_iterator
{
	return byteCode.begin();
}

auto Chunk::end() const -> std::vector<Byte>::const_iterator
{
	return byteCode.end();
}

}