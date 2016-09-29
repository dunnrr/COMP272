/******************************************************************************
* Implementation of a specific graph for Quesion 5 of Assignment 3 in COMP 272
*
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		28 August, 2016
******************************************************************************/


#ifndef _GRAPH_H_
#define _GRAPH_H_


#include "RuntimeException.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::stack;

const int SIZE = 16;

class Graph
{
public:
	Graph();										//constructor
	void findPath(char x);							//find path
	void printMatrix();								//print matrix
	void printPath();								//print path
protected:
	void addEdge(char i, char j);					//add edge
	int matrix [SIZE][SIZE] = {0};					//adjacency matrix
	char map[SIZE];									//array of nodes
	bool visited[SIZE] = {false};					//array of visited nodes
	void visit(int node);							//visit node
	int findUnused(int node);						//find an unused path
	vector<char> path;								//path
};

Graph::Graph() 										//constructor
{ 
	for (int i = 0; i < SIZE; i++)					//initialize map
		map[i] = 'a' + i;
													
	addEdge('a','b');								//add edges
	addEdge('a','e');
	addEdge('a','f');
	addEdge('b','c');
	addEdge('c','d');
	addEdge('c','f');
	addEdge('d','g');
	addEdge('e','i');
	addEdge('f','j');
	addEdge('g','h');
	addEdge('g','j');
	addEdge('g','k');
	addEdge('h','o');
	addEdge('i','j');
	addEdge('i','m');
	addEdge('i','n');
	addEdge('k','o');
	addEdge('l','p');
	addEdge('n','o');
	addEdge('o','p');
}					

void Graph::findPath(char x)						//find path
{
	int node = int(x - 'a');						//convert character to int
	if (node < 0 || node >= SIZE)					//is index out of bounds?
		throw IndexOutOfBounds(
			"Index given is out of bounds.");		//throw error
	visit(node);									//visit first node
}

void Graph::printMatrix()							//print matrix
{
	cout << endl << "Matrix: " <<  endl << "  ";	
	for (int i = 0; i < SIZE; i++)					//show map columns
		cout << map[i] << " ";
	cout << endl;
	for(int i = 0; i < SIZE; i++)					//show map rows
	{
		cout << map[i] << " ";
		for(int j = 0; j < SIZE; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void Graph::printPath()								//print path
{
	cout << "Path: {";
	int i = 1;
	for (char n : path)								//for all items in path
	{
		cout << n;
		if (i < path.size())
			cout << ", ";
		i++;
	}
	cout << "}" << endl << endl;
}

void Graph::addEdge(char i, char j)					//add edge
{
	int n = i - 'a';								//convert to integer
	int m = j - 'a';								//convert to integer
	if ( (n < 0 || n >= SIZE) || 
		(m < 0 || m >= SIZE))						//is index out of bounds?
		throw IndexOutOfBounds(
			"Index given is out of bounds.");		//throw error
	matrix[n][m] = 1;								//assign edge
	matrix[m][n] = 1;								
}

void Graph::visit(int node)							//visit node
{
	path.push_back(map[node]);						//add node to path
	if (visited[node])								//check if visited
	{
		return;										//return
	}
	visited[node] = true;							//set node to visited
	int edge = findUnused(node);					//find unused path
	while(edge != -1)								//while unused paths
	{
		matrix[node][edge] = 2;						//mark edge as used one way
		visit(edge);								//visit node
		matrix[edge][node] = 2;						//mark edge as used two way
		path.push_back(map[node]);					//add node to path
		edge = findUnused(node);					//find unused edge
	}
}

int Graph::findUnused(int node)						//find an unused path
{
	for (int i = 0; i < SIZE; i++)					//for all possible paths
		if (matrix[node][i] == 1 && 
			matrix[i][node] == 1)					//is path unused?
			return i;								//return path
	return -1;										//return path not found
}

#endif


