CXX = g++
CXX_FLAGS = -Wall -Wextra -std=c++17
 
main: main.o x.o
	$(CXX) $(CXX_FLAGS) -o main.exe main.o x.o

main.o: main.cpp
	$(CXX) $(CXX_FLAGS) -c main.cpp

x.o: x.h

clean:
	rm -f *.o

distclean: clean
	rm -f main.exe