Game: Main.o Logic.o
	g++ Main.o Logic.o -o Game

Main.o: Main.cpp
	g++ -c -std=c++11 Main.cpp

Logic.o: Logic.cpp Logic.h
	g++ -c -std=c++11 Logic.cpp

clean:
	rm *.o Game
