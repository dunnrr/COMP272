/******************************************************************************
*Implementation of add(x), deleteMin(), and size(), using a singly-linked list.
*
*Author: Robert Ryan Dunn
*SN: 3070207
*Date: April, 2016
******************************************************************************/

#include "SLinkedList.h"
#include <stdio.h>

class PriorityQueue	: public SLinkedList<int>	// Priority Queue
{
public:
	void add(const int& e);						// add to front of list
	int size();									// returns the size of the list
	int deleteMin() const throw (StackEmpty);	// removes the smallest element
												// and returns its value		
};

void PriorityQueue::add(const int& e)			// add to front of list
{
	PriorityQueue::addFront(e)					// Add to front of list using
												// SLinkedList function
}

int PriorityQueue::size()						// return the size of the list
{
	int size = 0;								// create a counter
	SNode<int>* current = new SNode<int>;		// create a pointer
	current = head;								// v now equals head
	while (current != NULL)						// check for end of list
	{
		current = current->next;				// advance the pointer
		size++;									// increment the counter
	}
	delete current;								// delete current pointer
	return i;									// return the size
}

int PriorityQueue::deleteMin() const throw(StackEmpty)
												// return the lowest value and
												// remove element from list
{
	if (empty()) 
		throw StackEmpty("No items in Queue");	// Throw Error if empty
	SNode<int>* current = new SNode<int>;		// current pointer location
	SNode<int>* prevMin = new SNode<int>;		// location of pointer before
												// the minimum
	current = head;								// current is at start of list
	prevMin->next = head;						// prevMin is pointer before
												// minimum
	while (current->next != NULL)				// check for end of list
	{
		if (prevMin->next->elem > current->next->elem)	//check for minimum
			prevMin = current;					// assign new prev minimum
		current = current->next;				// increment current pointer
	}
	current = prevMin->next;					// Current is now minimum
												// value to be deleted
	int minimum = current->elem;				// retrieve value of element
	prevMin->next = current->next;				// prevMin now follows next 
												// link
	delete current;								// delete the minimum
	delete prevMin;								// delete the extra pointer
	return minimum;								// return the minimum value
}

int main(void)
{

}