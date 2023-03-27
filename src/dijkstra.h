#pragma once
#include "graph.h"


// 
std::vector<std::pair<int, double>> dijkstra(Graph* APgraph, int start, int end);


class pairComparator {
    public:
        int operator() (const std::pair<int,double>& pair1, const std::pair<int,double>& pair2);
};
