CXX = g++
CXX_FLAGS = -g -Wall -Wextra  -Werror -std=c++17

main: main.o mcts.o shortest_next.o tsp.o
	$(CXX) $(CXX_FLAGS) -o main.exe main.o mcts.o shortest_next.o tsp.o

main.o: main.cpp
	$(CXX) $(CXX_FLAGS) -c main.cpp

mcts.o: mcts.h

shortest_next.o: shortest_next.h

tsp.o: tsp.h

clean:
	rm -f *.o

distclean: clean
	rm -f main.exe
