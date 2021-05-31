FLAGS = -std=c++17 
BUILD_1 = Build/lab5_1
BUILD_2 = Build/lab5_2
SOURCE_1 = Source/lab5_1
SOURCE_2 = Source/lab5_2



$(shell  mkdir -p $(BUILD_1))
$(shell  mkdir -p $(BUILD_2))

all: lab5_1 lab5_2

lab5_1: $(BUILD_1)/main_1.o $(BUILD_1)/aho_corasick.o 
	@g++ $(BUILD_1)/main_1.o $(BUILD_1)/aho_corasick.o -o lab5_1 $(FLAGS)
	@echo "lab5_1 Builded"
	
lab5_2: $(BUILD_2)/main_2.o $(BUILD_2)/aho_corasick.o 
	@g++ $(BUILD_2)/main_2.o $(BUILD_2)/aho_corasick.o -o lab5_2 $(FLAGS)
	@echo "lab5_2 Builded"

$(BUILD_1)/main_1.o:  $(SOURCE_1)/main.cpp
	@g++ -c $(SOURCE_1)/main.cpp $(FLAGS) -o $(BUILD_1)/main_1.o

$(BUILD_2)/main_2.o:  $(SOURCE_2)/main.cpp
	@g++ -c $(SOURCE_2)/main.cpp $(FLAGS) -o $(BUILD_2)/main_2.o

$(BUILD_1)/aho_corasick.o: $(SOURCE_1)/aho_corasick.cpp
	@g++ -c $(SOURCE_1)/aho_corasick.cpp $(FLAGS) -o $(BUILD_1)/aho_corasick.o

$(BUILD_2)/aho_corasick.o: $(SOURCE_2)/aho_corasick.cpp
	@g++ -c $(SOURCE_2)/aho_corasick.cpp $(FLAGS) -o $(BUILD_2)/aho_corasick.o
clean:
	@rm -rf BUILD/
	@rm lab5_1 lab5_2 
	@echo "Clean Finished"