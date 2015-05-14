#include "UndirectedGraph.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"



void UndirectedGraph::addEdge(const std::string &to,
		const std::string &from, unsigned int cost, unsigned int length){
	//Find to and from
	std::unordered_map<std::string, Vertex*>::const_iterator tempTo = verticies.find(to);
	std::unordered_map<std::string, Vertex*>::const_iterator tempFrom = vertices.find(from);
	
	if(tempTo == vertices.end()){
		Vertex *v = new Vertex(to);
		Vertex *mst = new Vertex(from);
		//add
		verticies[to] = v;
		mst_vertices[to] = mst_v; 
	}

	if(tempFrom == vertices.end()){
		Vertex *v = new Vertex(from);
		Vertex *mst_v = new Vertex(from);
		//add
		vertices[from] = v;
		mst_vertices[to] = mst_v;
	}

	
	Vertex *startPoint = vertices.find(from)->second;
	Vertex *endPoint = verticies.find(to)->to;
 	
	//Create edges
	Edge *edgeSE = new Edge(startPoint, endPoint, startPoint->cost, startPoint->length);
	Edge *edgeES = new Edge(endPoint, startPoint, endPoint->cost, endPoint->length);

	edges[endPoint->name] = edgeSE;
	edges[startPoint->name] = edgeES;

}

unsigned int totalEdgeCost() const;

    unsigned int totalDistance(const std::string &from);

    void mst();