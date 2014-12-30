#include <iostream>
#include "Graph.h"

Graph::Graph (int adj_matrix[], int size)
{
    vertex = std::vector<Vertex>(size);
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            int cap = adj_matrix[pos(j, i, size)];
            if (cap == 0) continue;
            Edge e = Edge(j, i, cap);
            EdgeId edgeId = EdgeId(j, i);
            vertex[j].addOutwardEdge(edgeId);
            vertex[i].addInwardEdge(edgeId);
            edges.insert(std::pair<EdgeId, Edge>(edgeId, e));
        }
    }
}

Graph::~Graph ()
{

}

int Graph::pos(int orig, int dest, int size)
{
    return orig + dest * size;
}

const Edge& Graph::getEdge(EdgeId eId) const
{
    return edges.find(eId)->second;
}

Edge& Graph::getEdge(EdgeId eId)
{
    return edges.find(eId)->second;
}

// Vertex stuff
const std::vector<EdgeId>& Graph::getVertexInwardEdges(int id) const
{
    return vertex[id].getInwardEdges();
}

const std::vector<EdgeId>& Graph::getVertexOutwardEdges(int id) const
{
    return vertex[id].getOutwardEdges();
}

// Edge stuff
int Graph::getEdgeOrigin(EdgeId eId) const
{
    return getEdge(eId).getOrigin();
}

int Graph::getEdgeDestination(EdgeId eId) const
{
    return getEdge(eId).getDestination();
}

int Graph::getEdgeCapacity(EdgeId eId) const
{
    return getEdge(eId).getCapacity();
}

int Graph::getEdgeFlow(EdgeId eId) const
{
    return getEdge(eId).getFlow();
}

int Graph::getEdgeResidualFlow(EdgeId eId) const
{
    return getEdge(eId).getResidualFlow();
}

void Graph::setEdgeFlow(EdgeId eId, int new_flow)
{
    getEdge(eId).setFlow(new_flow);
}

// Graph stuff
int Graph::getNumVertex () const
{
    return vertex.size();
}

int Graph::getNumEdges () const
{
    return edges.size();
}

void Graph::getAdjacencyMatrix(int mat[])
{
    int size = getNumVertex();
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            EdgeId eId = EdgeId(j, i);
            if (edgeExists(eId))
                mat[pos(j, i, size)] = getEdge(eId).getCapacity();
            else
                mat[pos(j, i, size)] = 0;
        }
    }
}

bool Graph::edgeExists(EdgeId eId) const
{
    return (edges.find(eId) != edges.end());
}
