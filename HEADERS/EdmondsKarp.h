#ifndef EDMONDSKARP_H
#define EDMONDSKARP_H
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include "Graph.h"

class EdmondsKarp{
public:
	EdmondsKarp(const Graph& graph);
	~EdmondsKarp();

	bool isMaxFlow();
	const Graph& getResult();
	void solve();

private:
	Graph G;
	
	bool bfs(std::vector<int>& parent);
	void augment(std::vector<int>& parent);
	int getBottleneck(std::vector<int>& parent);
	

};
#endif
