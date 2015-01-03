#include "ReadGraph.h"
#include <iostream>
#include <vector>


int main(){
	ReadGraph rd = ReadGraph();
	rd.read();
	std::vector<Flight> f = rd.getFlights();

	std::cout << "Flights" << std::endl;
	for(int i = 0; i < f.size(); ++i){
		std::cout << f[i].getOrigin() << ' ';
		std::cout << f[i].getDestination() << ' ';
		std::cout << f[i].getTakeoffTime() << ' ';
		std::cout << f[i].getArrivalTime() << ' ';
		std:: cout << std::endl;
	}
	std::vector<constraints> c = rd.getRawAdjMatrix();
	int flights =rd.getNumFlights();

	std::cout << "Non transformed matrix" << std::endl;
	for(int i = 0; i < 2*flights+2; ++i){
		for(int j = 0; j < 2*flights+2; ++j){
			std::cout << c[i*(2*flights+2)+j].first << '/';
			std::cout << c[i*(2*flights+2)+j].second << ' ';
		}
		std::cout << std::endl;
	}


	int k = 2;
	int n = rd.getSize();

	int x[n*n];

	rd.parametrize(x,k);
	

	std::cout << "size: " << n << std::endl;
	std::cout << "source: " << rd.getSource() << std::endl;
	std::cout << "sink: " << rd.getSink() << std::endl;
	std::cout << "number of flights: "<<rd.getNumFlights() << std::endl;
 	std::cout << "Parametrized adjacency matrix with k = " << k << std::endl;

	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			std::cout << x[i*n+j] << ' ';
		}
		std::cout << std::endl;
	}
}