/******************************************************************************
* Test file of RandomQueue class as per assignment 1 question 4
*
* Source: Robert Ryan Dunn
* SN: 3070207
* Assignment 1, Question 4
* Date: May 23, 2016
******************************************************************************/

#include <iostream>
#include "RandomQueue.h"

void addQueue(RandomQueue<int> &queue, int size)
// addQueue adds a batch of items to the RandomQueue
{
	for (int i = 0; i < size; i++)				// cycle number of elements
		queue.add(i);							// add items to the queue
}

void printQueue(RandomQueue<int> &queue)
// printQueue prints out the list of items in RandomQueue
{
	std::cout << "The list values are: " 
		<< std::endl;
	for (int i = 0; i < queue.size(); i++)		// cycle through queue
		std::cout << queue.atIndex(i) << " ";	// output queue elements	
	std::cout << std::endl;
}

void batchRemove(RandomQueue<int> &queue, int x)
// batchRemove removes a batch of items from RandomQueue
{
	for (int i = 0; i < x; i++)					// cycle number of elements
		queue.remove();							// remove queue element
}

void Q4test()
// Q4test runs through adding and removing elements from the queue and 
// outputs resulting list several times
{
	RandomQueue<int> queue(20);					// initialize queue
	addQueue(queue, 20);						// add 20 items to queue
	printQueue(queue);							// print out elements of queue
	batchRemove(queue, 5);						// remove 5 elements from queue
	printQueue(queue);							// print out elements of queue
	addQueue(queue, 20);						// add 20 items to queue
	printQueue(queue);							// print out elements of queue
	batchRemove(queue, 9);						// remove 9 elements from queue	
	printQueue(queue);							// print out elements of queue
	try
	{
		std::cout << queue.atIndex(-1)
			<< std::endl;						// try to cause access error
	}
	catch (const char* msg)
	{
		std::cerr << msg << std::endl;			// access error message
	}
	try
	{
		std::cout << queue.atIndex(queue.size())
			<< std::endl;						// try to cause access error
	}
	catch (const char* msg)
	{
		std::cerr << msg << std::endl;			// access error message
	}
}

int main()
// main function used to launch Q4test()
{
	Q4test();									// launch test function
	return EXIT_SUCCESS;						// program ran successfully
}