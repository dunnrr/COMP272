/******************************************************************************
* Implementation of a RandomQueue meant to have operations add(X) and remove()
* operations operate in constant time
*
* Source: Robert Ryan Dunn
* SN: 3070207
* Assignment 1, Question 4
* Date: May 23, 2016
******************************************************************************/

#include "RandomQueue.h"						// includes required for class
#include <random>										
#include <time.h>
#include <exception>


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
E RandomQueue<E>::atIndex(const int i)			// returns element at index i
{
	if ((i >= queueSize) || (i < 0))			// check index for out of range
		throw "Index out of range!";			// throw error
	return queueEntries[i];						// return element at index i
}

template<typename E>
void RandomQueue<E>::remove()					// remove an item at random
{
	if (empty())								// check for empty
		return;
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

template class RandomQueue<int>;				// initialize class with <int>