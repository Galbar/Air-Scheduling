#include "FordFulkerson.h"

FordFulkerson::FordFulkerson(const Graph& graph):G(graph){
}

FordFulkerson::~FordFulkerson(){}

bool FordFulkerson::bfs(std::vector<int>& parent){
	int s = G.getSource();
	std::vector<bool> visited(G.getNumVertex(),false);


	std::queue<int> Q;

	Q.push(s);
	visited[s] = true;
	parent[s] = -1;
	while(not Q.empty()){
		int u = Q.front();
		Q.pop();

		std::vector<EdgeId> neighbors = G.getVertexOutwardEdges(u);
		std::vector<EdgeId> residual = G.getVertexInwardEdges(u);
		for(unsigned int i = 0; i < neighbors.size(); ++i){
			EdgeId e = neighbors[i];
			int v = G.getEdgeDestination(e);
			if(not visited[v]){
				if(G.getEdgeResidualFlow(e) > 0){
					Q.push(v);
					parent[v] = u;
					visited[v] = true;
				}
			}
		}
		for(unsigned int i = 0; i < residual.size(); ++i){
			EdgeId e = neighbors[i];
			int v = G.getEdgeOrigin(e);
			if(not visited[v]){
				if(G.getEdgeFlow(e) > 0){
					Q.push(v);
					parent[v] = u;
					visited[v] = true;
				}
			}
		}

	}
	return visited[G.getSink()];
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
	int bottleneck = 0;
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
		if(x > bottleneck) bottleneck = x;
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

void FordFulkerson::ff(){
	std::vector<int> parent(G.getNumVertex());
	while(bfs(parent)){
		augment(parent);
	}
}

const Graph& FordFulkerson::getResult(){
	return G;
}
