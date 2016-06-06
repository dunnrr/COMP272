/******************************************************************************
* Implementation of a Generic Singly Linked List for Assignment 1 of COMP 272
* Has added function swap for question 2b, a function reverse for question 5
* and added a print function to see contents of the list without having to 
* recreate the list every time.
*
* Modified from Source: Data Structures and Algorithms in C++, 2nd Edition,
*						by Michael T. Goodrich, Roberto Tamassia, David M.
*						Mount, Wiley publisher, February 2011, © 2011
*
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		5 June, 2016
******************************************************************************/

#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

template <typename E>
class DNode											//Double linked list node
{
private:
	E elem;											//linked list element value
	DNode<E>* prev;									//previous node in list
	DNode<E>* next;									//next node in list
	template <typename E>
	friend class DLinkedList;						//grant DLinkedList access
};

template <typename E>
class DLinkedList									//Double linked list
{
public:
	DLinkedList();									//empty list constructor
	~DLinkedList();									//destructor
	bool empty() const;								//is list empty?
	const E& front() const;							//return front element
	const E& back() const;							//return back element
	void addFront(const E& e);						//add to front of list
	void addBack(const E& e);						//add to back of list
	void removeFront();								//remove from front
	void removeBack();								//remove from back
	void print();									//print out list
	void swap(int index);							//swap consecutive nodes
	void reverse();									//reverse the list
private:
	DNode<E>* header;								//head of the list
	DNode<E>* trailer;								//back of the list
protected:
	void add(DNode<E>* v, const E& e);				//insert new node before v
	void remove(DNode<E>* v);						//remove node v
};

template <typename E>	
DLinkedList<E>::DLinkedList()						//constructor
{
	header = new DNode<E>;							//create sentinels
	trailer = new DNode<E>;
	header->next = trailer;
	trailer->prev = header;
}

template <typename E>
DLinkedList<E>::~DLinkedList()						//destructor
{
	while (!empty())
		removeFront();
	delete header;
	delete trailer;
}

template <typename E>
bool DLinkedList<E>::empty() const	 				//is list empty?
{
	return (header->next == trailer);
}

template <typename E>
const E& DLinkedList<E>::front() const				//return front element
{
	return header->next->elem;
}

template <typename E>
const E& DLinkedList<E>::back() const				//return back element
{
	return trailer->prev->elem;
}

template <typename E>
void DLinkedList<E>::add(DNode<E>* v, const E& e)	//insert new node before v
{
	DNode<E>* u = new DNode<E>;						//create new node for e
	u->elem = e;
	u->next = v;									//link u in between v
	u->prev = v->prev;								//and v->prev
	v->prev->next = u;
	v->prev = u;
}

template <typename E>
void DLinkedList<E>::addFront(const E& e)			//add to front of list
{
	add(header->next, e);
}

template <typename E>
void DLinkedList<E>::addBack(const E& e)			//add to back of list
{
	add(trailer, e);
}

template <typename E>
void DLinkedList<E>::remove(DNode<E>* v)			//remove node v
{
	DNode<E>* u = v->prev;							//predecessor
	DNode<E>* w = v->next;							//successor
	u->next = w;									//unlink v from list
	w->prev = u;
	delete v;
}

template <typename E>
void DLinkedList<E>::removeFront()					//remove front item
{
	remove(header->next);
}

template <typename E>
void DLinkedList<E>::removeBack()					//remove back item
{
	remove(trailer->prev);
}

template <typename E>
void DLinkedList<E>::print()						//list printout
{
	DNode<E>* current = header;						//assign a current pointer
	std::cout << "{";								//open list
	while (current->next != trailer)				//cycle through list
	{
		current = current->next;					//increment to next item
		std::cout << current->elem;					//print current elem
		if (current->next != trailer)				//check for end of list
			std::cout << ", ";						//add spacing
	}
	std::cout << "}";								//close list
}

template <typename E>
void DLinkedList<E>::swap(int index)				//swap consecutive nodes
{
	if (index < 0)									//check if index is below 0
	{
		std::cout << "Index is out of bounds.  "
			<< "Index must be 0 or greater." << std::endl;
		return;										//exit function with error
	}
	if (empty() || header->next == trailer->prev)	//ensure list is big enough
	{
		std::cout << "The list is empty or too small." 
			<< std::endl;
		return;										//exit function with error
	}

	DNode<int>* current = header->next;				//assign current pointer
	DNode<int>* swap = current->next;				//assign swap pointer
	int counter = 0;								//create a counter

	//increment the pointer in the list to specified index
	while (counter != index)						
	{
		counter++;									//increment counter
		if (swap->next != trailer)					//check for end of list
		{
			current = current->next;				//increment current pointer
			swap = swap->next;						//increment swap pointer
		}
		else
		{
			std::cout << "Index is out of bounds.  "
				<< "End of list occurred." << std::endl;
			return;									//exit function with error
		}
	}

	swap->prev = current->prev;						//swap links
	current->prev = swap;
	current->next = swap->next;
	swap->next = current;
	swap->prev->next = swap;
	current->next->prev = current;
}

template <typename E>
void DLinkedList<E>::reverse()						// reverse list
{
	DLinkedList<E> temp;							// temporary list container
	while (!empty())								// check for empty list
	{
		temp.addFront(front());						// add front element to temp
		removeFront();								// remove front element
	}
	while (!temp.empty())							// check for empty temp list
	{
		addFront(temp.back());						// add temps back to front
		temp.removeBack();							// remove temps back element
	}
}
#endif