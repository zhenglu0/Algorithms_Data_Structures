// Author : Zheng Luo
// Email : luozheng@wustl.edu
//
// CLOSEST-PAIR-NAIVE.CC
// Naive implementation of the closest-pair algorithm

#include <iostream>
#include <limits>

#include "closest-pair-naive.h"

using namespace std;

// bigger than any possible interpoint distance
const double INFTY = numeric_limits<double>::max(); 

//
// findClosestPair()
//
// Given a collection of nPoints points, find and ***print***
//  * the closest pair of points
//  * the distance between them
// in the form "(x1, y1) (x2, y2) distance"
//

// INPUTS:
//  - points (not necessarily sorted)
//  - # of input points
//

void findClosestPairNaive(Point *points[], int nPoints)
{
    // to store points of final result
    Point *p[2];
    p[0] = points[0];
    p[1] = points[1];
    // declare the minimal distance
    double distanceMin = points[0]->distance(points[1]);
    // check if there is only 2 points, directly return the distance
    if (nPoints == 2)
    {
        // sort the result 
        sortResultNA(p);
        cout << p[0] << " " << p[1] << " " << " " << distanceMin << endl;
    }
    // if there are more than two points
    else
    {
        for (int i = 0; i < nPoints; i++)
            for (int j = i+1; j < nPoints; j++)
            {
                // calculate the distance
                double d = points[i]->distance(points[j]);
                // if we find the distance is smaller
                if (d < distanceMin)
                {
                    distanceMin = d;
                    p[0] = points[i];
                    p[1] = points[j];
                }
            }
        // sort the result 
        sortResultNA(p);
        cout << p[0] << " " << p[1] << " " << " " << distanceMin << endl;
    }
}

// sort the result in order to print the point with lowest 
// X-coordinate first;
// if the two points have equal X-coordinates, print the point with 
// lowest Y-coordinate first.
void sortResultNA(Point *p[])
{
    Point *temp = p[1];
    if (p[0]->x() > p[1]->x())
    {
        p[1] = p[0];
        p[0] = temp;
    }
    else if(p[0]->x() == p[1]->x() && p[0]->y() > p[1]->y())
    {
        p[1] = p[0];
        p[0] = temp;
    }
}
