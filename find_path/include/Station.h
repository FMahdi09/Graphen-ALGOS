#ifndef STATION_H
#define STATION_H

#include <string>
#include <vector>
#include <iostream>

class Station
{
    public:
        //Constructor
        Station(std::string line, std::string name);
        Station(std::string line, std::string name, int weight);

        //Functions
        void addConnection(Station newConnection);
        void addLine(std::string newLine);

        //Getter
        const std::string getName() const;

        //Debug
        void printConnections();
        void printStation();

    private:
        //Variables
        std::string name;
        std::vector<std::string> lines;
        int weight;

        std::vector<Station> connections;
};

#endif // STATION_H
