#ifndef WRITERESULT_H
#define WRITERESULT_H
#include <iostream>
#include <fstream>
#include "Graph.h"
#include "FlightEdgeDict.h"

class WriteResult
{
private:
    Graph graph;
    FlightEdgeDict dict;
    int opt_num_pilot;
    std::vector<std::vector<int>> pilot_routes;

    void process(int src, std::vector<int>& route);

public:
    WriteResult(const Graph& graph, const FlightEdgeDict& dict);
    ~WriteResult();
    
    void process();

    bool writeToFile(std::string path) const;
    void print() const;
};
#endif