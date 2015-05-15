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
    UndirectedGraph() {}

    /**
     * Destructs an UndirectedGraph.
     */
    ~UndirectedGraph();
    /**
	 * Creates an edge within the graph, both to and from and from and to
	 * are created.
	 */
    void addEdge(const std::string &from, const std::string &to,
            unsigned int cost, unsigned int length);
	
	/**
	 * Returns the total cost of the UndirectedGraph
	 * Calculates individual vertices' total cost to create edges
	 * then sum them all
	 */
    unsigned int totalCost() const;

	/**
	 * Returns the total latency of all vertex to all the otehrs
	 * Uses the totalLatency with no argument
	 * to get value of one vertex's total latency
	 * then does this for all, then sum them together.
	 */
    unsigned int totalLatency(const std::string &from);

	/**
	 * Returns the total latency from one vertex to all the others
	 * The path from one to other vertices take the shortest path
	 * via Dijkstras
	 */
	unsigned int totalLatency() const;	

	/**
	 * Given a UndirectedGraph, returns a minimum spanning tree of that graph.
	 * Uses Prim's
	 */
    UndirectedGraph mst();


  private:
    /**
     * Comparison functor for use with Dijkstra's algorithm. Allows Vertices
     * to be added to a priority queue more than once, with different weights.
     */
    class DijkstraVertexComparator {
      public:
        bool operator()(const std::pair<Vertex*, unsigned int> &left,
                const std::pair<Vertex*, unsigned int> &right){
            return left.second > right.second;
        }
    };
    
    /**
     * Map of vertex name to Vertex.
     */
    std::unordered_map<std::string, Vertex*> vertices;
};

#endif
