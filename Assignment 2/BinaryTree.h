/******************************************************************************
* Implementation of a Binary Tree for Assignment 2 of COMP 272
*
* Modified from Source: Data Structures and Algorithms in C++, 2nd Edition,
*						by Michael T. Goodrich, Roberto Tamassia, David M.
*						Mount, Wiley publisher, February 2011, © 2011
*
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		26 August, 2016
******************************************************************************/

#ifndef _BINARYTREE_H_						//if not defined
#define _BINARYTREE_H_						//define BinaryTree

#include <iostream>
#include <list>
#include "RuntimeException.h"

using std::cout;
using std::endl;
using std::list;

template <typename E>
struct Node									//a node of the tree
{
	E element;								//element value
	Node<E>* parent;						//parent
	Node<E>* left;							//left child
	Node<E>* right;							//right child
	Node<E>() : element(), parent(nullptr), 
		left(nullptr), right(nullptr) {}	//constructor
};


template <typename E>
class Position								//position in the tree
{
private:
	Node<E>* v;								//pointer to the node
public:
	Position<E>(Node<E>* _v = nullptr) : v(_v) 
	{}										//constructor
	E& operator*()
	{ return v->element; }					//get element
	Position<E> left() const
	{ return Position(v->left); }			//get left child
	Position<E> right() const
	{ return Position(v->right); }			//get right child
	Position<E> parent() const
	{ return Position(v->parent); }			//get parent
	bool isRoot() const
	{ return v->parent == nullptr; }		//root of tree?
	bool isExternal() const					
	{ return v->left == nullptr && 
		v->right == nullptr; }				//an external node?
	template <typename E1>
	friend class BinaryTree;				//provide BinaryTree access
};


template <typename E, 
	typename GenericPosition = Position<E>>
using PositionList = list<GenericPosition>;	//list of positions



template <typename E>
class BinaryTree							//Binary Tree
{
protected:
public:
//	class Position<E>;						//a node position
//	class PositionList<E>;					//a list of positions
public:	
	BinaryTree();							//constructor
	~BinaryTree();							//destructor
	int size() const;						//number of nodes
	bool empty() const;						//is tree empty?
	Position<E> root() const;				//get the root
	PositionList<E> prePositions() const;	//preorder list of nodes
	PositionList<E> postPositions() const;	//postorder list of nodes
	PositionList<E> inPositions() const;	//inorder list of nodes
	void add(E value);						//add a value to the tree
//	void expandExternal(
//		const Position<E>& p);				//expand external node
//	Position<E> removeAboveExternal(
//		const Position<E>& p);				//remove p and parent
protected:
	void addRoot();							//add root to empty tree
	void addNode(Node<E>* v, bool addLeft,
		E value);							//add node to tree
	void deleteTree(Node<E>* v);			//destructor utility
	void addValue(Node<E>* v, E value);		//add utility
	void preorder(Node<E>* v, 
		PositionList<E>& pl) const;			//preorder utility
	void postorder(Node<E>* v,
		PositionList<E>& pl) const;			//postorder utility
	void inorder(Node<E>* v,
		PositionList<E>& pl) const;			//inorder utility
private:
	Node<E>* _root;							//pointer to the root
	int n;									//number of nodes
};

template <typename E>
BinaryTree<E>::BinaryTree()					//constructor
	: _root(nullptr), n(0) {};

template <typename E>
BinaryTree<E>::~BinaryTree()				//destructor
{
	deleteTree(_root);
}

template <typename E>						
int BinaryTree<E>::size() const				//number of nodes
{
	return n;
}

template <typename E>
bool BinaryTree<E>::empty() const	 		//is tree empty?
{
	return size() == 0;
}

template <typename E>						//get the root
Position<E> BinaryTree<E>::root() const
{
	return _root;
}


template <typename E>						//preorder list of nodes
PositionList<E> BinaryTree<E>::prePositions() const
{
	PositionList<E> pl;
	preorder(_root, pl);					//preorder traversal
	return PositionList<E>(pl);				//return resulting list
}

template <typename E>						//postorder list of nodes
PositionList<E> BinaryTree<E>::postPositions() const
{
	PositionList<E> pl;
	postorder(_root, pl);					//postorder traversal
	return PositionList<E>(pl);				//return resulting list
}

