FLAGS = -std=c++17 -Wall -Wextra
BUILD = build
SOURCE = source
TEST = test

$(shell  mkdir -p $(BUILD))


all: lab1

lab1: $(BUILD)/main.o $(BUILD)/Field.o
	@echo "To start enter ./lab1"
	@g++ $(BUILD)/main.o $(BUILD)/Field.o -o lab1 $(FLAGS)

run_tests: $(BUILD)/test_field.o $(BUILD)/Field.o
	@g++ $(BUILD)/test_field.o $(BUILD)/Field.o -o run_tests

$(BUILD)/test_field.o: $(TEST)/test_field.cpp
	@g++ -c $(TEST)/test_field.cpp -o $(BUILD)/test_field.o

$(BUILD)/Field.o: ${SOURCE}/Field.cpp
	@g++ -c ${SOURCE}/Field.cpp -o $(BUILD)/Field.o

$(BUILD)/main.o: ${SOURCE}/main.cpp
	@g++ -c $(SOURCE)/main.cpp -o $(BUILD)/main.o

clean:
	@rm -rf $(BUILD)/
	@rm -rf *.o lab1 run_tests
