CC = g++
PROFILE_FLAGS = -O2
FLAGS = -std=c++17 $(PROFILE_FLAGS)

VPATH = ./ ./Source/ ./Headers/ ./Tests

INCLUDE = -I./Headers/

OBJ_FILES := $(foreach dir,$(VPATH), $(patsubst $(dir)%.cpp, %.o,$(wildcard $(dir)*.cpp)))

lab1: lab4_1 Makefile
	./prog1

lab2: lab4_2 Makefile
	./prog2

lab4_1: lab4_1.o API.o
	$(CC) $(FLAGS) lab4_1.o API.o -o prog1

lab4_1.o: lab4_1.cpp
	$(CC) $(FLAGS) -c $(INCLUDE) $<

lab4_2: lab4_2.o API.o
	$(CC) $(FLAGS) lab4_2.o API.o -o prog2

lab4_2.o: lab4_2.cpp
	$(CC) $(FLAGS) -c $(INCLUDE) $<

test: test_comp Makefile
	./test

test_comp: test.o API.o
	$(CC) $(FLAGS) test.o API.o -o test

test.o: test.cpp
	$(CC) $(FLAGS) -c $(INCLUDE) $<

API.o: API.cpp API.h
	$(CC) $(FLAGS) -c $(INCLUDE) $<

clean:
	rm -rf *.o