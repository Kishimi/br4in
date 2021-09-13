#include "Compiler.hpp"

namespace Br4in
{

auto Compiler::operator()(ParseTreeNode *node) -> Chunk
{
	// reset chunk
	chunk = Chunk();

	// "compile"
	node->Accept(this);

	return chunk;
}

auto Compiler::Visit(ParseTreeUnit *unit) -> void
{
	BR4IN_ASSERT(unit != nullptr);
	for (auto node : *unit)
	{
		node->Accept(this);
	}
}

auto Compiler::Visit(ParseTreeMove *node) -> void
{
	BR4IN_ASSERT(node != nullptr);
	chunk.Write(OpCode::MovePtr);
	chunk.Write(node->moveAmount);
}

auto Compiler::Visit([[maybe_unused]] ParseTreeInc *node) -> void
{
	BR4IN_ASSERT(node != nullptr);
	chunk.Write(OpCode::Increment);
}

auto Compiler::Visit([[maybe_unused]] ParseTreeDec *node) -> void
{
	BR4IN_ASSERT(node != nullptr);
	chunk.Write(OpCode::Decrement);
}

auto Compiler::Visit([[maybe_unused]] ParseTreeWrite *node) -> void
{
	BR4IN_ASSERT(node != nullptr);
	chunk.Write(OpCode::Write);
}

auto Compiler::Visit([[maybe_unused]] ParseTreeRead *node) -> void
{
	BR4IN_ASSERT(node != nullptr);
	chunk.Write(OpCode::Read);
}

auto Compiler::Visit(ParseTreeLoop *loop) -> void
{
	BR4IN_ASSERT(loop != nullptr);

	chunk.Write(OpCode::JumpNext);
	for (auto node : *loop)
	{
		node->Accept(this);
	}
	chunk.Write(OpCode::JumpPrev);
}

}