#ifndef VERTEX_H
#define VERTEX_H
#include <initializer_list>
#include <vector>


class Vertex
{
public:
	// Vertex v = {2, 3, 5, 8} -> v tiene como vecinos los vertices 2, 3, 5, 8
	Vertex(std::initializer_list<int> adj_list);
	Vertex(std::vector<int> adj_list);
	~Vertex();
	
	int getNeighbour(int i);
	int getNumNeighbours();
};
#endif