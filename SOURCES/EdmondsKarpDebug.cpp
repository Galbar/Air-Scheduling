#include "EdmondsKarp.h"

int n, source, sink;
std::vector<int> mat;

void readAdjMatrix(){
	std::cin >> n >> source >> sink;


	mat = std::vector<int>(n*n);
	for(int i = 0; i < n*n; ++i){
		std::cin >> mat[i];
	}
}




int main(){
	readAdjMatrix();
	Graph G = Graph(mat,n,source,sink);
	EdmondsKarp ek = EdmondsKarp(G);
	Graph res = EdmondsKarp.getResult();
	
}