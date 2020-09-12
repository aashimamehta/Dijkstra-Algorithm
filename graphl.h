#pragma once
#include <iostream>
#include "nodedata.h"
using namespace std;

const int MAX = 100;

class GraphL {
private:
	struct EdgeNode;
	struct GraphNode{
		EdgeNode * edgeHead;
		NodeData* data;
		bool visited;
	};
	GraphNode arr[MAX];
	int size;
	struct EdgeNode {
		int adjGraphNode;
		EdgeNode* nextEdge = NULL;
	};

	//utility functions
	void depthFirstSearchHelper(int num);

public:
	GraphL();
	~GraphL();
	void buildGraph(istream& in);
	void displayGraph();
	void depthFirstSearch();
};