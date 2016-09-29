/******************************************************************************
* Test program for the Implementation of MeldableHeap function
* remove(x) as required for COMP 272 assignment 3 question 7.
*
* Author: Robert Ryan Dunn
* SN: 3070207
* Date: 28 September, 2016
******************************************************************************/

#include "MeldableHeap.h"
#include <iostream>

using std::cout;
using std::endl;

void removeRoot(MeldableHeap<int> &MH)
{
	try
	{
		MH.remove();								//remove root if possible
	}
	catch (HeapEmpty& err)							//show error if not
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

void removeNode(MeldableHeap<int> &MH, int x)
{
	try
	{
		MH.remove(MH.search(x));					//remove node if possible
	}
	catch (HeapEmpty& err)							//show error if not
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

void printRoot(MeldableHeap<int> &MH)				//print the root node
{
	try
	{
		cout << "The current root is : "
		<< *MH.root() << endl << endl;				//print out current root	
	}
	catch (HeapEmpty& err)							//show error if not
	{
		cout << "Exception: " << err.getMessage()
			<< endl << endl;						
	}
}

void emptyHeap(MeldableHeap<int> &MH)				//print out if empty or not
{
	cout << "The heap is empty: ";
	if ( MH.empty() )								//is the heap empty?
		cout << "TRUE" << endl << endl;
	else
		cout << "FALSE" << endl << endl;
}

void sizeHeap(MeldableHeap<int> &MH)				//print out the heap size
{
	cout << "The size of the heap is: "
		<< MH.size() << endl << endl;
}

void printList(
	MeldableHeap<int>::PositionList &positions)		//print out position list
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

void printMH(MeldableHeap<int> &MH)					//print out current heap
{
	MeldableHeap<int>::PositionList positions;

	cout << "The preorder positions are: ";
	positions = MH.prePositions();					
	printList(positions);							//print out preorder heap
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
	srand(time(NULL));								//set random seed
	
	MeldableHeap<int> MH;							//create heap
	int test = 1;									//assign test case value

	testCase(test);									//print out test case no.
	sizeHeap(MH);									//heap size

	testCase(test);									//print out test case no.
	MH.add(5);										//add items to heap
	MH.add(7);
	MH.add(9);
	MH.add(2);
	MH.add(1);
	MH.add(6);
	MH.add(4);
	MH.add(8);
	MH.add(3);
	printMH(MH);									//print heap

	testCase(test);									//print out test case no.
	sizeHeap(MH);									//heap size

	testCase(test);									//print out test case no.
	removeRoot(MH);									//remove root
	printMH(MH);									//print heap
	sizeHeap(MH);									//print heap size	

	testCase(test);									//print out test case no.
	removeNode(MH,7);								//remove non-root node
	printMH(MH);									//print heap
	sizeHeap(MH);									//print heap size	

	testCase(test);									//print out test case no.
	removeNode(MH,1);								//remove a non-existant node
	printMH(MH);									//print heap
	sizeHeap(MH);									//print heap size

	testCase(test);									//print out test case no.
	emptyHeap(MH);									//print out if empty or not
	cout << "Removing remaining nodes" << endl;		//remove remaining nodes
	removeNode(MH,2);
	removeNode(MH,3);
	removeNode(MH,4);
	removeNode(MH,6);
	removeNode(MH,5);
	removeNode(MH,9);
	removeNode(MH,8);
	sizeHeap(MH);									//print heap size
	
	emptyHeap(MH);									//print out if empty or not

	cout << "Error checking against empty heap." 
		<< endl;
	cout << "Printing empty heap: " << endl;
	printMH(MH);									//print heap
	
	cout << "Printing the root: ";
	printRoot(MH);									//print out current root
	
	cout << "Removing a node: ";
	removeNode(MH, 5);								//remove node
	
	cout << "Removing root: ";
	removeRoot(MH);									//remove root
	
	return EXIT_SUCCESS;							//exit success
}