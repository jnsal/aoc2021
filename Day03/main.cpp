#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits.h>

std::string o2_rating(std::string* str, size_t size, uint8_t index)
{
	size_t len = str[0].size();
	uint8_t n = 1;
	int z_count = 0;
	size_t t_size = size;
	char a, b;
	a = index == 0 ? '0' : '1';
	b = index == 0 ? '1' : '0';
	while (size > 1)
	{
		for (size_t i = 0; i < size; ++i) {
			if (str[i][0] != '0' && str[i][0] != '1') { // get new size
				size = i;
				break;
			}
			if (str[i][n] == '0') {
				z_count++;
			}
		}
		if (size == 1)
			break;
		uint8_t bigger;
		if (index == 0) {
			if (z_count > (int)size / 2)
				bigger = 0;
			else 
				bigger = 1;
		} else {
			if (z_count <= (int)size / 2)
				bigger = 1;
			else 
				bigger = 0;
		}
		
		if (bigger == 0) {
			for (size_t i = 0; i < t_size; ++i) {
				if (str[i][n] != a) {
					str[i].clear();
					str[i].insert(0, "nil");
				}
			}
		} else if (bigger == 1) {
			for (size_t i = 0; i < t_size; ++i) {
				if (str[i][n] != b) {
					str[i].clear();
					str[i].insert(0, "nil");
				}
			}
		}
		n++;
		z_count = 0;
		if (n > len)
			n = 0;
		for(size_t i = 0; i < t_size; ++i) {
			if (str[i][0] != '0' && str[i][0] != '1' && i + 1 < t_size) {
				for(size_t t = i; t < t_size; ++t) {
					if (str[t][0] == '0' || str[t][0] == '1') {
						str[i].swap(str[t]);
					}
				}
			}
		}
		
	}
	return str[0];
}

int strbin_to_decimal(std::string str)
{
	const int size = str.size();
	int len = str.size() - 1;
	int arr[size];
	for (size_t i = 0; i < str.size(); ++i)
		arr[i] = 0;
	
	for (size_t i = 0; i < str.size(); ++i) {
		if (str[i] == '1') {
			arr[i] = std::pow(2, len);
		}
		len--;
	}
	
	int result = 0;
	for (size_t i = 0; i < str.size(); ++i) {
		result += arr[i];
	}
	
	return result;
}

int main(int argc, char **argv)
{
	std::fstream smp;
	smp.open(argv[1]);
	std::vector<std::string> report;
	int length = 0;
	{ // Get length of the line to initialize counter.
		std::string line;
		std::getline(smp, line);
		for (size_t i = 0; i < line.size(); ++i)
			length++;
	}
	smp.seekg(0);
	
	int zero_count[length];
	for (int i = 0; i < length; ++i) {
		zero_count[i] = 0;
	}
	int lines = 0;
	
	if (smp.is_open())
	{
		std::string line;
		while (std::getline(smp, line))
		{
			report.push_back(line);
			lines++;
			for (size_t i = 0; i < line.size(); ++i)
			{
				if (line[i] == '0') {
					zero_count[i]++;
				}
			}
		}
	}
	smp.close();
	
	std::string o2_gen_rating;
	std::string co2_scr_rating;
	{
		size_t o2_size = 0;
		size_t co2_size = 0;
		unsigned char bigger;
		if (zero_count[0] > lines / 2) {
			o2_size = zero_count[0];
			co2_size = lines - zero_count[0];
			bigger = 0;
		} else if (zero_count[0] < lines /2) {
			o2_size = lines - zero_count[0];
			co2_size = zero_count[0];
			bigger = 1;
		} else {
			o2_size = lines / 2;
			co2_size = lines / 2;
			bigger = 2;
		}
		std::string o2_gen[o2_size];
		std::string co2_gen[co2_size];
		int a = 0, b = 0;
		std::string line;
		for (size_t i = 0; i < report.size(); ++i)
		{
			if (report[i][0] == '0') {
				if (bigger == 0) {
					o2_gen[a] = report[i];
					a++;
				}
				else if (bigger == 1 || bigger == 2){
					co2_gen[b] = report[i];
					b++;
				}
				
			} else if (report[i][0] == '1') {
				if (bigger == 0) {
					co2_gen[b] = report[i];
					b++;
				} else if (bigger == 1 || bigger == 2) {
					o2_gen[a] = report[i];
					a++;
				}
			}
		}
		for (size_t i = 0; i < o2_size; ++i) {
			if (o2_gen[i][0] != '0' && o2_gen[i][0] != '1') {
				o2_size = i;
				break;
			}
		}
		o2_gen_rating = o2_rating(o2_gen, o2_size, 0);
		co2_scr_rating = o2_rating(co2_gen, co2_size, 1);
		
		for (size_t i = 0; i < co2_size; ++i) {
			if (o2_gen[i][0] != '0' && o2_gen[i][0] != '1') {
				co2_size = i;
				break;
			}
		}
	}
	
	std::string gamma_bin;
	std::string eps_bin;
	
	for (int i = 0; i < length; ++i) {
		if (zero_count[i] > lines / 2) {
			gamma_bin.insert(gamma_bin.end(), '0');
			eps_bin.insert(eps_bin.end(), '1');
		} else {
			gamma_bin.insert(gamma_bin.end(), '1');
			eps_bin.insert(eps_bin.end(), '0');
		}
	}
	int gamma_rate = strbin_to_decimal(gamma_bin);
	int epsilon_rate = strbin_to_decimal(eps_bin);
	int o2_rate = strbin_to_decimal(o2_gen_rating);
	int co2_rate = strbin_to_decimal(co2_scr_rating);
	
	
	std::cout << "Result:\n";
	std::cout << "Part One: " << gamma_rate * epsilon_rate << std::endl;
	std::cout << "Part Two: " << o2_rate * co2_rate << std::endl;
	
	(void) report;
	(void) gamma_rate;
	(void) epsilon_rate;
	
	return 0;
}