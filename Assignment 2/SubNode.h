/******************************************************************************
* Implementation of expanded node and positionfor Assignment 2 of 
* COMP 272
*
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		8 September, 2016
******************************************************************************/

#ifndef _NODE_H_							//if not defined
#define _NODE_H_							//define Node

template <typename E>
class GenNode
{
public:
	E element;								//element
	GenNode<E>* left;						//left child
	GenNode<E>* right;						//right child
	GenNode<E>* parent;						//parent
	int prePos;								//preorder position
	int postPos;							//postorder position
	int inPos;								//inorder position
	GenNode<E>() : element(), left(nullptr), 
		right(nullptr), parent(nullptr), 
		prePos(), postPos(), inPos() {}		//constructor
};

template <typename E>
class GenPosition							//position in the tree
{
private:
	using Node = GenNode<E>;
	Node* v;								//pointer to the node
public:
	GenPosition<E>(Node* _v = nullptr) : v(_v) 
	{}
	E& operator*()
	{ return v->element; }					//get element
	GenPosition<E> left() const
	{ return GenPosition(v->left); }		//get left child
	GenPosition<E> right() const
	{ return SubPosition(v->right); }		//get right child
	GenPosition<E> parent() const
	{ return GenPosition(v->parent); }		//get parent
	int prePos() const						//return pre position number
	{ return v->prePos;	}
	int postPos() const
	{ return v->postPos; }					//return post position number
	int inPos() const
	{ return v->inPos; }					//return in position number
	bool isRoot() const
	{ return v->parent == nullptr; }		//root of tree?
	template <typename E1>
	friend class BinaryTree;				//provide SibBinaryTree access
	template <typename E1>
	friend class SubBinaryTree;				//provide SibBinaryTree access
};


#endif