template <typename E>						//inorder list of nodes
PositionList<E> BinaryTree<E>::inPositions() const
{
	PositionList<E> pl;
	inorder(_root, pl);						//inorder traversal
	return PositionList<E>(pl);				//return resulting list
}


template <typename E>
void BinaryTree<E>::addRoot()				//add root to empty tree
{
	_root = new Node<E>; 
	n = 1;
}

template <typename E>						//add node to tree
void BinaryTree<E>::addNode(Node<E>* v, bool addLeft, E value)
{
	Node<E>* w = new Node<E>;
	if(addLeft)
		v->left = w;
	else
		v->right = w;
	w->parent = v;
	w->element = value;
	n += 1;
}

template <typename E>
void BinaryTree<E>::add(E value)			//add a value to the tree
{
	if(empty())								//if empty
	{
		addRoot();							//create root
		Node<E>* v = _root;					
		v->element = value;					//assign a value to root
	}
	else
		addValue(_root, value);				//use add utility
		
}

/*
template <typename E>						//expande external node
void BinaryTree<E>::expandExternal(const Position<E>& p)
{
	Node* v = p.v;							//p's node
	v->left = new Node;						//add a new left child
	v->left->parent = v;					//v is its parent
	v->right = new Node;					//add a new right child
	v->right->parent = v;					//v is its parent
	n += 2;									//two more nodes
}

template <typename E>						//remove p and parent
BinaryTree<E>::Position<E> BinaryTree<E>::removeAboveExternal(
	const Position<E>& p)
{
	Node* w = p.v;							//p's node
	Node* v = w->parent;					//p's parent
	Node* sib = (w == v->left ? v->right : v->left);
	if (v == _root) {						//child of root?
		_root = sib;						//make sibling root
		sib->parent = nullptr;
	}
	else {
		Node* gparent = v->parent;			//w's grandparent
		if (v == gparent->left) {			//replace parent by sib
			gparent->left = sib;
		}
		else {
			gparent->right = sib;
			sib->parent = gparent;
		}
	}
	delete w; delete v;						//delete removed nodes
	n -= 2;									//two fewer nodes
	return Position(sib);
}
*/

template <typename E>
void BinaryTree<E>::deleteTree(Node<E>* v)	//destructor utility
{
	if(v) {									//if not null
		if(v->left)							//if left branch
			deleteTree(v->left);			//deleteTree left branch
		if(v->right)						//if right branch
			deleteTree(v->right);			//deleteTree right branch
		delete v;							//delete node
		n -= 1;
	}
}

template <typename E>						//add utility
void BinaryTree<E>::addValue(Node<E>* v, E value)
{
	bool addLeft = true;					//variable defining add to the left
	bool addRight = false;					//variable defining add to the right
	if( v->element == value )				//is add needed?
		return;								//if not, return
	if( v->element > value )				//is current greater than value?
	{
		if(v->left == nullptr)				//check for nullptr
			addNode(v, addLeft, value);		//add node if true
		else
			addValue(v->left, value);		//move left
	}
	else
	{
		if(v->right == nullptr)				//check for nullptr
			addNode(v, addRight, value);	//add node if true
		else
			addValue(v->right, value);		//move right
	}
		
}

template <typename E>						//preorder utility
void BinaryTree<E>::preorder(Node<E>* v, PositionList<E>& pl) const
{
	pl.push_back(v);						//add this node
	if (v->left != nullptr)					//traverse left subtree
		preorder(v->left, pl);
	if (v->right != nullptr)				//traverse right subtree
		preorder(v->right, pl);
}

template <typename E>						//postorder utility
void BinaryTree<E>::postorder(Node<E>* v, PositionList<E>& pl) const
{
	if (v->left != nullptr)					//traverse left subtree
		postorder(v->left, pl);
	if (v->right != nullptr)				//traverse right subtree
		postorder(v->right, pl);
	pl.push_back(v);						//add this node
}

template <typename E>						//inorder utility
void BinaryTree<E>::inorder(Node<E>* v, PositionList<E>& pl) const
{
	if (v->left != nullptr)					//traverse left subtree
		inorder(v->left, pl);
	pl.push_back(v);						//add this node
	if (v->right != nullptr)				//traverse right subtree
		inorder(v->right, pl);
}

#endif

