/******************************************************************************
* Implementation of a Binary Tree for Assignment 2 of COMP 272
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
* Date:		26 August, 2016
******************************************************************************/

#ifndef _BINARYTREE_H_						//if not defined
#define _BINARYTREE_H_						//define BinaryTree

#include <list>
#include "RuntimeException.h"

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
	template <typename E1>
	friend class BinaryTree;				//provide BinaryTree access
	template <typename E1>
	friend class BinaryTreeTester;			//provide BinaryTreeTester access
};


template <typename E, 
	typename GenericNode = Node<E>*>
using PositionList = list<GenericNode>;		//list of positions

enum Traversal { PREORDER, POSTORDER, 
	INORDER };								//types of traversal

template <typename E>
class BinaryTree							//Binary Tree
{
public:	
	BinaryTree();							//constructor
	~BinaryTree();							//destructor
	int size() const;						//number of nodes
	bool empty() const;						//is tree empty?
	Position<E> root() const;				//get the root
	Position<E> preorderNext(
		Position<E> x);						//get node after node x (preorder)
	Position<E> postorderNext(
		Position<E> x);						//get node after node x (postorder)
	Position<E> inorderNext(
		Position<E> x);						//get node after node x (inorder)
	PositionList<E> prePositions() const;	//preorder list of nodes
	PositionList<E> postPositions() const;	//postorder list of nodes
	PositionList<E> inPositions() const;	//inorder list of nodes
	void add(E x);							//add x to the tree
	void remove(Position<E> x);				//remove node x from the tree
	Position<E> search(E x);				//get node containing x
protected:
	void addRoot();							//add root to empty tree
	void addNode(Node<E>* v, bool addLeft,
		E value);							//add node to tree
	void splice(Node<E>* v);				//splice in a node from elsewhere
	void deleteTree(Node<E>* v);			//destructor utility
	void addValue(Node<E>* v, E x);			//add utility
	Node<E>* searchTree(Node<E>* v,
		E x);								//search tree utility
	void preNext(Node<E>* v, Node<E>* x, 
		Node<E>* y);						//get next utility (preorder)
	void postNext(Node<E>* v, Node<E>* x, 
		Node<E>* y);						//get next utility (postorder)
	void inNext(Node<E>* v, Node<E>* x, 
		Node<E>* y);						//get next utility (inorder)
	Node<E>* next(Node<E>* x, 
		Traversal order);					//return node after one given
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
	if ( empty() )
		throw TreeEmpty("Tree is empty.");	//throw error
	return Position<E>(_root);
}

template <typename E>						//get node after node x (preorder)
Position<E> BinaryTree<E>::preorderNext(Position<E> x)
{
	Traversal traversalType = PREORDER;		//assign type of traversal
	return Position<E>(next(x.v, 
		traversalType));					//return the next node
}

template <typename E>						//get node after node x (postorder)
Position<E> BinaryTree<E>::postorderNext(Position<E> x)
{
	Traversal traversalType = POSTORDER;	//assign type of traversal
	return Position<E>(next(x.v, 
		traversalType));					//return the next node
}

template <typename E>						//get node after node x (inorder)	
Position<E> BinaryTree<E>::inorderNext(Position<E> x)
{
	Traversal traversalType = INORDER;		//assign type of traversal
	return Position<E>(next(x.v, 
		traversalType));					//return the next node
}

template <typename E>						//preorder list of nodes
PositionList<E> BinaryTree<E>::prePositions() const
{
	PositionList<E> pl;
	if ( !empty() )							//check for empty
		preorder(_root, pl);				//preorder traversal
	return pl;								//return resulting list
}

template <typename E>						//postorder list of nodes
PositionList<E> BinaryTree<E>::postPositions() const
{
	PositionList<E> pl;
	if ( !empty() )							//check for empty
		postorder(_root, pl);				//postorder traversal
	return pl;								//return resulting list
}

template <typename E>						//inorder list of nodes
PositionList<E> BinaryTree<E>::inPositions() const
{
	PositionList<E> pl;
	if ( !empty() )							//check for empty
		inorder(_root, pl);					//inorder traversal
	return pl;								//return resulting list
}

template <typename E>
void BinaryTree<E>::add(E x)				//add a value to the tree
{
	if(empty())								//if empty
	{
		addRoot();							//create root
		Node<E>* v = _root;					
		v->element = x;						//assign a value to root
	}
	else
		addValue(_root, x);					//use add utility		
}

template <typename E>
void BinaryTree<E>::remove(Position<E> x)	//remove node x from the tree
{
	if ( x.v->left == nullptr || 
		x.v->right == nullptr )				//does x only have 0 or 1 children?
		splice(x.v);						//splice node x
	else
	{
		Node<E>* w = x.v->right;			//assign node w to x's right
		while ( w->left != nullptr )		//until w->left is a nullptr
			w = w->left;					//assign w as w->left
		x.v->element = w->element;			//move the value of w to x
		splice(w);							//splice node w
	}
}

template <typename E>
Position<E> BinaryTree<E>::search(E x)		//get node containing x
{
	if ( empty() )							//check for empty
		throw TreeEmpty("Tree is empty.");	//throw error
	return Position<E>(searchTree(_root,x));//search for the result
}

