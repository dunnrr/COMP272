// comments from page 240

#include "Queue.h"



template <typename E>
Queue<E>::Queue()
	: C(), n(0) {};

template <typename E>
int Queue<E>::size() const
{
	return n;
}

template <typename E>
bool Queue<E>::empty() const
{
	return n == 0;
}

template <typename E>
const E& Queue<E>::front() const //throw(QueueEmpty)
{
	//if (empty())
	//	throw QueueEmpty("front of empty queue");
	return C.front();
}

template <typename E>
void Queue<E>::enqueue(const E& e)
{
	C.add(e);
	C.advance();
	n++;
}

template <typename E>
void Queue<E>::dequeue() //throw(QueueEmpty)
{
	//if (empty())
	//	throw QueueEmpty("dequeue of empty queue");
	C.remove();
	n--;
}

template class Queue<int>;