make : 
	
	g++ -c src/include/*.cpp
	g++ -o game game.cpp *.o -l -lncurses

