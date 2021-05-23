BUILD = build
SOURCE = source
TEST = tests

all: release tests

release: main.o ford_falk.o 
	g++ main.o ford_falk.o -o lab

tests: test.o ford_falk.o
	g++ test.o ford_falk.o -o test

main.o: $(SOURCE)/main.cpp
	g++ -c -O2 $(SOURCE)/main.cpp -o main.o

ford_falk.o: $(SOURCE)/ford_falk.cpp
	g++ -c -O2 $(SOURCE)/ford_falk.cpp -o ford_falk.o

test.o: $(TEST)/test.cpp
	g++ -c $(TEST)/test.cpp -o test.o

clean:
	rm -rf *.o