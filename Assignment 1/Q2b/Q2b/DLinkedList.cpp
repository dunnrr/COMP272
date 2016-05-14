/******************************************************************************
* Implementation of a Generic Singly Linked List
*
* Source: Data Structures and Algorithms in C++, 2nd Edition,
*         by Michael T. Goodrich, Roberto Tamassia, David M. Mount,
*         Wiley publisher, February 2011, © 2011
******************************************************************************/

#include "DLinkedList.h"

template <typename E>
DLinkedList<E>::DLinkedList()				// constructor
{
	header = new DNode<E>;		//create sentinels
	trailer = new DNode<E>;
	header->next = trailer;
	trailer->prev = header;
}

template <typename E>
DLinkedList<E>::~DLinkedList()				// destructor
{
	while (!empty())
		removeFront();
	delete header;
	delete trailer;
}

template <typename E>
bool DLinkedList<E>::empty() const	 		// is list empty?
{
	return (header->next == trailer);
}

template <typename E>
const E& DLinkedList<E>::front() const		//return front element
{
	return header->next->elem;
}

template <typename E>
const E& DLinkedList<E>::back() const		//return back element
{
	return trailer->prev->elem;
}

template <typename E>
void DLinkedList<E>::add(DNode<E>* v, const E& e)	//insert new node before v
{
	DNode<E>* u = new DNode<E>;					//create new node for e
	u->elem = e;
	u->next = v;								// link u in between v
	u->prev = v->prev;							// and v->prev
	v->prev->next = u;
	v->prev = u;
}

template <typename E>
void DLinkedList<E>::addFront(const E& e)	// add to front of list
{
	add(header->next, e);
}

template <typename E>
void DLinkedList<E>::addBack(const E& e)	// add to back of list
{
	add(trailer, e);
}

template <typename E>
void DLinkedList<E>::remove(DNode<E>* v)	// remove node v
{	
	DNode<E>* u = v->prev;					// predecessor
	DNode<E>* w = v->next;					// successor
	u->next = w;							// unlink v from list
	w->prev = u;
	delete v;
}

template <typename E>
void DLinkedList<E>::removeFront()			// remove front item
{
	remove(header->next);
}

template <typename E>
void DLinkedList<E>::removeBack()			// remove back item
{
	remove(trailer->prev);
}


template class DNode<int>;
template class DLinkedList<int>;