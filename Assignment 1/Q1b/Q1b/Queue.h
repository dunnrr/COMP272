// comments from page 239


#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "CircleList.h"

template <typename E>
class Queue
{
public:
	Queue();
	int size() const;
	bool empty() const;
	const E& front() const/* throw(QueueEmpty)*/;
	void enqueue(const E& e);
	void dequeue()/* throw(QueueEmpty)*/;
private:
	CircleList<E> C;
	int n;
	template <typename E>
	friend class Stack;
};


#endif