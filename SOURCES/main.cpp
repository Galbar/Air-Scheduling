#include <iostream>
#include "EdmondsKarp.h"
#include "ReadGraph.h"

int binarySearch(ReadGraph& rg, int i, int j){
	int n = rg.getSize();
	while(not(i > j)){
        int k = (i+j)/2;

        int mat[n*n];

		rg.parametrize(mat,k);
		int source = rg.getSource();
		int sink = rg.getSink();
		Graph G = Graph(mat,n,source,sink);
		EdmondsKarp ek = EdmondsKarp(G);
		ek.solve();
 
        if(ek.isMaxFlow())
        {
        	if(k == i)return k;
        	else{
        		j = k;
        	}
        }
        else
        {
        	i = k+1;
        }
    }
    return -1;
}


	



int main ()
{
	ReadGraph rg;
	rg.read();
	int k = rg.getNumFlights();
	int res = binarySearch(rg, 1, k);

	std::cout << res << std::endl;
    return 0;
}
