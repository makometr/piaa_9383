$(shell mkdir -p Build/buildAStar)
$(shell mkdir -p Build/buildGreedy)

all:astar greedy

astar: Build/buildAStar/main.o Build/buildAStar/astar.o
	g++ Build/buildAStar/main.o Build/buildAStar/astar.o -o lab2_astar -std=c++17

Build/buildAStar/main.o: Source/A-star/main.cpp
	g++ -c Source/A-star/main.cpp -std=c++17 -o Build/buildAStar/main.o

Build/buildAStar/astar.o: Source/A-star/astar.cpp
	g++ -c Source/A-star/astar.cpp -std=c++17 -o Build/buildAStar/astar.o

greedy: Build/buildGreedy/main.o Build/buildGreedy/greedy.o
	g++ Build/buildGreedy/main.o Build/buildGreedy/greedy.o -o lab2_greedy -std=c++17

Build/buildGreedy/main.o: Source/Greedy/main.cpp
	g++ -c Source/Greedy/main.cpp -std=c++17 -o Build/buildGreedy/main.o

Build/buildGreedy/greedy.o: Source/Greedy/greedy.cpp
	g++ -c Source/Greedy/greedy.cpp -std=c++17 -o Build/buildGreedy/greedy.o

clean:
	rm -rf Build/