template <typename E>
void BinaryTree<E>::addRoot()				//add root to empty tree
{
	_root = new Node<E>; 
	n = 1;
}

template <typename E>						//add node to tree
void BinaryTree<E>::addNode(Node<E>* v, bool addLeft, E x)
{
	Node<E>* w = new Node<E>;
	if(addLeft)
		v->left = w;
	else
		v->right = w;
	w->parent = v;
	w->element = x;
	n += 1;
}

template <typename E>
void BinaryTree<E>::splice(Node<E>* v)		//splice in a node from elsewhere
{
	Node<E>* s = v;							//assign s as v
	Node<E>* p = v->parent;					//assign p as v->parent
	if ( v->left != nullptr)				//is v->left not null?
		s = v->left;						//assign s as v->left
	else									//else
		s = v->right;						//assign s as v->right
	if ( Position<E>(v).isRoot() )			//is v root?
		_root = s;							//assign root to s
	else									//else
	{
		if ( p->left == v )					//is v a left child?
			p->left = s;					//assign p->left as s
		else								//else
			p->right = s;					//assign p->right as s
	}
	if ( s != nullptr )
		s->parent = p;						//assign s->parent as p
	delete v;								//delete v;
	n--;									//reduce size count by 1
}


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
void BinaryTree<E>::addValue(Node<E>* v, E x)
{
	bool addLeft = true;					//variable defining add to the left
	bool addRight = false;					//variable defining add to the right
	if( v->element == x )					//is add needed?
		return;								//if not, return
	if( v->element > x )					//is current greater than value?
	{
		if(v->left == nullptr)				//check for nullptr
			addNode(v, addLeft, x);			//add node if true
		else
			addValue(v->left, x);			//move left
	}
	else
	{
		if(v->right == nullptr)				//check for nullptr
			addNode(v, addRight, x);		//add node if true
		else
			addValue(v->right, x);			//move right
	}
		
}

template <typename E>
Node<E>* BinaryTree<E>::searchTree(
	Node<E>* v, E x)						//search tree utility
{
	if ( v->element == x )					//is node or end of branch?
		return v;
	if ( v->element > x )					//is v greater than x?
	{	
		if ( v->left == nullptr )			//end of the search?
			throw NodeNotFound(
				"Node is not in tree.");	//throw error
		return searchTree(v->left,x);		//traverse left
	}
	if ( v->element < x )					//is v less than x?
	{
		if ( v->right == nullptr )			//end of the search?
			throw NodeNotFound(
				"Node is not in tree.");	//throw error
		return searchTree(v->right,x);		//traverse right
	}
}


template <typename E>						//get next utility (preorder)
void BinaryTree<E>::preNext(Node<E>* v, Node<E>* x, Node<E>* y)
{
	if( y->parent != nullptr )				//check if given node is found
	{								
		y->parent = nullptr;				//prevent triggering later
		y->left = v;						//assign left to next node
	}
	if(v == x)								//is this the node?
		y->parent = x;						//flag subject node is found

	if( v->left != nullptr )				//traverse left subtree
		preNext(v->left,x,y);
	if( v->right != nullptr )				//traverse right subtree
		preNext(v->right,x,y);
}

template <typename E>						//get next utility (postorder)
void BinaryTree<E>::postNext(Node<E>* v, Node<E>* x, Node<E>* y)
{
	if( v->left != nullptr )				//traverse left subtree
		postNext(v->left,x,y);
	if( v->right != nullptr )				//traverse right subtree
		postNext(v->right,x,y);

	if( y->parent != nullptr )				//check if given node is found
	{								
		y->parent = nullptr;				//prevent triggering later
		y->left = v;						//assign left to next node
	}
	if(v == x)								//is this the node?
		y->parent = x;						//flag subject node is found

}

template <typename E>						//get next utility (inorder)
void BinaryTree<E>::inNext(Node<E>* v, Node<E>* x, Node<E>* y)
{
	if( v->left != nullptr )				//traverse left subtree
		inNext(v->left,x,y);

	if( y->parent != nullptr )				//check if given node is found
	{								
		y->parent = nullptr;				//prevent triggering later
		y->left = v;						//assign left to next node
	}
	if(v == x)								//is this the node?
		y->parent = x;						//flag subject node is found


	if( v->right != nullptr )				//traverse right subtree
		inNext(v->right,x,y);
}

template <typename E>						//return node after one given
Node<E>* BinaryTree<E>::next(Node<E>* x, Traversal order)
{
	if ( empty() )							//check for empty tree
		throw TreeEmpty(
			"Tree is empty.");				//throw error
	Node<E>* y = new Node<E>;				//create new node
	switch (order)							//call the required traverse
	{
		case PREORDER:
			preNext(_root,x,y);
			break;
		case POSTORDER:
			postNext(_root,x,y);
			break;
		case INORDER:
			inNext(_root,x,y);
			break;
	}
	if ( y->left == nullptr )				//check for a result
		if( y->parent != nullptr )			//check if initial item found
			throw TreeLastItem(
				"Last item in tree.");		//throw last item error
		else
			throw NodeNotFound(
				"Node not found in tree.");	//throw not found error
	return y->left;							//return next node
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

