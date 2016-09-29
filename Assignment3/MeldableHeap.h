/******************************************************************************
* Implementation of a Meldable Heap for Assignment 3 of COMP 272
*
* Modified from Sources: Open Data Structures an Introduction, by Pat Morin,
* 						AU Press, © 2013
*
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		28 September, 2016
******************************************************************************/

#ifndef _MELDABLEHEAP_H_					//if not defined
#define _MELDABLEHEAP_H_		

#include "RuntimeException.h"
#include "Node.h"
#include <random>
#include <time.h>
#include <list>

template <typename E>
class MeldableHeap
{
public:
	using Node = GenNode<E>;
	using Position = GenPosition<E>;
	using PositionList = std::list<Node*>;
public:
	MeldableHeap();							//constructor
	~MeldableHeap();						//destructor
	int size() const;						//number of nodes
	bool empty() const;						//is heap empty?
	void add(E x);							//add x to heap
	void remove();							//remove root
	void remove(Node* x);					//remove node x
	PositionList prePositions() const;		//inorder list of nodes
	Node* search(E x);						//get node containing x
	Position root() const;					//get the root	
protected:
	Node* merge(Node* h1, Node* h2);		//merge two heaps
	void searchHeap(Node* v, 
		PositionList& pl, E x);				//search heap utility
	void preorder(Node* v,
		PositionList& pl) const;			//preorder utility
private:
	Node* _root;
	int n;
};

template <typename E>
MeldableHeap<E>::MeldableHeap()				//constructor
	: _root(nullptr), n(0) {};

template <typename E>
MeldableHeap<E>::~MeldableHeap()			//destructor
{
	while ( !empty() )						//while not empty
		remove();							//remove root
}

template <typename E>						
int MeldableHeap<E>::size() const			//number of nodes
{
	return n;
}

template <typename E>
bool MeldableHeap<E>::empty() const	 		//is heap empty?
{
	return size() == 0;
}

template <typename E>
void MeldableHeap<E>::add(E x)				//add x to heap
{
	Node* u = new Node;						//create new node
	u->element = x;							//assign element
	_root = merge(u, _root);				//get new root
	_root->parent = nullptr;				//assign root parent
	n++;									//increase size
}

template <typename E>
void MeldableHeap<E>::remove()				//remove root
{
	if (empty())							//check for empty
		throw HeapEmpty("Heap is empty.");	//throw heap empty
	Node* temp = _root;						//assign a node to root
	_root = merge(_root->left,_root->right);//reassign root
	if (_root != nullptr)
		_root->parent = nullptr;			//assign root's parent
	n--;									//size counter reduced
	delete temp;							//delete node
}

template <typename E>
void MeldableHeap<E>::remove(Node* x)		//remove node x
{
	if ( x->parent == nullptr )				//is node root?
		remove();							//remove root
	else
	{
		Node* p = x->parent;				//assign x's parent
		if ( p->left == x )					//is x a left child?
			p->left = merge(x->left,
				x->right);					//reassign the parents left
		else
			p->right = merge(x->left,
				x->right);					//reassign the parents right
		n--;								//size counter reduced
		delete x;							//delete node
	}
}

template <typename E>						//preorder list of nodes
typename MeldableHeap<E>::PositionList MeldableHeap<E>::prePositions() const
{
	PositionList pl;
	if ( !empty() )							//check for empty
		preorder(_root, pl);				//preorder traversal
	return pl;								//return resulting list
}

template <typename E>						//get node containing x
typename MeldableHeap<E>::Node* MeldableHeap<E>::search(E x)		
{
	if ( empty() )							//check for empty
		throw HeapEmpty("Heap is empty.");	//throw error
	PositionList pl;
	searchHeap(_root, pl, x);				//search for the result
	if ( pl.empty() )						//check if found
		throw NodeNotFound(
			"Node is not in heap.");
	return pl.front();						//return node
}

template <typename E>						//get the root
typename MeldableHeap<E>::Position MeldableHeap<E>::root() const
{
	if ( empty() )
		throw HeapEmpty("Heap is empty.");	//throw error
	return Position(_root);
}

template <typename E>
typename MeldableHeap<E>::Node* MeldableHeap<E>::merge(
	Node* h1, Node* h2)						//merge two heaps
{
	if ( h1 == nullptr )					//is h1 null?
		return h2;							//return h2
	if ( h2 == nullptr )					//is h2 null?
		return h1;							//return h1
	if ( h2->element < h1->element )		//is h2 smaller than h1?
		return merge( h2, h1 );				//switch to smaller value
	if ( rand() % 2 )						//randomly choose left or right
	{
		h1->left = merge( h1->left, h2 );	//h2 becomes left child
		h1->left->parent = h1;
	}
	else
	{
		h1->right = merge( h1->right, h2 );	//h2 becomes right child
		h1->right->parent = h1;
	}
	return h1;								//return h1
}

template <typename E>
void MeldableHeap<E>::searchHeap(
	Node* v, PositionList& pl, E x)			//search heap utility
{
	if (v->element == x)					//is this the node?
		pl.push_back(v);					//add this node
	if (v->left != nullptr)					//traverse left subtree
		searchHeap(v->left, pl, x);
	if (v->right != nullptr)				//traverse right subtree
		searchHeap(v->right, pl, x);
}

template <typename E>						//preorder utility
void MeldableHeap<E>::preorder(Node* v, PositionList& pl) const
{
	pl.push_back(v);						//add this node
	if (v->left != nullptr)					//traverse left subtree
		preorder(v->left, pl);
	if (v->right != nullptr)				//traverse right subtree
		preorder(v->right, pl);
}

#endif