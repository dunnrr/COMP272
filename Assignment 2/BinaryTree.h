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

#include "Node.h"
#include <list>
#include "RuntimeException.h"

using std::list;
enum Traversal { PREORDER, POSTORDER, 
	INORDER };								//types of traversal

template <typename E>
class BinaryTree							//Binary Tree
{
public:
	using Node = GenNode<E>;
	using Position = GenPosition<E>;
	using PositionList = list<Node*>;
public:	
	BinaryTree();							//constructor
	~BinaryTree();							//destructor
	int size() const;						//number of nodes
	bool empty() const;						//is tree empty?
	Position root() const;					//get the root
	Position preorderNext(Position x);		//get node after node x (preorder)
	Position postorderNext(Position x);		//get node after node x (postorder)
	Position inorderNext(Position x);		//get node after node x (inorder)
	PositionList prePositions() const;		//preorder list of nodes
	PositionList postPositions() const;		//postorder list of nodes
	PositionList inPositions() const;		//inorder list of nodes
	void add(E x);							//add x to the tree
	void remove(Position x);				//remove node x from the tree
	Position search(E x);					//get node containing x
protected:
	void addRoot();							//add root to empty tree
	void addNode(Node* v, bool addLeft,
		E value);							//add node to tree
	void splice(Node* v);					//splice in a node from elsewhere
	void deleteTree(Node* v);				//destructor utility
	void addValue(Node* v, E x);			//add utility
	Node* searchTree(Node* v, E x);			//search tree utility
	void preNext(Node* v, Node* x, Node* y);//get next utility (preorder)
	void postNext(Node* v, Node* x, 
		Node* y);							//get next utility (postorder)
	void inNext(Node* v, Node* x, Node* y);	//get next utility (inorder)
	Node* next(Node* x, Traversal order);	//return node after one given
	void preorder(Node* v, 
		PositionList& pl) const;			//preorder utility
	void postorder(Node* v,
		PositionList& pl) const;			//postorder utility
	void inorder(Node* v,
		PositionList& pl) const;			//inorder utility
	int n;									//number of nodes
	Node* _root;							//pointer to the root
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
typename BinaryTree<E>::Position BinaryTree<E>::root() const
{
	if ( empty() )
		throw TreeEmpty("Tree is empty.");	//throw error
	return Position(_root);
}

template <typename E>						//get node after node x (preorder)
typename BinaryTree<E>::Position BinaryTree<E>::preorderNext(Position x)
{
	Traversal traversalType = PREORDER;		//assign type of traversal
	return Position(next(x.v, 
		traversalType));					//return the next node
}

template <typename E>						//get node after node x (postorder)
typename BinaryTree<E>::Position BinaryTree<E>::postorderNext(Position x)
{
	Traversal traversalType = POSTORDER;	//assign type of traversal
	return Position(next(x.v, 
		traversalType));					//return the next node
}

template <typename E>						//get node after node x (inorder)	
typename BinaryTree<E>::Position BinaryTree<E>::inorderNext(Position x)
{
	Traversal traversalType = INORDER;		//assign type of traversal
	return Position(next(x.v, 
		traversalType));					//return the next node
}

template <typename E>						//preorder list of nodes
typename BinaryTree<E>::PositionList BinaryTree<E>::prePositions() const
{
	PositionList pl;
	if ( !empty() )							//check for empty
		preorder(_root, pl);				//preorder traversal
	return pl;								//return resulting list
}

template <typename E>						//postorder list of nodes
typename BinaryTree<E>::PositionList BinaryTree<E>::postPositions() const
{
	PositionList pl;
	if ( !empty() )							//check for empty
		postorder(_root, pl);				//postorder traversal
	return pl;								//return resulting list
}

template <typename E>						//inorder list of nodes
typename BinaryTree<E>::PositionList BinaryTree<E>::inPositions() const
{
	PositionList pl;
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
		Node* v = _root;					
		v->element = x;						//assign a value to root
	}
	else
		addValue(_root, x);					//use add utility		
}

template <typename E>
void BinaryTree<E>::remove(Position x)		//remove node x from the tree
{
	if ( x.v->left == nullptr || 
		x.v->right == nullptr )				//does x only have 0 or 1 children?
		splice(x.v);						//splice node x
	else
	{
		Node* w = x.v->right;				//assign node w to x's right
		while ( w->left != nullptr )		//until w->left is a nullptr
			w = w->left;					//assign w as w->left
		x.v->element = w->element;			//move the value of w to x
		splice(w);							//splice node w
	}
}

template <typename E>						//get node containing x
typename BinaryTree<E>::Position BinaryTree<E>::search(E x)		
{
	if ( empty() )							//check for empty
		throw TreeEmpty("Tree is empty.");	//throw error
	return Position(searchTree(_root,x));	//search for the result
}

template <typename E>
void BinaryTree<E>::addRoot()				//add root to empty tree
{
	_root = new Node; 
	n = 1;
}

template <typename E>						//add node to tree
void BinaryTree<E>::addNode(Node* v, bool addLeft, E x)
{
	Node* w = new Node;
	if(addLeft)
		v->left = w;
	else
		v->right = w;
	w->parent = v;
	w->element = x;
	n += 1;
}

template <typename E>
void BinaryTree<E>::splice(Node* v)			//splice in a node from elsewhere
{
	Node* s = v;							//assign s as v
	Node* p = v->parent;					//assign p as v->parent
	if ( v->left != nullptr)				//is v->left not null?
		s = v->left;						//assign s as v->left
	else									//else
		s = v->right;						//assign s as v->right
	if ( Position(v).isRoot() )				//is v root?
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
void BinaryTree<E>::deleteTree(Node* v)		//destructor utility
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
void BinaryTree<E>::addValue(Node* v, E x)
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
typename BinaryTree<E>::Node* BinaryTree<E>::searchTree(
	Node* v, E x)							//search tree utility
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
void BinaryTree<E>::preNext(Node* v, Node* x, Node* y)
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
void BinaryTree<E>::postNext(Node* v, Node* x, Node* y)
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
void BinaryTree<E>::inNext(Node* v, Node* x, Node* y)
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
typename BinaryTree<E>::Node* BinaryTree<E>::next(Node* x, Traversal order)
{
	if ( empty() )							//check for empty tree
		throw TreeEmpty(
			"Tree is empty.");				//throw error
	Node* y = new Node;						//create new node
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
void BinaryTree<E>::preorder(Node* v, PositionList& pl) const
{
	pl.push_back(v);						//add this node
	if (v->left != nullptr)					//traverse left subtree
		preorder(v->left, pl);
	if (v->right != nullptr)				//traverse right subtree
		preorder(v->right, pl);
}

template <typename E>						//postorder utility
void BinaryTree<E>::postorder(Node* v, PositionList& pl) const
{
	if (v->left != nullptr)					//traverse left subtree
		postorder(v->left, pl);
	if (v->right != nullptr)				//traverse right subtree
		postorder(v->right, pl);
	pl.push_back(v);						//add this node
}

template <typename E>						//inorder utility
void BinaryTree<E>::inorder(Node* v, PositionList& pl) const
{
	if (v->left != nullptr)					//traverse left subtree
		inorder(v->left, pl);
	pl.push_back(v);						//add this node
	if (v->right != nullptr)				//traverse right subtree
		inorder(v->right, pl);
}

#endif

