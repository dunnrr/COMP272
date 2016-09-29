/******************************************************************************
* Test program for the Implementation of findPath function
* as required for COMP 272 assignment 3 question 5.
*
* Author: Robert Ryan Dunn
* SN: 3070207
* Date: 28 September, 2016
******************************************************************************/

#include "Graph.h"

void findPath(Graph& G, char start)					//finds the path
{
	try
	{
		G.findPath(start);							//try to find path
	}
	catch (IndexOutOfBounds& err)					//show error 
	{
		cout << endl << "Exception: " << 
			err.getMessage() << endl << endl;						
	}
}

void testCase(int &test)							//prints test case value
{
	cout << "Test Case: " << test
		<< endl;
	test++;
}

int main(void)									
{
	Graph G;										//create graph
	int test = 1;									//assign test case value
	
	testCase(test);									//print out test case no.
	G.printMatrix();								//print matrix
	G.printPath();									//print path
	
	testCase(test);									//print out test case no.
	findPath(G,'q');								//find path (cause error)
	
	testCase(test);									//print out test case no.	
	findPath(G,'a');								//find path
	G.printMatrix();								//print matrix
	G.printPath();									//print path

	return EXIT_SUCCESS;
}