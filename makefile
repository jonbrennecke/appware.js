cxx = g++
cxxflags = -std=c++11 -Wall -pedantic
objcflags = -lobjc -framework Cocoa
objcsrc = ./src/view.mm
cxxsrc = ./src/test.cpp

all:
	$(cxx) $(cxxflags) $(objcflags) $(objcsrc) $(cxxsrc)