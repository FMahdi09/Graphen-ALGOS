#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <algorithm>
#include <chrono>

#include "Station.h"

class Graph
{
    public:
        //Constructor
        Graph(std::string filepath);

        //Functions
        void findPath(std::string start, std::string goal);

        //Debug
        void printConnections(std::string toPrint);

    private:
        //Variables
        std::vector<Station> stations;

        //Functions
        int createStation(std::string name, std::string line);
        Station* getStationFromName(std::string name);
        bool allStationsVisited();
        Station* getLowestCostStation();
        void printPath(Station* goal);

};

#endif // GRAPH_H
