/******************************************************************************
* Implementation of a RandomQueue meant to have operations add(X) and remove()
* operations operate in constant time
*
* Source: Robert Ryan Dunn
* SN: 3070207
* Assignment 1, Question 4
* Date: May 23, 2016
******************************************************************************/

#ifndef _RANDOMQUEUE_H_						// ensure header hasn't already
#define _RANDOMQUEUE_H_						// been defined

#include <random>							// includes required for class
#include <time.h>
#include <exception>

template <typename E>
class RandomQueue							// RandomQueue
{
public:
	RandomQueue(int maxEnt);				// empty queue constructor
	~RandomQueue();							// destructor
	bool empty() const;						// is queue empty?
	int size() const;						// return the size of queue
	void add(const E& e);					// add item to end of queue
	E atIndex(const int i);					// returns element at index i
	void remove();							// remove an item at random
private:
	int maxEntries;							// maximum number of entries
	int queueSize;							// size of queue counter
	E* queueEntries;						// array of queue entries
protected:
	void doubleSize();						// double the size of the array
};

#endif										// end header definition



