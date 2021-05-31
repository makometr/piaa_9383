FLAGS = -std=c++17 -Wall -Wextra
BUILD = build
SOURCE_TASK1 = source/task1
SOURCE_TASK2 = source/task2
TEST = test

$(shell  mkdir -p $(BUILD))


all: lab5_task1 lab5_task2

lab5_task1: $(BUILD)/main1.o $(BUILD)/ahocorasick1.o
	@echo "To start enter ./lab5_task1"
	@g++ $(BUILD)/main1.o $(BUILD)/ahocorasick1.o -o lab5_task1 $(FLAGS)

lab5_task2: $(BUILD)/main2.o $(BUILD)/ahocorasick2.o
	@echo "To start enter ./lab5_task2"
	@g++ $(BUILD)/main2.o $(BUILD)/ahocorasick2.o -o lab5_task2 $(FLAGS)

$(BUILD)/main1.o: $(SOURCE_TASK1)/main.cpp
	@g++ -c $(SOURCE_TASK1)/main.cpp -o $(BUILD)/main1.o $(FLAGS)

$(BUILD)/main2.o: $(SOURCE_TASK2)/main.cpp
	@g++ -c $(SOURCE_TASK2)/main.cpp -o $(BUILD)/main2.o $(FLAGS)

$(BUILD)/ahocorasick1.o: $(SOURCE_TASK1)/ahocorasick.cpp $(SOURCE_TASK1)/ahocorasick.hpp
	@g++ -c $(SOURCE_TASK1)/ahocorasick.cpp -o $(BUILD)/ahocorasick1.o $(FLAGS)

$(BUILD)/ahocorasick2.o: $(SOURCE_TASK2)/ahocorasick.cpp $(SOURCE_TASK2)/ahocorasick.hpp
	@g++ -c $(SOURCE_TASK2)/ahocorasick.cpp -o $(BUILD)/ahocorasick2.o $(FLAGS)

clean:
	@rm -rf $(BUILD)/
	@rm -rf *.o lab5_task1 lab5_task2
