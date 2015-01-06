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
    std::cerr << "Source: " << go.getSource() << std::endl;
    std::cerr << "Sink: " << go.getSink() << std::endl;
    process(go.getSource(), go.getSink(), v);
}

void WriteResult::process(int src, int sink, std::vector<int>& route)
{
    if (src >= sink)
    {
        std::cerr << "caso base" << std::endl;

        if (route.size() != 0)
            pilot_routes.push_back(route);
    }
    else
    {
        bool is_origin_of_flight = false;
        // mirar si es origen y si lo es tratarlo
        std::cerr << "no es caso base:" << std::endl;    
        const std::vector<EdgeId>& v = go.getVertexOutwardEdges(src);
        std::cerr << "es origen?" << std::endl;    
        for (int i = 0; i < v.size(); ++i)
        {
            std::cerr << "vecino #" << i << "/" << v.size() <<  std::endl;
            EdgeId eId = v[i];
            std::cerr << "Probando edge: " << eId.first << "->" << eId.second << std::endl;
            if (dict.isFlight(eId))
            {
                std::cerr << "vuelo encontrado";
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
                    std::cerr << "(tiene flujo)";
                    std::cerr << std::endl << "el flight: " << dict.getFlightByEdge(eId);
                    route.push_back(dict.getFlightByEdge(eId));
                    std::cerr << "llamada recursiva de vertice " << src << std::endl;
                    process(vertex, sink, route);
                    std::cerr << "vuelve llamada recursiva de vertice " << src << std::endl;
                    route.pop_back();
                }
                std::cerr << std::endl;
            }
        }
        // si no es origen de viaje, seguir por gr
        if (not is_origin_of_flight)
        {
            std::cerr << "no es origen de vuelo" << std::endl;    
            for(EdgeId eId : gr.getVertexOutwardEdges(src))
            {
                std::cerr << "el eid es" << std::endl;
                std::cerr << eId.first << ' ' << eId.second << std::endl;

                if(gr.getEdgeFlow(eId)>0){
                    std::cerr << "llamada recursiva para arco: " << eId.first << "->" << eId.second << std::endl;

                    process(gr.getEdgeDestination(eId), sink, route);
                    std::cerr << "vuelve llamada recursiva para arco: " << eId.first << "->" << eId.second << std::endl;

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
    std::cout << "the routes" << std::endl;
    //std::cout << pilot_routes.size() << std::endl;
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
