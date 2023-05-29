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
    //start Timer
    auto startTime = std::chrono::steady_clock::now();

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
    curStation->setPredecessor(curStation);

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
                    curConnection->setPredecessor(curStation);
                    std::string lineUsed = connections[i].getLine()[0];
                    curConnection->setLineUsed(lineUsed);
                }
            }
        }

        curStation->isVisited();

        //get unvisited station with the smallest cost for next iteration
        curStation = getLowestCostStation();
    }

    //end Timer and calculate time spent
    auto endTime = std::chrono::steady_clock::now();

    float elapsed = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    //print path
    printPath(endStation);

    //print computational time
    std::cout << "\nComputation Time: " << elapsed/1000 << " ms\n";
}

void Graph::printPath(Station* goal)
{
    std::string curLine = goal->getLineUsed();

    std::cout << "\nTotal Cost: " << goal->getWeight() << "\n";

    std::cout << "\nStarting Line: " << curLine << "\n\n";

    std::cout << goal->getName() << "\n";

    Station* curStation = goal->getPredecessor();

    while(curStation != curStation->getPredecessor())
    {
        std::string newLine = curStation->getLineUsed();

        std::cout << curStation->getName() << "\n";

        if(curLine != newLine)
        {
            std::cout << "\nChange line to: " << newLine << "\n\n";
            curLine = newLine;
        }

        curStation = curStation->getPredecessor();
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
