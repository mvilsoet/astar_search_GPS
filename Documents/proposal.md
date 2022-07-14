Final Project Proposal (Due Nov 8th)

Taylor Shimkus, Megan Zhou, Michael Vilsoet, Tabish Shaik

Real Datasets for Spatial Databases: Road Networks and Category Points (utah.edu)

Link: https://www.cs.utah.edu/~lifeifei/SpatialDataset.htm

Leading Question: We want to create a program that will build a route given two data points, where the route covers the shortest distance possible. So given an input of two points the program will determine the minimum distance and roads to take to get from one point to the other. It will also give a map visualization of the route. For this our database is targeting roads in California so our visualization will be specific to California, however the search algorithm will be general and usable for any set of roads given the same data format.

Dataset Acquisition and Processing: We will be using two public datasets for the California Road Network and Points of Interest, posted by SSTD 2005 (On Trip Planning Queries in Spatial Databases). The dataset contains, in order of columns, dataset 1: (Edge ID, Start Node ID, End Node ID, L2 Distance), and dataset 2: (Node ID, Longitude, Latitude). This will be processed into a graph where each intersection of roads is represented by a vertex, with the roads represented by edges between the vertices, and each edge is given a weight based on the distance of the road based on the datasets distance information. The road dataset given to us is likely missing smaller roads and paths that might alter the results of our graph, but we believe that the variation between including and excluding these small paths is minimal, and the purpose of our search is to provide a higher-level overview of the path with larger roads. We also believe that there is a robust enough network to not run into dead ends or problematic cases of “missing” data.

Graph Algorithms: The algorithms we will be implementing an A* search algorithm to answer our leading question and give us the ideal path to take for our road trip, and a BFS traversal of the graph to traverse the entirety of the graph. The inputs for our A-star algorithm will be the start and end node we want to travel between. We have longitude and latitude for each node which will be included in the Node struct. To calculate distances(our weight parameter), take the absolute difference between the coordinates and convert it to a distance metric such as meters. This will result in a weight for each edge that can be a heuristic to inform our A-star search. The heuristic function is the Euclidean distance of the current node from the destination node, calculated using the latitude and longitude values. The actual cost function, g(n), will be calculated using the total of the distances of the edges between the traversed nodes.

We will also be implementing a graphical representation of the route solutions on a map of California. The BFS will be used to traverse the graph and plot each node on the map image. This visualization will comprise the data points of our path projected onto the scaled map image to show the path of edges between the start and endpoint. The expected output should be a list of edges (roads) to traverse to reach the input points in a minimum length graph walk, as well as a graphical representation of this route on a map so that our results can be more easily interpreted and understood. For our graphical representation, we will plot all of the nodes on a scaled image of California and highlight the edges used in our A-star algorithm. 

Expected Runtimes: The time complexity of A* of an unbounded search space, is O(b^n), where b is the branching factor (the average number of successors per state) and n is the number of nodes in the graph (A-star search algorithm - Wikipedia (odu.edu)). The expected time complexity of our traversal is O(n), since each node will be visited while traversing. Finally, the expected time complexity of our visualization is O(n) because the longest possible path could be the whole graph (of n nodes), and an edge will need to be highlighted between each of these nodes.

Timeline:

Week 0

Initial planning and project proposal
We discussed goals and decided on a project plan. We will continue fleshing out details for the goals of our project
We are also performing the background research necessary to understand the problem we are trying to solve and beginning to think about how we want to design our project around our dataset

Week 1

Completing and formalizing the list of goals, and attempting to make documentation for our basic helper functions and classes to convert our data into a graph, and easily retrieve data.

Week 2

Implementing the BFS of our graph. Start implementing the A* search algorithm.
We can first test our algorithm on smaller data sets, even data sets that we generate solely for the purpose of testing to ensure their functionality

Week 3

Completing A-star algorithm
Transitioning to use the full extent of the road dataset from any smaller testing subsets
Begin mapping the nodes and edges in our dataset visually on a map image California

Week 4

Complete and refine the mapped portrayal of data
Implement route drawing on the map, given output of our search algorithm
Work on resolving remaining bugs and issues in our code
Try to optimize our search algorithms and other aspects of our project that could be better scaled
Prepare our presentation and finalize our documentation
