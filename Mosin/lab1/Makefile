CC = g++
PROFILE_FLAGS = -O2
FLAGS = -std=c++17 $(PROFILE_FLAGS)

VPATH = ./ ./Source/ ./Headers/ ./Tests

INCLUDE = -I./Headers/

OBJ_FILES := $(foreach dir,$(VPATH), $(patsubst $(dir)%.cpp, %.o,$(wildcard $(dir)*.cpp)))

all: main Makefile
	./prog

main: main.o API.o
	$(CC) $(FLAGS) main.o API.o -o prog

test: create_test Makefile
	./test

create_test: test.o API.o
	$(CC) $(FLAGS) test.o API.o -o test

main.o: main.cpp API.h
	$(CC) $(FLAGS) -c $(INCLUDE) $<

API.o: API.cpp API.h
	$(CC) $(FLAGS) -c $(INCLUDE) $<

test.o: test.cpp API.h
	$(CC) $(FLAGS) -c $(INCLUDE) $<

clean:
	rm -rf *.o