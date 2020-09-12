#include "graphl.h"
#include <iomanip>
using namespace std;

//------------------ GraphL() ------------------
//default constructor, initializes all values
//Preconditions: 
//Postconditions:
GraphL::GraphL() {
	size = 0;
	for (int i = 1; i < MAX; i++) {
		arr[i].visited = false;
		arr[i].data = NULL;
		arr[i].edgeHead = NULL;
	}
}

// ------------------------ ~GraphL() ---------------
//destructor, de-allocates pointers from the memory
//Preconditions: 
//Postconditions:
GraphL::~GraphL() {
	for (int i = 1; i <= size; i++) {
		arr[i].visited = false;
		arr[i].data = NULL;
		delete arr[i].data;
		//traverse through the list to delete all nodes
		if (arr[i].edgeHead != NULL)
		{
			EdgeNode* node = arr[i].edgeHead;
			arr[i].edgeHead = arr[i].edgeHead->nextEdge; //move pointer/edgeHead
			node = NULL;
			delete node;
		}
	}
}

// --------------------------- buildGraph(istream& in) --------------
//builds the graph
//Preconditions: the file passed is in the valid format
//Postconditions: builds the graph successfully
void GraphL::buildGraph(istream& in) {
	//get the size
	in >> size;
	string name = "";
	getline(in, name); //read the lines in the file
	for (int i = 1; i <= size; i++)
	{
		getline(in, name);
		NodeData* tmp = new NodeData(name);
		arr[i].data = tmp;
	}
	
	//know the start and end points
	int start, end;
	while (in >> start >> end)
	{
		if (start == 0)
			break;
		if (arr[start].edgeHead == NULL)
		{
			EdgeNode* node = new EdgeNode;
			node->adjGraphNode = end;
			arr[start].edgeHead = node;
			arr[start].edgeHead->nextEdge = NULL;
		}
		else
		{
			EdgeNode* node = new EdgeNode;
			node->adjGraphNode = end;
			node->nextEdge = arr[start].edgeHead;
			arr[start].edgeHead = node;
		}
	}
}

//----------------------------- displayGraph() ----------------------
//displays all the elements of the graph
//Preconditions: graph already exists
//Postconditions: creates an adjacency list, and prints it out.
void GraphL::displayGraph() {
	cout << "Graph: " << endl;
	for (int i = 1; i <= size; i++)
	{
		cout << "Node" << i << "   " << *arr[i].data << endl;
		cout << endl;
		EdgeNode* node = arr[i].edgeHead;
		while (node != NULL)
		{
			cout << setw(7) << "edge " << i << setw(2) << node->adjGraphNode << endl;
			node = node->nextEdge; //move pointer
		}
	}
}


//--------------------------- depthFirstSearchHelper(int num) ---------------------
//helper for depth first search
//Preconditions: none.
//Postconditions: the DFS order will be outputed recursively
void GraphL::depthFirstSearchHelper(int vis) {
	//print the node to get the print correct
	cout << setw(2) << vis;
	//set visited so that it wont be called again
	arr[vis].visited = true;
	
	//traverse the list
	EdgeNode* node = arr[vis].edgeHead;
	while (node != NULL)
	{
		if (!arr[node->adjGraphNode].visited)
			depthFirstSearchHelper(node->adjGraphNode);
		node = node->nextEdge; //move pointer
	}
}


//--------------------------- depthFirstSearch() ---------------------
//prints the depth first search of a graph
//Preconditions: graph exists.
//Postconditions: the DFS order will be outputed
void GraphL::depthFirstSearch() {
	cout << "Depth-first ordering: ";
	for (int i = 1; i <= size; i++)
	{
		//if the node is not yet visited then recurse using helper
		if (!arr[i].visited)
			depthFirstSearchHelper(i);
	}
}

