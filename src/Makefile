ifeq ($(DEBUG), 1)
	MODE = -g -O0 -DDEBUG
else
	MODE = -O3 -DNDEBUG
endif

CXX = g++
CXX_FLAGS = \
	-std=c++17 \
	$(MODE) \
	-Wall \
	-Wextra \
	-Wfatal-errors \
	-Wformat=2 \
	-Werror
OBJFLAGS = -c

TARGET = main
MCTS = mcts
MCTS2 = mcts2
MCTS3 = mcts3
SHORTEST_NEXT = shortest_next
TSP = tsp
UTILS = utils

INCLUDED = \
	$(MCTS).o \
	$(MCTS2).o \
	$(MCTS3).o \
	$(SHORTEST_NEXT).o \
	$(TSP).o \
	$(UTILS).o

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

$(MCTS3).o: $(MCTS3).cpp
	$(CXX) $(CXX_FLAGS) $(OBJFLAGS) $(MCTS3).cpp

$(SHORTEST_NEXT).o: $(SHORTEST_NEXT).cpp
	$(CXX) $(CXX_FLAGS) $(OBJFLAGS) $(SHORTEST_NEXT).cpp

$(TSP).o: $(TSP).cpp
	$(CXX) $(CXX_FLAGS) $(OBJFLAGS) $(TSP).cpp

$(UTILS).o: $(UTILS).cpp
	$(CXX) $(CXX_FLAGS) $(OBJFLAGS) $(UTILS).cpp

clean:
	rm -f *.o

distclean: clean
	rm -f main.exe
