# This MAKEFILE was adapted from mps and the project template provided at https://github-dev.cs.illinois.edu/cs225-sp21/rittika2-xz33-gcevans-atharva2
# This version of the MAKEFILE allows the use of gdb
# Executable Name
EXENAME = finalproj

# Object Types
OBJS = readFromFile.o main.o graph.o dfs.o dijkstra.o

# Compilation Flags
CXX = clang++
CXXFLAGS = $(CS225) -std=c++14 -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++14 -stdlib=libc++ -lc++abi -lm -g
CUSTOM = $(CS225) -std=c++14 -stdlib=libc++ -g -O0 -Wall -Wextra -pedantic
# Custom Clang version enforcement logic:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu") 
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
ifneq ($(strip $(SKIP_EWS_CHECK)),True)
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif
endif


# Define Makefile Rules
.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

graph: graph.cpp
	$(CXX) $(CXXFLAGS) graph.cpp

readFromFile: readFromFile.cpp
	$(CXX) $(CXXFLAGS) readFromFile.cpp

testbench: testbench.cpp
	$(CXX) $(CXXFLAGS) testbench.cpp

dijkstra: dijkstra.cpp
	$(CXX) $(CXXFLAGS) dijkstra.cpp

test: output_msg catch/catchmain.cpp tests/tests.cpp readFromFile.cpp graph.cpp dfs.cpp dijkstra.cpp debug.cpp tarjan.cpp
	$(LD) catch/catchmain.cpp tests/tests.cpp readFromFile.cpp testbench.cpp graph.cpp dfs.cpp dijkstra.cpp debug.cpp tarjan.cpp $(LDFLAGS) -o test

clean:
	-rm -f *.o $(EXENAME) test