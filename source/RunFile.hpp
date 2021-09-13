#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>

#include "VirtualMachine.hpp"

namespace Br4in
{

auto RunFile(const std::string &filename) -> void;

}