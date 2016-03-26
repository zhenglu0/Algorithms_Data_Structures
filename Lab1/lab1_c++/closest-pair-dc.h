// Author : Zheng Luo
// Email : luozheng@wustl.edu
//
// CLOSEST-PAIR-DC.H
// Interface to student-supplied divide-and-conquer
// closest pair function
//

#ifndef __CLOSEST_PAIR_DC_H
#define __CLOSEST_PAIR_DC_H

#include "point.h"

void findClosestPair(Point *pointsByX[], Point *pointsByY[],
		     int nPoints);

double findClosestPairDC(Point *pointsByX[], Point *pointsByY[],
                       int nPoints, Point *p[]);

double minLR(double d1, double d2, Point *p1[],Point *p2[],Point *p[]);// minimal distance in left and right

double minLRS(double dLR, double dS, Point *p3[],Point *p[]); // minimal distance in left and right and strip

double pairDistanceInStrip(Point *pointsByY[], int nPoints, int xmid, double dLR, Point *p[]);

void sortResultDC(Point *p[]); // sort the result

#endif
