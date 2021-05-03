all:: proc

proc: main.o Graph.o Resolver.o Finder.o Edge.o
	g++ main.o Graph.o Resolver.o Finder.o Edge.o -o proc

main.o: main.cpp Graph.h Resolver.h Finder.h
	g++ -c main.cpp

Graph.o: Graph.cpp Graph.h Edge.h
	g++ -c Graph.cpp

Edge.o: Edge.cpp Edge.h
	g++ -c Edge.cpp
	
Finder.o: Finder.cpp Finder.h Graph.h
	g++ -c Finder.cpp

Resolver.o: Resolver.cpp Resolver.h Graph.h
	g++ -c Resolver.cpp
 
clean:
	rm -rf *.o proc
