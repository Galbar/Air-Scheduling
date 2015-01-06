#ifndef WRITERESULT_H
#define WRITERESULT_H
#include <iostream>
#include <fstream>
#include "Graph.h"
#include "FlightEdgeDict.h"

class WriteResult
{
private:
    Graph go, gr;
    FlightEdgeDict dict;
    std::vector<std::vector<int>> pilot_routes;

    void process(int src, int sink, std::vector<int>& route);

public:
    WriteResult(const Graph& graphOriginal, const Graph& graphResult, const FlightEdgeDict& dict);
    ~WriteResult();
    
    void process();

    bool writeToFile(std::string path) const;
    void print() const;
};
#endif