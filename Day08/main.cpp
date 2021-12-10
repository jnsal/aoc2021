#include <iostream>
#include <fstream>
#include <string>

bool compare(std::string a, std::string b)
{
	size_t size = b.size();
	int count = 0;
	if (a.size() != size) return false;
	
	for (size_t i = 0; i < size; ++i) {
		for (size_t n = 0; n < size; ++n) {
			if (a[i] == b[n]) {
				count++;
				break;
			}
		}
	}
	if (count == (int)size) {
		return true;
	} else {
		return false;
	}
}

int main(int argc, char** argv)
{
	std::fstream input;
	input.open(argv[1]);
	int asw_one = 0;
	int asw_two = 0;
	
	if (input.is_open())
	{
		std::string line;
		while (std::getline(input, line))
		{
			std::string values[10];
			std::string asw = "\0";
			for (size_t i = 0; i < 10; ++i) values[i] = "nil";
			bool def_values = false;
			size_t pipe = line.find_first_of('|');
			for (size_t i = 0; i < pipe; ++i)
			{
				if (line[i] != ' ' && line[i] != '\n' && line[i] != '|')
				{
					size_t d = line.find_first_of(" ", i);
					std::string value;
					if (d == std::string::npos) d = pipe - 1;
					value = line.substr(i, d - i);
					if (values[1] == "nil" || values[7] == "nil" || values[4] == "nil" || values[8] == "nil")
					{
						if (value.size() == 2) values[1] = value;
						else if (value.size() == 3) values[7] = value;
						else if (value.size() == 4) values[4] = value;
						else if (value.size() == 7) values[8] = value;
						
					} else if (values[1] != value && values[7] != value && values[4] != value && values[8] != value) {
						if (value.size() == 5) {
							int miss_values = 0;
							for(size_t n = 0; n < value.size(); ++n) {
								size_t pos = values[4].find(value[n]);
								if (pos != std::string::npos)
									miss_values++;
							} 
							if (miss_values == 3) {
								miss_values = 0;
								for(size_t n = 0; n < value.size(); ++n) {
									size_t pos = values[7].find(value[n]);
									if (pos != std::string::npos)
										miss_values++;
								}
								if (miss_values == 3) {
									values[3] = value;
								} else {
									values[5] = value;
								}
							} else {
								values[2] = value;
							}
						} else if (value.size() == 6) {
							int miss_values = 0;
							for (size_t n = 0; n < value.size(); ++n) {
								size_t pos = values[4].find(value[n]);
								if (pos != std::string::npos)
									miss_values++;
							}
							if (miss_values != 4) {
								miss_values = 0;
								for (size_t n = 0; n < value.size(); ++n) {
									size_t pos = values[1].find(value[n]);
									if (pos != std::string::npos)
										miss_values++;
								}
								if (miss_values == 1) {
									values[6] = value;
								} else {
									values[0] = value;
								}
							} else {
								values[9] = value;
							}
						}
					}
					i = d;
					if (!def_values && values[1] != "nil" && values[7] != "nil" && values[4] != "nil" && values[8] != "nil") {
						i = -1;
						def_values = true;
					}
				}
			}
			for (size_t i = pipe; i < line.size(); ++i)
			{
				std::string value;
				if (line[i] != ' ' && line[i] != '\n' && line[i] != '|')
				{
					size_t d = line.find_first_of(" ", i);
					if (d > line.size()) d = line.size();
					value = line.substr(i, d - i);
					
					for (int n = 0; n < 10; ++n) {
						if(compare(values[n], value)) {
							asw += n + '0';
							if (n == 1 || n == 4 || n == 7 || n == 8)
								asw_one++;
						}
					}
					i = d;
				}
			}
			asw_two += std::stoi(asw);
		}
	}
	
	std::cout << "Result:\n";
	std::cout << "Part One: " << asw_one << std::endl;
	std::cout << "Part Two: " << asw_two << std::endl;
	return 0;
}