#include <iostream>
#include <vector>
#include "Graph.h"

class FordFulkerson{
	public:
		Graph solve(Graph G);



		FordFulkerson::FordFulkerson();
		FordFulkerson::~FordFulkerson();
	
		bool ff(Graph& G);

	private:
		bool bfs(Graph& G, vector<int>& parent);
		void augment(Graph& G, vector<int>& parent);
		int getBottleneck(Graph& G, vector<int>& parent);
		bool isMaxFlow(Graph& G);

};