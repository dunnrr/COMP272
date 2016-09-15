#ifndef _POSITION_H_						//if not defined
#define _POSITION_H_						//define POSITION

#include "Node.h"

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
	friend class BinaryTreeTester;			//provide BinaryTreeTester access
};

#endif