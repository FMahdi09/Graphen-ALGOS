#include "Station.h"

//Constructor
Station::Station(std::string line, std::string name)
{
    this->lines.push_back(line);
    this->name = name;
    this->weight = 10000;
    visited = false;
}

Station::Station(std::string line, std::string name, int weight)
{
    this->lines.push_back(line);
    this->name = name;
    this->weight = weight;
    visited = false;
}

//Functions

void Station::addConnection(Station newConnection)
{
    connections.push_back(newConnection);
}

void Station::addLine(std::string newLine)
{
    lines.push_back(newLine);
}

//Getter

const std::string Station::getName() const
{
    return name;
}

const int Station::getWeight() const
{
    return weight;
}

const std::vector<Station> Station::getConnections() const
{
    return connections;
}

const std::string Station::getPredecessor() const
{
    return predecessor;
}

const bool Station::wasVisited() const
{
    return visited;
}

//Setter

void Station::isVisited()
{
    visited = true;
}

void Station::setWeight(int amount)
{
    weight = amount;
}

void Station::setPredecessor(std::string name)
{
    predecessor = name;
}

//Debug
void Station::printConnections()
{
    for(Station curStation : connections)
    {
        curStation.printStation();
    }
    std::cout << std::endl;
}

void Station::printStation()
{
    std::cout << "Linie: ";

    for(std::string line : lines)
    {
        std::cout << line << " ";
    }

    std::cout << ", Station: " << name << ", Dauer: " << weight << std::endl;
}
