all: x

x: main.o Resolver.o Position.o Tile.o
	g++ main.o Resolver.o Position.o Tile.o -o x
	
main.o: main.cpp Resolver.h
	g++ -c main.cpp

Resolver.o: Resolver.cpp Resolver.h Tile.h
	g++ -c Resolver.cpp

Position.o: Position.cpp Position.h
	g++ -c Position.cpp
	
Tile.o: Tile.cpp Tile.h Position.h
	g++ -c Tile.cpp
	
clean:
	rm -rf *.o x
