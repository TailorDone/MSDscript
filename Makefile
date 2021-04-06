INCS = MSDscript/MSDscript/cmdline.hpp MSDscript/MSDscript/expr.hpp MSDscript/MSDscript/parse.hpp MSDscript/MSDscript/val.hpp MSDscript/MSDscript/pointer.h MSDscript/MSDscript/env.hpp MSDscript/MSDscript/step.hpp MSDscript/MSDscript/cont.hpp

INCS2 = MSDscriptTest/MSDscriptTest/exec.hpp

OBJS = MSDscript/MSDscript/main.o MSDscript/MSDscript/cmdline.o MSDscript/MSDscript/expr.o MSDscript/MSDscript/parse.o MSDscript/MSDscript/val.o MSDscript/MSDscript/env.o MSDscript/MSDscript/step.o MSDscript/MSDscript/cont.o

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

exec.o: MSDscriptTest/MSDscriptTest/exec.cpp $(INCS2)
	$(CXX) $(CXXFLAGS) -c exec.cpp

cmdline.o: MSDscript/MSDscript/cmdline.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c cmdline.cpp

expr.o: MSDscript/MSDscript/expr.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c expr.cpp

parse.o: MSDscript/MSDscript/parse.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c parse.cpp

val.o: MSDscript/MSDscript/val.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c val.cpp

env.o: MSDscript/MSDscript/env.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c env.cpp

step.o: MSDscript/MSDscript/step.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c step.cpp

cont.o: MSDscript/MSDscript/cont.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c cont.cpp