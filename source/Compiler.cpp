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

auto Compiler::Visit(ParseTreeLMove *node) -> void
{
	chunk.Write(OpCode::MovePrev);
}

auto Compiler::Visit(ParseTreeRMove *node) -> void
{
	chunk.Write(OpCode::MoveNext);
}

auto Compiler::Visit(ParseTreeInc *node) -> void
{
	chunk.Write(OpCode::Increment);
}

auto Compiler::Visit(ParseTreeDec *node) -> void
{
	chunk.Write(OpCode::Decrement);
}

auto Compiler::Visit(ParseTreeWrite *node) -> void
{
	chunk.Write(OpCode::Write);
}

auto Compiler::Visit(ParseTreeRead *node) -> void
{
	chunk.Write(OpCode::Read);
}

auto Compiler::Visit(ParseTreeLoop *loop) -> void
{
	chunk.Write(OpCode::JumpNext);

	for (auto node : *loop)
	{
		node->Accept(this);
	}

	chunk.Write(OpCode::JumpPrev);
}

}