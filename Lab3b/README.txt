***************************************************************************Lab 3bAuthor: Zheng LuoEmail: luozheng@wustl.edu******************************************************************************************************************Brief Summary of Implementation***************************************
ShortestPaths.cc include the Dijkstra's algorithm to calculate the shortest path. 
It is very straight forward to impelemnt Dijkstra algorithm.

There is a bug that took me 3 hours to figure out. That I first set every element in d[] 
except for source to infinity. Then I got some strange result.
Finally I found that I can not use numeric_limits<int>::max() to define infinity here.
Because  checking  whether we need the relaxation step, if I use numeric_limits<int>::max(), 
d[u->id()] + e->weight()  may overflow for some on reachable vetext whose d[i] is infinity, 
so I have to use something like numeric_limits<int>::max()/2
because none of the edeg weight is larger than numeric_limits<int>::max()/2


**********************************************Extra credit Brief Summary of Implementation**********************************************
For the extra credit, we need to change the relaxation step a little bit. 

If the node we extract is the source, we calculate layOver by using 
layOver = PrettyTime::elapsed(startTime, input->flights[e->id()]->startTime); 

If the node we extract is NOT source, we calculate layOver by using 
layOver = PrettyTime::elapsed(input->flights[p[u->id()]->id()]->endTime,
                                                      input->flights[e->id()]->startTime);

Then we check it in the relaxation step
// check whether we need the relaxation step
 if ((d[v->id()] > d[u->id()] + e->weight() + layOver) &&
       layOver >= 45 )
{
	// update d[]
        d[v->id()] = d[u->id()] + e->weight()+ layOver;
        // do the decrease key operation in the priority queue
        q.decreaseKey(h[v->id()],d[v->id()]);
        // set v's parent u, becuase we can easily find the
        // from vertext by call from(), and we need the edge information in
        // returnPath(), so we store Edge * in the vector p
	p[v->id()] = e;
}

