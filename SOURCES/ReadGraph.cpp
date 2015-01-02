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
	adjMatrix=std::vector<constraints>((2*numFlights+2)*(2*numFlights+2),std::make_pair(0,0));

	weights = std::vector<int>(2*numFlights+2,0);


	for(int i = 1; i < numFlights+1; i+=2){
		adjMatrix[pos(i,i+1)] = constraints(1,1);
	}

	for(int i = 1; i < numFlights+1; ++i){
		for(int j = 1; j < numFlights+1; ++j){
			if(flights[i-1].getDestination() == flights[j-1].getOrigin()
				and flights[i-1].getArrivalTime()+15 < flights[j-1].getTakeoffTime()){
				adjMatrix[pos(2*i+1,2*j)] = constraints(0,1);
			}
		}
	}


	for(int i = 2; i < numFlights*2; i+=2){
		
		adjMatrix[pos(0,i)] = constraints(0,1);
		adjMatrix[pos(2*numFlights+1,i+1)] = constraints(0,1);
	}

}

int ReadGraph::pos(int i, int j){
	return (2*numFlights+2)*i+j;
}



const std::vector<Flight>& ReadGraph::getFlights(){
	return flights;
}

const std::vector<int>& ReadGraph::getAdjMatrix(){
	return adj;
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

void ReadGraph::parametrize(int k){
	weights = std::vector<int>(2*numFlights+4,0);
	weights[0] = -k;
	weights[2*numFlights+1] = k;
	int n = 2*numFlights+4;
	adj = std::vector<int>(n*n);
	removeLowerBounds(n);
	removeWeights(n);

}




void ReadGraph::removeLowerBounds(int n){
	for(int i = 0; i < n-2; ++i){
		int L = 0;
		for(int j = 0; j < n-2; ++j){
			L += adjMatrix[i*n+j].first;
			L -= adjMatrix[i*n+j].first;
		}
		weights[i] = weights[i]-L;
	}

	for(int i = 0; i < n-2; ++i){
		for(int j = 0; j < n-2; ++j){
			adj[i*n+j] = adjMatrix[i*n+j].second - adjMatrix[i*n+j].first;
		}
	}


}

void ReadGraph::removeWeights(int n){
	for(int i = 0; i < n-2; ++i){
		if(weights[i] > 0){
			adj[i*n+n-1] = weights[i];
		}
		else if(weights[i] < 0){
			adj[(n-2)*n+i] = -weights[i];
		}
	}
}