#include "UndirectedGraph.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"



void UndirectedGraph::addEdge(const std::string &from,
		const std::string &to, unsigned int cost, unsigned int length){
	//Find to and from
	std::unordered_map<std::string, Vertex*>::const_iterator tempTo = verticies.find(to);
	std::unordered_map<std::string, Vertex*>::const_iterator tempFrom = vertices.find(from);
	

    //If to vertex doesn't exist, create one
	if(tempTo == vertices.end()){
		Vertex *v = new Vertex(to);
		verticies[to] = v;
	}

    //If from vertex does not exist, create one
	if(tempFrom == vertices.end()){
		Vertex *v = new Vertex(from);
		vertices[from] = v;
	}

	
	Vertex *startPoint = vertices.find(from)->second;
	Vertex *endPoint = verticies.find(to)->to;
 	
	//Create edges
	Edge *edgeSE = new Edge(startPoint, endPoint, startPoint->cost, startPoint->length);
	Edge *edgeES = new Edge(endPoint, startPoint, endPoint->cost, endPoint->length);

	edges[endPoint->name] = edgeSE;
	edges[startPoint->name] = edgeES;

}

unsigned int totalCost() const{
    double totalCost = 0;

	for(auto it = vertices.begin(); it != vectices.end(); ++it){
        totalCost += it->second->totalCostVert();
    }
    return totalCost;
}



unsigned int totalLatency(const std::string &from) {
   
    //Define infinity and total latency value
    const unsinged int infinity = std:numeric_limits<int>::max();
    unsigned totalLat = 0;

    //Holds mininum value found by Dijkstras Algorithm
    std::vector<unsigned int> latVec;

    //Set all vertices distance to infinity and visted to false
    for(auto it=vertices.begin(); it != vertices.end(); ++it) {
        it->second->distance = infinity;
        it->second->visited = false;
    }

    std::priority_queue<vertex*, unsigned int>,
        std::vector<std::pair<Vertex*, unsigned int >>,
        DijkstraVertexComparator> pq;
    
    //Define vertex we start from
    Vertex* start = vertices[from];

    //Initialize starting vertex to 0 distance and visited
    start->distance = 0;
    start->visited = true;
    
    //Push into pq, also set to correect edge lengths in pairs
    for(auto it = start->edges.begin(); it != start->edgesLat.end(); ++it) {
        Vertex* temp = it->second->to;
        temp->distance = e->second->length;
        pq.push(std::make_pair(to, to->distance));
    }


    while(!pq.empty()) {
        std::pair<vertex*, unsigned int> tempPair = pq.top();
        pq.pop();

        Vertex* tempVert = tempPair->first;

        if(tempVert->visited == false) {
            curr->visited = true;
            latVec.insert(curr->distance);

            for(auto it = curr->edges.begin(); it != curr->edges.end(); ++it) {
                unsigned int tempLat = 0;
                Vertex* to = it->second->to;
                if(to->visited == false){
                    newLat = tempVert->distance + it->second.length;

                    if(newLat < to->distance) {
                        to->distance = newLat;
                        pq.push(std::make_pair(to, to->distance));
                    }
                }
            }
         } 
    }

    for(auto it = latVec.begin(); it != latVec.end(); ++it) totalLat += it;

    return totalLat;
}


unsigned int totalLatency(){

    double totalLatency = 0;

    for(auto it = vertices.begin(); it != vertices.end(); ++it){
        totalLatency += this->totalLatency(it->first);
    }
    return totalLatency;
}

UndirectedGraph UndirectedGraph::mst() {
    
    UndirectedGraph minGraph;
    std:priority_queue<Edge, std::vector<Edge>> pq;
    
    //Set all vertices to not visited
    for(auto it=vertices.begin(); it !=vertices.end(); ++it) {
        it->second->visited = false;
    }
    
    //Set first vertex to visited
    std:unordered_map<std::string,Vertex*>::const_iterator firstIt = vertices.begin();
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

        if(edgeTemp->to->visited != true) {
            
            //Set to visited
            edgeTemp->to->visited = true;
            
            //Create edge in the MST
            minGraph.addEdge(edgeTemp->from->name, edgeTemp->to->name,
                    edgeTemp.cost, edge.length);

            //Add the new edges to pq
            for(auto it = edgeTemp->to->edges.begin();
                    it != edgeTemp->to->edges.end(); ++it) {
                if(it->second->to->visited == false) pq.push(it->second);
            }
            

        }
        else continue;
    }

    return minGraph;


}
