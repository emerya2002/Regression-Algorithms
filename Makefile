# TODO

all:main

main: LinearRegression.o LogisticRegression.o Parser.o Util.o main.o
	g++ -std=c++11 -Wall LinearRegression.o LogisticRegression.o Parser.o Util.o main.o -o main

LinearRegression.o: LinearRegression.cpp
	g++ -std=c++11 -Wall -c LinearRegression.cpp

LogisticRegression.o: LogisticRegression.cpp
	g++ -std=c++11 -Wall -c LogisticRegression.cpp

Parser.o: Parser.cpp
	g++ -std=c++11 -Wall -c Parser.cpp

Util.o: Util.cpp
	g++ -std=c++11 -Wall -c Util.cpp

main.o: main.cpp
	g++ -std=c++11 -Wall -c main.cpp

clean: 
	rm -f *.o *.h.gch main
