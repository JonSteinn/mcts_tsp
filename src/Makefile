CXX = g++
CXX_FLAGS = -g -Wall -Wextra  -Werror -std=c++17

main: main.o tsp.o tree.o mcts.o
	$(CXX) $(CXX_FLAGS) -o main.exe main.o tsp.o tree.o mcts.o

main.o: main.cpp
	$(CXX) $(CXX_FLAGS) -c main.cpp

tsp.o: tsp.h
tree.o: tree.h
mcts.o: mcts.o

clean:
	rm -f *.o

distclean: clean
	rm -f main.exe