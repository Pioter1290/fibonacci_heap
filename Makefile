CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS =

SOURCES = Main.cpp
HEADERS = Kopiec.hpp
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))
TARGETS = $(patsubst %.o,%.x,$(OBJECTS))

.PHONY: all clean

all: $(TARGETS)

%.x: %.o
	$(CXX) $(LDFLAGS) -o $@ $<

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJECTS) $(TARGETS)

