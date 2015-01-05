#include <iostream>
#include "EdmondsKarp.h"
#include "ReadGraph.h"
#include "WriteResult.h"


void writeResult(Graph& G, std::vector<Flight>& flights, bool file, char* outfile){
	FlightEdgeDict fed(flights);
	WriteResult wr(G, fed);
	wr.process();
	if(file){
		wr.writeToFile(outfile);
	}
	else{
		wr.print();
	}
}





int main (int argc, char* argv[])
{
	char* outfile;
	bool isfileout = false;
	char* infile;
	bool isfilein = false;
	if (argc == 2 or argc == 4 or argc > 5) {
        std::cout << "Usage is [-i <infile>][-o <outfile>]" << std::endl;
        std::cin.get();
        exit(0);
    }
    else if(argc == 3 or argc == 5){
        for (int i = 1; i < argc; i+=2) {
            if (i + 1 != argc){
                if (std::string(argv[i]) == "-o") {
                    outfile = argv[i+1];
                    isfileout = true;
                }
                if(std::string(argv[i]) == "-i"){
                	infile = argv[i+1];
                	isfilein = true;
                }
                else {
                    std::cout << "Invalid arguments" << std::endl;
                    exit(0);
                }
            }
        }
    }
    else{
    	isfilein = isfileout = false;
    }




	ReadGraph rg;

	if(isfilein){
		rg.readFromFile(infile);
	}
	else{
		rg.read();
	}
	
	int f = rg.getNumFlights();
	std::cout << f << std::endl;


//binary search

	int n = rg.getSize();
	int i, j;
	i = 1;
	j = f;
	while(not(i > j)){
        int k = (i+j)/2;

        int mat[n*n];

		rg.parametrize(mat,k);


		std::vector<Flight> flights = rg.getFlights();

		int source = rg.getSource();
		int sink = rg.getSink();
		Graph G = Graph(mat,n,source,sink);
		EdmondsKarp ek = EdmondsKarp(G);

		ek.solve();
		
 
        if(ek.isMaxFlow())
        {
        	if(k == i){
        		Graph g = ek.getResult();
        		//writeResult(g,flights,isfileout,outfile);
        		std::cout << k << std::endl;
        		break;
        		
        	}
        	else{
        		j = k;
        	}
        }
        else
        {
        	i = k+1;
        }
    }
    
}
