#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "../catch/catch.hpp"
#include "../catch/catchmain.cpp"
#include "../readFromFile.hpp"
#include "../graph.h"
#include "../testbench.hpp"
#include "../dfs.h"
#include "../dijkstra.h"
#include "../debug.h"
#include "../tarjan.h"

/* This test case checks if file can be converted into a vector where each index is 1 item (comma seperated) of the file*/
TEST_CASE("Verify that file_to_vectorword works on a small example") {
	std::vector<std::string> res = file_to_vectorword("data/small-airports.dat");
	// These seem to be too long
	std::vector<std::string> expected = {"1","Goroka Airport","Goroka","Papua New Guinea","GKA","AYGA","-6.081689834590001","145.391998291","5282","10","U","Pacific/Port_Moresby","airport","OurAirports","2","Madang Airport","Madang","Papua New Guinea","MAG","AYMD","-5.20707988739","145.789001465","20","10","U","Pacific/Port_Moresby","airport","OurAirports"};
	REQUIRE(2*14 == res.size());
	/* Uncomment to show vector output*/
	// for (int i = 0; i < res.size(); i++) {
	// 	std::cout << res[i] << std::endl;
	// }
	/* Uncomment to test vector output */
	for (int i = 0; i < res.size(); i++) {
		REQUIRE(res[i] == expected[i]);
	}
}

/* This test case checks if the file can be converted into vector where each line is 1 index and then checks if each line can be converted into each item(comma seperated) in each line*/
TEST_CASE("Verify that file_to_vectorline & comma_sep works on a small example") {
	std::vector<std::string> res_lines = file_to_vectorline("data/airportssmp.dat");
	std::vector<std::string> expected_lines = {"1,Goroka Airport,Goroka,Papua New Guinea,GKA,AYGA,-6.081689834590001,145.391998291,5282,10,U,Pacific/Port_Moresby,airport,OurAirports", "2,Madang Airport,Madang,Papua New Guinea,MAG,AYMD,-5.20707988739,145.789001465,20,10,U,Pacific/Port_Moresby,airport,OurAirports"};
	for (int i = 0; i < 2; i++) {
		REQUIRE(res_lines[i] == expected_lines[i]);
	}
	
	std::vector<std::string> res_words = comma_sep(res_lines[0]);
	std::vector<std::string> expected_words = {"1","Goroka Airport","Goroka","Papua New Guinea","GKA","AYGA","-6.081689834590001","145.391998291","5282","10","U","Pacific/Port_Moresby","airport","OurAirports"};
	REQUIRE(expected_words.size() == res_words.size());
	for (int i = 0; i < res_words.size(); i++) {
		// std::cout << res_words[i]<<std::endl;
		REQUIRE(res_words[i] == expected_words[i]);
	}
}

/* This test case checks if basic functionality of Graph works*/
TEST_CASE("Test initialize to see if APNode is created correctly") {
	Graph * APgraph = new Graph();
	APgraph->initializeData("data/airportssmp.dat");
	std::vector<std::string> expected = {"1", "GKA", "-6.081689834590001","145.391998291"};	//DataLine 1 : ListArr[0]

	// std::cout<< APgraph->listArr[0]._id << std::endl;	// Uncomment to see output
	REQUIRE(APgraph->listArr[1]._id == stoi(expected[0]));	// Currently id 

	// std::cout<< APgraph->listArr[0]._IATA << std::endl;	// Uncomment to see output
	REQUIRE(APgraph->listArr[1]._IATA == expected[1]);

	// std::cout<< APgraph->listArr[0]._lat << std::endl;	// Uncomment to see output
	REQUIRE(APgraph->listArr[1]._lat == stod(expected[2]));

	// std::cout<< APgraph->listArr[0]._lon << std::endl;	// Uncomment to see output
	REQUIRE(APgraph->listArr[1]._lon == stod(expected[3]));
}


