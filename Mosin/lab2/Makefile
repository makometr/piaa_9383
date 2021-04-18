CC = g++
PROFILE_FLAGS = -O2
FLAGS = -std=c++17 $(PROFILE_FLAGS)

VPATH = ./ ./Source/ ./Headers/ ./Tests

INCLUDE = -I./Headers/

OBJ_FILES := $(foreach dir,$(VPATH), $(patsubst $(dir)%.cpp, %.o,$(wildcard $(dir)*.cpp)))

greed: main Makefile
	./prog Greed

star: main Makefile
	./prog Star

main: main.o API.o
	$(CC) $(FLAGS) main.o API.o -o prog

main.o: main.cpp API.o
	$(CC) $(FLAGS) -c $(INCLUDE) $<

test: test_comp Makefile
	./test

test_comp: test.o API.o
	$(CC) $(FLAGS) test.o API.o -o test

test.o: test.cpp API.o
	$(CC) $(FLAGS) -c $(INCLUDE) $<

API.o: API.cpp API.h
	$(CC) $(FLAGS) -c $(INCLUDE) $<

clean:
	rm -rf *.o