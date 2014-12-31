#ifndef FLIGHT_EDGE_DICT_H
#define FLIGHT_EDGE_DICT_H
#include <utility>
#include <vector>
#include <unordered_map>
#include "hash_pair.h"
#include "Flight.h"

typedef std::pair<int, int> EdgeId;

class FlightEdgeDict
{
private:
	std::vector<Flight> flights;
	std::unordered_map<EdgeId, int> edgeToFlight;
	std::vector<std::vector<EdgeId>> flightToEdges;

public:
	FlightEdgeDict (const std::vector<Flight>& flights);
	~FlightEdgeDict ();
	void addEdgeToFlight (int flightId, const EdgeId& eId);
	int getFlightByEdge (const EdgeId& eId);
	const std::vector<EdgeId>& getEdgesByFlight (int id) const;
	const Flight& getFlight (int id) const;
	bool isFlight (const EdgeId& eId) const;
	
};
#endif