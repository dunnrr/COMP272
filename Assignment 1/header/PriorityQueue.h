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
#include "RuntimeException.h"

template <typename E>
class PriorityQueue										//priority queue
{
public:
	PriorityQueue();									//constructor
	void add(const E& e);								//add item queue
	bool empty() const;									//checks for empty
	const E& min() throw(QueueEmpty);					//returns min value
	int size() const;									//returns queue size 
	void deleteMin() throw(QueueEmpty);					//deletes min item
	void print() const;									//prints queue
private:
	SLinkedList<E> SLList;								//list to manipulate
	int queueSize;										//size counter
};

template <typename E>
PriorityQueue<E>::PriorityQueue()						//constructor
	:SLList(), queueSize(0) {};

template <typename E>
void PriorityQueue<E>::add(const E& e)					//add item to queue
// this function ensures that the items 
// are sorted when added to ensure that
// the deleteMin function works properly
{
	SLinkedList<E> temp;								//create a temp list
	while (!empty() && e > SLList.front())				//search for min
	{
		temp.addFront(SLList.front());					//add front item
		SLList.removeFront();							//remove front item
	}
	SLList.addFront(e);									//add new item to list
	while (!temp.empty())								//cycle through temp
	{
		SLList.addFront(temp.front());					//add front element
		temp.removeFront();								//remove front element
	}
	queueSize++;										//increment queueSize
}

template <typename E>
bool PriorityQueue<E>::empty() const					//checks for empty
{
	return SLList.empty();
}

template <typename E>
const E& PriorityQueue<E>::min() throw(QueueEmpty)		//returns min value
{
	if (empty())										//check for empty
		throw QueueEmpty("Queue is Empty");
	return SLList.front();
}

template <typename E>
int PriorityQueue<E>::size() const						//returns queue size
{
	return queueSize;
}

template <typename E>
void PriorityQueue<E>::deleteMin() throw(QueueEmpty)	//delete minimum
{
	if (empty())										//check for empty
		throw QueueEmpty("Queue is Empty");
	SLList.removeFront();
	queueSize--;
}

template <typename E>
void PriorityQueue<E>::print() const					//print list
{
	SLList.print();
}
#endif
