/******************************************************************************
* Implementation of a Binary Tree Testing algorithm for Assignment 2 of 
* COMP 272
*
* 
* Notes: changeNode is really not meant to ever be used, but was implemented to
* 		confirm results won't always show true if the tree is not a binary 
* 		search tree.
*
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		8 September, 2016
******************************************************************************/

#ifndef _BINARYTREETESTER_H_					//if not defined
#define _BINARYTREETESTER_H_					//define BinaryTreeTester

#include "BinaryTree.h"

template <typename E>
struct MinMaxBST
{
	E min;
	E max;
	bool BST = true;
};

template <typename E>
class BinaryTreeTester: public BinaryTree<E>
{
private:
	using Node = GenNode<E>;
public:
	void changeNode(E initial, E change);		//change the value of root
	bool isBST();								//is the tree a BST?
private:
	MinMaxBST<E> checkBST(Node* x);				//check if tree is BST
};

template <typename E>
void BinaryTreeTester<E>::changeNode(E initial,
	E change)									//change the value of a node
{
	if ( this->empty() )						//check if empty
		throw TreeEmpty("Tree is empty.");		//throw error
	Node* x = this->search(initial).v;			//find the node
	x->element = change;						//change the nodes element
}

template <typename E>
bool BinaryTreeTester<E>::isBST()				//is the tree a BST?
{
	return checkBST(this->root().v).BST;	
}

template <typename E>
MinMaxBST<E> BinaryTreeTester<E>::checkBST(
	Node* x)									//check if tree is BST
{
	if ( this->empty() )						//check if empty
		throw TreeEmpty("Tree is empty.");		//throw error
	
	MinMaxBST<E> leftTree;						//values for left sub tree
	MinMaxBST<E> rightTree;						//values for right sub tree
	
	if ( x->left != nullptr )					//check if left tree is nullptr
	{
		leftTree = checkBST(x->left);			//get the values from left tree
		
		if ( !leftTree.BST )					//is left subtree not a BST?
			return leftTree;
		else
		{
			if ( leftTree.min >= x->element ||
				leftTree.max >= x->element)		//x value <= any of left tree?
				{
					leftTree.BST = false;
					return leftTree;
				}
		}
	}
	else										//assign x value to min max
	{
		leftTree.min = x->element;
		leftTree.max = x->element;
	}
	
	if ( x->right != nullptr )					//check if right tree is nullptr
	{
		rightTree = checkBST(x->right);			//get the values from right tree
		
		if ( !rightTree.BST )					//is right subtree not a BST?
			return rightTree;
		else
		{
			if ( rightTree.min <= x->element ||
				rightTree.max <= x->element)	//x value >= any of right tree?
				{
					rightTree.BST = false;
					return rightTree;
				}
		}
	}
	else										//assign x value to min max
	{
		rightTree.min = leftTree.min;
		rightTree.max = x->element;
	}	
	
	return rightTree;
}

#endif