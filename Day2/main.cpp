#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main(int argc, char *argv[])
{
	std::fstream course;
	course.open(argv[1]);
	int horizontal = 0;
	int depth = 0, depth_two = 0;
	int aim = 0;
	
	if (course.is_open())
	{
		std::string line;
		while(std::getline(course, line)) {
			size_t l = line.find(' ');
			
			if (line[0] == 'f') {
				line.erase(0, l);
				int value = std::stoi(line);
				horizontal += value;
				if (aim != 0) {
					depth_two += value * aim;
				}
			} else if (line[0] == 'u') {
				line.erase(0, l);
				int value = std::stoi(line);
				depth-= value;
				aim -= value;
			} else if (line[0] == 'd') {
				line.erase(0, l);
				int value = std::stoi(line);
				depth += value;
				aim += value;
			}
		}
	}
	
	std::cout << "Result\n";
	std::cout << "Part One: " << (depth * horizontal) << std::endl;
	std::cout << "Part One: " << (depth_two * horizontal) << std::endl;
	
	return 0;
}