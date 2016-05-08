/******************************************************************************
*	Implementation of the push(x) and pop() operations using two Queues
*
*	Author: Robert Ryan Dunn
*	SN:	3070207
*	Date: May 6, 2016
******************************************************************************/

#include "Stack.h"

template <typename E>
Stack<E>::Stack()
	: S1(), S2(), n(0) {};

template <typename E>
int Stack<E>::size() const
{
	return n;
}

template <typename E>
bool Stack<E>::empty() const
{
	return n == 0;
}

template <typename E>
const E& Stack<E>::top() const/* throw(StackEmpty)*/
{
	//if (empty())
	//	throw StackEmpty("Top of empty stack");
	return S1.C.back();
}

template <typename E>
void Stack<E>::push(const E& e)
{
	++n;
	S1.enqueue(e);
}

template <typename E>
void Stack<E>::pop()/* throw(StackEmpty)*/
{
	//if (empty())
		//throw StackEmpty("Pop from empty stack");
	--n;
	while (!S1.empty())					//loop while S1 is not empty
	{
		if (S1.size() != 1)				//check for last element
			S2.enqueue(S1.front());		//load the front of S1 onto S2
		S1.dequeue();					//remove the element at the front of S1
	}
	while (!S2.empty())					//loop while S2 is not empty
	{
		S1.enqueue(S2.front());			//load the front of S2 onto S1
		S2.dequeue();					//remove the element at the front of S2
	}
}

template class Stack<int>;
