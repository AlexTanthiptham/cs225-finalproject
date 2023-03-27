/**
 * @file list.h
 * Doubly Linked List (MP 3).
 */
#pragma once
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <math.h> 
#include <string>   

using namespace std;

/* 
Airport node class. Routes pointing out stored as a vector of pointers as number of
routes leading out of each airport is variable.
Adapted from MP Lists
*/
        /**
         * Helper class. Simply stores data parsed from file for future reference.
         */
class APNode { 
    public:
        // Member Functions

        /**
         * Default APNode constructor.
         * @see List-given.hpp
         */
        APNode();

        /**
         * Custom APNode constructor
         * @brief Construct a new APNode object
         * 
         * @param id 
         * @param IATA 
         * @param lat 
         * @param lon 
         */
        APNode(int id, string IATA, double lat, double lon);

        /**
         * The data contained in this node. We do not allow you to
         * modify node data, so it is const.
         */
        int _id; // Openflights ID of the airport in input dataset        
        string _IATA; // 3-character IATA code of airport
        double _lat; // Latitude of airport
        double _lon; // Longitude of airport
    };

class Graph {
    public:
        //Private variables
        vector<APNode> listArr; // Vector of airport data index by ID if we ever need to recover the information
        vector<vector<pair<int, double>>> adjList; // Vector of outgoing rotues indexed by ID
        //Private Helper Functions

        /**
        Helper function to calculate distances between two input airports
        Used in assign_edges
        */
        double dist(double lat1, double lat2, double lon1, double lon2); 

        /**
         * Default graph constructor. Creates empty graph
         */
        Graph();

        /**
         * Overloaded assignment operator for graph.
         * Part of the Big Three that we must define because the class
         * allocates dynamic memory.
         */
        Graph operator=(const Graph rhs);

        /**
         * Destroys the current Graph. This function should ensure that
         * memory does not leak on destruction of a Graph.
         */
        ~Graph();

        /**
         * Initializes graph verticies & distances from airports file
         */
        void initializeData(const std::string & filename);
    
        /**
         * Intitializes graph edges from routes files
         */
        void initializeEdges(const std::string & filename);
        // void addVertex(int id, string IATA, double lat, double lon);
        // void removeVertex(int id);    
};




