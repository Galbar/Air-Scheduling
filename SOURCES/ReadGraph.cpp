#include "ReadGraph.h"

ReadGraph::ReadGraph(){

}


void ReadGraph::read(){
	int r,d,t,l;
	flights = std::vector<Flight>(0,Flight(0,0,0,0));
	while(std::cin >> r >> d >> t >> l){
		Flight f (r,d,t,l);
		flights.push_back(f);
	}
	numFlights = flights.size();
	makeAdjMatrix();

}


void ReadGraph::readFromFile(std::string path){
	std::ifstream infile;
    infile.open(path);

    int r,d,t,l;
    if (infile.good()){
		flights = std::vector<Flight>(0,Flight(0,0,0,0));
		while(infile >> r >> d >> t >> l){
			Flight f (r,d,t,l);
			flights.push_back(f);
		}
		numFlights = flights.size();
		makeAdjMatrix();
	}
	else{
		std::cerr << "Error opening file " << path << std::endl;
	}
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

const std::vector<constraints>& ReadGraph::getRawAdjMatrix(){
	return adjMatrix;
}


void ReadGraph::getUpperBoundsRawAdjMatrix(int adj[]){
	for(int i = 0; i < (2*numFlights+2)*(2*numFlights+2);++i){
		adj[i] = adjMatrix[i].second;
	}
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

void ReadGraph::parametrize(int adj[]){

	int n = 2*numFlights+4;

	for(int i = 0; i < n*n; ++i){
		adj[i] = 0;
	}
	weights = std::vector<int>(2*numFlights+4,0);
	weights[2*numFlights] = -1;
	weights[2*numFlights+1] = 1;
	
	removeLowerBounds(adj,n);
	removeWeights(adj,n);


}
void ReadGraph::reallyParametrize(int adj[], int k, int n){
	adj[pos(n-4,n-2,n)] = k;
	adj[pos(n-1,n-3,n)] = k;
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

void ReadGraph::makeFED(FlightEdgeDict& fed){
	for(int i = 0;i < numFlights; ++i){
		fed.addEdgeToFlight(i,EdgeId(2*i,2*i+1));
	}
}