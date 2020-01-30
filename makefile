#allows passing of additional defines in cmd with D=-D<define>
#DEFINES=$D

#icc compiler (on cora)
CXX=icc

#CXX=g++-7.2.0

#correct g++ compiler for cora
#CXX=/opt/global/gcc-7.2.0/bin/g++

#CXX=g++

#compiler flags
CXXFLAGS=-O3 -fopenmp -std=c++11 -mcmodel=large
#libs
LDLIBS=-pthread -fopenmp
#include paths
#CXXINCLUDE=
#executable names
EXECUTABLES=stencil

.PONY: all clean run

#default rule, compile all programs
all: $(EXECUTABLES)


#link executable from executble.o
$(EXECUTABLES): %: %.o
	$(CXX) -o $@ $^ $(LDLIBS) 

#rule to compile .cpp to .o
%.o: %.cpp
	$(CXX) $(DEFINES)  $(CXXFLAGS) -c -o $@ $< $(CXXINCLUDE)

#rule to compile .cc to .o
%.o: %.cc
	$(CXX) $(DEFINES) $(CXXFLAGS) -c -o $@ $< $(CXXINCLUDE)


#rule run Program, variable can be changed when needed
run: $(EXECUTABLES)
	./stencil 25 48 3000 2000 25673 41983

#cleanup rule
clean:
	rm -rf *.o $(EXECUTABLES)
