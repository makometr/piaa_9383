all:: lab5

lab5: main.o Bohr.o
	g++ main.o Bohr.o -o lab5
	
main.o: main.cpp Bohr.hpp
	g++ -c main.cpp
	
Bohr.o: Bohr.cpp Bohr.hpp
	g++ -c Bohr.cpp
	
clean:
	rm -rf *.o lab5
