all: programm

programm: main.o
	g++ main.o -o programm
	
main.o: main.cpp
	g++ -c main.cpp
	
clean:
	rm -rf *.o programm
