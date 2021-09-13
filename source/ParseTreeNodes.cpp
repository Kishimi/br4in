#include "ParseTreeNodes.hpp"

#include "Visitor.hpp"

namespace Br4in
{

ParseTreeUnit::~ParseTreeUnit()
{
	for (auto node : nodes)
	{
		if (node)
		{
			delete node;
		}
	}
}

auto ParseTreeUnit::Accept(Visitor *visitor) -> void
{
	BR4IN_ASSERT(visitor != nullptr);
	visitor->Visit(this);
}

auto ParseTreeUnit::AddNode(ParseTreeNode *node) -> void
{
	BR4IN_ASSERT(node != nullptr);
	nodes.push_back(node);
}

auto ParseTreeUnit::erase(
	const std::vector<ParseTreeNode*>::const_iterator &begin,
	const std::vector<ParseTreeNode*>::const_iterator &end)
	-> std::vector<ParseTreeNode*>::iterator
{
	return nodes.erase(begin, end);
}

auto ParseTreeUnit::begin() -> std::vector<ParseTreeNode*>::iterator
{
	return nodes.begin();
}

auto ParseTreeUnit::end() -> std::vector<ParseTreeNode*>::iterator
{
	return nodes.end();
}

auto ParseTreeUnit::begin() const -> std::vector<ParseTreeNode*>::const_iterator
{
	return nodes.begin();
}

auto ParseTreeUnit::end() const -> std::vector<ParseTreeNode*>::const_iterator
{
	return nodes.end();
}

ParseTreeMove::ParseTreeMove(const uByte moveAmount)
	: moveAmount(moveAmount)
{
}

auto ParseTreeMove::Accept(Visitor *visitor) -> void
{
	BR4IN_ASSERT(visitor != nullptr);
	visitor->Visit(this);
}

auto ParseTreeInc::Accept(Visitor *visitor) -> void
{
	BR4IN_ASSERT(visitor != nullptr);
	visitor->Visit(this);
}

auto ParseTreeDec::Accept(Visitor *visitor) -> void
{
	BR4IN_ASSERT(visitor != nullptr);
	visitor->Visit(this);
}

auto ParseTreeWrite::Accept(Visitor *visitor) -> void
{
	BR4IN_ASSERT(visitor != nullptr);
	visitor->Visit(this);
}

auto ParseTreeRead::Accept(Visitor *visitor) -> void
{
	BR4IN_ASSERT(visitor != nullptr);
	visitor->Visit(this);
}

ParseTreeLoop::~ParseTreeLoop()
{
	for (auto node : nodes)
	{
		if (node)
		{
			delete node;
		}
	}
}

auto ParseTreeLoop::Accept(Visitor *visitor) -> void
{
	BR4IN_ASSERT(visitor != nullptr);
	visitor->Visit(this);
}

auto ParseTreeLoop::AddNode(ParseTreeNode *node) -> void
{
	BR4IN_ASSERT(node != nullptr);
	nodes.push_back(node);
}

auto ParseTreeLoop::begin() -> std::vector<ParseTreeNode*>::iterator
{
	return nodes.begin();
}

auto ParseTreeLoop::end() -> std::vector<ParseTreeNode*>::iterator
{
	return nodes.end();
}

}