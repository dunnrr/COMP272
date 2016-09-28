
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
	void DFS(char x);
	void printMatrix();
	void printPath();
	void initialize(string filename);
	int matrix [SIZE][SIZE];
	char map[SIZE];
private:
	bool visited[SIZE] = {false};
	void visit(int node);
	int findUnused(int node);
//	int findUnusedEdges(int node);
	vector<char> path;
//	stack<char> S;
};
/*
int Graph::findUnusedEdges(int node)
{
	for (int i = 0; i < SIZE; i++)
		if (matrix[node][i] == 1)
}
*/
int Graph::findUnused(int node)
{
	for (int i = 0; i < SIZE; i++)
		if (matrix[node][i] == 1 && matrix[i][node] == 1)
			return i;
	return -1;
}

void Graph::visit(int node)
{
	if (visited[node])
	{
		path.push_back(map[node]);
		return;
	}
	visited[node] = true;
//	S.push(node);
	path.push_back(map[node]);
	int edge = findUnused(node);
	while(edge != -1)
	{
		matrix[node][edge] = 2;
		visit(edge);
		matrix[edge][node] = 2;
		path.push_back(map[node]);
		edge = findUnused(node);
	}

	
		
}

void Graph::DFS(char x)
{
	int node = int(x - 'a');
	visit(node);
}


void Graph::initialize(string filename)
{
	std::ifstream infile(filename);
	int temp;
	char mapChar = 'a';
	string line;
	
	int i = 0;
	while(std::getline(infile, line))
	{
		std::stringstream ss(line);
		int j = 0;
		while( ss >> temp )
		{
			matrix[i][j] = temp;
			j++;
		}
		map[i] = mapChar;
		i++;
		mapChar++;
	}
}

void Graph::printMatrix()
{
	cout << endl << endl << "  ";
	for (int i = 0; i < SIZE; i++)
		cout << map[i] << " ";
	cout << endl;
	for(int i = 0; i < SIZE; i++)
	{
		cout << map[i] << " ";
		for(int j = 0; j < SIZE; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void Graph::printPath()
{
	cout << "{";
	int i = 1;
	for (char n : path)
	{
		cout << n;
		if (i < path.size())
			cout << ", ";
		i++;
	}
	cout << "}";
}