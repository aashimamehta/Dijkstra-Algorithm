#include "graphm.h"
using namespace std;

//---------------------GraphM()------------------
//default constructor
//Preconditions: node;
//Postconditions: The nodes will be all initialized to infinity, i.e, INT_MAX
//					The nodes will be assigned "unvisited" with paths as 0.
GraphM::GraphM() 
{
	size = 0;
	for (int i = 0; i < MAXNODES; i++)
	{
		for (int j = 0; j < MAXNODES; j++) {
			T[i][j].visited = false;
			T[i][j].dist = INT_MAX;
			T[i][j].path = 0;
			C[i][j] = INT_MAX;
		}
	}
}

//---------------------GraphM::buildGraph(instream&)------------------
//builds the graph by reading the file passed
//Preconditions: the file data is in the correct format;
//Postconditions: the graph will be created according to the specifications.
void GraphM::buildGraph(istream& in) 
{

	int to, dist, from; //declare variable to get the positions
	in >> size;
	string name = "";
	getline(in, name);
	for (int i = 1; i <= size; i++)
		data[i].setData(in);
	while (in >> from >> to >> dist) {
		if (from == 0)
			break;
		C[from][to] = dist;
	}
}

//---------------------GraphM::insertEdge(int,int,int)------------------
//inserts an edge in the graph
//Preconditions: none.
//Postconditions: the graph will have one more edge in it.
void GraphM::insertEdge(int v, int v2, int edge) 
{
	if((v < 1 || v2 <1) || (v > size || v2 > size) ||(v==v2))
		return; //out of bounds
	C[v][v2] = edge; //assigns the new edge at the correct position
	findShortestPath(); //redo dijkstra
}

//-------------------------removeEdge(int,int)--------------------
//removes an edge
//Preconditions:
//Postconditions:
void GraphM::removeEdge(int v, int v2) 
{
	if (v > size || v < 1)
		return;
	if (v2 > size || v2 < 1)
		return;
	C[v][v2] = INT_MAX; //set to infinity // removed
	findShortestPath(); //do dijksta again 
}

//---------------------- getVHelper(int)---------------
//helper for findShortestPath to findnumber of nodes visited
//PreConditions: valid source is passed
//PostConditions: correct number of visited nodes will be returned
int GraphM::getVHelper(int source)
{
	int i = INT_MAX;
	int v = -1; //number of nodes visited
	for (int traverse = 1; traverse <= size; traverse++)
	{
		if (T[source][traverse].dist < i)
		{
			if (!T[source][traverse].visited)
			{
				i = C[source][traverse];
				v = traverse; //update node
			}
			else
				continue;
		}
	}
	return v; //return nodes
}

//------------------ findShortestPath() --------------------
//dijstra's algorithm
//Preconditions: none.
//Postconditions: gives out the shortestPath from one node to another.
void GraphM::findShortestPath()
{
	for (int source = 1; source <= size; source++)
	{
		T[source][source].dist = 0;
		//finds the shortest distance from source to all other nodes
		for (int i = 1; i <= size; i++)
		{
			//find number of visited nodes // used helper
			int vis = getVHelper(source);
			//mark visited?
			if (vis == -1)
				break;
			T[source][vis].visited = true;
			//for each w adjacent to v -- if w not visited
			//then visit it to find the shortest path recursively
			for (int j = 1; j <= size; j++)
			{
				if (!T[source][j].visited && C[vis][j] != INT_MAX)
				{
					if (T[source][j].dist > T[source][vis].dist + C[vis][j]) {
						T[source][j].dist = T[source][vis].dist + C[vis][j];
						T[source][j].path = vis;
					}
				}
			}
		}
	}

}


//---------------------print(int, int, string temp); -------------------
//helper for displayAll() // this method prints the path from the two ints passed 
//Preconditions: correct source, destination and string is passed,
//	             i.e, source != destination
//Postconditions: the path will be printed
void GraphM::printHelper(int source, int destination, string temp)
{
	if (T[source][destination].path > 0 && T[source][destination].path < 100) {
		printHelper(source, T[source][destination].path, temp); //recurse
		cout << T[source][destination].path << " ";
		temp += T[source][destination].path;
	}
}

void GraphM::printHelper2(int source, int destination, string temp, int word[], int i)
{
	if (T[source][destination].path > 0 && T[source][destination].path < 100) {
		printHelper(source, T[source][destination].path, temp); //recurse
		cout << T[source][destination].path << " ";
		temp += T[source][destination].path;
		word[i] = T[source][destination].path;
		i++;
	}
}

// -------------------- displayAll() ---------------------
//displays all the paths
//Preconditions: none
//Postconditions: displays/outputs all the shortest paths from all
//                node to all another, using dijkstra algorithm
void GraphM::displayAll()
{
	cout << "Desciption \t\t From_Node \t To_Node \t Dijkstra's \t Path " << endl;
	for (int i = 1; i <= size; i++) {
		cout << data[i] << endl;
		for (int j = 1; j <= size; j++) {
			//print the paths
			if (T[i][j].dist != INT_MAX && T[i][j].dist != 0) {
				cout << "\t\t\t    " << i << " \t            " << j;
				cout << " \t\t     " << T[i][j].dist << " \t ";
				string temp = "";
				string word = "";
				if (i != j)
					printHelper(i, j, temp); 
				cout << j << endl;
			}
			else{
				cout << "\t\t\t    " << i << " \t            " << j;
				cout << " \t\t     ** " << endl;
			}
		}
		cout << endl;
	}
}

// --------------- display(int, int) -----------------------
//displays the route asked
//Preconditions: none
//Postconditions: displays the shortest path form the source to destination
//                using dijkstra algorithm
void GraphM::display(int source, int des)
{
	if (T[source][des].dist != 0 && T[source][des].dist != INT_MAX)
	{
		cout << "\t\t" << source << "   " << des <<"   " << T[source][des].dist << "    ";
		string tmp= "";
		//initialiszed an array of size 100 to print elements
		int word[100];
		for (int i = 0; i < 100; i++) {
			word[i] = 0;
		}
		printHelper2(source, des, tmp, word, 0);
		cout << des << "   " << endl;
		tmp += des;
		for (int i = 0; i < 100; i++)
		{
			if (word[i] != 0) {

				int tmpData = word[i];
				cout << data[tmpData];
			}
		}
		cout << endl;
		//delete the array
		for (int i = 0; i < 100; i++) {
			word[i] = 0;
		}
	}
	else
		cout << "\t\t" << source << "   " << des << "   " << " **    " << endl;

}
