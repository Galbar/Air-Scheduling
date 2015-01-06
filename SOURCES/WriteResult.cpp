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
    // EdgeId e = gr.getVertexOutwardEdges(gr.getSource())[0];
    // int src = gr.getEdgeDestination(e);
    // e = gr.getVertexInwardEdges(gr.getSink())[0];
    // int sink = gr.getEdgeOrigin(e);
    process(go.getSource(), go.getSink(), v);
}

void WriteResult::process(int src, int sink, std::vector<int>& route)
{
    if (src == sink)
    {
        if (route.size() != 0)
            pilot_routes.push_back(route);
    }
    else
    {
        bool is_origin_of_flight = false;
        // mirar si es origen y si lo es tratarlo
        for (EdgeId eId : go.getVertexOutwardEdges(src))
        {
            if (dict.isFlight(eId))
            {
                std::cout << "isFlight";
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
                    std::cout << "(active)";
                    route.push_back(dict.getFlightByEdge(eId));
                    process(vertex, sink, route);
                    route.pop_back();
                }
                std::cout << std::endl;
            }
        }
        // si no es origen de viaje, seguir por gr
        if (not is_origin_of_flight)
        {
            for(EdgeId eId : gr.getVertexOutwardEdges(src))
            {
                process(gr.getEdgeDestination(eId), sink, route);
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
