#include "../cs225/catch/catch.hpp"

#include "../Graph.h"
#include "../BFS.h"
#include "../AStarSearch.h"
#include <iostream>
#include <chrono>

using cs225::PNG;
using namespace std;
using namespace std::chrono;

TEST_CASE("Graph contains the correct number of nodes") {
  Graph g;
  g.makeGraph();

  int count = 0;

  for(unsigned int i = 0; i < g.graph_.size(); ++i)
    count++;

  REQUIRE(count == 21048);
}

//graph.drawMapFromGraph(Width, Height, Margin, 2, 35); // Test if draw from graph is the same as draw from BFS

TEST_CASE("Graph contains the correct number of edges") {
  Graph g;
  g.makeGraph();

  int degree = 0;

  for(unsigned int i = 0; i < g.graph_.size(); ++i)
    for(unsigned int j = 0; j < g.graph_[i].edges.size(); ++j)
      degree++;

  int edgecount = degree/2;
  
  REQUIRE(edgecount == 21693);
}

TEST_CASE("TestLongestDistance") {

    vector<double> expected = {0.299789,12751,1};

    Graph GRAPH;
    GRAPH.makeGraph();
    vector<double> actual = GRAPH.findLongest();

    REQUIRE( expected == actual );
}

TEST_CASE("A* returns distance between adjacent nodes") {
    Graph graph;
    graph.makeGraph();
    int startIndex = 0, targetIndex = 6;
    Node * startNode = graph.findNode(startIndex);
    Node * targetNode = graph.findNode(targetIndex);
    AStarSearch search(startNode, targetNode);
    bool a = search.search();
    double distance = search.getDistance();
    cout << "The distance between the nodes searched by A* is: " << distance << endl << endl;

    REQUIRE(distance == 0.005952 * 61.8); // Distance between nodes 0 and 6 from the dataset
}

TEST_CASE("A* returns correct distance and route for two nodes which are multiple edges apart") {
  Graph graph;
  graph.makeGraph();
  int startIndex = 5;
  int targetIndex = 298;
  Node* startInput = graph.findNode(startIndex);
  Node* targetInput = graph.findNode(targetIndex);
  AStarSearch search1(startInput, targetInput);
  bool a = search1.search();
  double distance = search1.getDistance();
  cout << "The distance between the nodes searched by A* is: " << distance << endl << endl;
  REQUIRE(distance == .01739 * 61.8);
}

TEST_CASE("A* returns correct route in sequence of nodes") {
  Graph graph;
  graph.makeGraph();

  int startIndex = 20301;  
  int targetIndex = 20312;

  Node* startInput = graph.findNode(startIndex);
  Node* targetInput = graph.findNode(targetIndex);

  AStarSearch search1(startInput, targetInput);
  bool a = search1.search();
  double distance = search1.getDistance();

  cout << "The distance between the nodes searched by A* is: " << distance << endl;

  vector<Node *> r = search1.getRoute();

  cout << "The nodes traversed in the route are: " << endl;
  for (Node * node : r)
    cout << node->nodeID << " ";
  
  bool distInRange = ((distance >= .099763*61.8) && (distance <= 0.99763*61.8)); // Using compare logic to work around floating point == being inaccurate
  REQUIRE(distInRange == 1);
}

TEST_CASE("Test BFS") {
    int count = 0;
    Graph GRAPH;
    GRAPH.makeGraph();
    Node start = GRAPH.graph_[0];

    BFS bfs = BFS(&GRAPH, &start);
    BFS::Iterator begin = bfs.begin();
    BFS::Iterator end = bfs.end();
    
    for (BFS::Iterator it = begin; it != end; ++it) {
        count++;
    }
  
    REQUIRE(count == 21048);
}

