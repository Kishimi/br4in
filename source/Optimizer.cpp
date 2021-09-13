#include "Optimizer.hpp"

namespace Br4in
{

Optimizer::Optimizer(const ParseTreeUnit *unit)
	: unit(unit)
{
	BR4IN_ASSERT(unit != nullptr);
}

auto Optimizer::operator()() -> ParseTreeUnit*
{
	auto optimizedUnit = new ParseTreeUnit();

	for (auto node = unit->begin(); node < unit->end(); node++)
	{
		if (auto firstMove = dynamic_cast<ParseTreeMove*>(*node))
		{
			auto optimizedMove = new ParseTreeMove(*firstMove);

			if (node < unit->end())
			{
				while (auto nextMove = dynamic_cast<ParseTreeMove*>(*(node + 1)))
				{
					optimizedMove->moveAmount += nextMove->moveAmount;
					node++;

					if (node >= unit->end())
					{
						break;
					}
				}
			}

			optimizedUnit->AddNode(optimizedMove);
		}
		else
		{
			optimizedUnit->AddNode(*node);
		}
	}

	return optimizedUnit;
}

}