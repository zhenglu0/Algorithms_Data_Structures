// Author : Zheng Luo
// Email : luozheng@wustl.edu
//
// CLOSEST-PAIR-DC.CC 
// Implementation of the divide-and-conquer
// closest-pair algorithm

#include <iostream>
#include <limits>
#include <cmath>

#include "closest-pair-dc.h"

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
//  - points sorted in nondecreasing order by X coordinate
//  - points sorted in nondecreasing order by Y coordinate
//  - # of input points
//

void findClosestPair(Point *pointsByX[], Point *pointsByY[],
		     int nPoints)
{
    // declair the array to store the closet pairs
    // pointsCandidate[0] and pointsCandidate[1] is used for storing 
    // the closet pairs
    Point *pointsCandidate [2];
    // call the divide and conquer function to find the closest pair
    double distanceMin = findClosestPairDC(pointsByX,pointsByY,
                                           nPoints,pointsCandidate);
    // sort the result in order to print the point with lowest 
    // X-coordinate first;
    // if the two points have equal X-coordinates, print the point 
    // with lowest Y-coordinate first.
    // sort the result
    sortResultDC(pointsCandidate);
    // print the result
    cout << endl << pointsCandidate[0] << " " << pointsCandidate[1] 
         << " " << distanceMin << endl;
    
}


double findClosestPairDC(Point *pointsByX[], Point *pointsByY[],
                         int nPoints, Point *p[])
{
    // BASE
    // base case of the recursion
    // if there are two points, return distance between them
    if (nPoints == 2)
    {
        // store the address of the point
        p[0] = pointsByX[0];
        p[1] = pointsByX[1];
        return pointsByX[0]->distance(pointsByX[1]);
    }
    // if only one, return infinate distance
    if (nPoints <=1)
        return INFTY;
    
    // DEVIDE
    // calculate the midpoints by X and divide points apart
    int mid = nPoints/2;
    // calculate left part by x
    Point **XL = pointsByX;
    // calculate right part by x
    Point **XR = pointsByX+(mid+1);
    // use for left part by x
    Point **YL = new Point* [mid+1];
    // use for right part by x
    Point **YR = new Point* [nPoints-(mid+1)];
    // used for index
    int j = 0; // used for YL
    int k = 0; // used for YR
    // calculate the left and right part array sorted by Y
    for (int i = 0; i < nPoints; i++)
    {
        // if the points x coordinate value is small or equal 
        // to mid point, put to left otherwise put to right
        if ((pointsByY[i]->isLeftOf(pointsByX[mid])) || 
             pointsByY[i] == pointsByX[mid])
            YL[j++] = pointsByY[i];
        else
            YR[k++] = pointsByY[i];
    }
    
    // to store points of final result
    Point *p1[2]; // store left part
    Point *p2[2]; // store right part
    Point *p3[2]; // store strip part
    // recursive call the function
    double d1 = findClosestPairDC(XL,YL,mid+1,p1); // the left part
    double d2 = findClosestPairDC(XR,YR,nPoints-(mid+1),p2); // right
    // assign the small value to d from d1 and d2
    double dLR = minLR(d1,d2,p1,p2,p);
    
    // find the smallest value from the strip
    double dStrip = pairDistanceInStrip(pointsByY,nPoints,
                                        pointsByX[mid]->x(),dLR,p3);
    
    //COMBINE
    double distanceMin = minLRS(dLR,dStrip,p3,p);
    
    // free memory
    delete [] YL;
    delete [] YR;
    
    return distanceMin;
}


// minimal distance in left and right
double minLR(double d1, double d2, Point *p1[],Point *p2[],Point *p[])
{
    if (d1 <= d2)
    {
        // set the value of the point to the end of the array,
        // it records the final result
        p[0] = p1[0];
        p[1] = p1[1];
        return d1;
    }
    else
    {
        // set the value of the point to the end of the array,
        // it records the final result
        p[0] = p2[0];
        p[1] = p2[1];
        return d2;
    }
}


// minimal distance in left and right and strip
double minLRS(double dLR, double dS, Point *p3[],Point *p[])
{
    if (dLR <= dS)
    {
        return dLR;
    }
    else
    {
        // set the value of the points the array, 
        // it records the final result
        p[0] = p3[0];
        p[1] = p3[1];
        return dS;
    }
}


double pairDistanceInStrip(Point *pointsByY[], int nPoints, 
                           int xMid, double dLR, Point *p[])
{
    int total = 0, size = nPoints;
    // the distance
    double dStrip = INFTY;
    Point **yStrip = new Point *[size];
    // add points to the yStrip
    for (int i = 0; i < size; i++) {
        if (abs(xMid - pointsByY[i]->x()) <= dLR) {
            yStrip[total++] = pointsByY[i];
        }
    }
    // if there are more than 2 or equal 2 points
    if (total >=2)
    {
        // set the iniital value
        dStrip = yStrip[0]->distance(yStrip[1]); // the start value
        double d = INFTY;
        p[0] = yStrip[0];
        p[1] = yStrip[1];
        int k;
        // compare the points in the yStrip, get the dStrip value
        for (int i = 0; i < total; i++)
        {
            k = i+1; // index for the next points
            while (k < total && yStrip[k]->y() - yStrip[i]->y() <= dLR)
            {
                d = yStrip[i]->distance(yStrip[k]);
                if (d < dStrip)
                {
                    dStrip = d;
                    p[0] = yStrip[i];
                    p[1] = yStrip[k];
                }
                k++;
            }
            
        }
        // free memory
        delete [] yStrip;
    }
    return dStrip;
}

// sort the result in order to print the point with lowest 
// X-coordinate first;
// if the two points have equal X-coordinates, 
// print the point with lowest Y-coordinate first.
void sortResultDC(Point *p[])
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




