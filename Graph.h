
#pragma once

#include "cs225/PNG.h"

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <vector>
#include <string>

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;
using cs225::PNG;

class Graph {

    public:
        /* Definition of Node struct used by all the programs in our project */
        struct Node {
            /* Constructors for our Node struct */
            Node() : Long(INT_MIN), Lat(INT_MIN) {}; // Remove if unnecessary later
            Node(double x, double y) : Long(x), Lat(y), g(0), h(0), parent(NULL), openList(false), closedList(false) {};

            /* Node parameters */
            int nodeID;
            double Long, Lat;
            
            double g, h; // Heuristic variables used by the A* search
            Node* parent;
            bool openList;
            bool closedList;
            vector<pair<Node *, double>> edges; // Vector of edges connecting to each node (endNodeID, distance)

            bool operator==(Node n) const { // == operator for Node class
                return (n.Long == Long && n.Lat == Lat);
            }
        };

        void makeGraph(); // Constructs the graph by populating its node vector and initializing connections between the nodes

        /* Vector of graph nodes */
        vector<Node> graph_;

        Node * findNode(int nodeID); // Returns a pointer to a node given its index

        PNG * drawMap(); // Draws the visualization by plotting each nodes, without drawing the calculated path

        PNG * drawPath(); // Draws the visualization with the calculated path

        /* Generates a map only using the graph data without calling BFS */
        PNG * drawMapFromGraph(int Width, int Height, int margin, int nodeSize, int hue); // Draws the visualization using the graph vector, without using BFS (for verification)

        /* Takes in a vector of nodes and draws a map image */
        void _drawNodes(vector<Node> Nodes, PNG * png, int Width, int Height, int margin, int radius, int hue);

        /* Takes in a vector of node pointers and draws a map image */
        void _drawNodes(vector<Node *> Nodes, PNG * png, int Width, int Height, int margin, int radius, int hue);

        /* Draws a single node on the mpa, called by other drawing functions */
        void _drawNode(Node * Node, PNG * png, int Width, int Height, int margin, int radius, int hue);

        /* Returns the node that most closely matches the input coordinate */
        Node * findNearestCoord(double Latitude, double Longitude);

        vector<double> findLongest(); // Searches graph for longest single edge. Just a for fun function

        /* The following functions find the minimum and maximum latitude
        and longitude in the graph by searching through all the nodes */
        double findMaxLat();
        double findMinLat();
        double findMaxLong();
        double findMinLong();
        double MaxLat_, MinLat_, MaxLong_, MinLong_; // Member data variables for storing min and max latitude and longitude, used by visualization
};

//string split helpers
vector<string> _split(const string &S, char splitter);
void _split(const string &S, char splitter, vector<string> outString);