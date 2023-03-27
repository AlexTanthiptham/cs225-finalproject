/* This is used for debugging actual functions*/
#include "debug.h"
using namespace std;


void printedges(Graph* APgraph) {
	for (int i = 0; i < APgraph->adjList.size(); i++) {
		// std::cout<<"Current node is: "<<i<<" , Outgoing edges are: "<<std::endl; 	// Uncomment line 7 to 9 to see current node and out going edges
		// for (int j = 0; j < APgraph->adjList[i].size(); j++)	
			// std::cout<<"("<<APgraph->adjList[i][j].first<<", "<<APgraph->adjList[i][j].second <<")"<<std::endl; // Uncomment to see current node and out going edges
	}
}