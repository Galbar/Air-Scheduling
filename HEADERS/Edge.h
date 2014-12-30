#ifndef EDGE_H
#define EDGE_H


class Edge
{
    friend class Graph;
private:
    int origin, destination, capacity, flow;
public:
    // la capacidad es el flujo máximo que puede pasar por el arco
    Edge(int orig, int dest, int capacity);
    ~Edge();
    
    int getOrigin() const;
    int getDestination() const;
    int getCapacity() const;
    int getFlow() const;
    int getResidualFlow() const;
    
    void setFlow(int new_flow);
};
#endif