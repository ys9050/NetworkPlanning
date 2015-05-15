#include "UndirectedGraph.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"

/**
 * Creates an edge within the graph, both to and from and from and to
 * are created.
 */
void UndirectedGraph::addEdge(const std::string &from,
		const std::string &to, unsigned int cost, unsigned int length){
	//Find to and from
	std::unordered_map<std::string, Vertex*>::const_iterator tempTo = vertices.find(to);
	std::unordered_map<std::string, Vertex*>::const_iterator tempFrom = vertices.find(from);
	

    //If to vertex doesn't exist, create one
	if(tempTo == vertices.end()){
		Vertex *v = new Vertex(to);
		vertices[to] = v;
	}

    //If from vertex does not exist, create one
	if(tempFrom == vertices.end()){
		Vertex *v = new Vertex(from);
		vertices[from] = v;
	}
    
	//Temporary pointer to to and from vertices
	Vertex *startPoint = vertices.find(from)->second;
	Vertex *endPoint = vertices.find(to)->second;
 	
	//Create Edges
	startPoint->edges[endPoint->name] = Edge(startPoint, endPoint, cost, length);
	endPoint->edges[startPoint->name] = Edge(endPoint, startPoint, cost, length);

}


/**
 * Returns the total cost of the UndirectedGraph
 * Calculates individual vertices' total cost to create edges
 * then sum them all
 */
unsigned int UndirectedGraph::totalCost() const{
    unsigned int totalCostt = 0;
    
    //Adds all cost from each of the vertices
	for(auto it = vertices.begin(); it != vertices.end(); ++it){
        totalCostt += it->second->totalCostVert();
    }


    return totalCostt/2;
}

/**
 * Returns the total latency of all vertex to all the otehrs
 * Uses the totalLatency with no argument
 * to get value of one vertex's total latency
 * then does this for all, then sum them together.
 */
unsigned int UndirectedGraph::totalLatency(const std::string &from) {
   
    //Define infinity and total latency value
    const unsigned int infinity = std::numeric_limits<unsigned int>::max();
    unsigned totalLat = 0;

    //Holds mininum value found by Dijkstras Algorithm
    std::vector<unsigned int> latVec;

    //Set all vertices distance to infinity and visted to false
    for(auto it=vertices.begin(); it != vertices.end(); ++it) {
        it->second->distance = infinity;
        it->second->visited = false;
    }

    std::priority_queue<std::pair<Vertex*, unsigned int>,
        std::vector<std::pair<Vertex*, unsigned int >>,
        DijkstraVertexComparator> pq;
    
    //Define vertex we start from
    Vertex* start = vertices[from];

    //Initialize starting vertex to 0 distance and visited
    start->distance = 0;
    start->visited = true;
    
    //Push into pq, also set to correect edge lengths in pairs
    for(auto it = start->edges.begin(); it != start->edges.end(); ++it) {
        Vertex* temp = it->second.to;
        temp->distance = it->second.length;
        pq.push(std::make_pair(temp, temp->distance));
    }


    while(!pq.empty()) {
        std::pair<Vertex*, unsigned int> tempPair = pq.top();
        pq.pop();

        Vertex* tempVert = tempPair.first;
        //Visit all the unvisted vertices
        if(tempVert->visited == false) {
            tempVert->visited = true;
            //Put the distance value into a vector of latency
            latVec.push_back(tempVert->distance);
            //If not visited, set the distance to the distance from the start vertex
            for(auto it = tempVert->edges.begin(); it != tempVert->edges.end(); ++it) {
                unsigned int newLat = 0;
                Vertex* toTemp = it->second.to;
                if(toTemp->visited == false){
                    newLat = tempVert->distance + it->second.length;
                    //If new distance value is better, than replace the original
                    if(newLat < toTemp->distance) {
                        toTemp->distance = newLat;
                        pq.push(std::make_pair(toTemp, toTemp->distance));
                    }
                }
            }
         } 
    }
    //Add all the latency from start vertex to all vertices together
    for(auto it = latVec.begin(); it != latVec.end(); ++it) totalLat += *it;
    
    //Return the total latency
    return totalLat;
}

/**
 * Returns the total latency from one vertex to all the others
 * The path from one to other vertices take the shortest path
 * via Dijkstras from the same method with 1 argument
 */
unsigned int UndirectedGraph::totalLatency() {

    unsigned int totalLatencyVal = 0;
    
    //add all the vertices totalLatency
    for(auto it = vertices.begin(); it != vertices.end(); ++it){
        totalLatencyVal += totalLatency(it->first);
    }
    return totalLatencyVal;

}

/**
 * Given a UndirectedGraph, returns a minimum spanning tree of that graph.
 * Uses Prim's
 */
UndirectedGraph UndirectedGraph::mst() {
    
    UndirectedGraph minGraph;
    std::priority_queue<Edge, std::vector<Edge>> pq;
    
    //Set all vertices to not visited
    for(auto it=vertices.begin(); it !=vertices.end(); ++it) {
        it->second->visited = false;
    }
    
    //Set first vertex to visited
    std::unordered_map<std::string,Vertex*>::const_iterator firstIt = vertices.begin();
    Vertex* first = firstIt->second;
    first->visited = true;
    

    //Push all edges in the first vertex to priorty queue
    for(auto it=first->edges.begin(); it != first->edges.end(); ++it) {
        pq.push(it->second);
    }

    
    while(!pq.empty()) {

        //Pop the edge with smallest cost
        Edge edgeTemp = pq.top();
        pq.pop();

        if(edgeTemp.to->visited != true) {
            
            //Set to visited
            edgeTemp.to->visited = true;
            
            //Create edge in the MST
            minGraph.addEdge(edgeTemp.from->name, edgeTemp.to->name,
                    edgeTemp.cost, edgeTemp.length);

            //Add the new edges to pq
            for(auto it = edgeTemp.to->edges.begin();
                    it != edgeTemp.to->edges.end(); ++it) {
                if(it->second.to->visited == false) pq.push(it->second);
            }
        }
    }
    //Return the min cost graph
    return minGraph;
}

 

