# ! Makefile should be ran from top level folder (regression/)
FLAGS= -std=c++11 -Wall -Iinclude -c

all:main

main: LinearRegression.o LogisticRegression.o Parser.o Util.o main.o
	g++ -std=c++11 -Wall LinearRegression.o LogisticRegression.o Parser.o Util.o main.o -o main

main.o: src/main.cpp include/LinearRegression.h include/LogisticRegression.h include/Parser.h include/Util.h
	g++ $(FLAGS) src/main.cpp

LinearRegression.o: src/LinearRegression.cpp include/LinearRegression.h
	g++ $(FLAGS) src/LinearRegression.cpp

LogisticRegression.o: src/LogisticRegression.cpp include/LogisticRegression.h
	g++ $(FLAGS) src/LogisticRegression.cpp

Parser.o: src/Parser.cpp include/Parser.h
	g++ $(FLAGS) src/Parser.cpp

Util.o: src/Util.cpp include/Util.h
	g++ $(FLAGS) src/Util.cpp

clean: 
	rm -f *.o *.h.gch main
