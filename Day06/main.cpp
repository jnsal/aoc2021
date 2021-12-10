#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <algorithm>

#define DAY 256
#define LIFE_TIME 9

int main(int argc, char** argv)
{
	std::fstream input;
	input.open(argv[1]);
	long long life_time[LIFE_TIME];
	
	int lanterfish_count = 0;
	for (int i = 0; i < LIFE_TIME; ++i)  life_time[i] = 0;
	
	if (input.is_open())
	{
		std::string line;
		std::getline(input, line);
		for (size_t i = 0; i < line.size(); ++i) {
			if (line[i] != ',' && line[i] != '\n') {
				std::string number;
				number.assign(line, i, 1);
				int n = std::stoi(number);
				assert(n < LIFE_TIME);
				life_time[n] += 1;
				lanterfish_count++;
			}
		}
	}
	input.close();
	int asw_one = 0;
	long long asw_two = 0;
	
	for (int d = 1; d <= DAY; ++d) {
		long long born_fish[LIFE_TIME];
		for (int i = 0; i < LIFE_TIME; ++i )  born_fish[i] = 0;
		
		if (life_time[0] >= 1) {
			born_fish[8] += life_time[0];
			born_fish[6] += life_time[0];
			life_time[0] = 0;
		}
		for (int i = 1; i < LIFE_TIME; ++i) {
			if (i != 0) {
				born_fish[i - 1] += life_time[i];
			}
		}
		std::move(std::begin(born_fish), std::end(born_fish), std::begin(life_time));
		if (d == 80) {
			for (int i = 0; i < LIFE_TIME; ++i) {
				asw_one += life_time[i];
			}
		}
	}
	for (int i = 0; i < LIFE_TIME; ++i) {
		asw_two += life_time[i];
	}
	
	std::cout << "Result\n";
	std::cout << "Part One: " << asw_one << std::endl;
	std::cout << "Part Two: " << asw_two << std::endl;
	return 0;
}