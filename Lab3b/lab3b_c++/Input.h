//
// INPUT.H
// Input reader for airport and flight data
//
// To read all the information necessary for this lab:
//   (1) Create an object (say, "input") of type Input.
//   (2) Call input->readAirports(<airportFileName>)
//   (3) Call input->readFlights(<flightFileName>)
//
// Note that you *must* do (3) after (2).
//
// If all goes well, you will then have access to
//
//   * input->airports   -- an array of pointers to Airport objects
//
//   * input->flights    -- an array of pointers to Flight objects
//
//   * input->airportMap -- a map<string, Airport *> mapping airport 
//                          codes to the corresponding Airport objects
//

#ifndef __INPUT_H
#define __INPUT_H

#include <string>
#include <vector>
#include <map>

class Input {
    
public:
    //
    // Airport information
    //
    struct Airport {
        std::string name; // name of airport (3-letter code)
        int offset;  // offset of local time from GMT (in minutes)
        int id;      // convenient integer identifier
    };

    //
    // Flight information
    // NB: all times are GMT, in minutes since midnight
    //
    struct Flight {
        std::string name;                   // flight name
        Airport *startAirport, *endAirport; // flight termini
        int startTime, endTime;             // departure and arrive times
    };

    //
    // array of all airports read from input
    //
    std::vector <Airport *> airports;

    //
    // array of all flights read from input
    //
    std::vector <Flight *> flights;

    //
    // mapping from airport codes (strings) to Airport objects
    //
    std::map<std::string, Airport *> airportMap;

    //////////////////////////////////////////////////////////////////////

    //
    // readAirports()
    // Read the airport file
    //
    void readAirports(const char * filename);

    //
    // readFlights()
    // read the flight file
    //
    void readFlights(const char * filename);

private:

    static int toTime(int timeRaw, std::string ampm, int offset);
};

#endif
