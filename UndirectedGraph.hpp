#ifndef UNDIRECTEDGRAPH_HPP
#define UNDIRECTEDGRAPH_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <string>
#include <unordered_map>

#include "Vertex.hpp"

/**
 * Implements an undirected graph. Any edge in the graph
 * represents a bidirectional connection between two vertices.
 * 
 * Implements methods for producing a minimum spanning tree of the
 * graph, as well as calculating the total length of the shortest
 * paths between each pair of vertices.
 */  
class UndirectedGraph {
    friend class Vertex;
    friend class Edge;
    public:
    /**
     * Constructs an empty UndirectedGraph with no vertices and
     * no edges.
     */
    UndirectedGraph();

    /**
     * Destructs an UndirectedGraph.
     */
    ~UndirectedGraph();
    
    void addEdge(const std::string &from, const std::string &to,
            unsigned int cost, unsigned int length);

    unsigned int totalCost() const;

    unsigned int totalLatency(const std::string &from);

	unsigned int totalLatency() const;	

    UndirectedGraph mst();


  private:
    /**
     * Comparison functor for use with Dijkstra's algorithm. Allows Vertices
     * to be added to a priority queue more than once, with different weights.
     */
    class DijkstraVertexComparator {
      public:
        bool operator()(const std::pair<Vertex*, unsigned int> &left,
                const std::pair<Vertex*, unsigned int> &right);
    };
    
    /**
     * Map of vertex name to Vertex.
     */
    std::unordered_map<std::string, Vertex*> vertices;
};

#endif
