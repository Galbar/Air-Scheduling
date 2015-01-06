#include "WriteResult.h"

WriteResult::WriteResult(const Graph& graphOriginal, const Graph& graphResult, const FlightEdgeDict& dict):
go(graphOriginal),
gr(graphResult),
dict(dict)
{}

WriteResult::~WriteResult()
{

}

void WriteResult::process()
{
    std::vector<int> v;
    process(go.getSource(), go.getSink(), v);
}

void WriteResult::process(int src, int sink, std::vector<int>& route)
{
    if (src >= sink)
    {
        if (route.size() != 0)
            pilot_routes.push_back(route);
    }
    else
    {
        bool is_origin_of_flight = false;
        // mirar si es origen y si lo es tratarlo
        const std::vector<EdgeId>& v = go.getVertexOutwardEdges(src);
        for (unsigned int i = 0; i < v.size(); ++i)
        {
            EdgeId eId = v[i];
            if (dict.isFlight(eId))
            {
                int vertex = go.getEdgeDestination(eId);
                bool is_flow = false;
                for (EdgeId e : gr.getVertexInwardEdges(vertex))
                {
                    is_flow = (0 < gr.getEdgeFlow(e));
                    if (is_flow) break;
                }
                if (is_flow)
                {
                    is_origin_of_flight = true;
                    route.push_back(dict.getFlightByEdge(eId));
                    process(vertex, sink, route);
                    route.pop_back();
                }
            }
        }
        // si no es origen de viaje, seguir por gr
        if (not is_origin_of_flight)
        {
            for(EdgeId eId : gr.getVertexOutwardEdges(src))
            {
                if(gr.getEdgeFlow(eId)>0){
                    process(gr.getEdgeDestination(eId), sink, route);
                }
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
            std::cout << pilot_routes[i][j]+1;
        }
        std::cout << std::endl;
    }
}
