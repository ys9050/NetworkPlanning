#include "Vertex.hpp"
#include "Edge.hpp"

/**
 * Adds edge cost of all edges cost on this vertex
 */
unsigned int Vertex::totalCostVert() const {
	unsigned int totalCost = 0;

	for(auto it = edges.begin(); it != edges.end(); ++it){
        totalCost += it->second.cost;
    }
    
    return totalCost;
}
// Method implementations here
