//
// INPUT.CC
// Input reader for airport and flight data
//

#include <iostream>
#include <fstream>

#include "Input.h"

using namespace std;
  
//
// Input::readAirports()
// Read the airport file
//
void Input::readAirports(const char *filename)
{
    ifstream fp(filename);
  
    while (!fp.eof())
    {
        Airport *ap = new Airport;
        int i;
      
        fp >> ap->name >> i;
        ap->offset = (i / 100) * 60;
      
        if (!fp.eof())
            airports.push_back(ap);
        else
            delete ap;
    }
  
    // create the mapping from names to objects
    for (unsigned int j = 0; j < airports.size(); j++)
    {
        Airport *ap = airports[j];
      
        pair<string, Airport *> pr(ap->name, ap);
        airportMap.insert(pr);
    }
}


//
// readFlights()
// read the flight file
//
void Input::readFlights(const char *filename)
{
    ifstream fp(filename);
  
    // read the flights and store their times in GMT
    while (!fp.eof())
    {
        Flight *fl = new Flight;
      
        string airline, flightno;
        fp >> airline >> flightno;
      
        fl->name = airline + string("-") + flightno;
      
        if (fp.eof())
            break;
      
        string code;
        int tm;
        string ampm;
      
        fp >> code;
        fl->startAirport = airportMap.find(code)->second;
      
        fp >> tm >> ampm;
        fl->startTime = toTime(tm, ampm, fl->startAirport->offset);
      
        fp >> code;
        fl->endAirport = airportMap.find(code)->second;
      
        fp >> tm >> ampm;
        fl->endTime = toTime(tm, ampm, fl->endAirport->offset);
      
        flights.push_back(fl);
    }
}


//
// toTime()
// convert raw time value and AM/PM in local time, to minutes
// since midnight in GMT, using supplied offset from GMT.
//
int Input::toTime(int timeRaw, string ampm, int offset)
{
    int hour   = (timeRaw / 100) % 12;
    int minute = timeRaw % 100;

    bool isPM = (ampm[0] == 'P');

    int minutes = hour * 60 + minute;
    if (isPM) minutes += 12 * 60;

    int finalTime = (minutes - offset + 24 * 60) % (24 * 60);
    return finalTime;
}
