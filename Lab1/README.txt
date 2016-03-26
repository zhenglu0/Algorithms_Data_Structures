***************************************************************************Lab 1Author: Zheng LuoEmail: luozheng@wustl.edu******************************************************************************************************************Part One:Implement the Algorithms***************************************
***************************************1. Test cases ***************************************---------------Case1: ---------------Test only one pointInput File: 10 1Output:Error: need at least two points!---------------Case2: ---------------Test two points with different pointsInput File:20 12 3Output:The closest pair is (0,1) (2,3), the distance between them is 2.82843For n = 2, the divide and conquer time is 0.047 millisecondsThe closest pair is (0,1) (2,3), the distance between them is 2.82843For n = 2, the naive time is 0.007 milliseconds---------------Case3: ---------------Test two points with same pointsInput File:20 10 1Output:The closest pair is (0,1) (0,1), the distance between them is 0For n = 2, the divide and conquer time is 0.038 millisecondsThe closest pair is (0,1) (0,1), the distance between them is 0For n = 2, the naive time is 0.006 milliseconds---------------Case4: ---------------Test three points with different pointsInput File:32 33 56 7Output:The closest pair is (2,3) (3,5), the distance between them is 2.23607For n = 3, the divide and conquer time is 0.047 millisecondsThe closest pair is (2,3) (3,5), the distance between them is 2.23607For n = 3, the naive time is 0.008 milliseconds---------------Case5: ---------------Test three points with two same pointsInput File:32 33 52 3Output:The closest pair is (2,3) (2,3), the distance between them is 0For n = 3, the divide and conquer time is 0.044 millisecondsThe closest pair is (2,3) (2,3), the distance between them is 0For n = 3, the naive time is 0.007 milliseconds---------------Case6: ---------------Test three points with three same pointsInput File:32 32 32 3Output:The closest pair is (2,3) (2,3), the distance between them is 0For n = 3, the divide and conquer time is 0.044 millisecondsThe closest pair is (2,3) (2,3), the distance between them is 0For n = 3, the naive time is 0.007 milliseconds---------------Case7: ---------------Test five different points:Input File: 513 2115 279 24 176 1Output:The closest pair is (6,1) (9,2), the distance between them is 3.16228For n = 5, the divide and conquer time is 0.054 millisecondsThe closest pair is (6,1) (9,2), the distance between them is 3.16228For n = 5, the naive time is 0.009 milliseconds---------------Case8: ---------------Test five different points, some of them have same X or Y value:Input File: 513 2115 279 24 176 1Output:The closest pair is (13,21) (13,27), the distance between them is 6For n = 5, the divide and conquer time is 0.053 millisecondsThe closest pair is (13,21) (13,27), the distance between them is 6For n = 5, the naive time is 0.007 milliseconds---------------Case9: ---------------Test five different points and two pairs of points have the same distance:Input File:50 15 610 127 82 3Output:The closest pair is (0,1) (2,3), the distance between them is 2.82843For n = 5, the divide and conquer time is 0.053 millisecondsThe closest pair is (0,1) (2,3), the distance between them is 2.82843For n = 5, the naive time is 0.009 milliseconds---------------Case10: ---------------Test five different points and two pairs of points have the same distance:Input File:55 610 127 82 30 1Output:The closest pair is (0,1) (2,3), the distance between them is 2.82843For n = 5, the divide and conquer time is 0.053 millisecondsThe closest pair is (5,6) (7,8), the distance between them is 2.82843For n = 5, the naive time is 0.009 milliseconds---------------Case11: ---------------Test ten different points:Input File:1013 2115 2712 141 53 76 49 517 5520 3311 12Output:The closest pair is (11,12) (12,14), the distance between them is 2.23607For n = 10, the divide and conquer time is 0.055 millisecondsThe closest pair is (11,12) (12,14), the distance between them is 2.23607For n = 10, the naive time is 0.008 milliseconds

*******************************************2. Lab1 implementation brief description*******************************************
---------------------Naive implementation: ---------------------
Just use two for loop to do the calculation and then put the result into an array
then call sortResultNA(Point *p[]) to sort the result.
Finally display the result

---------------------------------Divide and Conquer implementation: ---------------------------------

