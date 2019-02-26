
CXX := g++
CXXFLAGS := -O3 -Wall -Wshadow -std=c++11
INC = -I./lib/ -I/usr/local/boost/ -I../src/
LDFLAGS := -L/usr/local/lib/ 

PRG_SUFFIX_FLAG := 0

LDIR := ./lib
LODIR = ../bin/test/lib
ODIR := ../bin/test/obj
EDIR := ../bin/test/exe

LSRC := $(wildcard $(LDIR)/*.cpp)
LOBJ := $(patsubst %.cpp, $(LODIR)/%.o, $(notdir $(LSRC)))
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp, $(ODIR)/%.o, $(SRC))
SOBJ := ../bin/obj/*.o
PRG := $(EDIR)/test_polymer_mc #$(patsubst %.cpp,$(EDIR)/%,$(SRC))
PRG_SUFFIX=
BIN := $(patsubst %,%$(PRG_SUFFIX),$(PRG))


all : $(LOBJ) $(OBJ) $(BIN)

% : %.cpp
	make $(EDIR)/$@

$(ODIR)/%.o : %.cpp 
	mkdir -p $(ODIR)
#	rm ../bin/obj/run_polymer_mc.o
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

$(EDIR)/% : $(ODIR)/%.o $(LOBJ) $(OBJ)
	mkdir -p $(EDIR)
	$(CXX) $(LDFLAGS) $^ $(SOBJ) -o $@

$(LODIR)/%.o : $(LDIR)/%.cpp
	mkdir -p $(LODIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY : clean
clean : 
	rm -rf $(EDIR) $(ODIR) $(LODIR)
