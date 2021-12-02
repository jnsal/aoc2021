#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main(int argc, char **argv)
{
	std::fstream smp;
	smp.open(argv[1]);
	std::vector<int> part_one;
	std::vector<int> part_two;
	int asw_one = 0;
	int asw_two = 0;
	
	if (smp.is_open())
	{
		std::string line;
		while(std::getline(smp, line)) {
			part_one.push_back(std::stoi(line));
		}
	}
	smp.close();
	
	
	
	for (size_t i = 0; i < part_one.size(); ++i) {
		if (part_one[i] > part_one[i - 1]) {
			asw_one++;
		}
		int n = part_one[i] + part_one[i + 1] + part_one[i + 2];
		part_two.push_back(n);
	}
	for (size_t i = 0; i < part_two.size(); ++i) {
		if (part_two[i] > part_two[i - 1]) {
			asw_two++;
		}
		
	}
	std::cout << "Result\n";
	std::cout << "Part One: " << asw_one << std::endl;
	std::cout << "Part Two: " << asw_two << std::endl;
	
	return 0;
}
