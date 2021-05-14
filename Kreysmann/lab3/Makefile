$(shell mkdir -p Build)

all:ff

ff: Build/main.o Build/ford_fulkerson.o
	g++ Build/main.o Build/ford_fulkerson.o -o lab3 

Build/main.o: Source/main.cpp
	g++ -c Source/main.cpp   -o Build/main.o

Build/ford_fulkerson.o: Source/ford_fulkerson.cpp
	g++ -c Source/ford_fulkerson.cpp  -o Build/ford_fulkerson.o

clean:
	rm -rf Build/