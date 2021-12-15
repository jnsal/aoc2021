SAMPLE = input.txt
TEST = sample.txt

CC = g++

CC_FLAGS = -Wall -Werror -Wshadow 

all: main.cpp
	$(CC) $(CC_FLAGS) main.cpp -o result
	./result $(SAMPLE)

test: main.cpp
	$(CC) $(CC_FLAGS) main.cpp -o result
	./result $(TEST)
