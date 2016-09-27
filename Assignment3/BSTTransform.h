/******************************************************************************
* Implementation of a Binary Search Tree Transform tool for Assignment 2 of 
* COMP 272
*
* Modified from Sources: Data Structures and Algorithms in C++, 2nd Edition,
*						by Michael T. Goodrich, Roberto Tamassia, David M.
*						Mount, Wiley publisher, February 2011, © 2011
* 
* 						Open Data Structures an Introduction, by Pat Morin,
* 						AU Press, © 2013
*
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		September 17, 2016
******************************************************************************/

#ifndef _BSTTRANSFORM_H_					//if not defined
#define _BSTTRANSFORM_H_					//define BSTTransform

#include "BinaryTree.h"

template <typename E>
class BSTTransform: public BinaryTree<E>	//class to perform AVL rotations
{
public:
	using Node = GenNode<E>;				//define what Node to use
	using Position = GenPosition<E>;		//define what position to use
public:
	void transform(Position x, Position v);	//check if nodes are the same
private:
	Position findNode(Position x, Position v);		//find specific node in tree
	void rotateLeft(Node* x);				//AVL rotate left
	void rotateRight(Node* x);				//AVL rotate right
};

template <typename E>
void BSTTransform<E>::transform(Position x, 		
	Position v)								//check if nodes are the same
{
	
	if ( x.v == nullptr )					//check for null
		return;
	x = findNode(x,v);						//find x such that it matches v
	while ( v.isRoot()? 					//while x parent != v parent
		x.v->parent != nullptr : 
		x.v->parent->element != v.v->parent->element )
	{
		if ( x.v->parent->left == x.v )		//if parents left is x
			rotateRight(x.v);				//rotate right
		else
			rotateLeft(x.v);				//rotate left
	}
	transform(x.left(),v.left());			//transform left branch
	transform(x.right(),v.right());			//transform right branch
	
	if ( x.v->parent == nullptr )			//if node's parent is null
		this->_root = x.v;					//reassign root to this node
}

template <typename E>
typename BSTTransform<E>::Position
BSTTransform<E>::findNode(Position x, 
	Position v)								//find specific node in tree
{
	if (x.v == nullptr)
		throw NodeNotFound("");
	if ( *x == *v )							//is this the correct node?
		return x;
	if ( *x < *v )							//is x smaller than v?
	{
		return findNode(x.right(),v);		//traverse right
	}
	else
	{
		return findNode(x.left(),v);		//traverse left
	}
}

template <typename E>
void BSTTransform<E>::rotateLeft(Node* x)	//AVL rotate left
{
	Node* v = x->parent;					//assign node v as x parent
	v->right = x->left;						//assign v->right as x->left
	if ( v->right != nullptr )				//check for nullptr at v->right
		v->right->parent = v;				//assign v->right->parent as v
	x->left = v;							//assign x->left as v
	x->parent = v->parent;					//assign x->parent as v->parent
	if ( v->parent != nullptr )				//check for nullptr at v->parent
	{
		if ( v->parent->right == v )		//if v is a right node
			v->parent->right = x;			//assign v->right as x
		else
			v->parent->left = x;			//assign v->left as x
	}
	v->parent = x;							//assign v->parent as x
}

template <typename E>
void BSTTransform<E>::rotateRight(Node* x)	//AVL rotate right
{
	Node* v = x->parent;					//assign node v as x parent
	v->left = x->right;						//assign v->left as x->right
	if ( v->left != nullptr )				//check for nullptr at v->left
		v->left->parent = v;				//assign v->left->parent as v
	x->right = v;							//assign x->right as v
	x->parent = v->parent;					//assign x->parent as v->parent
	if ( v->parent != nullptr )				//check for nullptr at v->parent
	{
		if ( v->parent->left == v )			//if v is a left node
			v->parent->left = x;			//assign v->left as x
		else
			v->parent->right = x;			//assign v->right as x
	}
	v->parent = x;							//assign v->parent as x
}

#endif
