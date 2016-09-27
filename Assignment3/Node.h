/******************************************************************************
* Implementation of node and position for Assignment 3 of 
* COMP 272
*
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		September 17, 2016
******************************************************************************/

#ifndef _NODE_H_							//if not defined
#define _NODE_H_							//define Node

template <typename E>
class GenNode								//a node of the tree
{
public:
	E element;								//element value
	GenNode<E>* parent;						//parent
	GenNode<E>* left;						//left child
	GenNode<E>* right;						//right child
	GenNode<E>() : element(), parent(nullptr), 
		left(nullptr), right(nullptr) {}	//constructor
};

template <typename E>
class GenPosition							//position in the tree
{
private:
	using Node = GenNode<E>;
	Node* v;								//pointer to the node
public:
	GenPosition<E>(Node* _v = nullptr) : v(_v) 
	{}										//constructor
	E& operator*()
	{ return v->element; }					//get element
	GenPosition<E> left() const
	{ return GenPosition(v->left); }		//get left child
	GenPosition<E> right() const
	{ return GenPosition(v->right); }		//get right child
	GenPosition<E> parent() const
	{ return GenPosition(v->parent); }		//get parent
	bool isRoot() const
	{ return v->parent == nullptr; }		//root of tree?
	template <typename E1>
	friend class BinaryTree;				//provide BinaryTree access
	template <typename E1>
	friend class BSTTransform;				//provide BinaryTreeTester access
};

#endif