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

void Graph::findPath(std::string start, std::string goal)
{
    Station *curStation, *endStation;

    try
    {
        curStation = getStationFromName(start);
        endStation = getStationFromName(goal);
    }
    catch(const std::invalid_argument& except)
    {
        std::cout << except.what() << std::endl;
        return;
    }

    curStation->setWeight(0);
    curStation->setPredecessor(start);

    while(!allStationsVisited())
    {
        //get Connections of current station
        std::vector<Station> connections = curStation->getConnections();

        //iterate through all connections and calculate the needed cost
        for(int i = 0; i < int(connections.size()); ++i)
        {
            Station* curConnection = getStationFromName(connections[i].getName());

            //only calculate for unvisited stations
            if(!curConnection->wasVisited())
            {
                int totalCost = curStation->getWeight() + connections[i].getWeight();

                if(curConnection->getWeight() > totalCost)
                {
                    curConnection->setWeight(totalCost);
                    curConnection->setPredecessor(curStation->getName());
                }
            }
        }

        curStation->isVisited();

        //get unvisited station with the smallest cost for next iteration
        curStation = getLowestCostStation();
    }

    //print path
    printPath(endStation);
}

void Graph::printPath(Station* goal)
{
    std::cout << goal->getWeight() << std::endl;

    std::cout << goal->getName() << " - ";

    Station* curStation = getStationFromName(goal->getPredecessor());

    while(curStation->getName() != curStation->getPredecessor())
    {
        std::cout << curStation->getName() << " - ";

        curStation = getStationFromName(curStation->getPredecessor());
    }

    std::cout << curStation->getName() << std::endl;
}

Station* Graph::getStationFromName(std::string name)
{
    for(int i = 0; i < int(stations.size()); ++i)
    {
        if(stations[i].getName() == name)
        {
            return &stations[i];
        }
    }

    throw std::invalid_argument("Station: \"" + name + "\" does not exist");
}

Station* Graph::getLowestCostStation()
{
    int minimun = 10000;
    int lowestIndex = 0;

    for(int i = 0; i < int(stations.size()); ++i)
    {
        if(!stations[i].wasVisited() && stations[i].getWeight() < minimun)
        {
            minimun = stations[i].getWeight();
            lowestIndex = i;
        }
    }

    return &stations[lowestIndex];
}

bool Graph::allStationsVisited()
{
    for(int i = 0; i < int(stations.size()); ++i)
    {
        if(stations[i].wasVisited() == false)
        {
            return false;
        }
    }

    return true;
}

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
