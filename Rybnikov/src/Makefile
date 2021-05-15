all:: programm

programm: main.o Orgraph.o GreedyAlg.o AStar.o Option.o
	g++ main.o Orgraph.o GreedyAlg.o AStar.o Option.o -o programm

main.o: main.cpp Option.h Orgraph.h GreedyAlg.h AStar.h
	g++ -c main.cpp

Orgraph.o: Orgraph.cpp Orgraph.h
	g++ -c  Orgraph.cpp
	
GreedyAlg.o: GreedyAlg.cpp GreedyAlg.h Orgraph.h
	g++ -c GreedyAlg.cpp
	
AStar.o: AStar.cpp AStar.h Orgraph.h
	g++ -c AStar.cpp
	
Option.o: Option.cpp Option.h Orgraph.h AStar.h

 clean:
	rm -rf *.o programm
