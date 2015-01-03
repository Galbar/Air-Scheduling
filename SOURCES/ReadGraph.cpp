#include "ReadGraph.h"

ReadGraph::ReadGraph(){

}


void ReadGraph::read(){
	int r,d,t,l;
	flights = std::vector<Flight>(0,Flight(0,0,0,0));
	while(std::cin >> r >> d >> t >> l){
		Flight f = Flight(r,d,t,l);
		flights.push_back(f);
	}
	numFlights = flights.size();
	makeAdjMatrix();
}

void ReadGraph::makeAdjMatrix(){
	int n = 2*numFlights+2;
	adjMatrix=std::vector<constraints>((n)*(n),std::make_pair(0,0));

	weights = std::vector<int>(n,0);


	for(int i = 0; i < n-2; i+=2){
		adjMatrix[pos(i+1,i,n)] = constraints(1,1);
	}
	for(int i = 0; i < numFlights; ++i){
		for(int j = 0; j < numFlights; ++j){
			if(flights[i].getDestination() == flights[j].getOrigin()
				and flights[i].getArrivalTime()+15 < flights[j].getTakeoffTime()){
				adjMatrix[pos(2*j,2*i+1,n)] = constraints(0,1);
			}
		}
	}
	

	for(int i = 0; i < n-2; i+=2){
		
		adjMatrix[pos(i,n-2,n)] = constraints(0,1);
	}
	for(int i = 0; i < n-2; i+=2){
		adjMatrix[pos(n-1, i+1,n)] = constraints(0,1);

	}
}

int ReadGraph::pos(int i, int j, int n){
	return (n)*i+j;
}



const std::vector<Flight>& ReadGraph::getFlights(){
	return flights;
}

int ReadGraph::getNumFlights(){
	return numFlights;
}
/*
const std::vector<int>& ReadGraph::getAdjMatrix(){
	return adj;
}
*/

const std::vector<constraints>& ReadGraph::getRawAdjMatrix(){
	return adjMatrix;
}

int ReadGraph::getSize(){
	return 2*numFlights+4;
}

int ReadGraph::getSink(){
	return 2*numFlights+3;
}

int ReadGraph::getSource(){
	return 2*numFlights+2;
}

void ReadGraph::parametrize(int adj[], int k){

	int n = 2*numFlights+4;

	adjMatrix[pos(n-3,n-4,n-2)].second = k;
	for(int i = 0; i < n*n; ++i){
		adj[i] = 0;
	}
	weights = std::vector<int>(2*numFlights+4,0);
	weights[2*numFlights] = -k;
	weights[2*numFlights+1] = k;
	
	removeLowerBounds(adj,n);
	removeWeights(adj,n);


}




void ReadGraph::removeLowerBounds(int adj[],int n){
	for(int i = 0; i < n-2; ++i){
		int L = 0;
		for(int j = 0; j < n-2; ++j){
			L += adjMatrix[pos(i,j,n-2)].first;
			L -= adjMatrix[pos(j,i,n-2)].first;
		}
		weights[i] = weights[i]-L;
	}

	for(int i = 0; i < n-2; ++i){
		for(int j = 0; j < n-2; ++j){
			adj[pos(j,i,n)] = adjMatrix[pos(j,i,n-2)].second - adjMatrix[pos(j,i,n-2)].first;
		}
	}

}

void ReadGraph::removeWeights(int adj[], int n){
	for(int i = 0; i < n-2; ++i){
		if(weights[i] > 0){
			adj[pos(n-1,i,n)] = weights[i];
		}
		else if(weights[i] < 0){
			adj[pos(i,n-2,n)] = -weights[i];
		}
	}
}