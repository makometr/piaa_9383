$(shell mkdir -p build)

prog: build/main.o build/backTracking.o
	g++ build/main.o build/backTracking.o -o lab1 -std=c++17

tests: build/tests-main.o build/backTracking.o build/tests.o
	g++ build/tests-main.o build/backTracking.o build/tests.o -std=c++17 -o run_tests

build/main.o: Source/main.cpp
	g++ -c Source/main.cpp -std=c++17 -o build/main.o

build/backTracking.o: Source/backTracking.cpp
	g++ -c Source/backTracking.cpp -std=c++17 -o build/backTracking.o

build/tests-main.o: Tests/tests-main.cpp
	g++ -c Tests/tests-main.cpp -std=c++17 -o build/tests-main.o

build/tests.o: Tests/tests.cpp
	g++ -c Tests/tests.cpp -std=c++17 -o build/tests.o


clean:
	rm -rf build/