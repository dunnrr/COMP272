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
	std::cout << "The queue values are: ";
	queue.print();
	std::cout << std::endl << std::endl;
}

void remove(RandomQueue<int> &queue)			// deletes random value
{
	try
	{
		std::cout << "Removing an item..."
			<< std::endl;
		queue.remove();							// delete value if possible
	}
	catch (QueueEmpty& err)						// show error if not
	{
		std::cout << "Exception: " << err.getMessage()
			<< std::endl << std::endl;
	}
}

void printIndex(RandomQueue<int> &queue, int index)
{
	std::cout << "The item at index "
		<< index << " is:" << std::endl;
	try
	{
		std::cout << queue.atIndex(index)
			<< std::endl << std::endl;			// output value if possible
	}
	catch (IndexOutOfBounds& err)
	{
		std::cout << "Exception: " << err.getMessage()
			<< std::endl << std::endl;			// show error if not
	}
}

void batchRemove(RandomQueue<int> &queue, int x)
// batchRemove removes a batch of items from RandomQueue
{
	for (int i = 0; i < x; i++)					// cycle number of elements
		remove(queue);							// remove queue element
}

void testCase(int &test)						// prints test case value
{
	std::cout << "Test Case: " << test
		<< std::endl;
	test++;
}

void Q4test()
// Q4test runs through adding and removing elements from the queue and 
// outputs resulting list several times
{
	RandomQueue<int> queue(10);					// initialize queue
	int test = 1;								// assign test case value
	
	printQueue(queue);							// print out elements of queue

	testCase(test);								// print out test case no.
	addQueue(queue, 20);						// add 20 items to queue
	printQueue(queue);							// print out elements of queue

	testCase(test);								// print out test case no.
	batchRemove(queue, 5);						// remove 5 elements from queue
	printQueue(queue);							// print out elements of queue

	testCase(test);								// print out test case no.
	printIndex(queue, -1);						// try to cause access error

	testCase(test);								// print out test case no.
	printIndex(queue, queue.size());			// try to cause access error

	testCase(test);								// print out test case no.
	printQueue(queue);							// print out elements of queue
	printIndex(queue, 10);						// retrieve value at index 10
	printQueue(queue);							// print out elements of queue

	testCase(test);								// print out test case no.
	batchRemove(queue, 15);						// remove all items from queue
	printQueue(queue);							// print out elements of queue

	testCase(test);								// print out test case no.
	batchRemove(queue, 1);						// remove 1 item from queue
	printQueue(queue);

}

int main()
// main function used to launch Q4test()
{
	Q4test();									// launch test function
	return EXIT_SUCCESS;						// program ran successfully
}