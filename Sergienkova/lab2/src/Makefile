all:: window

window: main.o Graph.o Resolver.o Resolver2.o Resolver3.o Edge.o
	g++ main.o Graph.o Resolver.o Resolver2.o Resolver3.o Edge.o -o window

main.o: main.cpp Resolver.h Resolver2.h Resolver3.h Graph.h
	g++ -c main.cpp

Resolver.o: Resolver.cpp Resolver.h Graph.h
	g++ -c  Resolver.cpp
	
Resolver2.o: Resolver2.cpp Resolver2.h Graph.h
	g++ -c Resolver2.cpp
	
Resolver3.o: Resolver3.cpp Resolver3.h Resolver2.h
	g++ -c Resolver3.cpp
	
Graph.o: Graph.cpp Graph.h Edge.h
	g++ -c Graph.cpp
	
Edge.o: Edge.cpp Edge.h
	g++ -c Edge.cpp

 clean:
	rm -rf *.o window
