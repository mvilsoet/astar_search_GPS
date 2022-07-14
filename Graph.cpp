#include "Graph.h"
using Node = Graph::Node;

void Graph::makeGraph() {
    ///// Make Nodes /////
    string line;
    ifstream nodeFile("Documents/nodes.txt");
    int counter = 0;
    while(getline(nodeFile, line)) {
        vector<string> Line = _split(line, ' '); // Fetches current row of .txt as stores as string
        double longitude = stod(Line[1]); // Extracts latitude from string and stores as int
        double latitude = stod(Line[2]); // Extracts longitude
        graph_.push_back(Node(longitude, latitude));
        graph_.back().nodeID = counter;
        counter++;
    }
    ///// Build Edges /////
    ifstream edgeFile("Documents/edges.txt");
    while(getline(edgeFile, line)) {
        vector<string> Line = _split(line, ' '); // Fetches current row of .txt as stores as string
        int startNodeIndex = stoi(Line[1]); // Converts node indices from string to int
        int targetNodeIndex = stoi(Line[2]);
        double distance = stod(Line[3]); // Converts node distance from string to double
        Node * startNode = &graph_[startNodeIndex]; 
        Node * targetNode = &graph_[targetNodeIndex]; // Creates a pointer to node with index from file
        graph_[startNodeIndex].edges.push_back(make_pair(targetNode, distance)); // Adds to current node's edge vector
        graph_[targetNodeIndex].edges.push_back(make_pair(startNode, distance));
    }
    MinLat_ = findMinLat();
    MinLong_ = findMinLong();
    MaxLat_ = findMaxLat();
    MaxLong_ = findMaxLong();
}

vector<double> Graph::findLongest() {
    double dist = 0, I = 0, J = 0;
    vector<double> result = {};

    for(double i = 0; i < graph_.size(); i++)
        for(double j = 0; !graph_[i].edges.empty() && j < graph_[i].edges.size(); j++)
            if(graph_[i].edges[j].second > dist) {
                dist = graph_[i].edges[j].second;
                I = i; J = j;
            }

    result.push_back(dist);
    result.push_back(I);
    result.push_back(J);

    return result;
}

Node * Graph::findNearestCoord(double Latitude, double Longitude) {
    Node * closest = NULL;
    double curBestDist = 2147483647;
    for(unsigned int i = 0; i < graph_.size(); ++i) {
        Node * cur = &graph_[i];
        double curNodeDist = (Latitude - cur->Lat) * (Latitude - cur->Lat) + (Longitude - cur->Long) * (Longitude - cur->Long);
        if(curNodeDist < curBestDist) {
            curBestDist = curNodeDist;
            closest = cur;
        }
    }

    return closest;
}

PNG * Graph::drawMap() {
    return NULL;
}

PNG * Graph::drawMapFromGraph(int Width, int Height, int margin, int radius, int hue) {
    PNG * png = new PNG(Width + 2 * margin, Height + 2 * margin);
    _drawNodes(graph_, png, Width, Height, margin, radius, hue);

    return png;
}

void Graph::_drawNodes(vector<Node> nodes, PNG * png, int Width, int Height, int margin, int radius, int hue) {
// Iterate through the vector and print it node-by-node
    for(unsigned int i = 0; i < nodes.size(); ++i)
        _drawNode(&nodes[i], png, Width, Height, margin, radius, hue);
}

void Graph::_drawNodes(vector<Node *> nodes, PNG * png, int Width, int Height, int margin, int radius, int hue) {
    for(unsigned int i = 0; i < nodes.size(); ++i)
        _drawNode(nodes[i], png, Width, Height, margin, radius, hue);
}

void Graph::_drawNode(Node * node, PNG * png, int Width, int Height, int margin, int radius, int hue) {
    double curLat = node->Lat;
    double curLong = node->Long;

    int x = Width * (curLong - MinLong_)/(MaxLong_ - MinLong_);
    int y = Height * (curLat - MaxLat_)/(MinLat_ - MaxLat_);

    if(radius >= margin) 
        radius = 0; // Exceeds limit testcase?!?! // Change to helper function or just reuse code

    for(int X = (x + margin) - radius; X <= (x + margin) + radius; X++)
        for(int Y = (y + margin) - radius; Y <= (y + margin) + radius; Y++)
            if((X - (x + margin)) * (X - (x + margin)) + (Y - (y + margin)) * (Y - (y + margin)) <= radius * radius) {
                cs225::HSLAPixel & pixel = png->getPixel(X, Y);
                pixel.h = hue;
                pixel.s = 1;
                pixel.l = 0.5;
            }
}

PNG * Graph::drawPath() {  // Temporary so the compiler doesn't complain
    PNG * png = NULL;
    return png;
}

void _drawNodeSize(cs225::HSLAPixel & pixel, int nodeSize) {
    pixel.h = 300;
    pixel.s = 1;
    pixel.l = 0;
    pixel.a = 1;
}

template <typename Out> // Find a way to use without templating
void _split(const string &S, char splitter, Out outString) {
    istringstream Stream(S);
    string val;
    while (getline(Stream, val, splitter))
        *outString++ = val;
}

vector<string> _split(const string &S, char splitter) {
    vector<string> elems;
    _split(S, splitter, back_inserter(elems));
    return elems;
}

Node * Graph::findNode(int NodeID) {
    return &graph_.at(NodeID);
}

double Graph::findMaxLat() {
    double MaxLat = -2147483647;
    for(unsigned int i = 0; i < graph_.size(); ++i)
        if(graph_[i].Lat > MaxLat)
            MaxLat = graph_[i].Lat;

    return MaxLat;
}

double Graph::findMinLat() {
    double MinLat = 2147483647;
    for(unsigned int i = 0; i < graph_.size(); ++i)
        if(graph_[i].Lat < MinLat)
            MinLat = graph_[i].Lat;

    return MinLat;
}

double Graph::findMaxLong() {
    double MaxLong = -2147483647;
    for(unsigned int i = 0; i < graph_.size(); ++i)
        if(graph_[i].Long > MaxLong)
            MaxLong = graph_[i].Long;

    return MaxLong;
}

double Graph::findMinLong() {
    double MinLong = 2147483647;
    for(unsigned int i = 0; i < graph_.size(); ++i)
        if(graph_[i].Long < MinLong)
            MinLong = graph_[i].Long;

    return MinLong;
}