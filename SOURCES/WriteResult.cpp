#include "WriteResult.h"

WriteResult::WriteResult(const Graph& graph, const FlightEdgeDict& dict):
graph(graph),
dict(dict)
{}

WriteResult::~WriteResult()
{

}

void WriteResult::process()
{
    std::vector<int> v;
    process(graph.getSource(), v);
}

void WriteResult::process(int src, std::vector<int>& route)
{
    if (src == graph.getSink())
    {
        pilot_routes.push_back(route);
    }
    else
    {
        for (EdgeId eId : graph.getVertexOutwardEdges(src))
        {
            // Add flight to route
            if (dict.isFlight(eId))
            {
                route.push_back(dict.getFlightByEdge(eId) + 1);
            }
            // Process edge
            while (graph.getEdgeFlow(eId) != 0)
            {
                process(eId.second, route);
                graph.setEdgeFlow(eId, graph.getEdgeFlow(eId) - 1);
            }
            // Remove flight from route
            if (dict.isFlight(eId))
            {
                route.pop_back();
            }
        }
    }
}

bool WriteResult::writeToFile(std::string path) const
{
    std::ofstream out_file;
    out_file.open(path);
    if (out_file.good())
    {
        out_file << pilot_routes.size() << std::endl;
        for (unsigned int i = 0; i < pilot_routes.size(); ++i)
        {
            for (unsigned int j = 0; j < pilot_routes[i].size(); ++j)
            {
                if (j != 0)
                    out_file << " ";
                out_file << pilot_routes[i][j];
            }
            out_file << std::endl;
        }
        return true;
    }
    return false;
}

void WriteResult::print() const
{
    std::cout << pilot_routes.size() << std::endl;
    for (unsigned int i = 0; i < pilot_routes.size(); ++i)
    {
        for (unsigned int j = 0; j < pilot_routes[i].size(); ++j)
        {
            if (j != 0)
                std::cout << " ";
            std::cout << pilot_routes[i][j];
        }
        std::cout << std::endl;
    }
}
