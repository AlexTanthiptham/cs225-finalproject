// Inspired by pseudocode from Wikipedia, CS225 Resources Page

#include "graph.h"
#include "dijkstra.h"

#include <stack>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

std::vector<std::pair<int, double>> dijkstra(Graph* APgraph, int start, int end) {
    int size = APgraph->listArr.size();
    int distance[size]; // Holds total distance to the given vertex from the source // Note: Possibly change to vector implementation
    int previous[size]; // Holds ids of nodes in path taken
    std::vector<int> visited; // Holds ids of visited nodes
    std::priority_queue <std::pair<int,double>, std::vector<std::pair<int,double>>, pairComparator > pQueue;
    std::vector<std::pair<int, double>> output; // Output vector

    // Exceptions Block
        // Insufficient Nodes in Graph
        std::vector<std::pair<int, double>> empty;
        if (size == 0 || size == 1) {
            std::cout<<"Input graph has insufficient ("<< size << ") nodes"<<std::endl;
            return empty;
        }
        // Input nodes are invalid
        if (APgraph->listArr[start]._id == -1 || APgraph->listArr[end]._id == -1) {
            std::cout<<"Input nodes are invalid!"<<std::endl;
            return empty;
        }
        // Direct path between nodes
        for (unsigned int i = 0; i<APgraph->adjList[start].size(); i++) {
            std::pair<int,double> neighbor = APgraph->adjList[start][i];
            if (neighbor.first == end) {
                output.push_back(std::pair<int,double>(end, neighbor.second));
                std::cout<<"Dijkstra's: There is a direct path between airports "<< APgraph->listArr[start]._IATA << " (id: " << start <<") and " << APgraph->listArr[end]._IATA << " (id: "<< end <<")" <<std::endl;
                return output;
            }
        }
    // Exceptions block

    // Initialize distance values as infinite  
    for(unsigned int i=0; i<size; i++){
        distance[i]= std::numeric_limits<int>::max();
        previous[i] = -1; 
    }
    pQueue.push(std::pair<int,double>(start, 0));


    // Initialize
    visited.push_back(start);
    distance[start] = 0;
    int currid = 0;

    while (!pQueue.empty() || pQueue.top().first != end) { 

        currid = pQueue.top().first; // Extract current node
        pQueue.pop();

        // Iterate through edges out of current node. For each edge, add tentative distance to priority queue
        for (int i = 0; i < APgraph->adjList[currid].size(); i++) { 

            std::pair<int,double> neighbor = APgraph->adjList[currid][i];

            //Check if node has been visited 
            bool currvisited = false;
            for (int j = 0; j < visited.size(); j++) {
                if (neighbor.first == visited[j]) {
                    currvisited = true;
                    break;
                }
            }
            if (currvisited == true) continue;


            // Extract neighbor data
            int nextid = neighbor.first;
            double tentdist = distance[currid] + neighbor.second; // Distance values extracted from adjList
            
            // Check if current path to node is closer than previous path & update if true
            if (distance[nextid] > tentdist) {
                previous[nextid] = currid;      // Update path to previous from current id
                distance[nextid] = tentdist;    
                pQueue.push(std::pair<int,double>(nextid, distance[nextid]));
            }
        }
        visited.push_back(currid);       // Save current node to visited 
    }

    // Find end node in previous[] by tracing back path
    // After breaking out of loop, currid should be index of 
    double extdist = 0.0;
    int extid = end;
    while (extid != start) {
        extdist = distance[extid];
        output.push_back(std::pair<int,double>(extid, extdist)); 
        extid = previous[extid];
    }
    output.push_back(std::pair<int,double>(extid, extdist)); 
    std::reverse(output.begin(), output.end());
    return output;
}

// Helper class, compares the distance of two pairs. Used for priority queue
int pairComparator::operator() (const std::pair<int,double>& pair1, const std::pair<int,double>& pair2) {
        return pair1.second > pair2.second;
    }



