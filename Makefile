INCS = MSDscript/MSDscript/cmdline.hpp MSDscript/MSDscript/expr.hpp

OBJS = MSDscript/MSDscript/main.o MSDscript/MSDscript/cmdline.o MSDscript/MSDscript/expr.o

CXX = c++

CXXFLAGS = --std=c++14 -O2

MSDscript: $(OBJS)
	$(CXX) $(CXXFLAGS) -o MSDscript/MSDscript/MSDscript $(OBJS)

.PHONY: test
test: MSDscript
	./MSDscript/MSDscript/MSDscript --test

main.o: MSDscript/MSDscript/main.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c main.cpp

cmdline.o: MSDscript/MSDscript/cmdline.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c cmdline.cpp

expr.o: MSDscript/MSDscript/expr.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c expr.cpp
