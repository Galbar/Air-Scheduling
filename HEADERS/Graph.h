#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <unordered_map>
#include "Vertex.h"
#include "Edge.h"

// Stuff for hashing std::pair<int, int>
template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
  template<typename S, typename T> struct hash<pair<S, T>>
  {
    inline size_t operator()(const pair<S, T> & v) const
    {
      size_t seed = 0;
      ::hash_combine(seed, v.first);
      ::hash_combine(seed, v.second);
      return seed;
    }
  };
}

typedef std::pair<int, int> EdgeId;

class Graph
{
private:
    std::vector<Vertex> vertex;
    std::unordered_map<EdgeId, Edge> edges;

    static inline int pos(int orig, int dest, int size);
public:
    // adj_matrix es un array de tamaño size*size que representa
    // la matriz de adyacencia. Dónde adj_matrix[x+y*size]
    // es el valor de la capacidad del arco que va de x a y
    // (si es 0 no hay arco)
    Graph(int adj_matrix[], int size);
    ~Graph();

    // Vertex stuff
    int getVertexNeighbourId(int id, int i) const;
    int getVertexNumNeighbours(int id) const;
    std::vector<EdgeId> getVertexInnerEdges(int id) const;
    std::vector<EdgeId> getVertexOuterEdges(int id) const;

    // Edge stuff
    int getEdgeOrigin(EdgeId eId) const;
    int getEdgeDestination(EdgeId eId) const;
    int getEdgeCapacity(EdgeId eId) const;
    int getEdgeFlow(EdgeId eId) const;
    int getEdgeResidualFlow(EdgeId eId) const;

    void setEdgeFlow(EdgeId eId, int new_flow);

    // Graph stuff
    int getNumVertex() const;
    int getNumEdges() const;
    void getAdjacencyMatrix(int mat[]);
    bool edgeExists(EdgeId eId) const;
};
#endif