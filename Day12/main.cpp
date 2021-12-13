#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#define LINES 23

struct Cave
{
	std::string here;
	struct Cave* linked_caves[LINES];
	int paths = 0;
	bool relevant;
	int visited = 0;
	
	Cave() { visited = 0; }
	
	void set_cave(std::string cave, bool b) {
		this->here = cave;
		this->relevant = b;
	}
	void add_path(Cave* linked) {
		linked_caves[paths] = linked;
		paths++;
	}
	void print_paths() {
		printf("%s -", relevant ? "Is Relevant" : "is not Relevant");
		printf("-> %s ", here.c_str());
		for (int i = 0; i < paths; ++i) printf("%s ",linked_caves[i]->here.c_str());
		printf("\n");
	}
	
	int get_paths()
	{
		if (here == "end") return 1;
		visited++;
		int result = 0;
		
		
		for (int i = 0; i < paths; ++i) {
			if (linked_caves[i]->here != "start") {
				if (linked_caves[i]->relevant || linked_caves[i]->visited < 1) {
					result += linked_caves[i]->get_paths();
				}
			}
		}
		
		visited = 0;
		return result;
	}
	
	int get_paths2(bool double_check)
	{
		if (here == "end") return 1;
		visited++;
		int result = 0;
		
		for (int i = 0; i < paths; ++i) {
			if (linked_caves[i]->here != "start") {
				if (!double_check || (!relevant && visited > 1)) {
					if (linked_caves[i]->relevant || linked_caves[i]->visited < 1) {
						result += linked_caves[i]->get_paths2(false);
					}
				} else if (double_check){
					if (!linked_caves[i]->relevant && linked_caves[i]->visited > 1) {
						result += linked_caves[i]->get_paths2(false);
					}
					else
						result += linked_caves[i]->get_paths2(true);
				}
			}
		}
		
		visited--;
		return result;
	}
};

int get_paths(std::string all_caves[][2])
{
	int size = LINES;
	std::vector<std::string> relevant_caves;
	relevant_caves.push_back(std::string("start"));
	for (int i = 0; i < LINES; ++i) {
		size = i;
		if (all_caves[i][0] == "") {
			break;
		}
		auto result = std::find(relevant_caves.begin(), relevant_caves.end(), all_caves[i][0]);
		if (result == relevant_caves.end()) {
			relevant_caves.push_back(all_caves[i][0]);
			continue;
		}
		result = std::find(relevant_caves.begin(), relevant_caves.end(), all_caves[i][1]);
		if (result == relevant_caves.end()) {
			relevant_caves.push_back(all_caves[i][1]);
			continue;
		}
	}
	std::vector<std::string> temp = relevant_caves;
	Cave path[relevant_caves.size()];
	for (size_t i = 0; i < relevant_caves.size(); ++i) {
		bool relevant = true;
		if (relevant_caves[i][0] >= 97 && relevant_caves[i][0] <= 122) relevant = false;
		path[i].set_cave(relevant_caves[i], relevant);
	}
	for (int i = 0; i < size; ++i) {
		for (size_t l = 0; l < relevant_caves.size(); ++l) {
			if (all_caves[i][0] == path[l].here) {
				int cave = 0;
				for (size_t n = 0; n < relevant_caves.size(); ++n) {
					if (all_caves[i][1] == path[n].here) {
						cave = n;
						break;
					}
				}
				path[l].add_path(&path[cave]);
			}
			if (all_caves[i][1] == path[l].here) {
				int cave = 0;
				for (size_t n = 0; n < relevant_caves.size(); ++n) {
					if (all_caves[i][0] == path[n].here) {
						cave = n;
						break;
					}
				}
				path[l].add_path(&path[cave]);
			}
		}
	}
	for (size_t i = 0; i < relevant_caves.size(); ++i) path[i].print_paths();
	
	
	return path[0].get_paths2(true);
}

int main(int argc, char** argv)
{
	std::fstream input;
	input.open(argv[1]);
	int asw_one = 0;
	int asw_two = 0;
	std::string paths[LINES][2];
	
	if (input.is_open())
	{
		int n = 0;
		std::string line;
		while(std::getline(input, line)) 
		{
			size_t found = line.find('-');
			paths[n][0] = line.substr(0, found);
			paths[n][1] = line.substr(found + 1, line.size());
			n++;
		}
	}
	input.close();
	// for (int i = 0; i < LINES; ++i) printf("%s, %s\n", paths[i][0].c_str(), paths[i][1].c_str());

	asw_one = get_paths(paths);
	
	std::cout << "Result\n";
	std::cout << "Part One: " << asw_one << std::endl;
	std::cout << "Part Two: " << asw_two << std::endl;
}
