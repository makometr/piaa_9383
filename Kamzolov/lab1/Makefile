FLAGS = -std=c++17 -Wall -Wextra
BUILD = build
SOURCE = Source
TEST = Tests

$(shell  mkdir -p $(BUILD))

lab1: $(BUILD)/main.o $(BUILD)/Table.o tests
	@g++ $(BUILD)/main.o $(BUILD)/Table.o  -o lab1 $(FLAGS)
	@echo "lab1 Builded"

tests: $(BUILD)/Table.o $(BUILD)/algosTest.o
	@g++ $(BUILD)/Table.o $(BUILD)/algosTest.o $(FLAGS) -o run_tests
	@echo "run_tests Builded"

$(BUILD)/main.o:  $(SOURCE)/main.cpp
	@g++ -c $(SOURCE)/main.cpp $(FLAGS) -o $(BUILD)/main.o
$(BUILD)/Table.o: $(SOURCE)/Table.cpp
	@g++ -c $(SOURCE)/Table.cpp $(FLAGS) -o $(BUILD)/Table.o
$(BUILD)/algosTest.o: $(TEST)/algosTest.cpp
	@g++ -c $(TEST)/algosTest.cpp $(FLAGS) -o $(BUILD)/algosTest.o
clean:
	@rm -rf BUILD/
	@rm lab1 run_tests
	@echo "Clean Finished"
