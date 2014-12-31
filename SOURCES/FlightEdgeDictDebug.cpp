#include <iostream>
#include "FlightEdgeDict.h"

void printFlight(const Flight& f)
{
    std::cout << "Origin: " << f.getOrigin() << std::endl;
    std::cout << "Destination: " << f.getDestination() << std::endl;
    std::cout << "TakeoffTime: " << f.getTakeoffTime() << std::endl;
    std::cout << "ArrivalTime: " << f.getArrivalTime() << std::endl;
}

void printEdge(const EdgeId& eId)
{
    std::cout << "(" << eId.first << "->" << eId.second << ")" << std::endl;
}

int main ()
{
    auto f = std::vector<Flight>();
    f.push_back(Flight(0, 1, 0, 100));
    f.push_back(Flight(1, 2, 0, 100));
    f.push_back(Flight(2, 3, 0, 100));
    FlightEdgeDict fed = FlightEdgeDict(f);
    fed.addEdgeToFlight(0, EdgeId(0, 1));
    fed.addEdgeToFlight(1, EdgeId(1, 3));
    fed.addEdgeToFlight(1, EdgeId(2, 3));
    fed.addEdgeToFlight(2, EdgeId(3, 4));

    int fId = fed.getFlightByEdge(EdgeId(2, 3));
    std::cout << "Flight " << fId << ":" << std::endl;
    printFlight(fed.getFlight(fId));
    fId = fed.getFlightByEdge(EdgeId(1, 3));
    std::cout << "Flight " << fId << ":" << std::endl;
    printFlight(fed.getFlight(fId));

    auto v = fed.getEdgesByFlight(fId);
    for(auto eId : v)
    {
        printEdge(eId);
    }
    return 0;
}
