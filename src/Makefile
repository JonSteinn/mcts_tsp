CXX = g++
CXX_FLAGS = -g -Wall -Wextra -Werror -std=c++17
OBJFLAGS = -c

TARGET = main
MCTS = mcts
MCTS2 = mcts2
SHORTEST_NEXT = shortest_next
TSP = tsp

INCLUDED = \
	$(MCTS).o \
	$(MCTS2).o \
	$(SHORTEST_NEXT).o \
	$(TSP).o

.DEFAULT: all
.PHONY: all
all: $(TARGET)

$(TARGET): $(TARGET).o $(INCLUDED)
	$(CXX) $(CXX_FLAGS) -o $(TARGET).exe $(TARGET).o $(INCLUDED)

$(TARGET).o: $(TARGET).cpp
	$(CXX) $(CXX_FLAGS) $(OBJFLAGS) $(TARGET).cpp

$(MCTS).o: $(MCTS).cpp
	$(CXX) $(CXX_FLAGS) $(OBJFLAGS) $(MCTS).cpp

$(MCTS2).o: $(MCTS2).cpp
	$(CXX) $(CXX_FLAGS) $(OBJFLAGS) $(MCTS2).cpp

$(SHORTEST_NEXT).o: $(SHORTEST_NEXT).cpp
	$(CXX) $(CXX_FLAGS) $(OBJFLAGS) $(SHORTEST_NEXT).cpp

$(TSP).o: $(TSP).cpp
	$(CXX) $(CXX_FLAGS) $(OBJFLAGS) $(TSP).cpp

clean:
	rm -f *.o

distclean: clean
	rm -f main.exe
