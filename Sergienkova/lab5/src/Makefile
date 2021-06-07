all:: lab5

lab5: main.o
	g++ main.o -o lab5
	
main.o: main.cpp Bohr.h Node.h
	g++ -c main.cpp
	
clean:
	rm -rf *.o lab5
