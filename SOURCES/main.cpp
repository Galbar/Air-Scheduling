#include <iostream>
#include "EdmondsKarp.h"
#include "ReadGraph.h"
#include "WriteResult.h"


void writeResult(Graph& Go, Graph& Gr, FlightEdgeDict& fed, bool file, char* outfile){
    
    WriteResult wr(Go, Gr, fed);
    wr.process();
    if(file){
        wr.writeToFile(std::string(outfile));
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
        std::cout << "Usage is: " << argv[0] << " [-i <infile>][-o <outfile>]" << std::endl;
        exit(0);
    }
    else if(argc == 3 or argc == 5){
        for (int i = 1; i < argc; i+=2) {
            if (i + 1 != argc){
                if (std::string(argv[i]) == "-o") {
                    outfile = argv[i+1];
                    isfileout = true;
                }
                else if (std::string(argv[i]) == "-i"){
                    infile = argv[i+1];
                    isfilein = true;
                }
                else if (std::string(argv[i]) == "-h")
                {
                    std::cout << "Usage is: " << argv[0] << " [-i <infile>][-o <outfile>]" << std::endl;
                    exit(0);
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


//binary search

    int n = rg.getSize();
    int i, j;
    i = 1;
    j = f;

    int mat[n*n];

    
    rg.parametrize(mat);
    

    while(not(i > j)){
        int k = (i+j)/2;


        
        rg.reallyParametrize(mat,k,n);


        std::vector<Flight> flights = rg.getFlights();
        FlightEdgeDict fed(flights);
        rg.makeFED(fed);

        int source = rg.getSource();
        int sink = rg.getSink();
        Graph G = Graph(mat,n,source,sink);
        EdmondsKarp ek = EdmondsKarp(G);

        ek.solve();



 
        if(ek.isMaxFlow())
        {
            if(k == i){
                Graph g = ek.getResult();
                int m[(n-2)*(n-2)];
                rg.getUpperBoundsRawAdjMatrix(m);
                Graph G = Graph(m,n-2,source-2,sink-2);
                for(int i = 0; i < n; ++i){
                    for(int j = 0; j < n; ++j){
                        if(g.edgeExists(EdgeId(j,i))){
                            std::cout << g.getEdgeFlow(EdgeId(j,i)) << ' ';
                        }
                        else{
                            std::cout << "0 ";
                        }
                    }
                    std::cout << std::endl;
                }
                writeResult(G, g, fed, isfileout, outfile);
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
