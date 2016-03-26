#
# Makefile for lab1
#

##############################################################
# Compiler and flags to use
##############################################################

CXX       = g++
CXXFLAGS  = -g -O2 -Wall -Werror

##############################################################
# You shouldn't have to change anything below this line.
##############################################################

LAB1_EXE  = lab1
LAB1_OBJS = lab1.o point.o timer.o closest-pair-dc.o closest-pair-naive.o

###

$(LAB1_EXE): $(LAB1_OBJS)
	$(CXX) -o $(LAB1_EXE) $(LAB1_OBJS) -lm

clean:
	rm -f $(LAB1_EXE) $(LAB1_OBJS)

###

.cc.o:
	$(CXX) $(CXXFLAGS) -c $<

###

closest-pair-dc.o: point.h
closest-pair-naive.o: closest-pair-naive.cc closest-pair-naive.h point.h
lab1.o: lab1.cc closest-pair-dc.h closest-pair-naive.h point.h prng.h
point.o: point.cc point.h
timer.o: timer.cc timer.h
prng.o: prng.cc prng.h
