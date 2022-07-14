#include <iostream>
#include "BFS.h"
#include "Graph.h"
#include "AStarSearch.h"

using namespace std;

void MapQuest(double startLat, double startLong, double endLat, double endLong);

int main() {
  /// Run the program by entering your desired starting and ending coordinates below as:
  /// (Starting Latitude, Starting Longitude, Ending Latitude, Ending Longitude)
  MapQuest(37.8199, -122.4783, 33.8121, -117.9190);
 
  return 0;
}

void MapQuest(double startLat, double startLong, double endLat, double endLong) {
  Graph graph;
  graph.makeGraph();
  int Width = 1000;
  int Height = 1000;
  int Margin = 20;
  cs225::PNG * png = new PNG(Width + 2 * Margin, Height + 2 * Margin);
  BFS bfs = BFS(&graph, &graph.graph_[0]);
  graph._drawNodes(bfs.returnVec(), png, Width, Height, Margin, 2, 35);
  Node * StartNode = graph.findNearestCoord(startLat, startLong);
  Node * EndNode = graph.findNearestCoord(endLat, endLong);

  int Begin = StartNode -> nodeID;
  int End = EndNode -> nodeID;

  Node * StartPath = graph.Graph::findNode(Begin);
  Node * EndPath = graph.Graph::findNode(End);
  AStarSearch Search(StartPath, EndPath);
  bool pathFound = Search.search();
  if(pathFound) {
    double distance = Search.getDistance();
    cout << "Distance from start to end: " << distance << endl;
    cout << "Successfully found path : " << pathFound << endl;
    vector<Node *> Route = Search.getRoute();
    cout << "Number of waypoints to traverse: " << Route.size() << endl << endl;
    cout << "Path of nodes to follow:" << endl;
    cout << Begin << " (Start)";
    bool first = 1; // ?
    for (Node * node : Route) {
      cout << " -> " << node->nodeID;
    }
    cout << " (End)";
    cout << endl << endl << "Euclidean distance from start point to end point: " << AStarSearch::findEuclideanDistance(StartPath, EndPath) << endl;
    graph._drawNodes(Route, png, Width, Height, Margin, 4, 222);
  }
  else
    cout << "No route exists between given points!" << endl;

  png->writeToFile("MyMap.png"); // Saves your desired path into visualization on a map of California
  delete png;
}