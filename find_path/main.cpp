#include <iostream>
#include <exception>

#include "Graph.h"

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        std::cout << "please provide arguments with the following structure: filename_graph start goal\n";
        return 1;
    }

    try
    {
        Graph graph(argv[1]);

        //Debug
        graph.printConnections(argv[2]);
    }
    catch(const std::invalid_argument& except)
    {
        std::cout << except.what() << std::endl;
        return 1;
    }

    return 0;
}
