CC = g++
PROFILE_FLAGS = -O2
FLAGS = -std=c++17 $(PROFILE_FLAGS)

VPATH = ./ ./Source/ ./Headers/

INCLUDE = -I./Headers/

OBJ_FILES := $(foreach dir,$(VPATH), $(patsubst $(dir)%.cpp, %.o,$(wildcard $(dir)*.cpp)))

lab5_1: lab5_1_comp Makefile
	./prog1

lab5_2: lab5_2_comp Makefile
	./prog2

lab5_1_comp: main1.o lab5_1.o
	$(CC) $(FLAGS) main1.o lab5_1.o -o prog1

lab5_2_comp: main2.o lab5_2.o
	$(CC) $(FLAGS) main2.o lab5_2.o -o prog2

lab5_1.o: lab5_1.cpp lab5_1.h
	$(CC) $(FLAGS) -c $(INCLUDE) $<

lab5_2.o: lab5_2.cpp lab5_1.h
	$(CC) $(FLAGS) -c $(INCLUDE) $<

main1.o: main1.cpp
	$(CC) $(FLAGS) -c $(INCLUDE) $<

main2.o: main2.cpp
	$(CC) $(FLAGS) -c $(INCLUDE) $<

clean:
	rm -rf *.o