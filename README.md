# shimkus3-tfshaik2-mvilso2-meganmz2
Final Project for shimkus3-tfshaik2-mvilso2-meganmz2

## (1) Files, Data, Results


Overall, our project uses coordinates and edge connections from two datasets and converts it into a vector of nodes that someone could follow in real life to reach a destination in California. There are four main files that hold the important aspects. Graph.cpp/h reads in the datasets and creates a graph data structure of our roadmap. In addition, the graph class invokes these algorithms and outputs a png image that is useful to the end user. Next, BFS.cpp/h and AStarSearch.cpp/h are the implementations of the alrogithms that we use to traverse our graph. BFS is a breadth-first-search that finds the optimal path by brute force. AStarSearch is a greedy algorithm which uses minimum distance as our heuristic. Finally, main.cpp uses these three objects to output the map and desired path onto a png. 

## (2) Steps to run the project


Open terminal in main directory of project, type: 

  ``make``       //uses makefile to compile all files
  
  ``./roadmap``  //will output RoadTrip.png as a test case
  
  
  To add your own path, navigate to line 13 of main.cpp and input the coordinates of the start and endpoint in MapQuest(StartLat, StartLong, EndLat, EndLong). When roadmap.exe is executed at this time, the output MyMap.png will contain the  shortest path between the nearest nodes to the input in our dataset.
  
  
## (3) Steps to run the testing suite

Open terminal in main directory of project, type:

  ``make test``  //testing suite
  
  ``./test``     //run test cases to validate
  
  
The first three test cases ensure our graph correctly converts the dataset into a graph of nodes with the correct data in them. Five test cases ensure that A* returns the correct path in both adjacent nodes and nodes with various amounts of edges between each other. Three more test cases similarly test the BFS search. A test case ensures that both searches run in a reasonable amount of time (less than a few seconds). Finally, some test cases test the final output map. RoadTrip.png is our example that would be verified by hand with Google Maps. Our presentation shows the successful output from Disney Land to Golden Gate and YourMap.png can be verified similarly with Google Maps.
