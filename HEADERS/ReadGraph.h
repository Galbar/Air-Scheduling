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


//	std::vector<int> adj;
	std::vector<int> weights;



	void makeAdjMatrix();
	static inline int pos(int i,int j, int n);
	void removeLowerBounds(int adj[], int n);
	void removeWeights(int adj[], int n);

public:
	ReadGraph();
	void read();


	const std::vector<Flight>& getFlights();
/*	const std::vector<int>& getAdjMatrix();*/
	const std::vector<constraints>& getRawAdjMatrix();
	int getSize();
	int getSource();
	int getSink();
	int getNumFlights();


	void parametrize(int adj[], int k);
};