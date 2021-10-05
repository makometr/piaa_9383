all: main.o solution.o
	g++ main.o solution.o -o lab3

main.o: source/main.cpp
	g++ -c source/main.cpp

graph.o: source/solution.cpp source/solution.h
	g++ -c source/solution.cpp

clean:
	@rm -rf *.o
