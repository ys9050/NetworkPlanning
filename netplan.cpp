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

    UndirectedGraph all;
    UndirectedGraph min;

    std::string start;
    std::string end;

    double cost;
    double latency;

    unsigned int totalCost = 0;
    unsigned int mstCost;
    unsigned int distanceAll;
    unsigned int distanceMin;

    while(in.good()){
        in >> start >> end >> cost >> latency;
        if(!in.good()) break;
        
        //calculate total cost of all possible network links
        totalCost += cost;

        all.addEdge(start, end, cost, latency);
        min.addEdge(start, end, cost, latency);
    }

    //Total cost of building all the possible network links
    //Add all of column three
    
    cout << totalCost << endl;

    //Total cost of building the cheapes network
    //Create MST where the edges connecting links are chosen on cheepest edge
    //add all edges of the tree
    

    //Part1 - Part 2
    
    // The total transit time to send if all of network link was built
    
    //Total transit time in minimum
    
    //Part 5 - Part 4

    return EXIT_SUCCESS;

