FLAGS = -std=c++17 -Wall -Wextra
BUILD = build
SOURCE = source
TEST = test

$(shell  mkdir -p $(BUILD))


all: lab4 run_tests

lab4: $(BUILD)/main.o $(BUILD)/kmp.o
	@echo "To start enter ./lab4.\nUse -h or --help for list of commands."
	@g++ $(BUILD)/main.o $(BUILD)/kmp.o -o lab4 $(FLAGS)

run_tests: $(BUILD)/test.o $(BUILD)/kmp.o
	@echo "To run tests enter ./run_tests"
	@g++ $(BUILD)/test.o $(BUILD)/kmp.o -o run_tests

$(BUILD)/main.o: $(SOURCE)/main.cpp
	@g++ -c $(SOURCE)/main.cpp -o $(BUILD)/main.o

$(BUILD)/kmp.o: $(SOURCE)/kmp.cpp $(SOURCE)/kmp.hpp
	@g++ -c $(SOURCE)/kmp.cpp -o $(BUILD)/kmp.o

$(BUILD)/test.o: $(TEST)/test.cpp
	@g++ -c $(TEST)/test.cpp -o $(BUILD)/test.o

clean:
	@rm -rf $(BUILD)/
	@rm -rf *.o lab4 run_tests
