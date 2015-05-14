#include "Vertex.hpp"

/**
 * Adds edge cost of all edges on this vertex
 */
double totalCostVert() const{
	double totalCost = 0;

	for(auto it = edges.begin(); it != edges.end(); ++it){
        totalCost += it->second->cost;
    }
    
    return totalCost;
}
// Method implementations here
