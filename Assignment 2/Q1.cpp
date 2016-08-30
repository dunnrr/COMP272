/******************************************************************************
* Test program for the Implementation of a Binary tree functions
* preorderNext(x), postorderNext(x), and inorderNext(x) as required for 
* COMP 272 assignment 2 question 1.
*
* Author: Robert Ryan Dunn
* SN: 3070207
* Date: 26 August, 2016
******************************************************************************/

#include "BinaryTree.h"
#include <iostream>

using std::cout;
using std::endl;

/*
void deleteMin(PriorityQueue<int> &queue)			//deletes minimum value
{
	try
	{
		queue.deleteMin();							//delete value if possible
	}
	catch (QueueEmpty& err)							//show error if not
	{
		cout << "Exception: " << err.getMessage()
			<< endl << endl;
	}
}

void minQueue(PriorityQueue<int> &queue)			//print out the min value
{
	try
	{												//print value if possible
		cout << "The minimum value is: "
			<< queue.min() << endl << endl;
	}
	catch (QueueEmpty& err)							//show error if not
	{
		cout << "Exception: " << err.getMessage()
			<< endl << endl;
	}
}
*/

void sizeTree(BinaryTree<int> &BT)					//print out the tree size
{
	cout << "The size of the tree is: "
		<< BT.size() << endl << endl;
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
	BinaryTree<int> BT;								//create tree
	int test = 1;									//assign test case value

	testCase(test);									//print out test case no.
	sizeTree(BT);									//queue size

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

	testCase(test);									//print out test case no.
	sizeTree(BT);									//tree size

//	testCase(test);									//print out test case no.
//	minQueue(queue);								//retrieve minimum element

//	testCase(test);									//print out test case no.
//	while (!queue.empty())							//cycle until empty
//	{
//		deleteMin(queue);							//delete minimum element
//		printQueue(queue);							//print queue
//	}

//	testCase(test);									//print out test case no.
//	minQueue(queue);								//retrieve minimum element

//	testCase(test);									//print out test case no.
//	deleteMin(queue);								//delete minimum element
	return EXIT_SUCCESS;							//exit success
}