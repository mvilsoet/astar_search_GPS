Final Presentation Video Link:
https://youtu.be/MYgL5We6MSc
 
 
 
Our final products include a Graph class that models our dataset, A star search, BFS traversal, and a visualization of the result of our A star search along with each node plotted on an outline of California. Our program outputs a PNG of the map with the shortest route highlighted in red, given an input of two coordinates. It also returns the nodes in the route and the total distance. 
 
 
 
Graph Class
 
Node Struct: The Graph class contains a Node struct that stores information about each node in our dataset. Each node corresponds to an intersection of 2 roads in California and stores its NodeID (indexed 0 - 21,047) as well as its latitude and longitude (Lat and Long). The Node struct also contains a vector<Node *, double> of each adjacent Node and its distance away from the parent node. The Node struct also contains some variables needed for the A star search: double g and f values and bool openList and ClosedList values. 
 
Graph Implementation: Our graph itself is a vector of Nodes, with each Node’s index as its NodeID. One of the main functions within the Graph class is makeGraph() which reads the data from our dataset and constructs the vector of Node along with the Nodes themselves. The functions for our graph visualization (described later) are also within this class and are called drawMap() and drawPath(). The code for our graph functions can be found in the Graph.cpp and Graph.h files.
 
 
 
A Star Search
 
The A star search features 3 main functions. The first is a search() function that returns a bool “true” if the search was successful and “false” if no path between 2 nodes exists. The second is a getRoute() function that returns a vector of pointers to each Node in the shortest path. The third is a getDistance() function that returns the distance of the shortest path between 2 Nodes in miles. The main search function uses a few helper functions, specifically: addNeighbors() to add the nodes neighboring the current node to the search, findFScore() to calculate the f value of a node, findEuclideanDistance() to find the heuristic value from the current node to the destination, and findRoute() to trace and store the route once the search is completed using the parent pointers starting from the destination node.
 
The algorithm operated off of three parameters, specifically the heuristic of Euclidean distance to the goal from the current node, the g value of total distance traveled up to the current node, and the f score as the sum of these two costs. The current g and h score were stored in each node, so they could be easily accessed using the node pointers. Node pointers were used to access the adjacent nodes, to eliminate the need for a lookup of the node in the entire graph. The open list was implemented as a priority queue which visited nodes with the minimum f value first.  It stored these as pairs of node pointers and their respective f score to quickly compare and determine the optimal direction to expand the search. A custom comparator was built to compare only the second f score value when ordering the priority queue. Booleans were used to mark whether a node was in the open or closed list of the search, to eliminate the need to iterate through the vector or queue when adding new neighbors to the search. Because of the implementation using variables in the nodes, only one a* search can be conducted at a time, after it is completed it will store the route and distance to be returned by helper functions. When the search function is complete it resets the booleans and g and h values in each node searched. 
 
The worst case runtime of A* is the same as Dijkstra's Algorithm, where O(bn), where b is the average branching of each node.  However, its runtime is much faster, as there are few obstacles in the road network, meaning the effective branching factor, b*, is much smaller as many edges can be eliminated based on the heuristic, as the route rarely travels away from the destination.
 
The code for A star search can be found in the AStarSearch.cpp and AStarSearch.h files.
 


BFS Traversal
 
The BFS algorithm carries out a traversal by implementing an Iterator that travels from a given starting Node and visits every point in the graph, starting with the ones closest to the starting node. The beginning and end iterators for the BFS are given by begin() and end(). begin() will create an iterator pointing to the given starting Node and end() will create an iterator with a nullptr. We tested that this algorithm was functional by using the Iterator to iterate through the graph, keeping track of the number of iterations. We then compared this number to our known number of nodes in the dataset.
 
The BFS class stores a pointer to the Graph to iterate through and a pointer to the Node to start from. In addition, it contains a queue of Node pointers to keep track of the traversal as well as a vector of booleans to keep track of which Nodes have been visited. Since each Node has its own NodeID indexed 0 - 21047, the vector can be easily indexed into using the node’s NodeID.
 
The traversal itself is mainly done with the ++ operator. First, the current Node’s “edge” vector (a vector with all of its adjacent Nodes) is looked through. This step will take O(n) time, since the worst case will be if a Node is adjacent to every other node. Secondly, each of the adjacent nodes are checked to see if they have been visited. This is done in O(1) time, since it only requires indexing into a vector. If an adjacent Node is unvisited, it will be added to the queue and marked as visited in O(1) time, as well. Each node is initially set as “false” within the BFS constructor by iterating through Graph’s vector of Nodes in O(n) time. Finally, the next Node in the traversal will be the front of the traversal queue. In order to handle unconnected segments, a helper function getNextUnvisited() will be called when the traversal queue is empty to check if all nodes have been visited. This helper function will iterate through the vector of booleans, and if there is an unvisited Node, it will be returned. Otherwise, the function returns NULL. The worst case for this step is if we have to look through “n” nodes to find the next unvisited, making the runtime O(n). Overall, the runtime for the BFS is O(n) time, which matches our proposed runtime. 
 
We ensured that BFS worked correctly by iterating through the entire graph and counting each Node that was visited. We compared this count to the known number of nodes, 21048. We also ran additional tests from multiple starting nodes to ensure that every node was still visited.
 
The code for BFS can be found in the BFS.cpp and BFS.h files.
 
 
 
Graph Visualization
 
The first visualization that we implemented was a simple visualization of the graph using the nodes contained within the graph’s node vector member. This visualization was generated by parsing through the node vector and extracting the latitude and longitude of each node. Then, each pair of latitudes and longitudes was scaled in accordance with the width and height of the visualization image. This scaling is dynamic and able to change with the image size, and the visualization nodes will be generated regardless of scale (and look better at higher resolutions, of course). Plotting all the nodes from the graph generated a thorough enough sampling of the map of California to generate an image that creates an outline of California.
 
The second visualization that we implemented is visualizing the ideal shortest path from a starting node to an ending node using the output of the A* algorithm. This was done similarly to the first visualization, except with each Node in the shortest path (from the vector returned by the A star search) highlighted. 
 
 
 
Application
 
To apply our project to a real-world problem, we decided to use our program to find the shortest path between the Golden Gate Bridge and Disneyland. This required adding a function that takes a latitude and longitude and finds the node that is the closest match. This allowed the A star search (which takes nodes as parameters) to be used on any longitude and latitude within California. To test the accuracy of our program, we compared our output to the path given by Google maps. We found that our output matched the given path fairly well, leading us to believe that both our algorithms and visualization were successful.
