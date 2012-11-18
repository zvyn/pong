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

%Main.o: %Main.cpp $(HAEDER)
	$(CXX) -c $<

verbose: 
	# CXX=$(CXX)
	# HAEDER=$(HAEDER)
	# OBJECTS=$(OBJECTS)
	# MAIN_BINARIES=$(MAIN_BINARIES)

	
