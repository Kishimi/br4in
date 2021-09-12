#include "ParseTreeNodes.hpp"

#include "Visitor.hpp"

namespace Br4in
{

auto ParseTreeLMove::Accept(Visitor *visitor) -> void
{
	visitor->Visit(this);
}

auto ParseTreeRMove::Accept(Visitor *visitor) -> void
{
	visitor->Visit(this);
}

auto ParseTreeInc::Accept(Visitor *visitor) -> void
{
	visitor->Visit(this);
}

auto ParseTreeDec::Accept(Visitor *visitor) -> void
{
	visitor->Visit(this);
}

auto ParseTreeWrite::Accept(Visitor *visitor) -> void
{
	visitor->Visit(this);
}

auto ParseTreeRead::Accept(Visitor *visitor) -> void
{
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
	visitor->Visit(this);
}

auto ParseTreeLoop::AddNode(ParseTreeNode *node) -> void
{
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