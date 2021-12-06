#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>


struct coord
{
	int x = 69, y = 69;
};

int get_all_coord_len(const char* path);

int main(int argc, char** argv)
{
	std::fstream input;
	input.open(argv[1]);
	coord initial_coord[get_all_coord_len(argv[1])];
	coord last_coord[get_all_coord_len(argv[1])];
	
	int n = 0;
	
	if(input.is_open())
	{
		std::string line;
		while(std::getline(input, line))
		{
			{ // get initial coords.
				std::string numbers;
				size_t first = line.find_first_of(' ');
				numbers.append(line, 0, first);
				size_t p = numbers.find_first_of(',');
				initial_coord[n].x = std::stoi(numbers.substr(0, p));;
				initial_coord[n].y = std::stoi(numbers.substr(p + 1, numbers.size()));
			}
			{ // get last coords.
				std::string numbers;
				size_t second = line.find_first_of("->");
				numbers.append(line, second + 3, line.size());
				size_t p = numbers.find_first_of(',');
				last_coord[n].x = std::stoi(numbers.substr(0, p));;
				last_coord[n].y = std::stoi(numbers.substr(p + 1, numbers.size()));
			}
			n++;
		}
	}
	
	int len = 0;
	for (int i = 0; i < n; ++i) {
		if (initial_coord[i].x > len && last_coord[i].x > len) {
			len = initial_coord[i].x > last_coord[i].x ? initial_coord[i].x : last_coord[i].x;
		} if (initial_coord[i].y > len && last_coord[i].y > len) {
			len = initial_coord[i].y > last_coord[i].y ? initial_coord[i].y : last_coord[i].y;
		}
	}
	len = n > len ? n : len + 1;
	
	int asw_one = 0;
	int asw_two = 0;
	char diagram[len][len];
	for (int b = 0; b < len; ++b) {
		for (int a = 0; a < len; ++a) {
			diagram[a][b] = '.';
		}
	}
	
	for (int i = 0; i < n; ++i) {
		int x = initial_coord[i].x <= last_coord[i].x ? initial_coord[i].x : last_coord[i].x;
		int y = initial_coord[i].y <= last_coord[i].y ? initial_coord[i].y : last_coord[i].y;
		if (initial_coord[i].x == last_coord[i].x) {
			int goal = initial_coord[i].y >= last_coord[i].y ? initial_coord[i].y : last_coord[i].y;
			do {
				char c = '1';
				if (diagram[x][y] != '.') {
					c = diagram[x][y];
					c += 1;
				}
				diagram[x][y] = c;
				y++;
			} while (y <= goal);
		} else if (initial_coord[i].y == last_coord[i].y) {
			int goal = initial_coord[i].x >= last_coord[i].x ? initial_coord[i].x : last_coord[i].x;
			do {
				char c = '1';
				if (diagram[x][y] != '.') {
					c = diagram[x][y];
					c += 1;
				}
				diagram[x][y] = c;
				x++;
			} while (x <= goal);
		}
	}
	
	for (int y = 0; y < len; ++y) {
		for (int x = 0; x < len; ++x) {
			if (diagram[x][y] > '1') {
				asw_one++;
			}
			//std::cout << diagram[x][y]; // Print Diagram
		}
		//std::cout << '\n'; // Print Diagram.
	}
	
	for (int i = 0; i < n; ++i) {
		if (last_coord[i].x - initial_coord[i].x == last_coord[i].y - initial_coord[i].y ||
			last_coord[i].x - initial_coord[i].x == (last_coord[i].y - initial_coord[i].y) * -1) {
			short int x = initial_coord[i].x > last_coord[i].x ? initial_coord[i].x + 1 : initial_coord[i].x - 1;
			short int y= initial_coord[i].y > last_coord[i].y ? initial_coord[i].y + 1 : initial_coord[i].y - 1;
			short int goal_x = last_coord[i].x;
			short int goal_y = last_coord[i].y;
			char c = '1';
			do {
				if (x != goal_x)
					x += x > goal_x ? -1 : 1;
				if (y != goal_y)
					y += y > goal_y ? -1 : 1;
				if (diagram[x][y] != '.') {
					c = diagram[x][y];
					c += 1;
				}
				diagram[x][y] = c;
				c = '1'; // Reset the char.
			} while (x != goal_x && y != goal_y);
		}
	}
	for (int y = 0; y < len; ++y) {
		for (int x = 0; x < len; ++x) {
			if (diagram[x][y] > '1') {
				asw_two++;
			}
			//std::cout << diagram[x][y]; // Print Diagram
		}
		//std::cout << '\n'; // Print Diagram.
	}
	
	std::cout << "Result\n";
	std::cout << "Part One: " << asw_one << std::endl;
	std::cout << "Part Two: " << asw_two << std::endl;
	
	return 0;
}

int get_all_coord_len(const char* path)
{
	std::fstream input;
	input.open(path);
	int len = 0;
	input.seekg(0);
	std::string line;
	while(std::getline(input, line))
		len++;
	return len - 1;
}
