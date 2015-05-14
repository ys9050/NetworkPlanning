#ifndef UNDIRECTEDGRAPH_HPP
#define UNDIRECTEDGRAPH_HPP

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

    unsigned int totalCostEdge() const;

    unsigned int totalLatency(const std::string &from);

    void mst();


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
    std::unordered_map<std::string, Vertex*> mst_vertices;
};

#endif
