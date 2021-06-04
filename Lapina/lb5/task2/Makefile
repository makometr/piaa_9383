BUILD = build
SOURCE = source

all: pr

pr: $(BUILD)/main.o $(BUILD)/lb5_2.o
	g++ $(BUILD)/main.o $(BUILD)/lb5_2.o -o pr

$(BUILD)/main.o: $(SOURCE)/main.cpp
	g++ -c $(SOURCE)/main.cpp -o $(BUILD)/main.o

$(BUILD)/lb5_2.o: $(SOURCE)/lb5_2.cpp
	g++ -c $(SOURCE)/lb5_2.cpp -o $(BUILD)/lb5_2.o

clean:
	rm -rf $(BUILD)/
