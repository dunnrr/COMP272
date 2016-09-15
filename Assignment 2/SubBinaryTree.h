/******************************************************************************
* Implementation of a Sub Binary Tree with expanded nodes for Assignment 2 of 
* COMP 272
*
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		8 September, 2016
******************************************************************************/

#ifndef _SUBBINARYTREE_H_					//if not defined
#define _SUBBINARYTREE_H_					//define SubBinaryTree

#include "SubNode.h"
#include "BinaryTree.h"

template <typename E>
class SubBinaryTree: public BinaryTree<E>
{
public:
	using Node = GenNode<E>;
	using Position = GenPosition<E>;
	using PositionList = list<Node*>;	
public:
	void preorderNumber();					//assign preorder numbers
	void postorderNumber();					//assign postorder numbers
	void inorderNumber();					//assign inorder numbers
protected:
	void preNumber(Node* v, int& counter);	//preorder number utility
	void postNumber(Node* v, int& counter);	//postorder number utility	
	void inNumber(Node* v, int& counter);	//inorder number utility
};

template <typename E>
void SubBinaryTree<E>::preorderNumber()		//assign preorder numbers
{
	int counter = 1;
	preNumber(this->_root, counter);
}

template <typename E>
void SubBinaryTree<E>::postorderNumber()	//assign postorder numbers
{
	int counter = 1;
	postNumber(this->_root, counter);
}

template <typename E>
void SubBinaryTree<E>::inorderNumber()		//assign inorder numbers
{
	int counter = 1;
	inNumber(this->_root, counter);
}

template <typename E>
void SubBinaryTree<E>::preNumber(
	Node* v, int& counter)					//preorder number utility
{
	v->prePos = counter;					//add counter to position
	counter++;								//increment counter
	if (v->left != nullptr)					//traverse left subtree
		preNumber(v->left , counter);
	if (v->right != nullptr)				//traverse right subtree
		preNumber(v->right, counter);
}

template <typename E>
void SubBinaryTree<E>::postNumber(
	Node* v, int& counter)					//postorder number utility	
{
	if (v->left != nullptr)					//traverse left subtree
		postNumber(v->left, counter);
	if (v->right != nullptr)				//traverse right subtree
		postNumber(v->right, counter);
	v->postPos = counter;					//add counter to position
	counter++;								//increment counter
}

template <typename E>
void SubBinaryTree<E>::inNumber(
	Node* v, int& counter)					//inorder number utility
{
	if (v->left != nullptr)					//traverse left subtree
		inNumber(v->left, counter);
	v->inPos = counter;						//add counter to position
	counter++;								//increment counter
	if (v->right != nullptr)				//traverse right subtree
		inNumber(v->right, counter);
}

#endif