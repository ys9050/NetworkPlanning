#include "Vertex.hpp"
#include "Edge.hpp"

/**
 * Adds edge cost of all edges on this vertex
 */
unsigned int totalCostVert() const{
	unsigned int totalCostt = 0;

	for(auto it = edges.begin(); it != edges.end(); ++it){
        totalCost += it->second->cost;
    }
    
    return totalCostt;
}
// Method implementations here
