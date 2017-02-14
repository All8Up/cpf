#include "Application/ConsoleCommands.hpp"
#include <iostream>


void Cpf::ConsoleCommands::operator ()(const String& line)
{
	auto it = mCommands.find(line);
	if (it!=mCommands.end())
	{
		std::cout << "Found command: " << line << std::endl;
	}
	else
	{
		std::cout << "Unfound command: " << line << std::endl;
	}
}
