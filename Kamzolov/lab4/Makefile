FLAGS = -std=c++17 -Wall -Wextra
BUILD = Build
SOURCE = Source
TEST = Tests
KMP = Source/KMP


$(shell  mkdir -p $(BUILD))

lab4_1: $(BUILD)/main_1.o $(BUILD)/KMP.o tests lab4_2
	@g++ $(BUILD)/main_1.o $(BUILD)/KMP.o -o lab4_1 $(FLAGS)
	@echo "lab4_1 Builded"
	
lab4_2: $(BUILD)/main_2.o $(BUILD)/KMP.o
	@g++ $(BUILD)/main_2.o $(BUILD)/KMP.o -o lab4_2 $(FLAGS)
	@echo "lab4_2 Builded"

tests: $(BUILD)/KMPTest.o $(BUILD)/KMP.o
	@g++ $(BUILD)/KMP.o $(BUILD)/KMPTest.o $(FLAGS) -o run_tests
	@echo "run_tests Builded"

$(BUILD)/main_1.o:  $(SOURCE)/main_1.cpp
	@g++ -c $(SOURCE)/main_1.cpp $(FLAGS) -o $(BUILD)/main_1.o

$(BUILD)/main_2.o:  $(SOURCE)/main_2.cpp
	@g++ -c $(SOURCE)/main_2.cpp $(FLAGS) -o $(BUILD)/main_2.o

$(BUILD)/KMP.o: $(KMP)/KMP.cpp
	@g++ -c $(KMP)/KMP.cpp $(FLAGS) -o $(BUILD)/KMP.o

$(BUILD)/KMPTest.o: $(TEST)/KMPTest.cpp
	@g++ -c $(TEST)/KMPTest.cpp $(FLAGS) -o $(BUILD)/KMPTest.o
clean:
	@rm -rf BUILD/
	@rm lab4_1 lab4_2 run_tests
	@echo "Clean Finished"
