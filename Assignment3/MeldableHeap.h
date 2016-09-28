#include "RuntimeException.h"
#include "Node.h"
#include <random>
#include <time>
#include <list>

srand(time(NULL));								//set random seed

template <typename E>
class MeldableHeap
{
public:
	using Node = GenNode<E>;
	using Position = GenPosition<E>;
	using PositionList = list<Node*>;
public:
	MeldableHeap();							//constructor
	~MeldableHeap();						//destructor
	int size() const;						//number of nodes
	bool empty() const;						//is heap empty?
	void add(E x);							//add x to heap
	void remove();							//remove root
	void remove(Position& x);				//remove node x
	PositionList inPositions() const;		//inorder list of nodes
	Position search(E x);					//get node containing x
	Position root() const;					//get the root	
protected:
	Node* merge(Node* h1, Node* h2);
	void searchHeap(Node* v, E x);			//search heap utility
	void inorder(Node* v,
		PositionList& pl) const;			//inorder utility
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
	while ( !empty() )
		remove();
}

template <typename E>						
int BinaryTree<E>::size() const				//number of nodes
{
	return n;
}

template <typename E>
bool BinaryTree<E>::empty() const	 		//is heap empty?
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
	Node* temp = _root;						//assign a node to root
	_root = merge(_root->left,_root->right);//reassign root
	if (_root != nullptr)
		_root->parent = nullptr;			//assign root's parent
	n--;									//size counter reduced
	delete temp;							//delete node
}

void MeldableHeap<E>::remove(Position& x)	//remove node x
{
	Node* temp = x.v;						//assign a node to x
	x.v = merge(x.v->left,x.v->right);		//reassign x
	if (x.v != nullptr)						
		x.v->parent = temp->parent;			//assign x's parent
	n--;									//size counter reduced
	delete temp;							//delete node
}

template <typename E>						//inorder list of nodes
typename MeldableHeap<E>::PositionList MeldableHeap<E>::inPositions() const
{
	PositionList pl;
	if ( !empty() )							//check for empty
		inorder(_root, pl);					//inorder traversal
	return pl;								//return resulting list
}

template <typename E>						//get node containing x
typename MeldableHeap<E>::Position MeldableHeap<E>::search(E x)		
{
	if ( empty() )							//check for empty
		throw HeapEmpty("Heap is empty.");	//throw error
	PositionList pl;
	searchHeap(_root, pl, x);				//search for the result
	if ( pl.empty() )						//check if found
		throw NodeNotFound(
			"Node is not in heap.")
	return Position(pl.front());			//return position
}

template <typename E>						//get the root
typename MeldableHeap<E>::Position MeldableHeap<E>::root() const
{
	if ( empty() )
		throw HeapEmpty("Heap is empty.");	//throw error
	return Position(_root);
}

void MeldableHeap<E>::remove(Position& x)	//remove node x
{
	Node* temp = x.v;						//assign a node to x
	x.v = merge(x.v->left,x.v->right);		//reassign x
	if (x.v != nullptr)						
		x.v->parent = temp->parent;			//assign x's parent
	n--;									//size counter reduced
	delete temp;							//delete node
}

template <typename E>
typename MeldableHeap<E>::Node* MeldableHeap<E>::merge(
	Node* h1, Node* h2)
{
	if ( h1 == nullptr )
		return h2;
	if ( h2 == nullptr )
		return h1;
	if ( h2->element < h1->element )
		return merge( h2, h1 )
	if ( rand() % 2 )
	{
		h1->left = merge( h1->left, h2 )
		h1->left->parent = h1;
	}
	else
	{
		h1->right = merge( h1->right, h2 )
		h1->right->parent = h1;
	}
	return h1;
}

template <typename E>
void MeldableHeap<E>::searchHeap(
	Node* v, PositionList& pl, E x)			//search heap utility
{
	if (v->left != nullptr)					//traverse left subtree
		inorder(v->left, pl);
	if (v->element == x)					//is this the node?
		pl.push_back(v);					//add this node
	if (v->right != nullptr)				//traverse right subtree
		inorder(v->right, pl);
}

template <typename E>						//inorder utility
void MeldableHeap<E>::inorder(Node* v, PositionList& pl) const
{
	if (v->left != nullptr)					//traverse left subtree
		inorder(v->left, pl);
	pl.push_back(v);						//add this node
	if (v->right != nullptr)				//traverse right subtree
		inorder(v->right, pl);
}