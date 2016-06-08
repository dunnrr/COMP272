/******************************************************************************
* Implementation of a Generic Circle Linked List for Assignment 1 of COMP 272
*
* Modified from Source: Data Structures and Algorithms in C++, 2nd Edition,
*						by Michael T. Goodrich, Roberto Tamassia, David M.
*						Mount, Wiley publisher, February 2011, © 2011
*
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		5 June, 2016
******************************************************************************/


#ifndef _CIRCLELIST_H_								//if not defined
#define _CIRCLELIST_H_								//define CircleList

#include "RuntimeException.h"

template <typename E>
class CNode											//circle list node
{
private:
	E elem;											//linked list element value
	CNode* next;									//next item in the list
	template <typename E>							
	friend class CircleList;						//provide CircleList access
};

template <typename E>
class CircleList									//circle list
{
public:
	CircleList();									//empty list constructor
	~CircleList();									//destructor
	bool empty() const;								//is list empty?
	const E& front() const throw(ListEmpty);		//return front element					
	const E& back() const throw(ListEmpty);			//return back element
	void advance();									//advance to next element
	void add(const E& e);							//add after cursor
	void remove() throw(ListEmpty);					//remove node after cursor
private:
	CNode<E>* cursor;								//list cursor
};

template <typename E>
CircleList<E>::CircleList()							//empty list constructor
	: cursor(nullptr) {};


template <typename E>
CircleList<E>::~CircleList()						//destructor
{
	while (!empty())
		remove();
}



template <typename E>
bool CircleList<E>::empty() const					//is list empty?
{
	return cursor == nullptr;
}

template <typename E>
const E& CircleList<E>::front() const throw(ListEmpty)	//return front element
{
	if (empty())										//if empty
		throw ListEmpty("List is empty");				//throw error
	return cursor->next->elem;
}

template <typename E>
const E& CircleList<E>::back() const throw(ListEmpty)	//return back element
{
	if (empty())										//if empty
		throw ListEmpty("List is empty");				//throw error	
	return cursor->elem;
}

template <typename E>
void CircleList<E>::advance()						//advance to next element
{
	if (empty())									//if empty
		return;										//return
	cursor = cursor->next;
}

template <typename E>
void CircleList<E>::add(const E& e)					//add after cursor
{
	CNode<E>* v = new CNode<E>;						//create a new node
	v->elem = e;									
	if (cursor == nullptr)							//check for empty list
	{
		v->next = v;								//v points to itself
		cursor = v;									//cursor points to v
	}
	else
	{												//list is nonempty
		v->next = cursor->next;						//link in v after cursor
		cursor->next = v;
	}
}

template <typename E>
void CircleList<E>::remove() throw(ListEmpty)		//remove node after cursor
{
	if (empty())									//if empty
		throw ListEmpty("List is empty");			//throw error
	CNode<E>* old = cursor->next;					//node being removed
	if (old == cursor)								//removing only node?
		cursor = nullptr;							//list is now empty
	else
		cursor->next = old->next;					//link out the old node
	delete old;										//delete the old node
}


#endif