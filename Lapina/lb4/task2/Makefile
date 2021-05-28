BUILD = build
SOURCE = source
TEST = test

all: pr tests

pr: $(BUILD)/main.o $(BUILD)/lb4_2.o
	g++ $(BUILD)/main.o $(BUILD)/lb4_2.o -o pr

tests: $(BUILD)/tests_programm.o $(BUILD)/lb4_2.o
	g++ $(BUILD)/tests_programm.o $(BUILD)/lb4_2.o -o tests

$(BUILD)/main.o: $(SOURCE)/main.cpp
	g++ -c $(SOURCE)/main.cpp -o $(BUILD)/main.o

$(BUILD)/lb4_2.o: $(SOURCE)/lb4_2.cpp
	g++ -c $(SOURCE)/lb4_2.cpp -o $(BUILD)/lb4_2.o

$(BUILD)/tests_programm.o: $(TEST)/tests_programm.cpp
	g++ -c $(TEST)/tests_programm.cpp -o $(BUILD)/tests_programm.o

clean:
	rm -rf $(BUILD)/
