#include "Graph.h"

Graph::Graph (int adj_matrix[], int size):
v({}),
e(Edge(0,0,0))
{}

Graph::~Graph ()
{

}

Vertex& Graph::getVertex (int id)
{
    return v;
}

const Vertex& Graph::getVertex (int id) const
{
    return v;
}


Edge& Graph::getEdge (int orig, int dest)
{
    return e;
}

const Edge& Graph::getEdge (int orig, int dest) const
{
    return e;
}


int Graph::getNumVertex () const
{
    return 0;
}

int Graph::getNumEdges () const
{
    return 0;
}

