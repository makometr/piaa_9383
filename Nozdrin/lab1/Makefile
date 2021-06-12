FLAGS = -std=c++17 -Wall -Wextra
BUILD = build
SOURCE = src
TEST = test

$(shell  mkdir -p $(BUILD))

all: $(BUILD)/main.o $(BUILD)/Squaring.o
	@g++ $(FLAGS) $(BUILD)/main.o $(BUILD)/Squaring.o  -o lab1.out
	@echo "lab1 Builded"

tests: $(BUILD)/Squaring.o $(BUILD)/tests.o
	@g++ $(FLAGS) $(BUILD)/Squaring.o $(BUILD)/tests.o -o run_tests.out
	@echo "run_tests.out Builded"

$(BUILD)/main.o:  $(SOURCE)/main.cpp
	@g++ -c $(SOURCE)/main.cpp $(FLAGS) -o $(BUILD)/main.o

$(BUILD)/Squaring.o: $(SOURCE)/Squaring.cpp
	@g++ -c $(SOURCE)/Squaring.cpp $(FLAGS) -o $(BUILD)/Squaring.o

$(BUILD)/tests.o: $(TEST)/tests.cpp
	@g++ -c $(TEST)/tests.cpp $(FLAGS) -o $(BUILD)/tests.o

run:
	@./lab1.out

clean:
	@rm -rf BUILD/
	@#rm *.out
	@echo "Clean Finished"
