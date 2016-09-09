/******************************************************************************
* Test program for the Implementation of a Binary tree functions
* preorderNext(x), postorderNext(x), and inorderNext(x) as required for 
* COMP 272 assignment 2 question 1.
*
* Author: Robert Ryan Dunn
* SN: 3070207
* Date: 26 August, 2016
******************************************************************************/

#include "BinaryTreeTester.h"
#include <iostream>

using std::cout;
using std::endl;


void BSTCheck(BinaryTreeTester<int> &BT)			//Is this a BST
{
	try
	{
		cout << "The tree is a BST: ";
		if ( BT.isBST() )							//is the tree empty?
			cout << "TRUE" << endl << endl;
		else
			cout << "FALSE" << endl << endl;		//remove node if possible
	}
	catch (TreeEmpty& err)							//show error if not
	{
		cout << "Exception: " << err.getMessage()
			<< endl << endl;						
	}
}

void change(BinaryTreeTester<int> &BT, int initial, 
	int change)										//change the node's value
{
	try
	{
		BT.changeNode(initial,change);				//remove node if possible
	}
	catch (TreeEmpty& err)							//show error if not
	{
		cout << "Exception: " << err.getMessage()
			<< endl << endl;						
	}
	catch (NodeNotFound& err)						//show error if not
	{
		cout << "Exception: " << err.getMessage()
			<< endl << endl;
	}	
}

void printList(PositionList<int> positions)			//print out position list
{
	cout << "[";
	int i = 1;
	for(Position<int> n : positions)
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
	PositionList<int> positions;
	cout << "The preorder positions are: ";
	positions = BT.prePositions();					
	printList(positions);							//print out preorder tree
	cout << endl << endl;
	
	cout << "The postorder positions are: ";
	positions = BT.postPositions();					
	printList(positions);							//print out preorder tree
	cout << endl << endl;
	
	cout << "The inorder positions are: ";
	positions = BT.inPositions();					
	printList(positions);							//print out preorder tree
	cout << endl << endl;	
}

void testCase(int &test)							//prints test case value
{
	cout << "Test Case: " << test
		<< endl;
	test++;
}

int main(void)
{
	BinaryTreeTester<int> BT;						//create tree
	int test = 1;									//assign test case value

	testCase(test);									//print out test case no.
	change(BT,5,4);									//Try changing empty tree
	BSTCheck(BT);									//Try to check empty tree

	testCase(test);									//print out test case no.
	BT.add(5);										//add items to tree
	BT.add(7);
	BT.add(9);
	BT.add(2);
	BT.add(1);
	BT.add(6);
	BT.add(4);
	BT.add(8);
	BT.add(3);
	printBT(BT);									//print tree
	BSTCheck(BT);									//Check if result is a BST

	testCase(test);									//print out test case no.
	change(BT,9,10);								//change the tree
	printBT(BT);									//print tree
	BSTCheck(BT);									//Check if result is a BST

	testCase(test);									//print out test case no.
	change(BT,6,9);									//change the tree
	printBT(BT);									//print tree
	BSTCheck(BT);									//Check if result is a BST

	return EXIT_SUCCESS;							//exit success
}