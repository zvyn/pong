CXX = g++ -g  -Wall
HAEDER = $(wildcard *.h)
OBJECTS = $(addsuffix .o, $(basename $(filter-out %Main.cpp %Test.cpp,$(wildcard *.cpp))))
MAIN_BINARIES = $(basename $(wildcard *Main.cpp))

all: build

static: CXX += -static
static: build

build: $(MAIN_BINARIES)

clean:
	rm -f *.o
	rm -f *Main
	rm -f *Test
	
%Main: %Main.o $(OBJECTS)
	$(CXX) -o $@ $^ -lcurses
	mv PongMain pong

%Main.o: %Main.cpp $(HAEDER)
	$(CXX) -c $<
