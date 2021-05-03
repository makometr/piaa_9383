FLAGS = -std=c++17 -Wall -Wextra
BUILD = Build
SOURCE = Source
TEST = Tests

$(shell  mkdir -p $(BUILD))

lab3: $(BUILD)/main.o $(BUILD)/FordFulkerson.o tests
	@g++ $(BUILD)/main.o $(BUILD)/FordFulkerson.o  -o lab3 $(FLAGS)
	@echo "lab3 Builded"

tests: $(BUILD)/FordFulkersonTest.o $(BUILD)/FordFulkerson.o
	@g++ $(BUILD)/FordFulkerson.o $(BUILD)/FordFulkersonTest.o $(FLAGS) -o run_tests
	@echo "run_tests Builded"

$(BUILD)/main.o:  $(SOURCE)/main.cpp
	@g++ -c $(SOURCE)/main.cpp $(FLAGS) -o $(BUILD)/main.o
$(BUILD)/FordFulkerson.o: $(SOURCE)/FordFulkerson.cpp
	@g++ -c $(SOURCE)/FordFulkerson.cpp $(FLAGS) -o $(BUILD)/FordFulkerson.o
$(BUILD)/FordFulkersonTest.o: $(TEST)/FordFulkersonTest.cpp
	@g++ -c $(TEST)/FordFulkersonTest.cpp $(FLAGS) -o $(BUILD)/FordFulkersonTest.o
clean:
	@rm -rf BUILD/
	@rm lab3 run_tests
	@echo "Clean Finished"
