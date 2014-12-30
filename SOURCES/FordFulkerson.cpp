#include "input.h"

FordFulkerson::FordFulkerson(){

}

FordFulkerson::~FordFulkerson(){}

bool FordFulkerson::bfs(Graph& G, vector<int>& parent){
	int s = G.getSource();
	vector<bool> visited(G.getNumVertex(),false);


	queue<int> Q;

	Q.push(s);
	visited[s] = true;
	parent[s] = -1;
	while(not Q.empty()){
		int u = Q.front();
		Q.pop();

		vector<EdgeId> *neighbors = G.getVertexOutwardEdges(u);
		vector<EdgeId> *residual = G.getVertexInwardEdges(u);
		for(int i = 0; i < *neighbors.size(); ++i){
			EdgeId e = *neighbors[i];
			int v = G.getEdgeDestination(e);
			if(not visited[v]){
				if(G.getResidualFlow(e) > 0){
					Q.push(v);
					parent[v] = u;
					visited[v] = true;
				}
			}
		}
		for(int i = 0; i < *residual.size(); ++i){
			EdgeId e = *neighbors[i];
			int v = G.getEdgeOrigin(e);
			if(not visited[v]){
				if(G.getFlow(e) > 0){
					Q.push(v);
					parent[v] = u;
					visited[v] = true;
				}
			}
		}

	}
	return visited[G.getSink()];


}

void FordFulkerson::augment(Graph& G, vector<int>& parent){
	int x = getBottleneck(G,parent);
	int v = G.getSink();
	while(parent[v] != -1){
		EdgeId bw = EdgeId(v,parent[v]);
		EdgeId fw = EdgeId(parent[v],v);
		if(G.edgeExists(fw){
			G.setEdgeFlow(G.getEdgeFlow(fw)+x);
		}
		else{
			G.setEdgeFlow(G.getEdgeFlow(bw)-x);
		}
		v = parent[v];
	}

}


int FordFulkerson::getBottleneck(Graph& G, vector<int>& parent){
	int bottleneck = 0;
	int v = G.getSink();
	while(parent[v] != -1){
		EdgeId bw = EdgeId(v,parent[v]);
		EdgeId fw = EdgeId(parent[v],v);
		int x;
		if(G.edgeExists(fw)){
			x = getResidualFlow(fw);
		}
		else{
			x = getEdgeFlow(bw);
		}
		if(x > bottleneck) bottleneck = x;
		v = parent[v];
	}
	return bottleneck;
}


bool isMaxFlow(Graph& G){
	int t = G.getSink();
	vector<EdgeId> *incident = G.getVertexInwardEdges(t);
	for(int u = 0; u < *incident.size(); ++u){
		if(G.getResidualFlow(*incident[u]) > 0){
			return false
		}
	}
	return true;
}

bool FordFulkerson::ff(Graph& G){
	vector<int> parent(G.size());
	while(bfs(G,parent)){
		augment(G,parent);
	}
	return isMaxFlow(G);
}

