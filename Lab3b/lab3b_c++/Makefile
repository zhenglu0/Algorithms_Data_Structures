#
# Makefile for Lab 3, part (b)
# NB: you will have to add in the dependencies on your code
# from 3(a) to build a working program.

##############################################################
# Compiler and flags to use
##############################################################

CXX       = g++
CXXFLAGS  = -g -Wall -Werror -pedantic 

LAB3B_EXE  = Lab3b

# Add any additional object files to this list
LAB3B_OBJS = ShortestPaths.o Input.o Lab3b.o PrettyTime.o \
	Query.o QueryReader.o Tokenizer.o

##############################################################
# You shouldn't have to change anything below this line.
# However, you will be happier if you update the dependencies
# at the bottom of the file to include your Lab3a files.
##############################################################

###

$(LAB3B_EXE): $(LAB3B_OBJS)
	$(CXX) -o $(LAB3B_EXE) $(LAB3B_OBJS)

clean:
	rm -f $(LAB3B_EXE) $(LAB3B_OBJS)

###

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

###

Input.o: Input.cc Input.h
Lab3b.o: Lab3b.cc QueryReader.h Query.h Multigraph.h Vertex.h \
	Edge.h ShortestPaths.h Input.h PrettyTime.h
PrettyTime.o: PrettyTime.cc PrettyTime.h
Query.o: Query.cc Query.h PrettyTime.h
QueryReader.o: QueryReader.cc QueryReader.h Query.h Tokenizer.h \
  PrettyTime.h
ShortestPaths.o: ShortestPaths.cc ShortestPaths.h Input.h \
	Multigraph.h Vertex.h Edge.h PQNode.h Handle.h PriorityQueue.h
Tokenizer.o: Tokenizer.cc Tokenizer.h
