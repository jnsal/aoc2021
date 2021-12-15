#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <float.h>
int main(int argc, char** argv)
{
    std::fstream input;
    input.open(argv[1]);
    std::string polymer;
    std::vector<std::string> pair_insertion;
    int asw_one = 0;
	unsigned long long asw_two = 0;
	
    if (input.is_open())
    {
		bool is_polymer = true;
		std::string line;
		while(std::getline(input, line)) 
		{
			if (is_polymer) {
				if (line.size() < 2) {
					is_polymer = false;
					continue;
				}
				polymer.append(line);
			} else {
				pair_insertion.push_back(line);
			}
		}
    }
	input.close();
	unsigned long long pairs[pair_insertion.size()];
    for (size_t i = 0; i < pair_insertion.size(); ++i) pairs[i] = 0;
    for (size_t l = 0; l < polymer.size() - 1; ++l) {
		std::string pair(polymer.substr(l, 2));
		for (size_t i = 0; i < pair_insertion.size(); ++i) {
			if (pair_insertion[i].substr(0, 2) == pair) {
				pairs[i]++;
				break;
			}
		}
    }
    {// one step
		int steps = 1;
		while (steps <= 40)
		{
			unsigned long long temp[pair_insertion.size()];
			for (size_t i = 0; i < pair_insertion.size(); ++i) temp[i] = 0;
			for (size_t i = 0; i < pair_insertion.size(); ++i) {
				if (pairs[i] != 0) {
					char element = pair_insertion[i].back();
					std::string pair(pair_insertion[i].substr(0, 1) + element);
					int n = 0;
					for (size_t l = 0; l < pair_insertion.size(); ++l) {
						if (pair_insertion[l].substr(0,2) == pair) {
							n = l;
							break;
						}
					}
					temp[n] += pairs[i];
					pair.assign(element + pair_insertion[i].substr(1, 1));
					for (size_t l = 0; l < pair_insertion.size(); ++l) {
						if (pair_insertion[l].substr(0,2) == pair) {
							n = l;
							break;
						}
					}
					temp[n] += pairs[i];
				}
			}
			for (size_t i = 0; i < pair_insertion.size(); ++i) pairs[i] = temp[i];
			if (steps == 10) { // Counting the characters for part one
				unsigned long long count[26];
				for (int i = 0; i < 26; ++i) count[i] = 0.f;
				for (size_t i = 0; i < pair_insertion.size(); ++i)
				{
					if (pairs[i] != 0) {
						char first = pair_insertion[i][0];
						char second = pair_insertion[i][1];
						count[first - 'A'] += pairs[i];
						count[second - 'A'] += pairs[i];
					}
				}
				for (int i = 0; i < 26; ++i) {
					if(count[i] != 0) 
					{
						count[i] = count[i] / 2;
					}
				}
				unsigned long long least_common = ULLONG_MAX, most_common = 0;
				for (int i = 0; i < 26; ++i) {
					if (count[i] > 1.f) 
					{
						least_common = count[i] < least_common ? count[i] : least_common;
						most_common = count[i] > most_common ? count[i] : most_common;
					}
				}
				asw_one = most_common - least_common;
			}
			steps++;
		}
    }
    { // Counting the characters for part two
		unsigned long long count[26];
		for (int i = 0; i < 26; ++i) count[i] = 0.f;
		for (size_t i = 0; i < pair_insertion.size(); ++i)
		{
			if (pairs[i] != 0) {
				char first = pair_insertion[i][0];
				char second = pair_insertion[i][1];
				count[first - 'A'] += pairs[i];
				count[second - 'A'] += pairs[i];
			}
		}
		for (int i = 0; i < 26; ++i) {
			if(count[i] != 0) 
			{
				count[i] = count[i] / 2;
			}
		}
		unsigned long long least_common = ULLONG_MAX, most_common = 0;
		for (int i = 0; i < 26; ++i) {
			if (count[i] > 1.f) 
			{
				least_common = count[i] < least_common ? count[i] : least_common;
				most_common = count[i] > most_common ? count[i] : most_common;
			}
		}
		asw_two = most_common - least_common;
    }
	std::cout.precision(17);
    std::cout << "Result\n";
	std::cout << "Part One: " << asw_one << std::endl;
    std::cout << "Part Two: " << asw_two << std::endl;
    return 0;
}
