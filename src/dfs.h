#pragma once


#include "graph.h"
#include <stack>
#include <vector>




class DFS {
    public:
        DFS(Graph* graph, APNode & start_node, APNode & end_node);

        vector<int> path_finder();
        vector<int> traversal();
    
    private:
        Graph* graph;
        APNode start;
        APNode end;
        std::stack<int> traversal_order; //stack that indicates order in which nodes will be visited
        std::vector<bool> visited_before; //vector that marks which nodes have been visited using their id
        
        void add(int id);
        void remove();
        APNode pop();
        APNode peek() const;
        bool empty() const;
        bool visitedBefore(int id) const;
};