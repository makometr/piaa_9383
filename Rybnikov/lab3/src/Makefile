all:: programm

programm: main.o Orgraph.o FF.o
	g++ main.o Orgraph.o FF.o -o programm

main.o: main.cpp Orgraph.h FF.h
	g++ -c main.cpp

Orgraph.o: Orgraph.cpp Orgraph.h
	g++ -c Orgraph.cpp

FF.o: FF.cpp FF.h Orgraph.h
	g++ -c FF.cpp
 
clean:
	rm -rf *.o programm
