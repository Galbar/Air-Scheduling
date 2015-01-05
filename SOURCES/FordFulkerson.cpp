#include <iostream>
#include "FordFulkerson.h"

FordFulkerson::FordFulkerson(const Graph& graph):G(graph){
	//solve();
}

FordFulkerson::~FordFulkerson(){}

bool FordFulkerson::findPath(int src, std::vector<int>& parent){
    if (src == G.getSink())
    {
        return true;
    }
    else
    {
        for (EdgeId eId : G.getVertexOutwardEdges(src))
        {
            if (G.getEdgeResidualFlow(eId) <= 0) continue;
            parent[G.getEdgeDestination(eId)] = G.getEdgeOrigin(eId);
            if (findPath(eId.second, parent))
                return true;
            parent[G.getEdgeDestination(eId)] = -1;
        }
        return false;
    }
}

bool FordFulkerson::findPath(std::vector<int>& parent){
	int s = G.getSource();
    bool b = findPath(s, parent);/*
    for (int i = 0; i < parent.size(); ++i)
    {
        std::cout << parent[i] << " ";
    }
    std::cout << std::endl;*/
    return b;
}

void FordFulkerson::augment(std::vector<int>& parent){
	int x = getBottleneck(parent);
	int v = G.getSink();
	while(parent[v] != -1){
		EdgeId bw = EdgeId(v,parent[v]);
		EdgeId fw = EdgeId(parent[v],v);
		if(G.edgeExists(fw)){
			G.setEdgeFlow(fw,G.getEdgeFlow(fw)+x);
		}
		else{
			G.setEdgeFlow(bw,G.getEdgeFlow(bw)-x);
		}
		v = parent[v];
	}
}


int FordFulkerson::getBottleneck(std::vector<int>& parent){
	int bottleneck = std::numeric_limits<int>::max();
	int v = G.getSink();
	while(parent[v] != -1){
		EdgeId bw = EdgeId(v,parent[v]);
		EdgeId fw = EdgeId(parent[v],v);
		int x;
		if(G.edgeExists(fw)){
			
			x = G.getEdgeResidualFlow(fw);
		}
		else{
			
			x = G.getEdgeFlow(bw);
		}
		if(x < bottleneck) bottleneck = x;
		v = parent[v];
	}
    return bottleneck;
}


bool FordFulkerson::isMaxFlow(){
	int t = G.getSink();
	std::vector<EdgeId> incident = G.getVertexInwardEdges(t);
	for(unsigned int u = 0; u < incident.size(); ++u){
		if(G.getEdgeResidualFlow(incident[u]) > 0){
			
            return false;
		}
	}
    return true;
}


bool FordFulkerson::isMinimum(){
	int source = G.getSource()-2;
	int sink = G.getSink()-2;
    if(G.getEdgeFlow(EdgeId(source,sink))>0) return false;
    return true;
}

void FordFulkerson::solve(){
    int i = 0;
    std::vector<int> parent(G.getNumVertex(), -1);
    while(findPath(parent)){
        augment(parent);
		++i;
	}
}

const Graph& FordFulkerson::getResult(){
    return G;
}
