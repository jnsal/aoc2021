#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <limits>

#define WIDTH 10
#define HEIGHT 10
// Yeah Yeah, global variable.
int table[HEIGHT][WIDTH];
bool all_flashes = false;

void printTable()
{
	for (int i = 0; i < HEIGHT; ++i) {
		for (int x = 0; x < WIDTH; ++x) {
			std::cout << table[i][x] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "-----------------\n";
}

int checkAdjacent(int x, int y)
{
	int result = 1;
	
	int up = y > 0 ? table[y - 1][x] : INT_MAX;
	int down = y < HEIGHT - 1 ? table[y + 1][x] : INT_MAX;
	int left = x > 0 ? table[y][x - 1] : INT_MAX;
	int right = x < WIDTH - 1 ? table[y][x + 1] : INT_MAX;
	
	int l_up = x > 0 && y > 0 ? table[y - 1][x - 1] : INT_MAX;
	int r_up = x < WIDTH - 1 && y > 0 ? table[y - 1][x + 1] : INT_MAX;
	int l_dw = x > 0 && y < HEIGHT - 1 ? table[y + 1][x - 1] : INT_MAX;
	int r_dw = x < HEIGHT - 1 && y < HEIGHT - 1 ? table[y + 1][x + 1] : INT_MAX;
	
	if (up < INT_MAX) {
		table[y - 1][x]++;
		if (table[y - 1][x] > 9) {
			table[y - 1][x] = INT_MAX;
			result += checkAdjacent(x, y - 1);
		}
	}
	if (l_up < INT_MAX) {
		table[y - 1][x - 1]++;
		if (table[y - 1][x - 1] > 9) {
			table[y - 1][x - 1] = INT_MAX;
			result += checkAdjacent(x - 1, y - 1);
		}
	}
	if (r_up < INT_MAX) {
		table[y - 1][x + 1]++;
		if (table[y - 1][x + 1] > 9) {
			table[y - 1][x + 1] = INT_MAX;
			result += checkAdjacent(x + 1, y - 1);
		}
	}
	if (down < INT_MAX) {
		table[y + 1][x]++;
		if (table[y + 1][x] > 9) {
			table[y + 1][x] = INT_MAX;
			result += checkAdjacent(x, y + 1);
		}
	}
	if (l_dw < INT_MAX) {
		table[y + 1][x - 1]++;
		if (table[y + 1][x - 1] > 9) {
			table[y + 1][x - 1] = INT_MAX;
			result += checkAdjacent(x - 1, y + 1);
		}
	}
	if (r_dw < INT_MAX) {
		table[y + 1][x + 1]++;
		if (table[y + 1][x + 1] > 9) {
			table[y + 1][x + 1] = INT_MAX;
			result += checkAdjacent(x + 1, y + 1);
		}
	}
	if (left < INT_MAX) {
		table[y][x - 1]++;
		if (table[y][x - 1] > 9) {
			table[y][x - 1] = INT_MAX;
			result += checkAdjacent(x - 1, y);
		}
	}
	if (right < INT_MAX) {
		table[y][x + 1]++;
		if (table[y][x + 1] > 9) {
			table[y][x + 1] = INT_MAX;
			result += checkAdjacent(x + 1, y);
		}
	}
	
	return result;
}

int nextStep()
{
	int result = 0;
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			table[y][x]++;
			if (table[y][x] > 9 && (table[y][x] > 9 || table[y][x] < 0)) {
				table[y][x] = INT_MAX;
				result += checkAdjacent(x, y);
			}
		}
	}
	int flashes = 0;
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			if (table[y][x] > 9 || table[y][x] < 0) {
				table[y][x] = 0;
				flashes++;
			}
		}
	}
	if (flashes == HEIGHT * WIDTH) all_flashes = true;

	return result;
}

int main(int argc, char** argv)
{
	std::fstream input;
	input.open(argv[1]);
	int asw_one = 0;
	int asw_two = 0;
	
	if (input.is_open())
	{
		int l = 0;
		std::string line;
		while(std::getline(input, line)) 
		{
			assert(line.size() == WIDTH);
			
			for (size_t i = 0; i < WIDTH; ++i) {
				table[l][i] = line[i] - '0';
			}
			l++;
		}
	}
	int step = 1;
	while (!all_flashes) {
		if (step <= 100) asw_one += nextStep();
		else {
			int n  = nextStep();
			(void) n;
		}
		step++;
	}
	asw_two = step - 1;
	
	std::cout << "Result\n";
	std::cout << "Part One: " << asw_one << std::endl;
	std::cout << "Part Two: " << asw_two << std::endl;
}
