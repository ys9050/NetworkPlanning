#include "UndirectedGraph.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"



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

	
	Vertex *startPoint = vertices.find(from)->second;
	Vertex *endPoint = vertices.find(to)->second;
 	
	//Create Edges
	startPoint->edges[endPoint->name] = Edge(startPoint, endPoint, cost, length);
	endPoint->edges[startPoint->name] = Edge(endPoint, startPoint, cost, length);

}

unsigned int UndirectedGraph::totalCost() const{
    unsigned int totalCostt = 0;

	for(auto it = vertices.begin(); it != vertices.end(); ++it){
        totalCostt += it->second->totalCostVert();
    }


    return totalCostt;
}



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

        if(tempVert->visited == false) {
            tempVert->visited = true;
            latVec.push_back(tempVert->distance);

            for(auto it = tempVert->edges.begin(); it != tempVert->edges.end(); ++it) {
                unsigned int newLat = 0;
                Vertex* toTemp = it->second.to;
                if(toTemp->visited == false){
                    newLat = tempVert->distance + it->second.length;

                    if(newLat < toTemp->distance) {
                        toTemp->distance = newLat;
                        pq.push(std::make_pair(toTemp, toTemp->distance));
                    }
                }
            }
         } 
    }

    for(auto it = latVec.begin(); it != latVec.end(); ++it) totalLat += *it;

    return totalLat;
}


unsigned int UndirectedGraph::totalLatency() const {

    /*unsigned int totalLatencyVal = 0;

    for(auto it = vertices.begin(); it != vertices.end(); ++it){
        totalLatencyVal += totalLatency(it->first);
    }
    return totalLatencyVal;
*/
return 0;
}

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
        else continue;
    }

    return minGraph;


}
