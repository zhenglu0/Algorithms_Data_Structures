//
// LAB1.CC
// Main driver code for CSE 241 Lab #1.
// Updated 9/7/2011

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>

#include <cstdlib>
#include <cmath>
#include <ctime>

#include "closest-pair-dc.h"
#include "closest-pair-naive.h"

#include "point.h"
#include "timer.h"
#include "prng.h"

using namespace std;

// Random seed, used when generating points at random.
static int seed = 5498;

///////////////////////////////////////////////////////////////////////
// Comparator functions for sort()

// compares p1 and p2 based on the x-coord
struct _lessThanX {
  bool operator() (const Point *p1, const Point *p2)
  { 
    return (p1->isLeftOf(p2));
  }
} lessThanX;

// compares p1 and p2 based on the y-coord
struct _lessThanY {
  bool operator()(const Point *p1, const Point *p2)
  { 
    return (p1->isBelow(p2));
  }
} lessThanY;


//
// genPointsAtRandom()
// Generate nPoints points uniformly at random.
//
static void genPointsAtRandom(Point *points[], int nPoints,
			      PRNG *prng)
{
  double x = 0.0;
  double y = 0.0;

  double step = sqrt(nPoints);
  
  for (int j = 0; j < nPoints; j++)
    {
      // bump next point's X coordinate
      x += 10000.0 * (prng->nextDouble() - 0.5);
      
      // move the Y coordinate a random amount up,
      // while keeping it within limits [0 .. nPoints)
      y = (y + step * prng->nextDouble());
      while (y > nPoints)
	y -= nPoints;
	   
      Point *p = new Point;
      p->setX((int) rint(x)); // set x and y coords of point
      p->setY((int) rint(y));
      points[j] = p;
    }
}


//
// readXYPoints()
// Read a collection of points from an input file.
// The first line of the file should give the number of points
// to read.  Each subsequent line should give the coordinates of
// one point in the form "x y".
//
// RETURNS: array of pointers to Point structures
// SETS: *inPoints to length of array
//
static Point **readXYPoints(const char *pointFileName, int *inPoints)
{
  ifstream pointFile(pointFileName);
  int nPoints;
  
  if (!pointFile)
    {
      cerr << "Error: could not open point file '"
	   << pointFileName << "'" << endl;
      exit(1);
    }
  
  pointFile >> nPoints;
  
  if (nPoints < 2)
    {
      cerr << "Error: need at least two points!" << endl;
      exit(1);
    }
  
  Point **points = new Point * [nPoints];
  
  for (int j = 0; j < nPoints; j++)
    {
      int x, y;
      
      pointFile >> x;
      pointFile >> y;
      
      if (!pointFile)
	{
	  cerr << "Error: could not read point #" << j << endl;
	  exit(1);
	}
      
      Point *p = new Point(x,y);
      
      points[j] = p;
    }
  
  *inPoints = nPoints;
  
  return points;
}


int main(int argc, char *argv[])
{
  Point **points;      // array of refs to points
  int nPoints;         // number of points
  Timer timer;  
  string fileName;

  // only argument is the input spec
  if (argc > 1)
    {
      fileName = argv[1];
    }
  else
    {
      cerr << "Syntax: Lab1 <filename>\n";
      exit(1);
    }
  
  // A filename argument of the form '@x', where x is a non-negative
  // integer, allocates x random points.  Any other argument is
  // assumed to be a file from which points are read.
  
  if (fileName[0] != '@')
    {
      points = readXYPoints(argv[1], &nPoints);
    }
  else
    {
      nPoints = strtoul(fileName.substr(1).c_str(), NULL, 10);
      
      // Use these lines if you want a different random set of points for each
      // run.  This code sets the seed for the RNG from the system clock time.
      /*
      {
          time_t tp;
          time(&tp);
          seed = tp;
      }
      */
      PRNG prng(seed);  // seed the random number generator
      
      points = new Point * [nPoints];
      genPointsAtRandom(points, nPoints, &prng);
    }
  
  if (nPoints < 2)
    {
      cerr << "ERROR: input must contain at least two points\n";
      exit(1);
    }
  
  timer.start();
    
  //////////////////////////////////////////////////////////////////////////
  // DIVIDE AND CONQUER CLOSEST-PAIR ALGORITHM STARTS HERE
  
  // The algorithm expects two arrays containing the same points.
  Point **pointsByX = new Point * [nPoints];
  Point **pointsByY = new Point * [nPoints];
  
  for (int j = 0; j < nPoints; j++)
    {
      pointsByX[j] = points[j];
      pointsByY[j] = points[j];
    }
  
  // NB: you should *not* have to call sort() in your
  // own code!
  sort(pointsByX, pointsByX + nPoints, lessThanX); // sort by x-coord to get X
  sort(pointsByY, pointsByY + nPoints, lessThanY); // sort by y-coord to get Y
  
  findClosestPair(pointsByX, pointsByY, nPoints);
  
  // DIVIDE AND CONQUER CLOSEST-PAIR ALGORITHM ENDS HERE
  //////////////////////////////////////////////////////////////////////////
  
  timer.stop();
  
  cout << "For n = " << nPoints << ", the divide and conquer time is ";
  cout << timer.elapsedTime() << " milliseconds\n\n";
  /*
  // write to a file to collect data
  ofstream myfile;
  myfile.open ("dc-running-time.txt",ios_base::app);
  myfile << timer.elapsedTime() << endl;
  myfile.close();
  */
  timer.start();
  
  ///////////////////////////////////////////////////////////////////////
  // NAIVE CLOSEST-PAIR ALGORITHM STARTS HERE
  
  findClosestPairNaive(points, nPoints);
  
  // NAIVE CLOSEST-PAIR ALGORITHM ENDS HERE
  ///////////////////////////////////////////////////////////////////////
  
  timer.stop();
  
  cout << "For n = " << nPoints << ", the naive time is ";
  cout << timer.elapsedTime() << " milliseconds\n\n";
  
  
  delete [] pointsByX;   // free storage from array ptsByX of pt refs 
  delete [] pointsByY;   // free storage from array ptsByY of pt refs
  
  for (int j = 0; j < nPoints; j++)
    delete points[j];  // free storage from points themselves
  
  delete [] points;
  
  return 0;
}
