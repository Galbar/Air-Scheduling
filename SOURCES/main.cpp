#include <iostream>
#include "FordFulkerson.h"
#include "EdmondsKarp.h"
#include "ReadGraph.h"
#include "WriteResult.h"

void usage(char* argv[])
{
    std::cout << "Usage is: " << argv[0] << " [-h][-i <infile>][-o <outfile>][-a ek | ff]" << std::endl;
    exit(0);
}

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
    std::string alg = "ek";
    if (argc == 2 or argc == 4 or argc == 6 or argc > 7) {
        usage(argv);
    }
    else if(argc == 3 or argc == 5 or argc == 7){
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
                else if (std::string(argv[i]) == "-a"){
                    alg = argv[i+1];
                    if (alg != "ek" and alg != "ff")
                        usage(argv);
                }
                else if (std::string(argv[i]) == "-h")
                {
                    usage(argv);
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


    int n = rg.getSize();
    int i, j;
    i = 1;
    j = f;

    int mat[n*n];

    
    rg.parametrize(mat);
    

//binary search

    while(not(i > j)){
        int k = (i+j)/2;


        
        rg.reallyParametrize(mat,k,n);


        std::vector<Flight> flights = rg.getFlights();
        FlightEdgeDict fed(flights);
        rg.makeFED(fed);

        int source = rg.getSource();
        int sink = rg.getSink();
        Graph G = Graph(mat,n,source,sink);
        FordFulkerson* algorithm;
        if (alg == "ek")
            algorithm = new EdmondsKarp(G);
        else
            algorithm = new FordFulkerson(G);

        algorithm->solve();



 
        if(algorithm->isMaxFlow())
        {
            if(k == i){
                Graph g = algorithm->getResult();
                int m[(n-2)*(n-2)];
                rg.getUpperBoundsRawAdjMatrix(m);
                Graph G = Graph(m,n-2,source-2,sink-2);
                writeResult(G, g, fed, isfileout, outfile);
                //std::cout << k << std::endl;
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
        delete algorithm;
    }
    
}
