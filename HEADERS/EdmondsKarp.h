#ifndef EDMONDSKARP_H
#define EDMONDSKARP_H
#include "FordFulkerson.h"

class EdmondsKarp: public FordFulkerson{
public:
	EdmondsKarp(const Graph& graph);
	~EdmondsKarp();

private:
	virtual bool findPath(std::vector<int>& parent);

};
#endif
