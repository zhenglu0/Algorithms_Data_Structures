#
# Makefile for Lab 3, part (a)
#

##############################################################
# Compiler and flags to use
##############################################################

CXX       = g++
CXXFLAGS  = -g -Wall -pedantic -Werror

##############################################################
# You shouldn't have to change anything below this line.
##############################################################

LAB3A_EXE  = Lab3a
LAB3A_OBJS = Lab3a.o

###

$(LAB3A_EXE): $(LAB3A_OBJS)
	$(CXX) -o $(LAB3A_EXE) $(LAB3A_OBJS)

clean:
	rm -f $(LAB3A_EXE) $(LAB3A_OBJS)

###

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

###

Lab3a.o: Lab3a.cc PriorityQueue.h Handle.h PQNode.h
