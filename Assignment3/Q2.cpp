/******************************************************************************
* Test program for the Implementation of Binary Search Tree AVL rotation
* to convert one binary search tree to another as required for 
* COMP 272 assignment 3 question 2.
*
* Author: Robert Ryan Dunn
* SN: 3070207
* Date: 26 August, 2016
******************************************************************************/

#include "BSTTransform.h"
#include <iostream>
#include <random>
#include <time.h>



using std::cout;
using std::endl;

void createTree(BinaryTree<int> &BT)				//create a random tree
{
	int arraySize = 9;
	int array[arraySize] = {1,2,3,4,5,6,7,8,9};
	while (arraySize != 0)
	{
		
		int removeIndex = rand() % arraySize;		//initialize index to remove
		BT.add(array[removeIndex]);
		array[removeIndex] = array[arraySize - 1];	//move last entry to location
													//of index being removed
		arraySize--;								//change size of array
	}
}

void printList(BinaryTree<int>::PositionList 
	&positions)										//print out position list
{
	cout << "[";
	int i = 1;
	for(GenPosition<int> n : positions)
	{
		cout << *n;
		if (i < positions.size())
			cout << ", ";
		i++;
	}
	cout << "]";
}

void printBT(BinaryTree<int> &BT)					//print out current tree
{
	BinaryTree<int>::PositionList positions;
	cout << "The preorder positions are: ";
	positions = BT.prePositions();					
	printList(positions);							//print out preorder tree
	cout << endl;
	
	cout << "The postorder positions are: ";
	positions = BT.postPositions();					
	printList(positions);							//print out preorder tree
	cout << endl;
	
	cout << "The inorder positions are: ";
	positions = BT.inPositions();					
	printList(positions);							//print out preorder tree
	cout << endl << endl;	
}

void printTrees(BSTTransform<int> &T1,
	BSTTransform<int> &T2)							//print out both trees
{
	cout << "Tree T1: " << endl << endl;
	printBT(T1);
	cout << "Tree T2: " << endl << endl;
	printBT(T2);
}

void convert(BSTTransform<int>& T1,
		BSTTransform<int>& T2)						//convert T1 into T2
{
	cout << "Converting Tree T1 into T2"
		<< endl << endl;
	T1.transform(T1.root(),T2.root());
}

void testCase(int &test)							//prints test case value
{
	cout << endl << "Test Case: " << test
		<< endl << endl;
	test++;
}

int main(void)
{
	BSTTransform<int> T1;							//create tree
	BSTTransform<int> T2;							//create second tree
	BSTTransform<int> T3;							//create third tree
	BSTTransform<int> T4;							//create fourth tree
	int test = 1;									//assign test case value

	T1.add(5);										//add items to T1 and T2
	T1.add(7);
	T1.add(9);
	T1.add(2);
	T1.add(1);
	T1.add(6);
	T1.add(4);
	T1.add(8);
	T1.add(3);
	
	T2.add(6);
	T2.add(4);
	T2.add(9);
	T2.add(1);
	T2.add(5);
	T2.add(7);
	T2.add(2);
	T2.add(3);
	T2.add(8);

	cout << "Generating Random Trees: " 
		<< endl << endl;
	srand(time(NULL));								//set random seed
	createTree(T3);									//create random Tree 1
	createTree(T4);									//create random Tree 2



	testCase(test);									//print out test case no.
	printTrees(T1,T2);								//print tree information
	convert(T1,T2);									//convert tree T1 into T2
	printTrees(T1,T2);								//print tree information

	testCase(test);									//print out test case no.	
	printTrees(T3,T4);								//print tree information
	convert(T3,T4);									//convert tree T3 into T4
	printTrees(T3,T4);								//print tree information

	
	return EXIT_SUCCESS;							//exit success
}