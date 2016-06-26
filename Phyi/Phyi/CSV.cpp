#include "CSV.hpp"

std::vector<std::string> readLine(std::string& line)
{
	std::vector<std::string>   result;

	std::stringstream          lineStream(line);
	std::string                cell;

	while (std::getline(lineStream, cell, ','))
	{
		result.push_back(cell);
	}

	return result;
}

std::vector<std::vector<std::string>> readFile(std::string filename)
{
	std::vector<std::vector<std::string>> result;

	std::ifstream file(filename);

	std::string line;
	while (std::getline(file, line))
	{
		result.push_back(readLine(line));
	}

	return result;
}
