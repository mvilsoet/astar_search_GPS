#include "AStarSearch.h"
#include <cmath>
#include <vector>
#include <algorithm>

#define PI 3.14159265


using namespace std;
using Node = Graph::Node;


    

    //constructor given two points
    AStarSearch::AStarSearch(Node* s, Node* g) {
        start = s;
        goal = g;
        distance = 0;
    }

    //helper to get route of nodes as vector
    vector<Node *> AStarSearch::getRoute() {
        std::reverse(route.begin(), route.end());
        return route;
    }

    //helper to get minimum distance
    double AStarSearch::getDistance(){
        return distance;
    }

    bool AStarSearch::search() {
        std::pair<Node*, double> one(start, findEuclideanDistance(start, goal));
        open.push(one);
        while(!open.empty()) {
            if (((open.top()).first->nodeID) == goal->nodeID) {
                findRoute();
                distance = goal->g * 61.8;
                
                while (!open.empty()) {
                    std::pair<Node*, double> pair = open.top();
                    (pair.first)->g = 0;
                    (pair.first)->h = 0;
                    (pair.first)->parent = NULL;
                    (pair.first)->openList = false;
                    open.pop();
                }
                while (!closed.empty()) {
                    Node* node = closed.back();
                    closed.pop_back();
                    node->parent = NULL;
                    node->g = 0;
                    node->h = 0;
                    node->closedList = false;
                }
                return 1;
            }
            std::pair<Node*, double> pair = open.top();
            pair.first->openList = false;
            open.pop();
            closed.push_back(pair.first);
            pair.first->closedList = true;
            addNeighbors(pair.first);
        }
        while (!open.empty()) {
            std::pair<Node*, double> pair = open.top();
            (pair.first)->g = 0;
            (pair.first)->h = 0;
            (pair.first)->parent = NULL;
            (pair.first)->openList = false;
            open.pop();
        }
        while (!closed.empty()) {
            Node* node = closed.back();
            closed.pop_back();
            node->parent = NULL;
            node->g = 0;
            node->h = 0;
            node->closedList = false;
        }
        return 0;
    }

    void AStarSearch::addNeighbors(Node* current) {
        for(std::pair<Node*, double> edge : current->edges) {
            if (edge.first->closedList) {
                continue;
            }
            if (edge.first->openList) {
                double a = (current->g + edge.second);
                if (edge.first->g > a) {
                    edge.first->parent = current;
                    edge.first->g = current->g + edge.second;
                }
            } else {
                edge.first->g = current->g + edge.second;
                edge.first->parent = current;
                edge.first->openList = true;
                std::pair<Node*, double> newPair(edge.first, edge.first->g + findEuclideanDistance(edge.first, goal));
                open.push(newPair);
            }
        }
    }


    double AStarSearch::findEuclideanDistance(Node * first, Node * end) {
       double longD = first->Long - end->Long;
       double latD = first->Lat - end->Lat;

       double degrees = latD*latD + longD*longD;
       return std::sqrt(degrees);
    }


    void AStarSearch::findRoute() {
        Node * current = goal;
        while(current->parent != NULL) {
            Node * next = current->parent; 
            route.push_back(current);
            current = next;
        }
    }
    //recursive helper to calculate f(n) to determine priority
    double AStarSearch::findFScore(Node * node) {
        node->h = findEuclideanDistance(node, goal);
        return node->h + node->g;
    }



   