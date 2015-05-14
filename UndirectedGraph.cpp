#include "UndirectedGraph.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"



void UndirectedGraph::addEdge(const std::string &from,
		const std::string &to, unsigned int cost, unsigned int length){
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

unsigned int totalCostEdge() const{
    double totalCost = 0;

	for(auto it = vertices.begin(); it != vectices.end(); ++it){
        totalCost += it->second->totalCostVert();
    }

//NEEDS WORK v
unsigned int totalLatencyEdge(const std::string &from){

    double totalLatency = 0;

    for(auto it = vertices.begin(); it != vertices.end(); ++it){
        totalLatency += it->second->distance
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
