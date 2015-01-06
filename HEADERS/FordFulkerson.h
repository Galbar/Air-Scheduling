#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H
#include <vector>
#include <queue>
#include <limits>
#include "Graph.h"

class FordFulkerson{
public:
	FordFulkerson(const Graph& graph);
	virtual ~FordFulkerson();

	bool isMaxFlow();
	bool isMinimum();
	const Graph& getResult();
	void solve();

protected:
	Graph G;
	
	virtual bool findPath(std::vector<int>& parent);
	bool findPath(int src, std::vector<int>& route, std::vector<bool>& visited);
	void augment(std::vector<int>& parent);
	int getBottleneck(std::vector<int>& parent);

};
#endif
