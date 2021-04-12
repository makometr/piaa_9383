BUILD = build
SOURCE = source
TEST = tests

all: releaseA releaseG testsA testsG

releaseA: mainA.o graph.o 
	g++ mainA.o graph.o -o labA
	
releaseG: mainG.o greedy.o 
	g++ mainG.o greedy.o -o labG

testsA: testA.o graph.o
	g++ testA.o graph.o -o testA

testsG: testG.o greedy.o
	g++ testG.o greedy.o -o testG

mainA.o: $(SOURCE)/mainA.cpp
	g++ -c -O2 $(SOURCE)/mainA.cpp -o mainA.o

mainG.o: $(SOURCE)/mainG.cpp
	g++ -c -O2 $(SOURCE)/mainG.cpp -o mainG.o

graph.o: $(SOURCE)/graph.cpp
	g++ -c -O2 $(SOURCE)/graph.cpp -o graph.o

greedy.o: $(SOURCE)/greedy.cpp
	g++ -c -O2 $(SOURCE)/greedy.cpp -o greedy.o

testA.o: $(TEST)/testA.cpp
	g++ -c $(TEST)/testA.cpp -o testA.o

testG.o: $(TEST)/testG.cpp
	g++ -c $(TEST)/testG.cpp -o testG.o

clean:
	rm -rf *.o