BUILD = build
SOURCE = source
TEST = tests

all: release tests

release: main.o square.o 
	g++ main.o square.o -o lab

tests: test.o square.o
	g++ test.o square.o -o test

main.o: $(SOURCE)/main.cpp
	g++ -c -O2 $(SOURCE)/main.cpp -o main.o

square.o: $(SOURCE)/square.cpp
	g++ -c -O2 $(SOURCE)/square.cpp -o square.o

test.o: $(TEST)/test.cpp
	g++ -c $(TEST)/test.cpp -o test.o

clean:
	rm -rf *.o