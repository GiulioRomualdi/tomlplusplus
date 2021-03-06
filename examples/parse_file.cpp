#include <iostream>
#include <fstream>
#include <toml++/toml.h>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
using namespace std::string_view_literals;

int main(int argc, char** argv)
{
	#ifdef _WIN32
	SetConsoleOutputCP(65001); //UTF-8 console output
	#endif

	auto path = std::string{ argc > 1 ? argv[1] : "example.toml" };
	auto file = std::ifstream{ path };
	if (!file)
	{
		std::cerr << "The file '"sv << path << "' could not be opened for reading."sv << std::endl;
		return 1;
	}
	try
	{
		const auto tbl = toml::parse(file, std::move(path));
		std::cout << tbl << std::endl;
	}
	catch (const toml::parse_error& err)
	{
		std::cerr << "Error parsing file:\n"sv << err << std::endl;
		return 1;
	}
	return 0;
}
