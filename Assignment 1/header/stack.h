/******************************************************************************
* Generic Stack Implementation where push(x) and pop() operations use two 
* Queues
*	
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		5 June, 2016
******************************************************************************/


#ifndef _STACK_H_									//if not defined						
#define _STACK_H_									//define Stack

#include <iostream>
#include "Queue.h"									
#include "RuntimeException.h"

template <typename E>
class Stack											//Stack
{
public:
	Stack();										//constructor
	int size() const;								//returns size of stack
	bool empty() const;								//is stack empty?
	const E& top() const throw(StackEmpty);			//returns top
	void push(const E& e);							//adds to top
	void pop() throw(StackEmpty);					//removes from top
	void print();									//prints out the stack
private:
	Queue<E> queue1;								//queue no 1
	Queue<E> queue2;								//queue no 2
	int stackSize;									//stack size counter
	E topElement;									//top element
};

template <typename E>
Stack<E>::Stack()									//constructor
	: queue1(), queue2(), stackSize(0) {};

template <typename E>
int Stack<E>::size() const							//returns size of stack
{
	return stackSize;
}

template <typename E>
bool Stack<E>::empty() const						//is stack empty?
{
	return stackSize == 0;
}

template <typename E>
const E& Stack<E>::top() const throw(StackEmpty)	//returns top
{
	if (empty())									//if empty
		throw StackEmpty("Top of empty stack");		//throw error
	return topElement;
}

template <typename E>
void Stack<E>::push(const E& e)						//add to top
{
	++stackSize;									//increment size
	topElement = e;									//assign new top element
	queue1.enqueue(e);								//add element to top
}

template <typename E>
void Stack<E>::pop() throw(StackEmpty)
{
	if (empty())									//if empty
		throw StackEmpty("Pop from empty stack");	//throw error
	--stackSize;
	while (!queue1.empty())							//while queue1 not empty
	{
		if (queue1.size() != 1)						//check for last element
			queue2.enqueue(queue1.front());			//move queue1 to queue2
		queue1.dequeue();							//remove queue1 front
	}
	while (!queue2.empty())							//while queue2 not empty
	{
		queue1.enqueue(queue2.front());				//move queue2 to queue1
		queue2.dequeue();							//remove queue2 front
	}
}

template <typename E>
void Stack<E>::print()								//prints out the stack
{
	int counter = stackSize;						//create a counter
	std::cout << "{";								//output start of stack
	while (counter != 0)							//cycle through queue
	{
		queue1.enqueue(queue1.front());				//add front to end
		std::cout << queue1.front();				//output front
		queue1.dequeue();							//remove front
		counter--;									//lower counter
		if (counter != 0)							//check for end of queue
			std::cout << ", ";						//output for list clarity
	}
	std::cout << "}";								//output end of stack
}
#endif

