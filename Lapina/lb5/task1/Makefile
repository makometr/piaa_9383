BUILD = build
SOURCE = source

all: pr

pr: $(BUILD)/main.o $(BUILD)/lb5_1.o
	g++ $(BUILD)/main.o $(BUILD)/lb5_1.o -o pr

$(BUILD)/main.o: $(SOURCE)/main.cpp
	g++ -c $(SOURCE)/main.cpp -o $(BUILD)/main.o

$(BUILD)/lb5_1.o: $(SOURCE)/lb5_1.cpp
	g++ -c $(SOURCE)/lb5_1.cpp -o $(BUILD)/lb5_1.o


clean:
	rm -rf $(BUILD)/
