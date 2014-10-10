cxx = g++
cxxflags = -std=c++11
objcflags = -lobjc -framework Cocoa
src = ./src/test.cpp

all:
	$(cxx) $(cxxflags) $(objcflags) $(src)