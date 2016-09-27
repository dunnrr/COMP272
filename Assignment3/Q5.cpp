#include "Graph.h"

int main(void)
{
	Graph G;
	G.initialize("AdjacencyMatrix.txt");
	G.printMatrix();
	G.printPath();
	G.DFS('g');
	G.printPath();
	G.printMatrix();
	return 0;
}