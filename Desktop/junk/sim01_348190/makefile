all: sim01

sim01: main.o Utils.o SimpleTimer.o
	g++ main.o Utils.o SimpleTimer.o -lpthread -o sim01

main.o: main.cpp Struct.h
	g++ -std=c++11 -c main.cpp

Utils.o: Utils.cpp Utils.h Struct.h
	g++ -std=c++11 -c Utils.cpp

SimpleTimer.o: SimpleTimer.cpp SimpleTimer.h
	g++ -std=c++11 -c SimpleTimer.cpp

clean:
	rm -rf *o sim01


#sim01: main.o Utils.o SimpleTimer.o
#	g++ -Wall -o sim01 Utils.o SimpleTimer.o

#main.o: main.cpp Utils.cpp Utils.h Struct.h
#	g++ -Wall -c main.cpp Utils.cpp

#Utils.o: Utils.cpp Utils.h SimpleTimer.cpp SimpleTimer.h Struct.h
#	g++ -Wall -c Utils.cpp

#SimpleTimer.o: SimpleTimer.cpp SimpleTimer.h
#	g++ -Wall -c SimpleTimer.cpp



#sim01: main.o SimpleTimer.o Struct.o Utils.o
#	g++ -std=c++11 -Wall -o main.o SimpleTimer.o Utils.o

#main.o: main.cpp Utils.cpp Utils.h SimpleTimer.cpp SimpleTimer.h Struct.h
#	g++ -std=c++11 -Wall -c main.cpp Utils.cpp SimpleTimer.cpp

#Utils.o: Utils.cpp Utils.h SimpleTimer.cpp SimpleTimer.h
#	g++ -std=c++11 -Wall -c Utils.cpp SimpleTimer.cpp

#SimpleTimer.o: SimpleTimer.cpp SimpleTimer.h
#	g++ -std=c++11 -Wall -c SimpleTimer.cpp



