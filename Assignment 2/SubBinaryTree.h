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

#include "BinaryTree.h"

template <typename E>
class SubNode: public GenNode<E>
{
public:
	SubNode<E>* left;
	SubNode<E>* right;
	SubNode<E>* parent;
	int prePos;
	int postPos;
	int inPos;
	SubNode<E>() : left(nullptr), 
		right(nullptr), parent(nullptr), 
		prePos(), postPos(), inPos() {}		//constructor
};


template <typename E>
class SubPosition: public GenPosition<E>
{
private:
	using Node = SubNode<E>;

	Node* v;							//pointer to the node

public:

	SubPosition<E>(SubNode<E>* _v = nullptr) : v(_v) 
	{}
	E& operator*()
	{ return v->element; }					//get element
	SubPosition<E> left() const
	{ return SubPosition(v->left); }		//get left child
	SubPosition<E> right() const
	{ return SubPosition(v->right); }		//get right child
	SubPosition<E> parent() const
	{ return SubPosition(v->parent); }		//get parent
	int prePos() const						//return pre position number
	{ return v->prePos;	}
	int postPos() const
	{ return v->postPos; }					//return post position number
	int inPos() const
	{ return v->inPos; }					//return in position number
};
/*
template <typename E, 
	typename SubGenNode = SubNode<E>*>
using SubPositionList = list<SubGenNode>;	//list of positions
*/

template <typename E>
class SubBinaryTree: public BinaryTree<E>
{
private:
	using Node = SubNode<E>;
	using Position = SubPosition<E>;
public:
	using PositionList = list<Node*>;	
public:
	void preorderNumber();					//assign preorder numbers
	void postorderNumber();					//assign postorder numbers
	void inorderNumber();					//assign inorder numbers
	PositionList prePositions() const;		//preorder list of nodes
	PositionList postPositions() const;		//postorder list of nodes
	PositionList inPositions() const;		//inorder list of nodes
	void add(E x);							//add x to the tree
protected:
	void preNumber(Node* v, int& counter);	//preorder number utility
	void postNumber(Node* v, int& counter);	//postorder number utility	
	void inNumber(Node* v, int& counter);	//inorder number utility
	void preorder(Node* v, 
		PositionList& pl) const;			//preorder utility
	void postorder(Node* v,
		PositionList& pl) const;			//postorder utility
	void inorder(Node* v,
		PositionList& pl) const;			//inorder utility	
	void addRoot();							//add root to empty tree
	void addNode(Node* v, bool addLeft,
		E value);							//add node to tree
	void addValue(Node* v, E x);			//add utility
private:
	Node* _root;

};

template <typename E>
void SubBinaryTree<E>::preorderNumber()		//assign preorder numbers
{
	int counter = 1;
	preNumber(_root, counter);
}

template <typename E>
void SubBinaryTree<E>::postorderNumber()	//assign postorder numbers
{
	int counter = 1;
	postNumber(_root, counter);
}

template <typename E>
void SubBinaryTree<E>::inorderNumber()		//assign inorder numbers
{
	int counter = 1;
	inNumber(_root, counter);
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

template <typename E>						//preorder list of nodes
typename SubBinaryTree<E>::PositionList SubBinaryTree<E>::prePositions() const
{
	PositionList pl;
	if ( !this->empty() )					//check for empty
		preorder(_root, pl);				//preorder traversal
	return pl;								//return resulting list
}

template <typename E>						//postorder list of nodes
typename SubBinaryTree<E>::PositionList SubBinaryTree<E>::postPositions() const
{
	PositionList pl;
	if ( !this->empty() )					//check for empty
		postorder(_root, pl);				//postorder traversal
	return pl;								//return resulting list
}

template <typename E>						//inorder list of nodes
typename SubBinaryTree<E>::PositionList SubBinaryTree<E>::inPositions() const
{
	PositionList pl;
	if ( !this->empty() )					//check for empty
		inorder(_root, pl);					//inorder traversal
	return pl;								//return resulting list
}

template <typename E>						//preorder utility
void SubBinaryTree<E>::preorder(Node* v, PositionList& pl) const
{
	pl.push_back(v);						//add this node
	if (v->left != nullptr)					//traverse left subtree
		preorder(v->left, pl);
	if (v->right != nullptr)				//traverse right subtree
		preorder(v->right, pl);
}

template <typename E>						//postorder utility
void SubBinaryTree<E>::postorder(Node* v, PositionList& pl) const
{
	if (v->left != nullptr)					//traverse left subtree
		postorder(v->left, pl);
	if (v->right != nullptr)				//traverse right subtree
		postorder(v->right, pl);
	pl.push_back(v);						//add this node
}

template <typename E>						//inorder utility
void SubBinaryTree<E>::inorder(Node* v, PositionList& pl) const
{
	if (v->left != nullptr)					//traverse left subtree
		inorder(v->left, pl);
	pl.push_back(v);						//add this node
	if (v->right != nullptr)				//traverse right subtree
		inorder(v->right, pl);
}


template <typename E>
void SubBinaryTree<E>::add(E x)				//add a value to the tree
{
	if( this->empty() )						//if empty
	{
		addRoot();							//create root
		Node* v = _root;					
		v->element = x;						//assign a value to root
	}
	else
		addValue(_root, x);					//use add utility		
}

template <typename E>
void SubBinaryTree<E>::addRoot()			//add root to empty tree
{
	_root = new Node; 
	this->n = 1;
}


template <typename E>						//add node to tree
void SubBinaryTree<E>::addNode(Node* v, bool addLeft, E x)
{
	Node* w = new Node;
	if(addLeft)
		v->left = w;
	else
		v->right = w;
	w->parent = v;
	w->element = x;
	this->n += 1;
}

template <typename E>						//add utility
void SubBinaryTree<E>::addValue(Node* v, E x)
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





#endif