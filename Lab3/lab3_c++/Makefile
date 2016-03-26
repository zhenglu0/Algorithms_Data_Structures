#
# Makefile for lab3
#

##############################################################
# Compiler and flags to use
##############################################################

CXX       = g++
CXXFLAGS  = -g -O2 -Wall -Werror -pedantic 

##############################################################
# You shouldn't have to change anything below this line.
##############################################################

LAB3_EXE  = Lab3
LAB3_OBJS = Lab3.o Event.o EventReader.o EventList.o \
			Query.o QueryReader.o Tokenizer.o

###

$(LAB3_EXE): $(LAB3_OBJS)
	$(CXX) -o $(LAB3_EXE) $(LAB3_OBJS)

clean:
	rm -f $(LAB3_EXE) $(LAB3_OBJS)

###

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

###

Event.o: Event.cc Event.h Tokenizer.h
EventList.o: EventList.cc EventList.h Event.h Item.h
EventReader.o: EventReader.cc EventReader.h Event.h Tokenizer.h
Lab3.o: Lab3.cc EventList.h Event.h EventReader.h \
		Query.h QueryReader.h
Query.o: Query.cc Query.h
QueryReader.o: QueryReader.cc QueryReader.h Query.h Tokenizer.h
Tokenizer.o: Tokenizer.cc Tokenizer.h
