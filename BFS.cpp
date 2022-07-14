#include "BFS.h"

BFS::BFS(Graph * graph, Node * start) {
    graph_ = graph;
    start_ = start;
    nodes.push(start_);

    // Go through graph and add all nodes, mark them as unvisited
    visitedNodes.reserve(graph_->graph_.size());
    for (unsigned i = 0; i < (graph_->graph_).size(); i++) {
        visitedNodes[i] = false;
    }
}

BFS::Iterator BFS::begin() {
    BFS::Iterator itStart = BFS::Iterator(start_, this);
    return itStart;
}

BFS::Iterator BFS::end() {
    return Iterator();
}

BFS::Iterator::Iterator() {
    curr_node = nullptr;
    bfs_ = nullptr;
}

BFS::Iterator::Iterator(Node * node, BFS * bfs) {
    curr_node = node;
    bfs_ = bfs;
}

BFS::Iterator BFS::Iterator::operator++() {
    Node * curr = bfs_->pop();
    bfs_->markVisited(curr);

    // If there are adjacent nodes, add each to the traversal queue and mark them as "visited"
    if (!(curr->edges).empty()) {
        for (pair<Node *, double> pair: curr->edges) { 
            if (bfs_->getVisited(pair.first) == false) {
                bfs_->nodes.push(pair.first); // add each adjacent node to the traversal queue
                bfs_->markVisited(pair.first); // mark the added node as "visited"
            }
        }
    } 
    
    // Handling unconnected components: Go through visitedNodes vector + add the next unvisited
    if ((bfs_->nodes).empty()) {
        if (bfs_->getNextUnvisited() != NULL) {
            bfs_->nodes.push(bfs_->getNextUnvisited());
        }
    }

    // Update the next Node of traversal and if traversal is empty, set curr_node to nullptr
    if ((bfs_->nodes).empty()) {
        curr_node = nullptr;
    } else {
        curr_node = bfs_->nodes.front();
    } 
    
    return *this;
}

Node & BFS::Iterator::operator*() {
    return *curr_node;
}

bool BFS::Iterator::operator!=(BFS::Iterator & other) {
    if (curr_node == nullptr) {
        return false;
    } else {
        return true;
    }
}


/* 
 * HELPER FUNCTIONS
 */

void BFS::markVisited(Node* node) {
    int id = node->nodeID;
    visitedNodes[id] = true;
}

bool BFS::getVisited(Node * node) {
    int id = node->nodeID;
    return visitedNodes[id];
}

Node * BFS::getNextUnvisited() {
    for (unsigned i = 0; i < visitedNodes.size(); i++) {
        if (visitedNodes[i] == false) {
            return &(graph_->graph_[i]);
        }
    }
    return NULL;
}

Node * BFS::pop() {
    Node * temp = nodes.front();
    nodes.pop();
    return temp;
}

vector<Node> BFS::returnVec() {
    vector<Node> nodeVec;
    BFS::Iterator begin = this->begin();
    BFS::Iterator end = this->end();
    for(auto it = begin; it != end; ++it)
        nodeVec.push_back(*it);
    return nodeVec;
}