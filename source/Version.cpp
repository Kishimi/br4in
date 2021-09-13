#include "Version.hpp"

using namespace std::string_literals;

namespace Br4in
{

auto Version() -> const std::string&
{
	static std::string version = std::to_string(BR4IN_VERSION_MAJOR) + "."s
		+ std::to_string(BR4IN_VERSION_MINOR) + "."s
		+ std::to_string(BR4IN_VERSION_PATCH);

	return version;
}

}