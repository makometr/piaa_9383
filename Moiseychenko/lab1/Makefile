all: main1.o field.o
	g++ main1.o field.o -o lab1

main1.o: source/main1.cpp
	g++ -c source/main1.cpp

field.o: source/field.cpp source/field.h
	g++ -c source/field.cpp

clean:
	@rm -rf *.o
