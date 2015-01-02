#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H
#include <iostream>
#include <vector>
#include <queue>
#include "Graph.h"

class FordFulkerson{
public:
	FordFulkerson(const Graph& graph);
	~FordFulkerson();

	void ff();
	const Graph& getResult();
private:
	Graph G;
	bool bfs(std::vector<int>& parent);
	void augment(std::vector<int>& parent);
	int getBottleneck(std::vector<int>& parent);
	bool isMaxFlow();

};
#endif
