all: main.o graph.o
	g++ main.o graph.o -o lab2

main.o: source/main.cpp
	g++ -c source/main.cpp

graph.o: source/graph.cpp source/graph.h
	g++ -c source/graph.cpp

clean:
	@rm -rf *.o
