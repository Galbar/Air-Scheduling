#include "EdmondsKarp.h"

EdmondsKarp::EdmondsKarp(const Graph& graph):FordFulkerson(graph){
	//solve();
}

EdmondsKarp::~EdmondsKarp(){}

bool EdmondsKarp::findPath(std::vector<int>& parent){
	int s = G.getSource();
	std::vector<bool> visited(G.getNumVertex(),false);


	std::queue<int> Q;

	Q.push(s);

	visited[s] = true;
	parent[s] = -1;

	while(not Q.empty()){
		
		int u = Q.front();
		Q.pop();
		const std::vector<EdgeId>& neighbors = G.getVertexOutwardEdges(u);
		const std::vector<EdgeId>& residual = G.getVertexInwardEdges(u);
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
			EdgeId e = residual[i];
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
