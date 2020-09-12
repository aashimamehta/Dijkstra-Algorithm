#pragma once
#pragma once
#include <climits>
#include "nodedata.h"
using namespace std;

const int MAXNODES = 100;

class GraphM {
private:
	NodeData data[MAXNODES];
	int C[MAXNODES][MAXNODES];
	int size;
	struct TableType {
		bool visited;      //whether the node has been visited
		int dist;			//shortest distance from source known so far
		int path;			//previous node in path of min dist
	};
	TableType T[MAXNODES][MAXNODES];

	//utility functions
	int getVHelper(int source);
	void printHelper(int source, int destination, string temp);
	void printHelper2(int source, int destination, string temp, int[], int i);

public:
	GraphM(); //constructor
	void buildGraph(istream &i); //builds the graph
	void insertEdge(int v, int v2, int edge); //inserts an Edge
	void removeEdge(int v, int v2); //removes an edge
	void findShortestPath(); //dijstra's algorithm
	void displayAll(); //displays all the paths
	void display(int source, int des); //displays the route asked

};