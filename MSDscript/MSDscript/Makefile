INCS = cmdline.hpp expr.hpp

OBJS = main.o cmdline.o expr.o

CXX = c++

CXXFLAGS = --std=c++14 -O2

MSDscript: $(OBJS)
	$(CXX) $(CXXFLAGS) -o MSDscript $(OBJS)

main.o: main.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c main.cpp

cmdline.o: cmdline.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c cmdline.cpp

expr.o: expr.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c expr.cpp
