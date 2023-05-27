#include "Graph.h"

//Constructor
Graph::Graph(std::string filepath)
{
    std::ifstream inf(filepath);

    if(!inf.is_open())
    {
        throw std::invalid_argument("invalid filepath");
    }

    while(!inf.eof())
    {
        //read line from file and store all connections and weights in stringstream "connections"
        std::string line, buf;
        std::stringstream connections;

        std::getline(inf, line, ':');
        std::getline(inf, buf, '\n');

        connections << buf;

        //temp storage for information about every connection
        std::string curStation;
        std::string beforeStation;
        std::string afterStation;

        int beforeWeight = 0;
        int afterWeight = 0;

        //store first station in curStation
        connections.ignore(256,'"');
        std::getline(connections, curStation, '"');

        //iterate over all stations and add them to the graph with their respective connections
        while(connections)
        {
            int curStationIndex = createStation(curStation, line);

            beforeWeight = afterWeight;

            connections >> afterWeight;

            connections.ignore(256,'"');
            std::getline(connections, afterStation, '"');

            //add connections to the current station (if they exist)
            if(beforeStation != "")
            {
                Station newStation(line, beforeStation, beforeWeight);
                stations[curStationIndex].addConnection(newStation);

            }

            if(afterStation != curStation)
            {
                Station newStation(line, afterStation, afterWeight);
                stations[curStationIndex].addConnection(newStation);
            }

            beforeStation = curStation;
            curStation = afterStation;
        }
    }

    inf.close();
}

//Functions

//creates new station
//if station with that name already exists instead adds another line to it
//returns index of the station
int Graph::createStation(std::string name, std::string line)
{
    for(int i = 0; i < int(stations.size()); ++i)
    {
        if(stations[i].getName() == name)
        {
            stations[i].addLine(line);
            return i;
        }
    }

    Station newStation(line, name);
    stations.push_back(newStation);

    return stations.size() - 1;
}

//Debug

void Graph::printConnections(std::string toPrint)
{
    for(Station curStation : stations)
    {
        if(curStation.getName() == toPrint)
        {
            curStation.printConnections();
            return;
        }
    }

    throw std::invalid_argument("Station " + toPrint + " does not exist");
}
