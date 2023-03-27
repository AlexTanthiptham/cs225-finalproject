#include <iostream>
#include <math.h>
#include <cmath>
#include <utility>
#include <string>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include "graph.h"
#include "readFromFile.hpp"
// using namespace std;
/* GRAPH.CPP
This file takes input data vector and outputs the required graph as an adjacency list
--------------
Input Data Format

10,"Thule Air Base","Thule","Greenland","THU","BGTL",76.5311965942,-68.7032012939,251,-4,"E","America/Thule","airport","OurAirports"
Airport ID, Airport Name, City, Country, 3-letter IATA, 4-letter ICAO, latitude, longitude, altitude, UTC time, DST time, timezone, data source
Relevant: Airport ID, 3-letter IATA, latitude, longitude

2B,410,AER,2965,KZN,2990,,0,CR2
Airline, Airline ID, Source IATA, Source airport ID, Destination IATA, Destination airport ID, Codeshare, Stops, Plane Type
Relevant: Source ID, Desintation ID
*/

//-------------------------------------------//


/*
 Parsed data is a vector of strings with each element representing a line in the document
For each element in input vector, seperate by commas and store in stack 
Construct APNodes (Airport Nodes) and pop data from stack to initialize values
------------------
Relevant info from airports.dat: Airport ID, 3-letter IATA code, Latitude, Longitude
*/

/*
Goes through routes.dat vector and takes the 3-letter IATA of the starting and ending airport.
Find the starting airport node and add a pointer to the ending airport node.
Calculate the distance using the latitude and longitude values and assign as edge weights.
------------------
Each node stores edges as a vector of (APNode*, double) pairs
APNode* is the destination pointed to, double holds the distance of the route.
*/

//--APNODE-FUNCTIONS----------------------------------------//
/**
 * @brief Construct a new APNode::APNode object
 * 
 */
APNode::APNode() {
    _id = 0;
    _IATA = "";
    _lat = 0.0;
    _lon = 0.0;
}

/**
 * @brief Construct a new APNode::APNode object
 * Initializes with input values
 */
APNode::APNode(int id, string IATA, double lat, double lon) {// Placeholder framework of the function
    _id = id; 
    _IATA = IATA;
    _lat = lat;
    _lon = lon;
}

//--GRAPH-FUNCTIONS----------------------------------------//

/**
 * @brief Construct a new Graph:: Graph object
 * 
 */
Graph::Graph() {
    //do nothing
}
/**
 * @brief Function to create vertexes
 * @param filename - filename that will open to parse routes
 */
void Graph::initializeData(const std::string & filename) {
    
    std::vector<std::string> data_line = file_to_vectorline(filename);
    
    // Default values
    int id = 0;       
    string IATA = ""; 
    double lat = 0.0; 
    double lon = 0.0;

    APNode invalid(-1, "", 0.0, 0.0); // Emplace_back until read id matches current value of i
                                    // When reading, ignore airports with id -1;

    for (unsigned i = 0; i < data_line.size(); i++) { // Iterate through all lines of airport files
        // Comma seperate the values
        std::vector<std::string> data_word = comma_sep(data_line[i]);
        // Check for data validity
        if (data_word.size() != 14) {
            id = std::stoi(data_word[0]);
            for (unsigned j = 1; j < data_word.size(); j++) {
                char curr = data_word[j][0];
                if ((int(curr) >= 48 && int(curr) <= 57) || int(curr) == 45) {

                    lat = std::stod(data_word[j]);
                    lon = std::stod(data_word[j+1]);
                    IATA = data_word[j-2];
                    break;
                }
            }
        } 
        else {
            // Input data into the variables
            id = std::stoi(data_word[0]);
            IATA = data_word[4];
            lat = std::stod(data_word[6]);
            lon = std::stod(data_word[7]);
        }

        //Fills out missing airports
        while (listArr.size()+1 <= id) {
            listArr.emplace_back(invalid);
        }

        // Use constructor to create node with variables
        APNode ap(id, IATA, lat, lon);
        listArr.emplace_back(ap);
    }
}

/**
 * @brief Function to create edges for vertexes
 * @param filename - filename that will open to parse routes
 */
void Graph::initializeEdges(const std::string & filename) {
    std::vector<std::string> data_line = file_to_vectorline(filename);
    int id_start = 0;   // Source airport (indexes listArr)
    int id_end = 0;     // Destination airport (first in pair of edgeList vector)
    adjList.resize(listArr.size());

    

    for (unsigned i = 0; i < data_line.size(); i++) { // Iterate through all lines of route
        
        // Comma seperate the values
        
        std::vector<std::string> data_word = comma_sep(data_line[i]);
        // Exception checking: Non-numeric ids are ignored
        if (!std::isdigit(data_word[3][0]) || !std::isdigit(data_word[5][0])) continue;

        id_start = std::stoi(data_word[3]);
        id_end = std::stoi(data_word[5]);
        

        // Exception Checking: Ignore airports that exceed current scope
        if (id_start > listArr.size() || id_end > listArr.size()) continue;
        // Exception Checking: Ignore invalid airports (Needs to get id values from these)
        if (listArr[id_start]._id == -1 || listArr[id_end]._id == -1) continue;
    
        // Extract data from listArr
        double lat_start = listArr[id_start]._lat;
        double lat_end = listArr[id_end]._lat;
        double lon_start = listArr[id_start]._lon;
        double lon_end = listArr[id_end]._lon;

        // Calculate Distance
        double distance = dist(lat_start, lat_end, lon_start, lon_end);  

        std::pair<int, double> route(id_end, distance);

        adjList[id_start].emplace_back(route);
    }
}
        
/**
 * @brief Helper function to calculate distances between two input airports Used in assign_edges 
 * @param lat1 = original latitude
 * @param lat2 = target latitude
 * @param lon1 = original longitude
 * @param lon2 = target longitude
 * Acknowledgement: This formula was adapted from https://www.movable-type.co.uk/scripts/latlong.html
 */

/////////////////////////////////////////////////////////////////////////////////////////////////
double Graph::dist(double lat1, double lat2, double lon1, double lon2 )  {
    
    double earth_radius = 6371*1000;
    double lat1_radians = lat1 * M_PI/180;
    double lat2_radians = lat2 * M_PI/180;
    double delta_lat_radians = abs(lat2 - lat1) * M_PI/180;
    double delta_lon_radians = abs(lon2 - lon1) * M_PI/180;

    double a = sin(delta_lat_radians/2) + sin(delta_lat_radians/2) + cos(lat1_radians) *
        cos(lat2_radians) * sin(delta_lon_radians/2) * sin(delta_lon_radians/2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    
    double distance = earth_radius * c / 1000; // Convert meters to kilometers
    return distance;
}