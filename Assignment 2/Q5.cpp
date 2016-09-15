/******************************************************************************
* Test program for the Implementation of a sub Binary tree with functions
* preorderNumber(), postorderNumber(), and inorderNumber() as required for 
* COMP 272 assignment 2 question 5.
*
* Author: Robert Ryan Dunn
* SN: 3070207
* Date: 8 September, 2016
******************************************************************************/

#include "SubBinaryTree.h"
#include <iostream>

using std::cout;
using std::endl;

void assignNodes(SubBinaryTree<int> &BT)
{
	BT.preorderNumber();
	BT.postorderNumber();
	BT.inorderNumber();
}

void printNodes(SubBinaryTree<int> &BT)
{
	SubBinaryTree<int>::PositionList positions;
	positions = BT.inPositions();
	for(GenPosition<int> n : positions)
	{
		cout << endl;
		cout << "Node: " << *n << endl;
		cout << "Preorder Number: "  << n.prePos() << endl;
		cout << "Postorder Number: " << n.postPos() << endl;
		cout << "Inorder Number: " << n.inPos() << endl;
	}
	cout << endl;
}

void nextBT(SubBinaryTree<int> &BT, 
	int x, Traversal order)							//print out next node value
{
	switch (order)
	{
		case PREORDER:
			cout << "Preorder: ";
			break;
		case POSTORDER:
			cout << "Postorder: ";
			break;
		case INORDER:
			cout << "Inorder: ";
			break;
	}
	try
	{												//print node if possible
		cout << "The next node after node " << x
			<< " is: ";
		switch (order)
		{
			case PREORDER:
				cout << *BT.preorderNext(BT.search(x));
				break;
			case POSTORDER:
				cout << *BT.postorderNext(BT.search(x));
				break;
			case INORDER:
				cout << *BT.inorderNext(BT.search(x));
				break;
		}
		cout << endl << endl;
	}
	catch (TreeEmpty& err)							//show error if not
	{
		cout << "Exception: " << err.getMessage()
			<< endl << endl;
	}
	catch (TreeLastItem& err)						//show error if not
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

void removeNode(SubBinaryTree<int> &BT, int x)
{
	try
	{
		BT.remove(BT.search(x));					//remove node if possible
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

void printRoot(SubBinaryTree<int> &BT)					//print the root node
{
	try
	{
		cout << "The current root is : "
		<< *BT.root() << endl << endl;				//print out current root	
	}
	catch (TreeEmpty& err)							//show error if not
	{
		cout << "Exception: " << err.getMessage()
			<< endl << endl;						
	}
}

void emptyTree(SubBinaryTree<int> &BT)					//print out if empty or not
{
	cout << "The tree is empty: ";
	if ( BT.empty() )								//is the tree empty?
		cout << "TRUE" << endl << endl;
	else
		cout << "FALSE" << endl << endl;
}

void sizeTree(SubBinaryTree<int> &BT)					//print out the tree size
{
	cout << "The size of the tree is: "
		<< BT.size() << endl << endl;
}

void printList(SubBinaryTree<int>::PositionList positions)			//print out position list
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

void printBT(SubBinaryTree<int> &BT)					//print out current tree
{
	SubBinaryTree<int>::PositionList positions;
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
	SubBinaryTree<int> BT;							//create tree
	int test = 1;									//assign test case value

	testCase(test);									//print out test case no.
	sizeTree(BT);									//tree size

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

	testCase(test);									//print out test case no.
	nextBT(BT,2,PREORDER);							//retreive the next element
	nextBT(BT,2,POSTORDER);							//retreive the next element
	nextBT(BT,2,INORDER);							//retreive the next element
	
	testCase(test);									//print out test case no.
	nextBT(BT,8,PREORDER);							//retreive the next element
	nextBT(BT,5,POSTORDER);							//retreive the next element
	nextBT(BT,9,INORDER);							//retreive the next element

	testCase(test);									//print out test case no.
	nextBT(BT,10,PREORDER);							//retreive the next element
	nextBT(BT,10,POSTORDER);						//retreive the next element
	nextBT(BT,10,INORDER);							//retreive the next element
	
	testCase(test);									//print out test case no.
	removeNode(BT,7);								//remove node w 2 children
	printBT(BT);									//print tree
	sizeTree(BT);									//print tree size	

	testCase(test);									//print out test case no.
	removeNode(BT,9);								//remove leaf
	printBT(BT);									//print tree
	sizeTree(BT);									//print tree size

	testCase(test);									//print out test case no.
	removeNode(BT,8);								//remove node w 1 child
	printBT(BT);									//print tree
	sizeTree(BT);									//print tree size

	testCase(test);									//print out test case no.
	printRoot(BT);									//print out current root
	removeNode(BT,5);								//remove root
	printRoot(BT);									//print out current root
	printBT(BT);									//print tree
	sizeTree(BT);									//print tree size

	testCase(test);									//print out test case no.
	removeNode(BT,5);								//remove a non-existant node
	printBT(BT);									//print tree
	sizeTree(BT);									//print tree size

	testCase(test);									//print out test case no.
	emptyTree(BT);									//print out if empty or not
	cout << "Removing remaining nodes" << endl;		//remove remaining nodes
	removeNode(BT,1);								
	removeNode(BT,2);
	removeNode(BT,3);
	removeNode(BT,4);
	removeNode(BT,6);
	sizeTree(BT);									//print tree size
	
	emptyTree(BT);									//print out if empty or not

	cout << "Error checking against empty tree." 
		<< endl;
	cout << "Printing empty tree: " << endl;
	printBT(BT);									//print tree
	
	cout << "Printing the root: ";
	printRoot(BT);									//print out current root
	
	cout << "Removing a node: ";
	removeNode(BT, 5);								//remove node
	
	cout << "Preorder next: ";
	nextBT(BT,5,PREORDER);							//find next node(preorder)
	
	cout << "Postorder next: ";
	nextBT(BT,5,POSTORDER);							//find next node(postorder)
	
	cout << "Inorder next: ";
	nextBT(BT,5,INORDER);							//find next node(inorder)

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
	assignNodes(BT);								//assign node numbers
	printNodes(BT);									//print node numbers
	
	return EXIT_SUCCESS;							//exit success
}