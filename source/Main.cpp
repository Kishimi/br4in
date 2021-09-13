#include <fstream>
#include <iterator>
#include <cstring>

#include "RunFile.hpp"
#include "Repl.hpp"

auto ShowHelp() -> void
{
	auto AddOption = [](const std::string &option, const std::string &desc)
	{
		std::cout << "\t" << option << "\t\t" << desc << "\n";
	};

	std::cout << "Usage: br4in [options] file...\n";
	std::cout << "Options:\n";
	AddOption("-h", "Display this information");
	AddOption("-i", "Start REPL");
}

auto main(i32 argc, const char **argv) -> int
{
	switch (argc)
	{
		case 1:
			Br4in::Repl();
			break;

		case 2:
			if (std::strcmp(argv[1], "-i") == 0)
			{
				Br4in::Repl();
			}
			else if (std::strcmp(argv[1], "-h") == 0)
			{
				ShowHelp();
			}
			else
			{
				Br4in::RunFile(argv[1]);
			}
			break;

		default:
			std::cout << "Unknown options\n";
			ShowHelp();
			return 1;
	}

	return 0;
}