#include <iostream>
#include "Graph.h"

int pos (int orig, int dest, int size)
{
    return orig+dest*size;
}

void init (int mat[], int size)
{
    for (int i = 0; i < size*size; ++i)
        mat[i] = 0;
}

int main ()
{
    int size = 5;
    int adj_matrix[size*size];
    init(adj_matrix, size);
    adj_matrix[pos(0, 1, size)] = 1;
    adj_matrix[pos(0, 2, size)] = 3;
    adj_matrix[pos(1, 2, size)] = 5;
    adj_matrix[pos(1, 3, size)] = 4;
    adj_matrix[pos(4, 2, size)] = 7;
    adj_matrix[pos(4, 3, size)] = 9;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            std::cout << adj_matrix[pos(j,i,size)] << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    Graph g = Graph(adj_matrix, size);
    int s = g.getNumVertex();

    for (int i = 0; i < s; ++i)
    {
        std::vector<EdgeId> inward = g.getVertexInwardEdges(i);
        std::vector<EdgeId> outward = g.getVertexOutwardEdges(i);
        std::cout << "Vertex " << i << ":" << std::endl;
        std::cout << "\tInward: ";
        for (int j = 0; j < inward.size(); ++j)
        {
            std::cout << "(" << inward[j].first << "->" << inward[j].second << ", " << g.getEdgeFlow(inward[j]) << "/" << g.getEdgeCapacity(inward[j]) << ") ";
        }
        std::cout << std::endl << "\tOutward: ";
        for (int j = 0; j < outward.size(); ++j)
        {
            std::cout << "(" << outward[j].first << "->" << outward[j].second << ", " << g.getEdgeFlow(outward[j]) << "/" << g.getEdgeCapacity(outward[j]) << ") ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    int m[s*s];
    g.getAdjacencyMatrix(m);
    for (int i = 0; i < s; ++i)
    {
        for (int j = 0; j < s; ++j)
        {
            std::cout << m[pos(j, i, s)] << "\t";
        }
        std::cout << std::endl;
    }
    return 0;
}
