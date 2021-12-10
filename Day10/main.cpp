#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>

// Kets = ( = 0, [ = 1, { = 2, < = 3

int main(int argc, char** argv)
{
	std::fstream input;
	input.open(argv[1]);
	int asw_one = 0;
	long long asw_two = 0;
	int scores[4] = {
		3,
		57,
		1197,
		25137
	};
	
	if (input.is_open())
	{
		std::string line;
		std::vector<long long> incomplete_lines;
		while(std::getline(input, line)) 
		{
			std::vector<int> last;
			long long score = 0;
			for(size_t i = 0; i < line.size(); ++i)
			{
				if (line[i] == '(') {
					last.push_back(0);
				} else if  (line[i] == '[') {
					last.push_back(1);
				} else if  (line[i] == '{') {
					last.push_back(2);
				} else if  (line[i] == '<') {
					last.push_back(3);
				}
				
				if (line[i] == ')') {
					if (last.back() != 0) {
						score = scores[0];
						break;
					} else {
						last.pop_back();
					}
				} else if (line[i] == ']') {
					if (last.back() != 1) {
						score = scores[1];
						break;
					} else {
						last.pop_back();
					}
				} else if (line[i] == '}') {
					if (last.back() != 2) {
						score = scores[2];
						break;
					} else {
						last.pop_back();
					}
				} else if (line[i] == '>') {
					if (last.back() != 3) {
						score = scores[3];
						break;
					} else {
						last.pop_back();
					}
				}
			}
			asw_one += score;
			if (score == 0) // Incomplete line.
			{
				for (size_t i = last.size(); i > 0; --i) {
					score = score * 5 + last.back() + 1;
					last.pop_back();
				}
				incomplete_lines.push_back(score);
			}
		}
		
		for(size_t i = 0; i < incomplete_lines.size(); ++i)
		{		
			for(size_t l = i + 1; l < incomplete_lines.size(); ++l)
			{
				if(incomplete_lines[i] > incomplete_lines[l])
				{
					long long temp = incomplete_lines[i];
					incomplete_lines[i] = incomplete_lines[l];
					incomplete_lines[l] = temp;
				}
			}
		}
		asw_two = incomplete_lines[incomplete_lines.size() / 2];
	}
	
	std::cout << "Result\n";
	std::cout << "Part One: " << asw_one << std::endl;
	std::cout << "Part Two: " << asw_two << std::endl;
}