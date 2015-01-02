#include <iostream>
#include <vector>
#include "Graph.h"
#include "Flight.h"
#include "FlightEdgeDict.h"

typedef std::pair<int,int> constraints;

class ReadGraph{
private:
	std::vector<Flight> flights;
	std::vector<constraints> adjMatrix;

	int numFlights;


	std::vector<int> adj;
	std::vector<int> weights;



	void makeAdjMatrix();
	inline int pos(int i,int j);
	void removeLowerBounds(int n);
	void removeWeights(int n);

public:
	ReadGraph();
	void read();


	const std::vector<Flight>& getFlights();
	const std::vector<int>& getAdjMatrix();
	int getSize();
	int getSource();
	int getSink();


	void parametrize(int k);
};