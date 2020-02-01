CPPFLAGS=-g -Wall
LDLIBS=-lncursesw

main: main.cpp grid.o
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

clean:
	rm *.o main
