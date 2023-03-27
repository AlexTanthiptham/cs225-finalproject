#include "dfs.h"

#include "graph.h"

#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

DFS::DFS(Graph* graph_param, APNode & start_node, APNode & end_node) {
    //initialize private variables
    graph = graph_param;
    start = start_node;
    end = end_node;
    if (start._id == -1 || end._id == -1) {
        std::cout << "Invalid input nodes." << std::endl;
        std::cout << "Results will be invalid. Please select new values." << std::endl;
    }

  
    //add starting node to traversal
    int start_id = start._id;
    traversal_order.push(start_id);

    //resize visited points to be the number of vertexes in the graph, initialize all to be false because they haven't been visited
    visited_before.resize(graph->listArr.size(), false);
}


/*
*   Pushes node to the top of the traversal stack using node id
*/
void DFS::add(int id) {
    traversal_order.push(id);
}


/*
*   Removes top element off the top of the traversal stack
*/
void DFS::remove() {
    traversal_order.pop();
}


/*
*  Returns the current top APNode in the traversal
*/
APNode DFS::peek() const {
    int top = traversal_order.top();
    if (top != -1)  return graph->listArr[top];
    else {          return APNode(-1, "Invalid", 0.0, 0.0);
                    std::cout<<"Invalid node encountered"<<std::endl;
    }
}


/*
*   Removes and returns the current top APNode in the traversal
*/
APNode DFS::pop() {
    //get curr6ent top of stack
    APNode top_temp = peek();

    //remove current top of stack
    remove();

    //mark as visited
    int id = top_temp._id;
    if (id != -1)   visited_before[id] = true;

    //return current top
    return top_temp;
}


/*
*   Returns whether the traversal is empty
*/
bool DFS::empty() const {
    return traversal_order.empty();
}

/*
*  Returns whether a node has been visited using id
*/

bool DFS::visitedBefore(int id) const {
    return visited_before[id];
}


/*
*  Returns a path from one node to another node by returning a vector of int node ids
*/
vector<int> DFS::path_finder() {
    vector<int> path;

    while (!empty()) {
        //gets and removes current top node, marks it as visited
        APNode curr_node = pop();

        if (curr_node._id == -1)    continue;

        //add current top node that has been visited to path
        path.push_back(curr_node._id);

        //check to see if curr node is end node, if so, break out of loop and return path
        if (curr_node._id == end._id) {
            break;
        }

        /*
        *   if curr node is not end node, add all adjacent nodes using the node's adjlist
        *   get the node's id using the first in the pair in adjlist
        *   only add node to stack if it has not been previously visited
        */
        for (unsigned int i = 0; i < graph->adjList[curr_node._id].size(); i++) {
            int curr_id = graph->adjList[curr_node._id][i].first;
            //if curr node has not been visited and node has not already been added to stack
            if (!visitedBefore(curr_id)) {
                add(curr_id);
            }
        }

    }

    return path;
}

/*
*  Returns a path taken to traverse entire graph
*/
vector<int> DFS::traversal() {
    vector<int> path;


    while (!empty()) {
        //gets and removes current top node, marks it as visited
        APNode curr_node = pop();

        //add current top node that has been visited to path
        path.push_back(curr_node._id);

        //check to see if curr node is end node, if so, break out of loop and return path
        // if (curr_node._id == end._id) {
        //     break;
        // }

        /*
        *   if curr node is not end node, add all adjacent nodes using the node's adjlist
        *   get the node's id using the first in the pair in adjlist
        *   only add node to stack if it has not been previously visited
        */
        for (unsigned int i = 0; i < graph->adjList[curr_node._id].size(); i++) {
            int curr_id = graph->adjList[curr_node._id][i].first;
            //if curr node has not been visited and node has not already been added to stack
            if (!visitedBefore(curr_id)) {
                add(curr_id);
            }
        }

    }

    return path;
}