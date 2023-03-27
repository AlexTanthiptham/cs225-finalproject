#pragma once
#include "graph.h"

class tarjan {
    public:
        tarjan(Graph * APgraph);
        vector<vector<int>> strongcc(Graph * APgraph);

    private:
        Graph* _graph;
        vector<int> strongcchelper(int next_id, vector<int> disc, vector<int> early, vector<bool> _stackelem, stack<int> _stack);
};
