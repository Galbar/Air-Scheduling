#include <iostream>
#include "WriteResult.h"

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
    int size = 8;
    int adj_matrix[size*size];
    init(adj_matrix, size);
    adj_matrix[pos(0, 1, size)] = 1;
    adj_matrix[pos(0, 3, size)] = 1;
    adj_matrix[pos(0, 5, size)] = 1;
    adj_matrix[pos(1, 2, size)] = 1;
    adj_matrix[pos(2, 3, size)] = 1;
    adj_matrix[pos(2, 7, size)] = 1;
    adj_matrix[pos(3, 4, size)] = 1;
    adj_matrix[pos(4, 7, size)] = 1;
    adj_matrix[pos(5, 6, size)] = 1;
    adj_matrix[pos(6, 7, size)] = 1;

    Graph g = Graph(adj_matrix, size, 0, 7);
    g.setEdgeFlow(EdgeId(0, 1), 1);
    g.setEdgeFlow(EdgeId(1, 2), 1);
    g.setEdgeFlow(EdgeId(2, 3), 1);
    g.setEdgeFlow(EdgeId(3, 4), 1);
    g.setEdgeFlow(EdgeId(4, 7), 1);
    g.setEdgeFlow(EdgeId(0, 5), 1);
    g.setEdgeFlow(EdgeId(5, 6), 1);
    g.setEdgeFlow(EdgeId(6, 7), 1);

    auto f = std::vector<Flight>();
    f.push_back(Flight(0, 1, 50, 100));
    f.push_back(Flight(1, 2, 75, 120));
    f.push_back(Flight(2, 0, 0, 35));
    FlightEdgeDict fed = FlightEdgeDict(f);
    fed.addEdgeToFlight(0, EdgeId(3, 4));
    fed.addEdgeToFlight(1, EdgeId(5, 6));
    fed.addEdgeToFlight(2, EdgeId(1, 2));

    WriteResult wr = WriteResult(g, fed);
    wr.process();
    wr.writeToFile("result.txt");
    wr.print();
    return 0;
}
