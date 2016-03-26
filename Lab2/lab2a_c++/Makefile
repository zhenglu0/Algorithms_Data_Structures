#
# Makefile for lab2
#

##############################################################
# Compiler and flags to use
##############################################################

CXX       = g++
CXXFLAGS  = -g -O -Wall -Werror -pedantic 

##############################################################
# You shouldn't have to change anything below this line.
##############################################################

LAB2_EXE  = Lab2
LAB2_OBJS = Lab2.o SeqReader.o StringTable.o

###

$(LAB2_EXE): $(LAB2_OBJS)
	$(CXX) -o $(LAB2_EXE) $(LAB2_OBJS)

clean:
	rm -f $(LAB2_EXE) $(LAB2_OBJS)

###

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

###

Lab2.o: Lab2.cc SeqReader.h StringTable.h Record.h
SeqReader.o: SeqReader.cc SeqReader.h
StringTable.o: StringTable.cc StringTable.h Record.h
