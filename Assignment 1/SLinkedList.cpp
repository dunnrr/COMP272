/******************************************************************************
* Implementation of a Generic Singly Linked List
*
* Source: Data Structures and Algorithms in C++, 2nd Edition,
*         by Michael T. Goodrich, Roberto Tamassia, David M. Mount,
*         Wiley publisher, February 2011, © 2011
******************************************************************************/

#include "SLinkedList.h"

template <typename E>
SLinkedList<E>::SLinkedList()				// constructor
	: head(NULL) {}

template <typename E>
bool SLinkedList<E>::empty() const	 		// is list empty?
{
	return head == NULL;
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