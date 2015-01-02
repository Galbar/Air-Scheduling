#ifndef EDMONDSKARP_H
#define EDMONDSKARP_H
#include <iostream>
#include <vector>
#include <queue>
#include "Graph.h"

class EdmondsKarp{
public:
	EdmondsKarp(const Graph& graph);
	~EdmondsKarp();

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
