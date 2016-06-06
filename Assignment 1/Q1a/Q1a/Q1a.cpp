/******************************************************************************
*Implementation of add(x), deleteMin(), and size(), using a singly-linked list.
*
*Author: Robert Ryan Dunn
*SN: 3070207
*Date: April, 2016
******************************************************************************/

#include "PriorityQueue.h"
#include <iostream>

void printQueue(PriorityQueue<int> &queue)			//print out current list
{
	std::cout << "The current queue is: ";
	queue.print();									//print out list
	std::cout << std::endl;
}

int main(void)
{
	PriorityQueue<int> queue;						//create queue
	queue.add(19);									//add items to queue
	queue.add(7);
	queue.add(1);
	queue.add(5);
	queue.add(3);
	queue.add(20);
	queue.add(15);
	queue.add(5);
	printQueue(queue);								//print queue
	while (!queue.empty())
	{
		queue.deleteMin();							//delete minimum element
		printQueue(queue);							//print queue
	}
	return EXIT_SUCCESS;							//exit success
}