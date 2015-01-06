#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <unordered_map>
#include "hash_pair.h"
#include "Vertex.h"
#include "Edge.h"


typedef std::pair<int, int> EdgeId;

class Graph
{
private:
	int source, sink;
    std::vector<Vertex> vertex;
    std::unordered_map<EdgeId, Edge> edges;

    static inline int pos(int orig, int dest, int size);
    inline Edge& getEdge(const EdgeId& eId);
    inline const Edge& getEdge(const EdgeId& eId) const;
public:
    // adj_matrix es un array de tamaño size*size que representa
    // la matriz de adyacencia. Dónde adj_matrix[x+y*size]
    // es el valor de la capacidad del arco que va de x a y
    // (si es 0 no hay arco)
    Graph(int adj_matrix[], int size, int source, int sink);
    ~Graph();

    // Vertex stuff
    const std::vector<EdgeId>& getVertexInwardEdges(int id) const;
    const std::vector<EdgeId>& getVertexOutwardEdges(int id) const;

    // Edge stuff
    int getEdgeOrigin(const EdgeId& eId) const;
    int getEdgeDestination(const EdgeId& eId) const;
    int getEdgeCapacity(const EdgeId& eId) const;
    int getEdgeFlow(const EdgeId& eId) const;
    int getEdgeResidualFlow(const EdgeId& eId) const;

    void setEdgeFlow(const EdgeId& eId, int new_flow);

    // Graph stuff
    int getSource() const;
    int getSink() const;
    int getNumVertex() const;
    int getNumEdges() const;
    void getAdjacencyMatrix(int mat[]) const;
    bool edgeExists(const EdgeId& eId) const;
};
#endif