void findClosestPair(Point *pointsByX[], Point *pointsByY[],int nPoints)
is a wrapper to call the recursive call findClosestPairDC.

double findClosestPairDC(Point *pointsByX[], Point *pointsByY[], int nPoints, Point *p[])
is used to find the closest pair recursively, p[] is used for collecting the points.

double minLR(double d1, double d2, Point *p1[],Point *p2[],Point *p[]) 
is used to compare minimal distance in left and right part of each division

double minLRS(double dLR, double dS, Point *p3[],Point *p[]) 
is used to compare distance in left and right and strip of each division

double pairDistanceInStrip(Point *YL[], Point *YR[], int nPoints, int mid, double dLR, Point *p[]);
is used to find minimal distance in strip of each division

void sortResultDC(Point *p[]) 
is used for sort the result


***************************************Part Two: Do the Comparison***************************************
Please see the excel document named "Compare DC & NA" and "Variation in DC" that I attached.


***************************************Part Three: Find the Crossover Point***************************************
I write a for loop, that make find both closest pair naive and divide and conquer run 10000 times.

Divide and conquer algorithm:

  timer.start();
    
  for (int i = 0; i < 10000 ; i++)
  {
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
      
      
      delete [] pointsByX;   // free storage from array ptsByX of pt refs
      delete [] pointsByY;   // free storage from array ptsByY of pt refs
      // DIVIDE AND CONQUER CLOSEST-PAIR ALGORITHM ENDS HERE
      //////////////////////////////////////////////////////////////////////////
  }
  timer.stop();

Naive algorithm:

  timer.start();
  
  ///////////////////////////////////////////////////////////////////////
  // NAIVE CLOSEST-PAIR ALGORITHM STARTS HERE
  for (int i = 0; i < 10000 ; i++)
    findClosestPairNaive(points, nPoints);
  
  // NAIVE CLOSEST-PAIR ALGORITHM ENDS HERE
  ///////////////////////////////////////////////////////////////////////
  
  timer.stop();

I tried several different input, I will list the different input and output:

---------------Runtime1: ---------------
MacBookAir:lab1_c++ luozheng03$ ./lab1 @2
For n = 2, the divide and conquer time is 3.72 milliseconds
For n = 2, the naive time is 0.209 milliseconds

---------------Runtime2: ---------------
MacBookAir:lab1_c++ luozheng03$ ./lab1 @10
For n = 10, the divide and conquer time is 49.975 milliseconds
For n = 10, the naive time is 4.293 milliseconds

---------------Runtime3: ---------------
MacBookAir:lab1_c++ luozheng03$ ./lab1 @20
For n = 20, the divide and conquer time is 109.982 milliseconds
For n = 20, the naive time is 20.672 milliseconds

---------------Runtime4: ---------------
MacBookAir:lab1_c++ luozheng03$ ./lab1 @40
For n = 40, the divide and conquer time is 261.138 milliseconds
For n = 40, the naive time is 86.572 milliseconds

---------------Runtime5: ---------------
MacBookAir:lab1_c++ luozheng03$ ./lab1 @80
For n = 80, the divide and conquer time is 500.572 milliseconds
For n = 80, the naive time is 368.041 milliseconds

---------------Runtime6: ---------------
MacBookAir:lab1_c++ luozheng03$ ./lab1 @100
For n = 100, the divide and conquer time is 624.277 milliseconds
For n = 100, the naive time is 580.599 milliseconds

---------------Runtime7: ---------------
MacBookAir:lab1_c++ luozheng03$ ./lab1 @110
For n = 110, the divide and conquer time is 708.895 milliseconds
For n = 110, the naive time is 706.775 milliseconds

---------------Runtime8: ---------------
MacBookAir:lab1_c++ luozheng03$ ./lab1 @115
For n = 115, the divide and conquer time is 724.47 milliseconds
For n = 115, the naive time is 773.216 milliseconds

---------------Runtime9: ---------------
MacBookAir:lab1_c++ luozheng03$ ./lab1 @120
For n = 120, the divide and conquer time is 760.493 milliseconds
For n = 120, the naive time is 866.534 milliseconds

---------------Conclusion: ---------------
At about n = 110 random points, the divide and conquer algorithm running time is equal to the naive algorithm running time.
