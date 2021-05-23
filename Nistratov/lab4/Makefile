BUILD = build
SOURCE = source
TEST = tests

all: release_1 tests_1 release_2 tests_2 clean

release_1: main_1.o lab4_1.o 
	g++ main_1.o lab4_1.o -o lab_1

tests_1: test_1.o lab4_1.o
	g++ test_1.o lab4_1.o -o test_1

main_1.o: $(SOURCE)/main_1.cpp
	g++ -c -O2 $(SOURCE)/main_1.cpp -o main_1.o

lab4_1.o: $(SOURCE)/lab4_1.cpp
	g++ -c -O2 $(SOURCE)/lab4_1.cpp -o lab4_1.o

test_1.o: $(TEST)/test_1.cpp
	g++ -c $(TEST)/test_1.cpp -o test_1.o

release_2: main_2.o lab4_2.o 
	g++ main_2.o lab4_2.o -o lab_2

tests_2: test_2.o lab4_2.o
	g++ test_2.o lab4_2.o -o test_2

main_2.o: $(SOURCE)/main_2.cpp
	g++ -c -O2 $(SOURCE)/main_2.cpp -o main_2.o

lab4_2.o: $(SOURCE)/lab4_2.cpp
	g++ -c -O2 $(SOURCE)/lab4_2.cpp -o lab4_2.o

test_2.o: $(TEST)/test_2.cpp
	g++ -c $(TEST)/test_2.cpp -o test_2.o

clean:
	rm -rf *.o