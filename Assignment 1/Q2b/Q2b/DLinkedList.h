/******************************************************************************
* Implementation of a Generic Double Linked List
*
* Source: Data Structures and Algorithms in C++, 2nd Edition, 
*         by Michael T. Goodrich, Roberto Tamassia, David M. Mount, 
*         Wiley publisher, February 2011, © 2011
******************************************************************************/

#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

template <typename E>
class DNode									// Double linked list node
{
private:
	E elem;									// linked list element value
	DNode<E>* prev;							// previous node in list
	DNode<E>* next;							// next node in list
	template <typename E>
	friend class DLinkedList;				// provide SLinkedList access
	friend void swapConsecutive(DLinkedList<E> &list, int index);
};

template <typename E>
class DLinkedList							// Double linked list
{
public:
	DLinkedList();							// empty list constructor
	~DLinkedList();							// destructor
	bool empty() const;						// is list empty?
	const E& front() const;					// return front element
	const E& back() const;					// return back element
	void addFront(const E& e);				// add to front of list
	void addBack(const E& e);				// add to back of list
	void removeFront();						// remove from front
	void removeBack();						// remove from back
private:
	DNode<E>* header;						// head of the list
	DNode<E>* trailer;						// back of the list
	friend void swapConsecutive(DLinkedList<E> &list, int index);
protected:
	void add(DNode<E>* v, const E& e);			// insert new node before v
	void remove(DNode<E>* v);					// remove node v
};

#endif