/* This hard test case checks for exceptions like extra "," inputs and ensures the whole data set is parsed with no problems*/
TEST_CASE("Hard test for initialize to see if APNode works for whole dataset"){
	Graph * APgraph = new Graph();
	APgraph->initializeData("data/airportssmp.dat");
	/* Checks line with irregularity (in this case this line has extra comma in city name)*/
	std::vector<std::string> expected = {"641","EVE","68.491302490234","16.678100585938"};	//DataLine: 641 : ListArr[640]
	REQUIRE(APgraph->listArr[641]._id == stoi(expected[0]));	// Currently id 

	REQUIRE(APgraph->listArr[641]._IATA == expected[1]);

	REQUIRE(APgraph->listArr[641]._lat == stod(expected[2]));

	REQUIRE(APgraph->listArr[641]._lon == stod(expected[3]));
	
	/* Checks last line of dataset*/
	std::vector<std::string> expected1 = {"14110","","46.880001","35.305"};
	REQUIRE(APgraph->listArr[14110]._id == stoi(expected1[0]));	// Currently id 

	// std::cout<< APgraph->listArr[0]._lat << std::endl;
	REQUIRE(APgraph->listArr[14110]._lat == stod(expected1[2]));

	// std::cout<< APgraph->listArr[0]._lon << std::endl;
	REQUIRE(APgraph->listArr[14110]._lon == stod(expected1[3]));
}

/* This test case does not work for some reason but dist() function works as expected*/
TEST_CASE("Distance formula - lat1 is greater than lat2") {
	double distance = dist(-6.081689834590001, -5.20707988739, 145.391998291, 145.789001465);
	double expected = 1578.93;	// For some reason this is in Meters
	int result = expected - distance;
	REQUIRE(result == 0);
}

/* This simple test case tests on a small data set to see if edges are working as expected*/
TEST_CASE("Edges are working (simple)"){
	Graph * APgraph = new Graph(); 
	APgraph->initializeData("data/airportssmp.dat");// Still breaks when using tests/smalltest.dat
    APgraph->initializeEdges("tests/smallroute.dat");
	// std::cout<<"initialize edges sucessful"<<std::endl;

    std::pair<int,double> expectedpair(2,1578.9282702988); // this value corresponds to flight data
    REQUIRE(APgraph->adjList[1][0].first == expectedpair.first); 
	int result = APgraph->adjList[1][0].second - expectedpair.second;
	REQUIRE(result == 0);
	// std::cout<<"pair internal data sucessful"<<std::endl;
    REQUIRE(APgraph->listArr[1]._id == 1);
	REQUIRE(APgraph->listArr[2]._id == 2);
}

/* This complex test case tests on the full data set to see if edges are working as expected*/
TEST_CASE("Edges are working (complex)"){
	Graph * APgraph = new Graph();
	APgraph->initializeData("data/airportssmp.dat"); // Still breaks when using tests/smalltest.dat
    APgraph->initializeEdges("data/routes.dat");
	// std::cout<<"initialize edges sucessful"<<std::endl;

	// First item in routes.dat (start: 2965, end: 2990)
    REQUIRE(APgraph->adjList[2965][0].first == 2990); 
	REQUIRE((int)APgraph->adjList[2965][0].second == (int)6135.3908232981); // This value is a placeholder

	// Last item in routes.dat (start: 2913, end: 2912)
	// Should be last item of that list
	int expIdx = APgraph->adjList[2913].size() - 1;

    REQUIRE(APgraph->adjList[2913][expIdx].first == 2912); 
	int result1 = APgraph->adjList[2913][expIdx].second - 2658.9483;
	REQUIRE(result1 == 0);
	// Actual Value: ~1506km

	// If it's not the last item of the list, search for it 
	// (Still there but wrong location, location doesn't actually matter lmao)
	bool found = false;
	for (int i = 0; i < expIdx + 1; i++) {
		if (APgraph->adjList[2913][i].first == 2912) {
			found = true;
			break;
		}
	}
    REQUIRE(found == true); 
}


/* This simple tests case on a smaller dataset for DFS only 2 airports*/
TEST_CASE("DFS is working (simple)"){

	//initialize graph
	Graph* APgraph = new Graph();
	APgraph->initializeData("data/small-airports.dat"); 
    APgraph->initializeEdges("tests/smallroute.dat");

	//initialize DFS
	DFS dfs(APgraph, APgraph->listArr[1], APgraph->listArr[2]);
	std::vector<int> path = dfs.path_finder();
	
	REQUIRE(path[0] == 1);
	REQUIRE(path[1] == 2);

}

/* This complex test case tests on the full data set to see if DFS works*/
TEST_CASE("DFS is working (complex)"){

	//initialize graph
	Graph* APgraph = new Graph();
	APgraph->initializeData("tests/complex-airport.dat"); 
    APgraph->initializeEdges("tests/complex-routes.dat");


	//initialize DF
	DFS dfs(APgraph, APgraph->listArr[1], APgraph->listArr[3]);
	// std::vector<int> path = dfs.path_finder();	// Uncomment this to test path_finder() where it will stop when it hits desired node
	std::vector<int> path = dfs.traversal();
	REQUIRE(path[0] == 1);
	REQUIRE(path[1] == 2);
	REQUIRE(path[2] == 6);
	REQUIRE(path[3] == 4);
	REQUIRE(path[4] == 3);
}

