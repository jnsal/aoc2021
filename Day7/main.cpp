#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <limits>

int crabs_count(char* path)
{
	std::fstream input;
	input.open(path);
	std::string line;
	std::getline(input, line);
	int result = 0;
	
	for(size_t i = 0; i < line.size(); ++i) {
		if (line[i] == ',' || line[i] == '\n')  result++;
	}
	
	return result;
}

int main(int argc, char** argv)
{
	std::fstream input;
	input.open(argv[1]);
	int pos[crabs_count(argv[1])];
	int crabs = 0;
	int min_fuel = INT_MAX, min_fuel_c = INT_MAX;
	int max = 0, min = INT_MAX;
	
	if (input.is_open())
	{
		std::string line;
		while (std::getline(input, line))
		{
			for(size_t i = 0; i < line.size(); ++i) {
				if (line[i] != ',' && line[i] != '\n') {
					size_t comma = line.find_first_of(",", i);
					if (comma > line.size()) comma = line.size();
					int n = std::stoi(line.substr(i, comma));
					if (n > max) max = n;
					if (n < min) min = n;
					pos[crabs] = n;
					if (comma <= line.size() && comma > 0) {
						i = comma;
						crabs++;
					}
				}
			}
		}
	}
	input.close();
	
	
	for (int i = min; i <= max; ++i) 
	{
		int value = 0;
		for (int n = 0; n < crabs; ++n) {
			value += i > pos[n] ? i - pos[n] : pos[n] - i;
		}
		if (value < min_fuel) 
		{
			min_fuel = value;
		}
	}
	
	for (int i = min; i <= max; ++i)
	{
		int value = 0;
		for (int n = 0; n < crabs; ++n) {
			int dist = i > pos[n] ? i - pos[n] : pos[n] - i;
			for (int v = 1; v < dist; v++) value += v; 
			value += dist;
		}
		if (value < min_fuel_c)
		{
			min_fuel_c = value;
		}
	}
	
	int asw_one = min_fuel;
	int asw_two = min_fuel_c;
	
	std::cout << "Result\n";
	std::cout << "Part One: " << asw_one << std::endl;
	std::cout << "Part Two: " << asw_two << std::endl;
	return 0;
}