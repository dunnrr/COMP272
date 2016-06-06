/******************************************************************************
* Implementation of a Generic Singly Linked List for Assignment 1 of COMP 272
* Has added function swap for question 2a, and added a print function to see
* contents of the list without having to recreate the list every time.
*
* Modified from Source: Data Structures and Algorithms in C++, 2nd Edition, 
*						by Michael T. Goodrich, Roberto Tamassia, David M. 
*						Mount, Wiley publisher, February 2011, © 2011
*
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		5 June, 2016
******************************************************************************/

#ifndef _SLINKEDLIST_H_
#define _SLINKEDLIST_H_

#include <iostream>

template <typename E>
class SNode									//singly linked list node
{
private:
	E elem;									//linked list element value
	SNode<E>* next;							//next item in the list
	template <typename E>
	friend class SLinkedList;				//provide SLinkedList access
};

template <typename E>
class SLinkedList							//singly linked list
{
public:
	SLinkedList();							//empty list constructor
	~SLinkedList();							//destructor
	bool empty() const;						//is list empty?
	const E& front() const;					//return front element
	void addFront(const E& e);				//add to front of list
	void removeFront();						//remove front item list
	void print();							//list printout
	void swap(int index);					//swap consecutive items
private:
	SNode<E>* head;							//head of the list
};

template <typename E>
SLinkedList<E>::SLinkedList()				//constructor
	: head(nullptr) {};

template <typename E>
bool SLinkedList<E>::empty() const	 		//is list empty?
{
	return head == nullptr;
}

template <typename E>
const E& SLinkedList<E>::front() const		//return front element
{
	return head->elem;
}

template <typename E>
SLinkedList<E>::~SLinkedList()				//destructor
{
	while (!empty())
		removeFront();
}

template <typename E>
void SLinkedList<E>::addFront(const E& e)	//add to front of list
{
	SNode<E>* v = new SNode<E>;				//create new node
	v->elem = e;							//store data
	v->next = head;							//head now follows v
	head = v;								//v is now the head
}

template <typename E>
void SLinkedList<E>::removeFront()			//remove front item
{
	SNode<E>* old = head;					//save current head
	head = old->next;						//skip over old head
	delete old;								//delete the old head
}

template <typename E>
void SLinkedList<E>::print()				//list printout
{
	SNode<E>* current = head;				//assign a current pointer
	std::cout << "{";						//open list
	while (current != nullptr)				//cycle through list
	{
		std::cout << current->elem;			//print current elem
		current = current->next;			//increment to next item
		if (current != nullptr)				//check for end of list
			std::cout << ", ";				//add spacing
	}
	std::cout << "}";						//close list
}

template <typename E>
void SLinkedList<E>::swap(int index)		//swap consecutive items in list
// Assignment 1 Question 2a:

{
	if (index < 0)							//check if index is below 0
	{
		std::cout << "Index is out of bounds.  "
			<< "Index must be 0 or greater." << std::endl;
		return;								//exit function with error
	}
	
	if (head == nullptr || 
		head->next == nullptr)				//ensure list is big enough to swap
	{
		std::cout << "The list is empty or too small." 
			<< std::endl;
		return;								//exit function with error
	}
	
	if (index == 0)							//special case for swap of head
	{
		SNode<E>* current = head;			//assign a pointer equal to head
		SNode<E>* swap = current->next;		//assign a swap pointer
		current->next = swap->next;			//change the links of the pointers
		swap->next = current;
		head = swap;
	}
	else
	{
		SNode<E>* prev = head;				//assign a previous pointer
		SNode<E>* current = prev->next;		//assign a current pointer
		SNode<E>* swap = current->next;		//assign a swap pointer
		int counter = 1;					//create a counter

		//increment the pointer in the list to specified index
		while (counter != index)			
		{
			counter++;						//increment the counter
			if (swap->next != nullptr)		//check for end of list
			{
				current = current->next;	//increment the list pointer
				prev = prev->next;			//increment the prev pointer
				swap = swap->next;			//increment the swap pointer
			}
			else
			{
				std::cout << "Index is out of bounds.  "
					<< "End of list occurred." << std::endl;		
				return;						//exit function with error
			}
		}

		prev->next = swap;					//change the links of the pointers
		current->next = swap->next;
		swap->next = current;
	}
}

#endif
