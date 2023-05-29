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
        const std::vector<std::string> getLine() const;
        const int getWeight() const;
        const std::vector<Station> getConnections() const;
        Station* getPredecessor();
        const bool wasVisited() const;
        const std::string getLineUsed() const;

        //Setter
        void isVisited();
        void setWeight(int amount);
        void setPredecessor(Station* pre);
        void setLineUsed(std::string lineUsed);

        //Debug
        void printConnections();
        void printStation();

    private:
        //Variables
        std::string name;
        std::vector<std::string> lines;
        int weight;

        bool visited;
        Station* predecessor;
        std::string lineUsed;

        std::vector<Station> connections;
};

#endif // STATION_H
