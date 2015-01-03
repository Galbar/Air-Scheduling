#include "EdmondsKarp.h"



void readAdjMatrix(int adj[], int n){
	
	for(int i = 0; i < n*n; ++i){
		std::cin >> adj[i];
	}
}




int main(){
	int n, source, sink;
	std::cin >> n >> source >> sink;
	int mat[n*n];

	std::cout << "asfkldslk" << std::endl;

	readAdjMatrix(mat,n);

	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			std::cout << mat[i*n+j] << ' ';
		}
		std::cout << std::endl;
	}
	Graph G = Graph(mat,n,source,sink);


	std::cout << "aslkfdsdf"<< std::endl;
	EdmondsKarp ek = EdmondsKarp(G);


	std::cout << ek.isMaxFlow();
	Graph res = ek.getResult();
}