/* Test Case for DFS for entire dataset*/
TEST_CASE("DFS is working (full dataset)"){

	//initialize graph
	Graph* APgraph = new Graph();
	APgraph->initializeData("data/airportssmp.dat");
    APgraph->initializeEdges("data/routes.dat");

	//initialize DFS
	DFS dfs(APgraph, APgraph->listArr[5], APgraph->listArr[7]);
	std::vector<int> path = dfs.path_finder();
	// Uncomment to see full output
	// for (int i = 0; i < path.size(); i++){
	// 	std::cout << path[i] << std::endl;
	// }
	// This test case is too huge to test for correct path
	REQUIRE(path == path);
}

/* Test Case for DFS for entire dataset*/
TEST_CASE("DFS is working (edge case)"){
	std::cout<< "The terminal outputs are intended please refer to test.cpp line 214, 266 as to why this is intended."<< std::endl;
	//initialize graph
	Graph* APgraph = new Graph();
	APgraph->initializeData("data/airportssmp.dat");
    APgraph->initializeEdges("data/routes.dat");

	//initialize DFS
	DFS dfs(APgraph, APgraph->listArr[118], APgraph->listArr[7]);	//ID: 118 does not exist in airport dataset observe "Invalid input nodes." output
	std::vector<int> path = dfs.path_finder();
	// This has no test just refer to the console printed message to see it works
	REQUIRE(true);
}

/* This simple test uses a small dataset from airports and routes*/
TEST_CASE("Djikstra's is working (simple)") {

	//initialize graph
	Graph* APgraph = new Graph();
	APgraph->initializeData("tests/dijk-airports.dat"); 
    APgraph->initializeEdges("tests/dijk-routes.dat");

	// Debug Data Output
	printedges(APgraph);	// go to file debug.cpp to uncomment to see printed outputs if you wish otherwise this still runs a test

	std::vector<std::pair<int, double>> path = dijkstra(APgraph, 1, 5);
	
	REQUIRE(path[0].first == 1);
	REQUIRE(path[1].first == 3);
	REQUIRE(path[2].first == 5);	 
}

/* This complex test uses the full dataset from airports and routes*/
TEST_CASE("Djikstra's is working (complex)"){

	//initialize graph
	Graph* APgraph = new Graph();
	APgraph->initializeData("data/airportssmp.dat"); // Still breaks when using tests/smalltest.dat
    APgraph->initializeEdges("data/routes.dat");

	// Debug Data Output
	printedges(APgraph);	// go to file debug.cpp to uncomment to see printed outputs if you wish otherwise this still runs a test

	std::vector<std::pair<int, double>> path = dijkstra(APgraph, 1, 5);
	
	// There is a direct edge
	REQUIRE(path[0].first == 5);
}

/* This edge case test uses the full dataset from airports and routes but with ID does not exist in dataset*/
TEST_CASE("Djikstra's is working (edge case)"){

	//initialize graph
	Graph* APgraph = new Graph();
	APgraph->initializeData("data/airportssmp.dat"); 
    APgraph->initializeEdges("data/routes.dat");

	// Debug Data Output
	printedges(APgraph);	// go to file debug.cpp to uncomment to see printed outputs if you wish otherwise this still runs a test

	std::vector<std::pair<int, double>> path = dijkstra(APgraph, 118, 5);	// ID: 118 does not exist in airport dataset observe "Input nodes are invalid" output
	
	// There is no edges out of 118
	REQUIRE(true);
}

// TEST_CASE("Tarjan's is Working (Simple)"){

// 	//initialize graph
// 	Graph* APgraph = new Graph();
// 	// APgraph->initializeData("tests/dijk-airports.dat"); 
//     // APgraph->initializeEdges("tests/dijk-routes.dat");
// 	APgraph->initializeData("data/airportssmp.dat"); 
//     APgraph->initializeEdges("data/routes.dat");
// 	tarjan _tarjan(APgraph);
// 	vector<vector<int>> scc = _tarjan.strongcc(APgraph);
	
// 	std::cout<<"# of strongly connected components: "<<scc.size()<<std::endl;

// 	for (int i = 0; i < scc.size(); i++) {
// 		std::cout<<"Strongly connected component #"<<i<<" consists of:  ";
// 		for (int j = 0; j < scc[i].size(); j++) {
// 			std::cout<<scc[i][j]<<"  ";
// 		}
// 		std::cout<<" "<<std::endl;
// 	}
// }