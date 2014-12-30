#ifndef VERTEX_H
#define VERTEX_H
#include <vector>

typedef std::pair<int, int> EdgeId;

class Vertex
{
    friend class Graph;
private:
    std::vector<EdgeId> inwardEdges;
    std::vector<EdgeId> outwardEdges;

    void addInwardEdge(EdgeId eId);
    void addOutwardEdge(EdgeId eId);
public:
    Vertex();
    ~Vertex();

    const std::vector<EdgeId>& getInwardEdges() const;
    const std::vector<EdgeId>& getOutwardEdges() const;
};
#endif