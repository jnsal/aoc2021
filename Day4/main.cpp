#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define CHART_LENGTH 25
#define NULL_VALUE 9999
#define BINGO 6969

struct Chart
{
	int num[25];
	int* index_table[5][5];
	int bingo = BINGO;
	int bingo_nums[5];
	int winner_number = NULL_VALUE;
	bool won = false;
	
	int sum_bingos() {
		int r = 0;
		for (int i = 0; i < 5; ++i) {
			for (int t = 0; t < 5; ++t) {
				if (index_table[t][i] != &bingo) {
					r += *index_table[t][i];
				}
			}
		}
		return r;
	}
	
	void print_table() {
		for (int i = 0; i < 5; ++i) {
			for (int t = 0; t < 5; ++t) {
				std::cout << *index_table[t][i] << ' ';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
	void bingo_mark(int a) {
		if (won)
			return;
		for (int i = 0; i < 5; ++i) {
			for (int t = 0; t < 5; ++t) {
				if (*index_table[t][i] == a) {
					index_table[t][i] = &bingo;
				}
			}
		}
	}
	bool check_bingo() {
		for (int i = 0; i < 5; ++i) {
			int bingo_column = 0;
			int bingo_row = 0;
			for (int t = 0; t < 5; ++t) {
				if (index_table[t][i] == &bingo) {
					bingo_row++;
					if (bingo_row == 5) {
						for (int r = 0; r < 5; ++r) {
							bingo_nums[r] = *index_table[r][i];
						}
						won = true;
						return true;
					}
				}
			}
			for (int t = 0; t < 5; ++t) {
				if (index_table[i][t] == &bingo) {
					bingo_column++;
					if (bingo_column == 5) {
						for (int r = 0; r < 5; ++r) {
							bingo_nums[r] = *index_table[i][t];
						}
						won = true;
						return true;
					}
				}
			}
		}
		return false;
	}
	void set_board() {
		int ptr = 0;
		for (int i = 0; i < 5; ++i) {
			for (int t = 0; t < 5; ++t) {
				index_table[t][i] = &num[ptr];
				ptr++;
			}
			bingo_nums[i] = NULL_VALUE;
		}
	}
	
	Chart(){
		for (int i = 0; i < CHART_LENGTH; ++i) {
			num[i] = NULL_VALUE;
		}
		set_board();
	}
};

size_t get_number_of_players(char* name)
{
	std::fstream input;
	input.open(name);
	size_t len = 0;
	input.seekg(0, input.beg);
	std::string line;
	std::getline(input, line);
	while (getline(input, line)){
		if (line.size() == 0)
			len++;
	}
	input.seekg(0, input.beg);
	return len + 11;
	
}

int main(int argc, char** argv)
{
	std::fstream input;
	input.open(argv[1]);
	std::vector<int> numbers;
	Chart* boards = new Chart[get_number_of_players(argv[1])];
	size_t player = 0;
	input.seekg(0, input.beg);
	if (input.is_open())
	{
		std::string line;
		std::getline(input, line);
		for (size_t i = 0; i < line.size(); ++i)
		{
			if (line[i] != ',' && line[i] != '\n') {
				if (i + 1 < line.size() && line[i + 1] != ',' && line[i + 1] != '\n')
				{
					std::string number;
					number.append(line, i, 2);
					numbers.push_back(std::stoi(number));
					i++;
				}
				else {
					std::string number;
					number.append(line, i, 1);
					numbers.push_back(std::stoi(number));
					
				}
			}
		}
		
		std::getline(input, line); // go to next line.
		
		while(std::getline(input, line))
		{
			if (line.size() == 0) {
				player++;
				continue;
			}
			for (size_t i = 0; i < line.size(); ++i) {
				if (line[i] != ' ' && line[i] != '\n') {
					std::string number;
					if (i + 1 < line.size() && line[i + 1] != ' ' && line[i + 1] != '\n') {
						number.append(line, i, 2);
						i++;
					} else {
						number.append(line, i, 1);
					}
					for (int n = 0; n < CHART_LENGTH; ++n) {
						if (boards[player].num[n] == NULL_VALUE) {
							boards[player].num[n] = std::stoi(number);
							break;
						}
					}
				}
			}
		}
	}
	
	int asw_one = NULL_VALUE;
	int asw_two = NULL_VALUE;
	bool winner = false;
	int last_winner = 0;
	for (size_t i = 0; i < numbers.size(); ++i) {
		for (size_t p = 0; p <= player; ++p) {
			boards[p].bingo_mark(numbers[i]);
		}
		for (size_t w = 0; w <= player; ++w) {
			if (!boards[w].won) {
				if (boards[w].check_bingo()) {
					last_winner = w;
					boards[w].winner_number = numbers[i];
					if (!winner) {
						asw_one = numbers[i] * boards[w].sum_bingos();
						winner = true;
					}
				}
			}
		}
	}
	asw_two = boards[last_winner].winner_number *  boards[last_winner].sum_bingos();
	
	std::cout << "Result\n";
	std::cout << "Part One: " << asw_one << std::endl;
	std::cout << "Part Two: " << asw_two << std::endl;
	return 0;
}