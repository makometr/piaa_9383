BUILD = build
SOURCE = source

all: pr

pr: $(BUILD)/main1.o $(BUILD)/lb5_1.o
	g++ $(BUILD)/main.o $(BUILD)/lb5_1.o -o pr

$(BUILD)/main1.o: $(SOURCE)/main1.cpp
	g++ -c $(SOURCE)/main1.cpp -o $(BUILD)/main1.o

$(BUILD)/lb5_1.o: $(SOURCE)/lb5_1.cpp
	g++ -c $(SOURCE)/lb5_1.cpp -o $(BUILD)/lb5_1.o


clean:
	rm -rf $(BUILD)/