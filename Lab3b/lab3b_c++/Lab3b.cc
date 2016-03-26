//
// LAB3B.CC
// Driver for airline scheduling shortest-paths code
//

#include <iostream>
#include <string>
#include <vector>

#include "QueryReader.h"
#include "Multigraph.h"
#include "ShortestPaths.h"
#include "PrettyTime.h"

using namespace std;

// local prototypes
static void findPaths(Input &input, Multigraph &G, const char *queryFile);
static void printPath(Input &input, vector<int> &flightIds);
static void validatePath(Input &input, int startTime, vector<int> &flightIds);

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        cerr << "Syntax: Lab3b <airports> <flights> <queries>\n";
        return -1;
    }
	
    // read the input
    Input input;
    input.readAirports(argv[1]);
    cout << "Read " << input.airports.size() << " airports\n";
    input.readFlights(argv[2]);
    cout << "Read " << input.flights.size() << " flights\n";

    //
    // construct the input graph
    //

    Multigraph G;

    // Allocate a vertex for every airport.  Logically, the jth 
    // vertex corresponds to the jth entry in input.airports[].
    //
    for (unsigned int j = 0; j < input.airports.size(); j++)
    {
        input.airports[j]->id = j;

        Vertex *v = new Vertex(j);
        G.addVertex(v);
    }
	
    // While we allocate all the edges, set the id for each
    // edge to the index of the corresponding flight in the
    // input.flights[] array.
    //
    for (unsigned int k = 0; k < input.flights.size(); k++)
    {
        Input::Flight *fl = input.flights[k];

        Vertex *from = G.get(fl->startAirport->id);
        Vertex *to   = G.get(fl->endAirport->id);

        int len = fl->endTime - fl->startTime;
        if (len < 0) len += 24 * 60; // next day

        Edge *e = new Edge(k, from, to, len);

        from->addEdge(e);
    }
  
    // Do the shortest-paths computation
    findPaths(input, G, argv[3]);
}
    
    
//
// findPaths()
// Construct shortest paths from a specified starting
// airport to every vertex of G, and then answer queries
// asking for the shortest path (least total travel time)
// from the start to other airports.
//
static void findPaths(Input &input, Multigraph &G, const char *queryFile)
{
    vector<Query *> *queries = QueryReader::readQueries(queryFile);
  
    if (queries == NULL) // I/O error
        return;
  
    for (unsigned int i = 0; i < queries->size(); i++)
    {
        Query *q = (*queries)[i];

        // 
        // Fix the starting airport
        //
        cout << "> " << *q << '\n';
      
        map<string, Input::Airport *>::iterator it =
            input.airportMap.find(q->from);
        Input::Airport *fromap =
            (it == input.airportMap.end() ? NULL : it->second);
      
          if (fromap == NULL)
          {
              cerr << "Error: airport code " << q->from << " is unknown\n";
              continue;
          }
      
        //
        // YOUR CODE CALLED HERE -- find shortest paths from start
        // 
        ShortestPaths sp(&G, fromap->id,
               &input,
               q->startTime);
      
        //
        // Field shortest-path queries to other airports
        //
        for (unsigned int i = 0; i < q->tos.size(); i++)
        {
            string to = q->tos[i];
	  
            map<string, Input::Airport *>::iterator it =
                input.airportMap.find(to);
            Input::Airport *toap =
                (it == input.airportMap.end() ? NULL : it->second);
	  
            if (toap == NULL)
            {
                cerr << "Error: airport code " << to << " is unknown\n";
                continue;
            }
	  
            if (toap == fromap)
            {
                cout << "You're already there!\n";
                continue;
            }
	  
            vector<int> flightIds = sp.returnPath(toap->id);
            if (flightIds.size() == 0)
                cout << "No path to " << to << '\n';
            else
            {
                printPath(input, flightIds);
                validatePath(input, q->startTime, flightIds);
            }
	  
            cout << '\n';
        }
    }
}
    
//
// printPath()
// print a path of edges (flight identifiers) between airports
//
static void printPath(Input &input, vector<int> &flightIds)
{
    cout << input.flights[flightIds[0]]->startAirport->name;
  
    for (unsigned int i = 0; i < flightIds.size(); i++)
    {
        int flightId = flightIds[i];
      
        Input::Flight *fl = input.flights[flightId];
      
        cout << endl << "---> " << fl->endAirport->name <<
            " (" << fl->name << ", ";
        PrettyTime::print(cout, fl->startTime) << "-";
        PrettyTime::print(cout, fl->endTime) << ", ";
        PrettyTime::printElapsed(cout, 
			       fl->startTime, 
			       fl->endTime) << ")";
    }
}
    
    
// validatePath()
// validate that a proposed path of flights is feasible (i.e., all
// legs are connected), and compute and print the total time spent
// flying (+ time spent waiting if startTime != 0).
//
static void validatePath(Input &input, int startTime, vector<int> &flightIds)
{
    int prevEndTime = startTime;
    Input::Flight *prevFl = NULL;
    int totalTime = 0;
	
    for (unsigned int f = 0; f < flightIds.size(); f++)
    {
        Input::Flight *fl = input.flights[flightIds[f]];
      
        // verify that the path of flights is connected
        if (f > 0)
        {
            if (fl->startAirport->id != prevFl->endAirport->id)
            {
                cout << "ERROR: path is not connected in G\n";
                break;
            }
          
            if (startTime != 0 &&
              PrettyTime::elapsed(prevEndTime, fl->startTime) < 45)
            {
                cout << "ERROR: connection time is too short!";
                break;
            }
        }
      
        // add the time spent in flight.  If the start time is
        // non-zero, we are minimizing time including layovers,
        // and we need to account waiting time as well.
        if (startTime != 0)
            totalTime += PrettyTime::elapsed(prevEndTime, fl->startTime);
      
        totalTime += PrettyTime::elapsed(fl->startTime, fl->endTime);

        prevFl = fl;
        prevEndTime = fl->endTime;
    }
	
    cout << endl << "@LENGTH = " << totalTime << " minutes\n";
}
