#ifndef GRAPH_H
#define GRAPH_H
#include "Vertex.h"
#include "Edge.h"


class Graph
{
private:
    Vertex v;
    Edge e;
public:
    // adj_matrix es un array de tamaño size*size que representa
    // la matriz de adyacencia. Dónde adj_matrix[x+y*size]
    // es el valor de la capacidad del arco que va de x a y
    // (si es 0 no hay arco)
    Graph(int adj_matrix[], int size);
    ~Graph();

    Vertex& getVertex(int id);
    const Vertex& getVertex(int id) const;

    Edge& getEdge(int orig, int dest);
    const Edge& getEdge(int orig, int dest) const;

    int getNumVertex() const;
    int getNumEdges() const;
};
#endif