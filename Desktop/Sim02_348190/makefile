all: sim02

sim02: main.o Utils.o SimpleTimer.o
	g++ main.o Utils.o SimpleTimer.o -lpthread -o sim02

main.o: main.cpp Struct.h
	g++ -std=c++11 -c main.cpp

Utils.o: Utils.cpp Utils.h Struct.h
	g++ -std=c++11 -c Utils.cpp

SimpleTimer.o: SimpleTimer.cpp SimpleTimer.h
	g++ -std=c++11 -c SimpleTimer.cpp

clean:
	rm -rf *o sim01

