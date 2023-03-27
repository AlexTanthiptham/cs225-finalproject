// Inspired by pseudocode from GeeksforGeeks, Wikipedia, Youtube and Tutorialspoint 

#include <stack>
#include <algorithm>
#include <vector>
#include "tarjan.h"

using namespace std;

tarjan::tarjan(Graph * APgraph) {
    _graph = APgraph;
}

vector<vector<int>> tarjan::strongcc(Graph * APgraph) {
    _graph = APgraph;
    int nodes = APgraph->adjList.size();
    vector<int> disc;
    vector<int> early; 
    vector<bool> _stackelem; 
    stack<int> _stack;
    vector<vector<int>> outputs;
    
    // Initialize internal variables
    for (unsigned int i = 0; i < nodes; i++) {
        disc.push_back(-1); 
        early.push_back(-1);
        _stackelem.push_back(false);
    }

    // Call recursive helper function to find
    for (unsigned int i = 0; i < nodes; i++) {
        if (disc[i] == -1){
            vector<int> strongcc = strongcchelper(i, disc,early,_stackelem,_stack);
            outputs.push_back(strongcc);
        }
    }
    return outputs;
}

// Helper function for Tarjan's algorithm. Searches for an SCC in each call.
vector<int> tarjan::strongcchelper(int next_id, vector<int> disc, vector<int> early, vector<bool> _stackelem, stack<int> _stack) {
    vector<int> _output;
    static int time = 0;
    
    disc[next_id] = early[next_id] = ++time;
    _stack.push(next_id);
    _stackelem[next_id] = true;

    for(int i=0; i< _graph->adjList[next_id].size(); i++) {
        
        int adj_id = _graph->adjList[next_id][i].first;
        //when it is not visited
        if(disc[adj_id] == -1) {
            strongcchelper(adj_id, disc, early, _stackelem, _stack);
            early[next_id] = min(early[next_id], early[adj_id]);
        }
        //update early, when i is not visited
        else if (_stackelem[adj_id] == true){
            early[next_id] = min(early[next_id], disc[adj_id]);
        }
    }
    
    
    int popped = 0;
    if(early[next_id] == disc[next_id]) {
        
        while(_stack.top()!=next_id && !_stack.empty()){
            
            popped=_stack.top();
            _stackelem[popped]=false;
            _stack.pop();
            _output.push_back(popped);
            
        }
        _output.push_back(popped);
        popped = _stack.top();
        
        _stackelem[popped]=false;
        _stack.pop();
    }   
    return _output;
}



