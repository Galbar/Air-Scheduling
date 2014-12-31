#include "FlightEdgeDict.h"

FlightEdgeDict::FlightEdgeDict (const std::vector<Flight>& flights):
flights(flights)
{
	flightToEdges = std::vector<std::vector<EdgeId>>(flights.size(), std::vector<EdgeId>());
}

FlightEdgeDict::~FlightEdgeDict ()
{

}

void FlightEdgeDict::addEdgeToFlight (int flightId, const EdgeId& eId)
{
	flightToEdges[flightId].push_back(eId);
	edgeToFlight.insert(std::pair<EdgeId, int>(eId, flightId));
}

int FlightEdgeDict::getFlightByEdge (const EdgeId& eId)
{
	return edgeToFlight.find(eId)->second;
}

const std::vector<EdgeId>& FlightEdgeDict::getEdgesByFlight (int id) const
{
	return flightToEdges[id];
}

const Flight& FlightEdgeDict::getFlight (int id) const
{
	return flights[id];
}

bool FlightEdgeDict::isFlight (const EdgeId& eId) const
{
	return (edgeToFlight.find(eId) != edgeToFlight.end());
}
