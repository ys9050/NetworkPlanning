#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "UndirectedGraph.hpp"

using namespace std;

/**
 * Entry point into the netplan program.
 *
 * Usage:
 *   ./netplan infile
 *
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " infile" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Unable to open file for reading." << std::endl;
        return EXIT_FAILURE;
    }
    
    // Implementation here

    UndirectedGraph fullNetwork;
    UndirectedGraph minNetwork;

    std::string start;
    std::string end;

    unsigned int cost;
    unsigned int latency;
    
    unsigned int totalCost = 0;
    unsigned int minTotalCost;

    unsigned int totalLat;
    unsigned int minTotalLat;

    while(in.good()){
        in >> start >> end >> cost >> latency;
        if(!in.good()) break;
        
        //calculate total cost of all possible network links
        totalCost += cost;

        fullNetwork.addEdge(start, end, cost, latency);
    }

    minNetwork = fullNetwork.mst();
    minTotalCost = minNetwork.totalCost();

    totalLat = fullNetwork.totalLatency();
    minTotalLat = minNetwork.totalLatency();

    //Total cost of building all the possible network links
    //Add all of column three
    
    cout << totalCost << endl;

    //Total cost of building the cheapest network
    //Create MST where the edges connecting links are chosen on cheepest edge
    //add all edges of the tree
    
    cout << minTotalCost << endl;
    

    //Part1 - Part 2
    
    cout << totalCost - minTotalCost << endl;

    // The total transit time to send if all of network link was built
  
    cout << totalLat << endl;

    //Total transit time in minimum
    
    cout << minTotalLat << endl;

    //Part 5 - Part 4

    cout << minTotalLat - totalLat << endl;
    
    return EXIT_SUCCESS;
}
