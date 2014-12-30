#include "Vertex.h"

Vertex::Vertex()
{

}

Vertex::~Vertex()
{

}

void Vertex::addInwardEdge(EdgeId eId)
{
    inwardEdges.push_back(eId);
}

void Vertex::addOutwardEdge(EdgeId eId)
{
    outwardEdges.push_back(eId);
}

const std::vector<EdgeId>& Vertex::getInwardEdges() const
{
    return inwardEdges;
}

const std::vector<EdgeId>& Vertex::getOutwardEdges() const
{
    return outwardEdges;
}
