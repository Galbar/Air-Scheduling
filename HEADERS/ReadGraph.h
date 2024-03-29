#include <iostream>
#include <vector>
#include <fstream>
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
	void readFromFile(std::string path);


	void getUpperBoundsRawAdjMatrix(int adj[]);
	const std::vector<Flight>& getFlights();
/*	const std::vector<int>& getAdjMatrix();*/
	const std::vector<constraints>& getRawAdjMatrix();
	int getSize();
	int getSource();
	int getSink();
	int getNumFlights();
	void makeFED(FlightEdgeDict& fed);


	void parametrize(int adj[]);
	void parametrize(int adj[], int k);
	void reallyParametrize(int adj[], int k, int n);
};