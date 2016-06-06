/******************************************************************************
* Implementation of a Generic Priority Queue using a single linked list for 
* Assignment 1 of COMP 272.
*
* This priority queue is implemented such that the queue is sorted using the 
* add function so that deleteMin() doesn't have to search through the entire
* queue looking for the minimum value.
*
*
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		5 June, 2016
******************************************************************************/

#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_

#include "SLinkedList.h"

template <typename E>
class PriorityQueue							//priority queue
{
public:
	PriorityQueue();						//constructor
	void add(const E& e);					//add an item to the queue
	bool empty();							//checks for empty
	E min();								//returns the minimum value
	void deleteMin();						//deletes the minimum item
	void print();							//prints the queue
private:
	SLinkedList<E> SLList;					//list to manipulate
};

template <typename E>
PriorityQueue<E>::PriorityQueue()			//constructor
	:SLList() {};

template <typename E>
void PriorityQueue<E>::add(const E& e)		//add an item to the queue
// this function ensures that the items 
// are sorted when added to ensure that
// the deleteMin function works properly
{
	SLinkedList<E> temp;					//create a temporary list
	while (!empty() && e > SLList.front())	//search for the minimum
	{
		temp.addFront(SLList.front());		//add front item to temp
		SLList.removeFront();				//remove the front item
	}
	SLList.addFront(e);						//add new item to list
	while (!temp.empty())					//cycle through temp
	{
		SLList.addFront(temp.front());		//add front element to SLList
		temp.removeFront();					//remove front element from temp
	}
}

template <typename E>
bool PriorityQueue<E>::empty()				//checks for empty
{
	return SLList.empty();
}

template <typename E>
E PriorityQueue<E>::min()					//returns the minimum value
{
	return SLList.front();
}

template <typename E>
void PriorityQueue<E>::deleteMin()			//delete the minimum
{
	SLList.removeFront();					
}

template <typename E>
void PriorityQueue<E>::print()				//print the list
{
	SLList.print();
}
#endif
