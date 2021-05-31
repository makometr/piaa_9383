BUILD = build
SOURCE = source
TEST = test

all: pr tests

pr: $(BUILD)/main2.o $(BUILD)/lb5_2.o
	g++ $(BUILD)/main2.o $(BUILD)/lb5_2.o -o pr

tests: $(BUILD)/tests.o $(BUILD)/lb5_2.o
	g++ $(BUILD)/tests.o $(BUILD)/lb5_2.o -o tests

$(BUILD)/main2.o: $(SOURCE)/main2.cpp
	g++ -c $(SOURCE)/main2.cpp -o $(BUILD)/main2.o

$(BUILD)/lb5_2.o: $(SOURCE)/lb5_2.cpp
	g++ -c $(SOURCE)/lb5_2.cpp -o $(BUILD)/lb5_2.o

$(BUILD)/tests.o: $(TEST)/tests.cpp
	g++ -c $(TEST)/tests.cpp -o $(BUILD)/tests.o

clean:
	rm -rf $(BUILD)/