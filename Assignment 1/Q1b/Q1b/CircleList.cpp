//comments from page 155

#include "CircleList.h"

template <typename E>
CircleList<E>::CircleList()
	: cursor(nullptr) {};


template <typename E>
CircleList<E>::~CircleList()
{
	while (!empty()) 
		remove();
}



template <typename E>
bool CircleList<E>::empty() const
{
	return cursor == nullptr;
}

template <typename E>
const E& CircleList<E>::back() const  //should throw an exception page 156
{
	return cursor->elem;
}

template <typename E>
const E& CircleList<E>::front() const  //should throw an exception page 156
{
	return cursor->next->elem;
}

template <typename E>
void CircleList<E>::advance()  // should just return if list is empty page 156
{
	cursor = cursor->next;
}

template <typename E>
void CircleList<E>::add(const E& e)
{
	CNode<E>* v = new CNode<E>;
	v->elem = e;
	if (cursor == nullptr)
	{
		v->next = v;
		cursor = v;
	}
	else
	{
		v->next = cursor->next;
		cursor->next = v;
	}
}

template <typename E>
void CircleList<E>::remove()
{
	CNode<E>* old = cursor->next;
	if (old == cursor)
		cursor = nullptr;
	else
		cursor->next = old->next;
	delete old;
}

template class CNode<int>;
template class CircleList<int>;