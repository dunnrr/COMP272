/******************************************************************************
* Implementation of a Generic Singly Linked List
*
* Source: Data Structures and Algorithms in C++, 2nd Edition, 
*         by Michael T. Goodrich, Roberto Tamassia, David M. Mount, 
*         Wiley publisher, February 2011, © 2011
******************************************************************************/

#pragma once
template <typename E>
class SNode									// singly linked list node
{
public:
	E elem;									// linked list element value
	SNode<E>* next;							// next item in the list
	template <typename E>
	friend class SLinkedList;				// provide SLinkedList access
	template <typename E>
	friend class PriorityQueue;				// provide PriorityQueue access
};

template <typename E>
class SLinkedList							// singly linked list
{
public:
	SLinkedList();							// empty list constructor
	~SLinkedList();							// destructor
	bool empty() const;						// is list empty?
	const E& front() const;					// return front element
	void addFront(const E& e);				// add to front of list
	void removeFront();						// remove front item list
//protected:
	SNode<E>* head;							// head of the list
	template <typename E>
	friend class PriorityQueue;				// provide PriorityQueue access
};

template <typename E>
SLinkedList<E>::SLinkedList()				// constructor
	: head(nullptr) {};

template <typename E>
bool SLinkedList<E>::empty() const	 		// is list empty?
{
	return head == nullptr;
}

template <typename E>
const E& SLinkedList<E>::front() const		//return front element
{
	return head->elem;
}

template <typename E>
SLinkedList<E>::~SLinkedList()				// destructor
{
	while (!empty())
		removeFront();
}

template <typename E>
void SLinkedList<E>::addFront(const E& e)	// add to front of list
{
	SNode<E>* v = new SNode<E>;				// create new node
	v->elem = e;							// store data
	v->next = head;							// head now follows v
	head = v;								// v is now the head
}

template <typename E>
void SLinkedList<E>::removeFront()			// remove front item
{
	SNode<E>* old = head;					// save current head
	head = old->next;						// skip over old head
	delete old;								// delete the old head
}