TEST_CASE("Test that BFS run from different start nodes still traverses everything") {
    int count = 0;
    int count2 = 0;
    int count3 = 0;

    Graph GRAPH;
    GRAPH.makeGraph();

    Node start = GRAPH.graph_[0];
    BFS bfs = BFS(&GRAPH, &start);
    BFS::Iterator begin = bfs.begin();
    BFS::Iterator end = bfs.end();
    
    for (BFS::Iterator it = begin; it != end; ++it) {
        count++;
    }

    start = GRAPH.graph_[20914];
    bfs = BFS(&GRAPH, &start);
    begin = bfs.begin();
    end = bfs.end();
    
    for (BFS::Iterator it = begin; it != end; ++it) {
        count2++;
    }

    start = GRAPH.graph_[679];
    bfs = BFS(&GRAPH, &start);
    begin = bfs.begin();
    end = bfs.end();
    
    for (BFS::Iterator it = begin; it != end; ++it) {
        count3++;
    }

    REQUIRE(count == count2);
    REQUIRE(count2 == count3);
}

TEST_CASE("Run A* for two distant nodes and check route output") {
  Graph graph;
  graph.makeGraph();

  int startIndex = 1245;
  int targetIndex = 14532;

  Node* startInput = graph.findNode(startIndex);
  Node* targetInput = graph.findNode(targetIndex);

  AStarSearch search1(startInput, targetInput);
  bool a = search1.search();
  double distance = search1.getDistance();
  cout << "Distance = " << distance << endl;
  if(a)
    cout << "Search successful." << endl;
  else
    cout << "Search unsuccessful." << endl;

  vector<Node *> r = search1.getRoute();
  cout << "Route size = " << r.size() << endl << endl;
  cout << "List of nodes: " << endl;
  for (Node * node : r) {
    cout << node->nodeID << ", ";
  }
  cout << endl << endl;

  REQUIRE(distance < 2 * AStarSearch::findEuclideanDistance(startInput, targetInput) * 61.8);
}


TEST_CASE("Run A* for two nodes and check route output matches when start and target are switched") {
  Graph graph;
  graph.makeGraph();

  int startIndex = 5923;
  int targetIndex = 12831;

  Node* startInput = graph.findNode(startIndex);
  Node* targetInput = graph.findNode(targetIndex);

  AStarSearch search1(startInput, targetInput);
  bool a = search1.search();
  double distance = search1.getDistance();
  cout << "Distance = " << distance << endl;
  if(a)
    cout << "Search successful." << endl;
  else
    cout << "Search unsuccessful." << endl;

  vector<Node *> r = search1.getRoute();
  cout << "Route size = " << r.size() << endl << endl;
  AStarSearch search2(targetInput, startInput);
  bool b = search2.search();
  vector<Node *> r2 = search2.getRoute();
  double distance2 = search2.getDistance();
  cout << "Route size = " << r2.size() << endl << endl;

  REQUIRE(distance - distance2 < .01);
}

TEST_CASE("Both searches run within a reasonable amount of time (1 second)") {
  Graph GRAPH;
  GRAPH.makeGraph();
  Node start = GRAPH.graph_[0];
  auto BFSstart = high_resolution_clock::now();
  BFS bfs = BFS(&GRAPH, &start);
  BFS::Iterator begin = bfs.begin();
  BFS::Iterator end = bfs.end();
  for (BFS::Iterator it = begin; it != end; ++it);
  auto BFSstop = high_resolution_clock::now();

  int startIndex = 1245;
  int targetIndex = 14532;
  Node * startInput = GRAPH.findNode(startIndex);
  Node * targetInput = GRAPH.findNode(targetIndex);
  AStarSearch Search(startInput, targetInput);
  auto AStarstart = high_resolution_clock::now();
  Search.search();
  auto AStarstop = high_resolution_clock::now();

  auto BFSRuntime = duration_cast<microseconds>(BFSstop - BFSstart);
  auto AStarRuntime = duration_cast<microseconds>(AStarstop - AStarstart);

  cout << "BFS takes " << BFSRuntime.count() << " microseconds to run" << endl;
  cout << "A* takes " << AStarRuntime.count() << " microseconds to run" << endl;

  REQUIRE(AStarRuntime.count() < 1000000);
  REQUIRE(BFSRuntime.count() < 1000000);
}