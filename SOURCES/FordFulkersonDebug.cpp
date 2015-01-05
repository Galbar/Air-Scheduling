#include "FordFulkerson.h"


void readAdjMatrix(int adj[], int n){
    
    for(int i = 0; i < n*n; ++i){
        std::cin >> adj[i];
    }
}

int main(){
    int n, source, sink;
    std::cin >> n >> source >> sink;
    int mat[n*n];


    readAdjMatrix(mat,n);

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            std::cout << mat[i*n+j] << ' ';
        }
        std::cout << std::endl;
    }
    Graph G = Graph(mat,n,source,sink);

    FordFulkerson ff = FordFulkerson(G);

    ff.solve();

    std::cout << "resultado: " << ff.isMaxFlow() << std::endl;
    std::cout << "el resultado es minimo?: " << ff.isMinimum() << std::endl;
    Graph res = ff.getResult();
    int vertices = res.getNumVertex();
    int adjMatrix[vertices*vertices];

    res.getAdjacencyMatrix(adjMatrix);

    for(int i = 0; i < vertices; ++i){
        for(int j = 0; j < vertices; ++j){
            if(adjMatrix[i*vertices+j] > 0){
                EdgeId eid = EdgeId(j,i);
                int flow = res.getEdgeFlow(eid);
                std::cout << flow << ' ';
            }
            else{
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }
}