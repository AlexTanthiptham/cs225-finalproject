#include <iostream>
#include <vector>
#include <string>
#include "readFromFile.hpp"
#include <math.h>
#include <cstdlib>
#include "graph.h"
#include "dfs.h"
#include "dijkstra.h"

using namespace std;

	// Invalid character in range 500-700

int main(int arg1, const char * argv[]) {
	cout << "Welcome to Placeholders' Airport Path Project!"<< endl;
	int x; 
	cout << "Type a start Airport ID: "; // Type a number and press enter
	cin >> x; // Get user input from the keyboard
	arg1 = x;
	int y; 
	cout << "Type a end Airport ID: "; // Type a number and press enter
	cin >> y; // Get user input from the keyboard

	cout << "Start Airport ID: " << x << endl; // Display the input value
	cout << "End Airport ID: " << y << endl; // Display the input value

	Graph * APgraph = new Graph();
	APgraph->initializeData("data/airportssmp.dat"); 
    APgraph->initializeEdges("data/routes.dat");

	cout << "Building Graph..." <<endl;

	cout<<"Beginning DFS"<< endl;
	DFS dfs1(APgraph, APgraph->listArr[x], APgraph->listArr[y]);
	cout<<"DFS Traversal"<< endl;
	vector<int> traversal = dfs1.traversal();
	cout<< "Maximum number of steps " << traversal.size() <<endl;
	int step = 1;
	cout << "Select number of traversal steps (more than 1) to print: "<< endl; // Display the input value
	cin >> step; // Get user input from the keyboard

	cout << "Traverse "<< step-1 <<" items in the dataset"<< endl;
 	for (int i = 0; i < step; i++) {
		if (i >= traversal.size()) break;
        cout <<"Path taken "<< traversal[i] << endl;
    }

	DFS dfs2(APgraph, APgraph->listArr[x], APgraph->listArr[y]);
	cout<<"DFS Path Finder (Shortened version where we stop once we find desired ID)"<< endl;
	vector<int> path = dfs2.path_finder();
	for (unsigned int i = 0; i < path.size(); i++) {
        cout <<"Path taken "<< path[i] << endl;
    }
	cout << path.size() << endl;


	cout<<"Beginning Dijkstra's"<< endl;
	std::vector<std::pair<int, double>> dijkpath = dijkstra(APgraph, x, y);
	double total_distance = 0.0;
	for (unsigned int i = 0; i < dijkpath.size(); i++) {
        cout <<"Dijk Path taken: "<< dijkpath[i].first << endl;
		cout<< "Distance between both airports: " << dijkpath[i].second<< "KM" << endl;
		total_distance += dijkpath[i].second;
    }
	cout<< "Total Distance travelled: " << total_distance << "KM"<< endl;

}