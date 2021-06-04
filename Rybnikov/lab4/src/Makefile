all:: lab4

lab4: main.o KMP.o
	g++ main.o KMP.o -o lab4
	
main.o: main.cpp KMP.hpp
	g++ -c main.cpp
	
KMP.o: KMP.cpp KMP.hpp
	g++ -c KMP.cpp
	
clean:
	rm -rf *.o lab4
