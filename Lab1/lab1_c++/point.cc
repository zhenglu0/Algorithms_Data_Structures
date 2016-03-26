//
// POINT.CC
// Implementation of the 2D Point class
// 

#include <cstdlib>
#include <cmath>

#include "point.h"

using namespace std;

// local counter used to produce globally unique point ID's
static int counter = 0;

// Constructor with no elements
Point::Point(void)
  : _x(0), _y(0)
{
  _num = counter++;
}

// Constructor with initial x and y values
Point::Point(int x, int y)
  : _x(x), _y(y)
{
  _num = counter++;
}

// Euclidean distance between this point and another
double Point::distance(const Point *other) const
{
  double dx = x() - other->x();
  double dy = y() - other->y();
  return sqrt(dx * dx + dy * dy);
}


// Print a point in the form "(x, y)"
ostream &operator<< (ostream &os, const Point &point)
{
  os << '(' << point.x() << ',' << point.y() << ')';
  return os;
}

// Print a point passed in by reference.  Freak if the caller
// passed us a NULL pointer!
ostream &operator<< (ostream &os, const Point *point)
{
  if (point == NULL)
    {
      os << "NULL (this shouldn't happen!)";
    }
  else
    os << *point;
  
  return os;
}
