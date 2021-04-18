FLAGS = -std=c++17 -Wall -Wextra
BUILD_GREEDY = Build/Greedy
BUILD_A_STAR = Build/A_star
BUILD_TEST_GREEDY = Build/Greedy/Test
BUILD_TEST_A_STAR = Build/A_star/Test
SOURCE_GREEDY = Source/Greedy
SOURCE_A_STAR = Source/A_star
TEST = Test

$(shell  mkdir -p $(BUILD_GREEDY))
$(shell  mkdir -p $(BUILD_A_STAR))
$(shell  mkdir -p $(BUILD_TEST_GREEDY))
$(shell  mkdir -p $(BUILD_TEST_A_STAR))

all: lab2_greedy lab2_a_star test_greedy a_star_test

lab2_greedy: $(BUILD_GREEDY)/main.o $(BUILD_GREEDY)/greedy.o
	@g++ $(BUILD_GREEDY)/main.o $(BUILD_GREEDY)/greedy.o  -o lab2_greedy $(FLAGS)
	@echo "lab2_greedy Builded"
lab2_a_star: $(BUILD_A_STAR)/main.o $(BUILD_A_STAR)/a_star.o
	@g++ $(BUILD_A_STAR)/main.o $(BUILD_A_STAR)/a_star.o  -o lab2_a_star $(FLAGS)
	@echo "lab2_a_star Builded"
test_greedy: $(BUILD_TEST_GREEDY)/greedyTest.o $(BUILD_GREEDY)/greedy.o
	@g++ $(BUILD_TEST_GREEDY)/greedyTest.o $(BUILD_GREEDY)/greedy.o -o test_greedy $(FLAGS)
	@echo "test_greedy Builded"
a_star_test: $(BUILD_TEST_A_STAR)/a_starTest.o $(BUILD_A_STAR)/a_star.o
	@g++ $(BUILD_TEST_A_STAR)/a_starTest.o $(BUILD_A_STAR)/a_star.o -o a_star_test $(FLAGS)
	@echo "a_star_test Builded"
$(BUILD_GREEDY)/main.o:  $(SOURCE_GREEDY)/main.cpp
	@g++ -c $(SOURCE_GREEDY)/main.cpp $(FLAGS) -o $(BUILD_GREEDY)/main.o
$(BUILD_GREEDY)/greedy.o:  $(SOURCE_GREEDY)/greedy.cpp
	@g++ -c $(SOURCE_GREEDY)/greedy.cpp $(FLAGS) -o $(BUILD_GREEDY)/greedy.o
$(BUILD_A_STAR)/main.o:  $(SOURCE_A_STAR)/main.cpp
	@g++ -c $(SOURCE_A_STAR)/main.cpp $(FLAGS) -o $(BUILD_A_STAR)/main.o
$(BUILD_A_STAR)/a_star.o:  $(SOURCE_A_STAR)/a_star.cpp
	@g++ -c $(SOURCE_A_STAR)/a_star.cpp $(FLAGS) -o $(BUILD_A_STAR)/a_star.o
$(BUILD_TEST_GREEDY)/greedyTest.o: $(TEST)/greedyTest.cpp
	@g++ -c $(TEST)/greedyTest.cpp $(FLAGS) -o $(BUILD_TEST_GREEDY)/greedyTest.o
$(BUILD_TEST_A_STAR)/a_starTest.o: $(TEST)/a_starTest.cpp
	@g++ -c $(TEST)/a_starTest.cpp $(FLAGS) -o $(BUILD_TEST_A_STAR)/a_starTest.o
clean:
	@rm -rf BUILD/
	@rm lab2_greedy lab2_a_star test_greedy a_star_test
	@echo "Clean Finished"
