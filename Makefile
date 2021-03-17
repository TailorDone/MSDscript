INCS = MSDscript/MSDscript/cmdline.hpp MSDscript/MSDscript/expr.hpp MSDscript/MSDscript/parse.hpp MSDscript/MSDscript/val.hpp MSDscript/MSDscript/pointer.h

INCS2 = MSDscriptTest/MSDscriptTest/exec.hpp

OBJS = MSDscript/MSDscript/main.o MSDscript/MSDscript/cmdline.o MSDscript/MSDscript/expr.o MSDscript/MSDscript/parse.o MSDscript/MSDscript/val.o

OBJS2 = MSDscriptTest/MSDscriptTest/main.o MSDscriptTest/MSDscriptTest/exec.o

CXX = c++

CXXFLAGS = --std=c++14 -O2 -Wall

MSDscript: $(OBJS)
	$(CXX) $(CXXFLAGS) -o MSDscript/MSDscript/MSDscript $(OBJS)

MSDscriptTest: $(OBJS2)
	$(CXX) $(CXXFLAGS) -o MSDscriptTest/MSDscriptTest/MSDscriptTest $(OBJS2)

.PHONY: test
test: MSDscript
	./MSDscript/MSDscript/MSDscript --test

main.o: MSDscript/MSDscript/main.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c main.cpp

main.o: MSDscriptTest/MSDscriptTest/main.cpp $(INCS2)
	$(CXX) $(CXXFLAGS) -c main.cpp

cmdline.o: MSDscript/MSDscript/cmdline.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c cmdline.cpp

expr.o: MSDscript/MSDscript/expr.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c expr.cpp

parse.o: MSDscript/MSDscript/parse.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c parse.cpp

val.o: MSDscript/MSDscript/val.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c val.cpp

exec.o: MSDscriptTest/MSDscriptTest/exec.cpp $(INCS2)
	$(CXX) $(CXXFLAGS) -c exec.cpp

