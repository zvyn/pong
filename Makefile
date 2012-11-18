CXX = g++ -g  -Wall
HAEDER = $(wildcard *.h)
OBJECTS = $(addsuffix .o, $(basename $(filter-out %Main.cpp %Test.cpp,$(wildcard *.cpp))))
MAIN_BINARIES = $(basename $(wildcard *Main.cpp))
TEST_BINARIES = $(basename $(wildcard *Test.cpp))

all: verbose lint build test

static: CXX += -static
static: build

build: $(MAIN_BINARIES) $(TEST_BINARIES)

test: $(TEST_BINARIES) 
	for T in $(TEST_BINARIES); do ./$$T; done

lint:
	python2 ../cpplint.py *.cpp *.h
clean:
	rm -f *.o
	rm -f *Main
	rm -f *Test
	
%Main: %Main.o $(OBJECTS)
	$(CXX) -o $@ $^ -lcurses

%Test: %Test.o $(OBJECTS)
	$(CXX) -o $@ $^ -lgtest -lgtest_main -lpthread

%Test.o: %Test.cpp $(HAEDER)
	$(CXX) -c $< -lgtest -lgtest_main -lpthread

%Main.o: %Main.cpp $(HAEDER)
	$(CXX) -c $<
verbose: 
	# CXX=$(CXX)
	# HAEDER=$(HAEDER)
	# OBJECTS=$(OBJECTS)
	# MAIN_BINARIES=$(MAIN_BINARIES)
	# TEST_BINARIES=$(TEST_BINARIES)

	
