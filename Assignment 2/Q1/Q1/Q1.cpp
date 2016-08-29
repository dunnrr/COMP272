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

void sizeQueue(PriorityQueue<int> &queue)			//print out the queue size
{
	cout << "The size of the queue is: "
		<< queue.size() << endl << endl;
}

void printBT(BinaryTree<int> &BT)			//print out current tree
{
	cout << "The current tree is: ";
	BT.print();									//print out tree
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
	BinaryTree<int> BT;						//create queue
	int test = 1;									//assign test case value

	testCase(test);									//print out test case no.
	BT.add(19);									//add items to queue
	BT.add(7);
	BT.add(1);
	BT.add(5);
	BT.add(3);
	BT.add(20);
	BT.add(15);
	BT.add(5);
	printBT(BT);								//print queue

	testCase(test);									//print out test case no.
	sizeQueue(queue);								//queue size

	testCase(test);									//print out test case no.
	minQueue(queue);								//retrieve minimum element

	testCase(test);									//print out test case no.
	while (!queue.empty())							//cycle until empty
	{
		deleteMin(queue);							//delete minimum element
		printQueue(queue);							//print queue
	}

	testCase(test);									//print out test case no.
	sizeQueue(queue);								//queue size

	testCase(test);									//print out test case no.
	minQueue(queue);								//retrieve minimum element

	testCase(test);									//print out test case no.
	deleteMin(queue);								//delete minimum element
	return EXIT_SUCCESS;							//exit success
}