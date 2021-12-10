#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <stdio.h>

struct v2
{
	int x, y;
	v2(int _x, int _y): x(_x), y(_y) {}
};
void print(int** table, int h, int len)
{
	for (int i = 0; i < h; ++i) {
		for (int n = 0; n < len; ++n) {
			std::cout << table[i][n] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "---- end \n\n";
}


int check_basin(int** table, int h, int len, v2 v)
{
	int i = table[v.y][v.x];
	
	int result = i == - 1 ? 0 : 1;
	
	int up = v.y > 0 && i != -1 ? table[v.y - 1][v.x] : INT_MAX;
	int down = v.y < h - 1 && i != -1 ? table[v.y + 1][v.x] : INT_MAX;
	int left = v.x > 0 && i != -1 ? table[v.y][v.x - 1] : INT_MAX;
	int right = v.x < len - 1 && i != -1 ? table[v.y][v.x + 1] : INT_MAX;
	
	table[v.y][v.x] = i != 9 ? -1 : i; // put garbage to not count again.
	
	if (up < INT_MAX && up != -1 && up != 9) result += check_basin(table, h, len, v2(v.x, v.y - 1));
	if (down < INT_MAX && down != -1 && down != 9) result += check_basin(table, h, len, v2(v.x, v.y + 1));
	if (left < INT_MAX && left != -1 && left != 9) result += check_basin(table, h, len, v2(v.x - 1, v.y));
	if (right < INT_MAX && right != -1 && right != 9) result += check_basin(table, h, len, v2(v.x + 1, v.y));
	
	return result;
}

int main(int argc, char** argv)
{
	std::fstream input;
	input.open(argv[1]);
	size_t h = 0;
	size_t len = 0;
	{ // get length and height
		std::string line;
		while(std::getline(input, line)) {
			h++;
			len = line.size();
		}
	}
	input.close();
	int** table { new int *[h]};
	for(size_t i = 0; i < h; ++i) table[i] = new int[len];
	
	int basin[3]; // 3 number 2 coord each
	for (int i = 0; i < 3; ++i) basin[i] = INT_MIN;
	int asw_one = 0;
	int asw_two = 0;
	input.open(argv[1]);
	if (input.is_open())
	{
		int l = 0;
		std::string line;
		while(std::getline(input, line)) 
		{
			for (size_t i = 0; i < line.size(); ++i)
			{
				if (line[i] != '\n') {
					table[l][i] = std::stoi(line.substr(i, 1));
				}
			}
			l++;
		}
	}
	for (size_t n = 0; n < h; ++n)
	{
		for (size_t i = 0; i < len; ++i)
		{
			int a = table[n][i];
			int up = n > 0 ? table[n - 1][i] : INT_MAX;
			int down = n < h - 1 ? table[n + 1][i] : INT_MAX;
			int left = i > 0 ? table[n][i - 1] : INT_MAX;
			int right = i < len - 1 ? table[n][i + 1] : INT_MAX;
			if (a < up && a < down && a < left && a < right) {
				asw_one += a + 1;
				
				{
					int** temp_table { new int *[h]};
					for(size_t y = 0; y < h; ++y) temp_table[y] = new int[len];
					
					for (int y = 0; y < (int)h; ++y) {
						for (int x = 0; x < (int)len; ++x) temp_table[y][x] = table[y][x];
					}
					int risk = check_basin(temp_table, (int)h, (int)len, v2(i, n));
					int m = basin[0];
					int m_i = 0;
					for (int b = 1; b < 3; ++b) {
						m = m >= basin[b] ? basin[b] : m;
						m_i = m >= basin[b]? b : m_i;
					}
					if (risk > m) {
						basin[m_i] = risk;
					}
				}
				
			}
		}
	}
	asw_two = basin[0] * basin[1] * basin[2];
	
	std::cout << "Result:\n";
	std::cout << "Part One: " << asw_one << std::endl;
	std::cout << "Part Two: " << asw_two << std::endl;
	return 0;
}