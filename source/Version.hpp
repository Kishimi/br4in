#pragma once

#include <string>

#define BR4IN_VERSION_MAJOR 1
#define BR4IN_VERSION_MINOR 0
#define BR4IN_VERSION_PATCH 0

namespace Br4in
{

auto Version() -> const std::string&;

}