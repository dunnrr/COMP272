/******************************************************************************
* Implementation of a RandomQueue meant to have operations add(X) and remove()
* operations operate in constant time
*
* Source: Robert Ryan Dunn
* SN: 3070207
* Assignment 1, Question 4
* Date: May 23, 2016
******************************************************************************/

#ifndef _RANDOMQUEUE_H_							// ensure header hasn't already
#define _RANDOMQUEUE_H_							// been defined

#include <random>								// includes required for class
#include <time.h>
#include <iostream>
#include "RuntimeException.h"

template <typename E>
class RandomQueue								// RandomQueue
{
public:
	RandomQueue(int maxEnt);					// empty queue constructor
	~RandomQueue();								// destructor
	bool empty() const;							// is queue empty?
	int size() const;							// return the size of queue
	void add(const E& e);						// add item to end of queue
	E atIndex(const int index) const
		throw(IndexOutOfBounds);				// returns element at index i
	void remove() throw(QueueEmpty);			// remove an item at random
	void print() const;							// print out the queue
private:
	int maxEntries;								// maximum number of entries
	int queueSize;								// size of queue counter
	E* queueEntries;							// array of queue entries
protected:
	void doubleSize();							// double the size of the array
};

template<typename E>
RandomQueue<E>::RandomQueue(int maxEnt)			// constructor
{
	maxEntries = maxEnt;						// save the max size
	queueEntries = new E[maxEnt];				// allocate array storage
	queueSize = 0;								// initialize queue size
}

template<typename E>
RandomQueue<E>::~RandomQueue()					// destructor
{
	delete[] queueEntries;
}

template<typename E>
bool RandomQueue<E>::empty() const				// is list empty?
{
	return (queueSize == 0);
}

template<typename E>
int RandomQueue<E>::size() const				// return the size of queue
{
	return queueSize;
}

template<typename E>
void RandomQueue<E>::add(const E& e)			// add item to end of queue
{
	if ((queueSize + 1) == maxEntries)			// exceeding max size of array?
		doubleSize();							// double array size
	queueEntries[queueSize] = e;				// assign element to queue
	queueSize++;								// increase queueSize count
}

template<typename E>							
E RandomQueue<E>::atIndex(const int index) 
	const throw(IndexOutOfBounds)				// returns element at index i
{
	if ((index >= queueSize) || (index < 0))	// check index for out of range
		throw 
		IndexOutOfBounds("Index out of bounds");// throw error
	return queueEntries[index];					// return element at index i
}

template<typename E>
void RandomQueue<E>::remove() throw(QueueEmpty)	// remove an item at random
{
	if (empty())								// check for empty
		throw QueueEmpty("Queue is empty");
	srand(time(NULL));
	int removeIndex = rand() % queueSize;		// initialize index to remove
	queueEntries[removeIndex] =
		queueEntries[queueSize - 1];			// move last entry to location
												// of index being removed
	queueSize--;								// change size of queue
}

template<typename E>
void RandomQueue<E>::doubleSize()				// double the size of the array
{
	maxEntries *= 2;							// increase capacity of array
	E* temp = new E[maxEntries];				// create temporary array
	for (int i = 0; i < queueSize; i++)
	{
		temp[i] = queueEntries[i];				// copy contents of array
	}
	delete[] queueEntries;						// delete initial array
	queueEntries = temp;						// reassign array to temp
}

template<typename E>
void RandomQueue<E>::print() const				// print the queue
{
	std::cout << "{";
	for (int i = 0; i < size(); i++)			// cycle through queue
	{
		std::cout << atIndex(i);				// output queue elements
		if (i != size() - 1)					// check for last element
			std::cout << " ";
	}
	std::cout << "}";
}

#endif											// end header definition



