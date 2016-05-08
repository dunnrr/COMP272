/******************************************************************************
*	Implementation of the push(x) and pop() operations using two Queues
*	
*	Author: Robert Ryan Dunn
*	SN:	3070207
*	Date: May 6, 2016
******************************************************************************/


#ifndef _STACK_H_
#define _STACK_H_

#include "Queue.h"

template <typename E>
class Stack
{
public:
	Stack();
	int size() const;
	bool empty() const;
	const E& top() const/* throw(StackEmpty)*/;
	void push(const E& e);
	void pop()/* throw(StackEmpty)*/;
private:
	Queue<E> S1;
	Queue<E> S2;
	int n;
};

#endif

