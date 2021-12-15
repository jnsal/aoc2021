#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

void max_axis(char* path, int* x, int* y, int* instructions)
{
	int max_x = 0, max_y = 0, max_instructions;
	std::fstream input;
	input.open(path);
	std::string line;
	bool coord = true;
	while (std::getline(input, line)) {
		if (coord) {
			if (line.size() < 2) {
				coord = false; 
				continue;
			}
		auto comma = line.find(',');
		int t_x = std::stoi(line.substr(0, comma));
		int t_y = std::stoi(line.substr(comma + 1, line.size()));
		max_x = t_x > max_x ? t_x : max_x;
		max_y = t_y > max_y ? t_y : max_y;
		} else {
			max_instructions++;
		}
	}
	input.close();
	
	*x = max_x;
	*y = max_y;
	*instructions = max_instructions;
}

int main(int argc, char** argv)
{
	int max_x = 0, max_y = 0, max_instructions = 0;
	max_axis(argv[1], &max_x, &max_y, &max_instructions);
	std::fstream input;
	input.open(argv[1]);
	std::string instructions[max_instructions];
	std::vector<std::array<int, 2> > coord;
	int asw_one = 0;
	
	if (input.is_open())
	{
		int i = 0;
		bool is_coord = true;
		std::string line;
		while(std::getline(input, line)) 
		{
			if (is_coord) {
				if (line.size() < 2){
					is_coord = false;
					continue;
				}
				auto comma = line.find(',');
				int x = std::stoi(line.substr(0, comma));
				int y = std::stoi(line.substr(comma + 1, line.size()));
				std::array<int, 2> t_coord;
				t_coord[0] = x;
				t_coord[1] = y;
				coord.push_back(t_coord);
			} else {
				instructions[i].append(line);
				i++;
			}
		}
	}
	input.close();
	for (int i = 0; i < max_instructions; ++i) {
		if (instructions[i].size() < 2) break;
		auto eq = instructions[i].find('=');
		char axis = instructions[i][eq - 1];
		int value = std::stoi(instructions[i].substr(eq + 1, instructions[i].size()));
		
		if (axis == 'y') {
			for (size_t n = 0; n < coord.size(); ++n) {
				if (coord[n][1] > value) {
					coord[n][1] = value - (coord[n][1] - value);
				}
			}
			max_y = value;
		} else if (axis == 'x') {
			for (size_t n = 0; n < coord.size(); ++n) {
				if (coord[n][0] > value) {
					coord[n][0] = value - (coord[n][0] - value);
				}
			}
			max_x = value;
		}
		if (asw_one == 0) {
			char table[max_y+1][max_x+1];
			for (int y = 0; y < max_y+1; ++y) {
				for(int x = 0; x < max_x+1; ++x) {
					table[y][x] = ' ';
				}
			}
			for (size_t n = 0; n < coord.size(); ++n) {
				int x = coord[n][0];
				int y = coord[n][1];
				table[y][x] = 'X';
			}
			for(int y = 0; y < max_y+1; ++y) {
				for (int x = 0; x < max_x+1; ++x) {
					if (table[y][x] == 'X') asw_one++;
				}
			}
		}
	}
	char table[max_y+1][max_x+1];
	for (int y = 0; y < max_y+1; ++y) {
		for(int x = 0; x < max_x+1; ++x) {
			table[y][x] = ' ';
		}
	}
	for (size_t i = 0; i < coord.size(); ++i) {
		int x = coord[i][0];
		int y = coord[i][1];
		table[y][x] = 'X';
	}

	std::cout << "Result\n";
	std::cout << "Part One: " << asw_one << std::endl;
	std::cout << "Part Two:\n";
	for(int y = 0; y < max_y+1; ++y) {
		for (int x = 0; x < max_x+1; ++x) {
			std::cout << table[y][x];
		}
		std::cout << std::endl;;
	}
	
	return 0;
}
