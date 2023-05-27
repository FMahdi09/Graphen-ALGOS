#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <fstream>
#include <sstream>
#include <exception>

#include "Station.h"

class Graph
{
    public:
        //Constructor
        Graph(std::string filepath);

        //Debug
        void printConnections(std::string toPrint);

    private:
        //Variables
        std::vector<Station> stations;

        //Functions
        int createStation(std::string name, std::string line);

};

#endif // GRAPH_H
