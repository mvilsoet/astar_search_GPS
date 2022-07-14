/* 
 * @file BFS.h
 */

#pragma once
#include <queue>
#include <vector>
#include <map>
#include <iterator>
#include "Graph.h"
using Node = Graph::Node;

/*
 * Breadth-first traversal of our implementation of a graph
 * Traverses each node of the graph given a starting node
 * Provides a traversal by returning instances of Iterator
 */
class BFS {
    public:
        /* 
         * Constructor for a BFS object - takes pointer to a Graph to iterate through and pointer to Node to start from
         * @param graph The graph to run the traversal on
         * @param start The node in the graph to start the traversal from
         *
         */
        BFS(Graph * graph, Node * start); 

        /* 
         * A forward iterator through a Graph
         */ 
        class Iterator : std::iterator<std:: forward_iterator_tag, Node> {
            public:
                /*
                 * Default constructor - creates iterator with curr_node as a nullptr
                 */
                Iterator();

                /* 
                 * Constructor: takes a Node pointer and an instance of a BFS object
                 * @param curr_node The node that the iterator is currently pointing to
                 * @param bfs An instance of the BFS class with the graph and starting node to run the traversal on
                 *
                 */
                Iterator(Node * curr_node, BFS * bfs);

                /*
                 * Overloaded operator++
                 * @return an Iterator reference containing the next node in the traversal
                 *
                 */
                Iterator operator++();

                /*
                 * Overloaded operator*
                 * @return a reference to the Node contained within this instance of Iterator
                 *
                 */
                Node & operator*(); // return by reference because Node has decently large amount of data

                /*
                 * Overloaded operator!=
                 * @param other The instance of Iterator to compare to "this" Iterator
                 * @return a boolean describing if the traversal is over (if the curr_node is nullptr)
                 *
                 */
                bool operator!=(Iterator & other);

            private:
                /* 
                 * Private Iterator member variables: Address of the node that this instance of Iterator points to and instance of BFS
                 * containing the graph and starting node to run the traversal on
                 */
                Node * curr_node; 
                BFS * bfs_; // In order to access BFS member variables

        };

        /*
         * Beginning of an iterator 
         * @return an Iterator pointing to the first node in the traversal
         *
         */
        Iterator begin();

        /* 
         * End of an iterator 
         * @return an Iterator pointing to nullptr
         *
         */
        Iterator end();

        /*
         * Helper functions 
         */ 

        /*
         * Marks the given node as "visited"
         * @param node The node to mark "visited"
         *
         */
        void markVisited(Node * node);

        /*
         * Returns whether or not the node has been visited
         * @param node The node to lookup
         * @return true if node has been visited, false if otherwise
         *
         */
        bool getVisited(Node * node);

        /*
         * Returns pointer to the next unvisited node
         * @return the pointer to the next unvisited node, returns NULL if no unvisited
         *
         */
        Node * getNextUnvisited();

        /*
         * Returns the next node of the traversal and deletes it from the traversal queue
         * @return pointer to the next node in the traversal
         *
         */
        Node * pop();

        /*
         * Returns a vector of nodes in traversal-order - used in visualization
         * @return a vector of Nodes in the order which they were traversed
         *
         */
        vector<Node> returnVec();
        
    private:
        //Graph to run the traversal on, starting node to run the traversal from
        Graph * graph_;
        Node * start_;

        // Keeps track of which nodes have been visited based on the Node's NodeID
        std::vector<bool> visitedNodes;

        // Keeps track of the nodes for the BFS traversal
        std::queue<Node*> nodes; 
};