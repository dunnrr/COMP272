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
private:
	E elem;									// linked list element value
	SNode<E>* next;							// next item in the list
	friend class SLinkedList<E>;			// provide SLinkedList access
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
private:
	SNode<E>* head;							// head of the list
};