#pragma once

#include <string>

#define BR4IN_VERSION_MAJOR 1
#define BR4IN_VERSION_MINOR 2
#define BR4IN_VERSION_PATCH 1

namespace Br4in
{

auto Version() -> const std::string&;

}