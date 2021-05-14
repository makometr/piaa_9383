FLAGS = -std=c++17 -Wall -Wextra
BUILD = build
SOURCE = source
TEST = test

$(shell  mkdir -p $(BUILD))


all: lab3 run_tests

lab3: $(BUILD)/graph.o $(BUILD)/main.o
	@echo "To start enter ./lab3"
	@g++ $(BUILD)/main.o $(BUILD)/graph.o -o lab3 $(FLAGS)

run_tests: $(BUILD)/test.o $(BUILD)/graph.o
	@echo "To run tests enter ./run_tests"
	@g++ $(BUILD)/test.o $(BUILD)/graph.o -o run_tests

$(BUILD)/main.o: $(SOURCE)/main.cpp
	@g++ -c $(SOURCE)/main.cpp -o $(BUILD)/main.o

$(BUILD)/graph.o: $(SOURCE)/graph.cpp $(SOURCE)/graph.hpp
	@g++ -c $(SOURCE)/graph.cpp -o $(BUILD)/graph.o

$(BUILD)/test.o: $(TEST)/test.cpp
	@g++ -c $(TEST)/test.cpp -o $(BUILD)/test.o

clean:
	@rm -rf $(BUILD)/
	@rm -rf *.o lab3 run_tests
