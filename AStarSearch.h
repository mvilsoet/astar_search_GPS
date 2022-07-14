/* 
 * @file AStarSearch.h
 */
#pragma once

#include "Graph.h"
#include <vector>
#include <queue>

using namespace std;
using Node = Graph::Node;

/*
* compare class to make a custom comparator to sort the priority queue based on pairs of nodes and their calculated f score
*/
class Compare
{
public:
    /* 
    * comparator to return true if f distance for pair a is greater than distance for pair b
    */
    bool operator() (std::pair<Node *, double> a, std::pair<Node *, double> b) {
        return a.second > b.second;
    }
};

/* given two nodes in the graph, find a route of nodes which travels the shortest distance and calculate the total distance in this route 
* using the astar pathfinding algorithm
*/
class AStarSearch {
    public:

    /* 
    * Constructor for a AStarSearch object - takes pointers to nodes to find the shortest route between
    * @param start The node pointer to the starting point in the route
    * @param start The node pointer to the destination to search for
    */
    AStarSearch(Node* start, Node* goal);

    /*
    * Getter function to return the route as a vector of node pointers after the search is complete
    * @return the vector of node pointers stored in route
    */
    vector<Node *> getRoute();

    /*
    * Getter function to return the total distance of the route 
    * @return minimum distance between start and goal converted to miles
    */
    double getDistance();

    /*
    * main function to conduct the AStar Search, finds shortest route using algorithm and stores route and distance in the instance of AStarSearch
    * @return true if successful in finding a route, false if no route exists
    */
    bool search();

        /*
    * Uses longitude and latitude of each node to calculate euclidean distance between two nodes
    * @param start node pointer to the first node 
    * @param end node pointer to the second node
    * @return the euclidean distance of the two nodes in degrees
    */
    static double findEuclideanDistance(Node * start, Node * end);

    /*
    * Helper function for search, to add the neighbors stored in edges for the current node to the search
    * @param current node pointer to the current node in the AStar Search
    */
    void addNeighbors(Node* current);

    private:
    /*
    * Helper to calculate f(n) to determine priority, given f(n) = g(n) + h(n)
    * @param node node to calculate the f score for
    * @return double giving f score of node in degrees
    */
    double findFScore(Node * node);
    /*
    * Helper function to trace the route after goal is reached using node pointers to parent starting from the goal node in the search
    * and tracing backwards, then reversing the vector and storing it as the route
    */
    void findRoute();
    /*
    * private member variables for AStarSearch: distance in miles of the route, route stored as vector of node pointers, the closed list for the search function, 
    * the open list of the search function as a priority queue, pointers to the start and end points, and a boolean to determine if search was completed
    */
    double distance;
    vector<Node *> route; 
    vector<Node *> closed; //closed list
    std::priority_queue<std::pair<Node *, double>, std::vector<std::pair<Node*,double>>, Compare> open; //open list 
    Node * start;
    Node * goal;
};