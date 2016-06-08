/******************************************************************************
* Implementation of a Generic Queue for Assignment 1 of COMP 272
*
* Modified from Source: Data Structures and Algorithms in C++, 2nd Edition,
*						by Michael T. Goodrich, Roberto Tamassia, David M.
*						Mount, Wiley publisher, February 2011, © 2011
*
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		5 June, 2016
******************************************************************************/


#ifndef _QUEUE_H_									//if not defined
#define _QUEUE_H_									//define Queue

#include "CircleList.h"
#include "RuntimeException.h"

template <typename E>			
class Queue											//Queue
{
public:
	Queue();										//constructor
	int size() const;								//returns size of queue
	bool empty() const;								//is queue empty?
	const E& front() const throw(QueueEmpty);		//returns front
	void enqueue(const E& e);						//adds item to end
	void dequeue() throw(QueueEmpty);				//removes item from front
private:
	CircleList<E> CList;							//circle list 
	int queueSize;									//size of queue
};

template <typename E>
Queue<E>::Queue()									//constructor
	: CList(), queueSize(0) {};

template <typename E>
int Queue<E>::size() const							//returns size of queue
{
	return queueSize;
}

template <typename E>
bool Queue<E>::empty() const						//is queue empty?
{
	return queueSize == 0;
}

template <typename E>
const E& Queue<E>::front() const throw(QueueEmpty)	//returns front
{
	if (empty())									//if empty
		throw QueueEmpty("Front of empty queue");	//throw error
	return CList.front();
}

template <typename E>
void Queue<E>::enqueue(const E& e)					//adds item to end
{
	CList.add(e);
	CList.advance();
	queueSize++;
}

template <typename E>
void Queue<E>::dequeue() throw(QueueEmpty)			//removes item from front
{
	if (empty())									//if empty
		throw QueueEmpty("Dequeue of empty queue");	//throw error
	CList.remove();
	queueSize--;
}


#endif