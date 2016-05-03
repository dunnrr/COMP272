/******************************************************************************
*Implementation of add(x), deleteMin(), and size(), using a singly-linked list.
*
*Author: Robert Ryan Dunn
*SN: 3070207
*Date: April, 2016
******************************************************************************/

#include "SLinkedList.h"
#include "RuntimeException.h"
#include <iostream>

class StackEmpty : public RuntimeException
{
public:
	StackEmpty(const std::string& err) : RuntimeException(err) {}
};

template <typename E>
class PriorityQueue : public SLinkedList<E>	// Priority Queue
{
public:
	void add(const E& e);						// add to front of list
	int size();									// returns the size of the list
	E deleteMin() const throw (StackEmpty);		// removes the smallest element
												// and returns its value		
};

template <typename E>
void PriorityQueue<E>::add(const E& e)			// add to front of list
{
	PriorityQueue<E>::addFront(e);				// Add to front of list using
												// SLinkedList function
}

template <typename E>
int PriorityQueue<E>::size()					// return the size of the list
{
	int listSize = 0;								// create a counter
	SNode<E>* current = new SNode<E>;			// create a pointer
	current = head;								// v now equals head
	while (current != NULL)						// check for end of list
	{
		current = current->next;				// advance the pointer
		listSize++;									// increment the counter
	}
	delete current;								// delete current pointer
	return listSize;								// return the size
}

template <typename E>
E PriorityQueue<E>::deleteMin() const throw(StackEmpty)
												// return the lowest value and
												// remove element from list
{
	if (empty()) 
		throw StackEmpty("No items in Queue");	// Throw Error if empty
	SNode<E>* current = new SNode<E>;			// current pointer location
	SNode<E>* prevMin = new SNode<E>;			// location of pointer before
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
	E minimum = current->elem;				// retrieve value of element
	prevMin->next = current->next;				// prevMin now follows next 
												// link
	delete current;								// delete the minimum
	delete prevMin;								// delete the extra pointer
	return minimum;								// return the minimum value
}

template <typename E>
void outputContents(PriorityQueue<E> temp)	// output contents of PriorityQueue
											// in order as shown in the stack
{
	std::cout << "The Current Stack is: ";
	if (temp.empty())
		std::cout << "empty";
	while (!temp.empty())						// cycle through stack until
												// empty
		{
			std::cout << temp.front() << " ";	// output front of the stack
			temp.removeFront();					// remove front of the stack
		}
	std::cout << std::endl;
}

int main(void)
{
	PriorityQueue<int> list;
	list.add(1);
	list.add(5);
	list.add(3);
	list.add(20);
	list.add(15);
	outputContents(list);
	outputContents(list);
	std::cout << "The smallest element is " << list.deleteMin() << std::endl;
	outputContents(list);
	std::cout << "The smallest element is " << list.deleteMin() << std::endl;
	outputContents(list);
	std::cout << "The size of the list is: " << list.size() << std::endl;
	std::cout << "The smallest element is " << list.deleteMin() << std::endl;
	outputContents(list);
	std::cout << "The smallest element is " << list.deleteMin() << std::endl;
	outputContents(list);
	std::cout << "The smallest element is " << list.deleteMin() << std::endl;
	outputContents(list);
	return EXIT_SUCCESS;
}