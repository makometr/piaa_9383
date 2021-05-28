$(shell mkdir -p Build/buildTask1)
$(shell mkdir -p Build/buildTask2)

all:task1 task2

task1: Build/buildTask1/main.o Build/buildTask1/task1.o
	g++ Build/buildTask1/main.o Build/buildTask1/task1.o -o lab4_task1 -std=c++17

Build/buildTask1/main.o: Source/task1/main.cpp
	g++ -c Source/task1/main.cpp -std=c++17 -o Build/buildTask1/main.o

Build/buildTask1/task1.o: Source/task1/task1.cpp
	g++ -c Source/task1/task1.cpp -std=c++17 -o Build/buildTask1/task1.o

task2: Build/buildTask2/main.o Build/buildTask2/task2.o
	g++ Build/buildTask2/main.o Build/buildTask2/task2.o -o lab4_task2 -std=c++17

Build/buildTask2/main.o: Source/task2/main.cpp
	g++ -c Source/task2/main.cpp -std=c++17 -o Build/buildTask2/main.o

Build/buildTask2/task2.o: Source/task2/task2.cpp
	g++ -c Source/task2/task2.cpp -std=c++17 -o Build/buildTask2/task2.o

clean:
	rm -rf Build/