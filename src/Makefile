CXX = g++
CXX_FLAGS = -g -Wall -Wextra -Werror -std=c++17
OBJFLAGS = -c

TARGET = main
MCTS = mcts
SHORTEST_NEXT = shortest_next
TSP = tsp

INCLUDED = \
	$(MCTS).o \
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
$(SHORTEST_NEXT).o: $(SHORTEST_NEXT).cpp
	$(CXX) $(CXX_FLAGS) $(OBJFLAGS) $(SHORTEST_NEXT).cpp
$(TSP).o: $(TSP).cpp
	$(CXX) $(CXX_FLAGS) $(OBJFLAGS) $(TSP).cpp

define MAKE_DOT_O
$(1).o: $(1).cpp
	$(CXX) $(CXX_FLAGS) $(OBJFLAGS) $($(1)).cpp
endef

#$(call MAKE_DOT_O,MCTS)
#$(call MAKE_DOT_O,SHORTEST_NEXT)
#$(call MAKE_DOT_O,TSP)

clean:
	rm -f *.o

distclean: clean
	rm -f main.exe
