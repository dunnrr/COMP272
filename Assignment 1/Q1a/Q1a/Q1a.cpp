/******************************************************************************
*Implementation of add(x), deleteMin(), and size(), using a singly-linked list.
*
*Author: Robert Ryan Dunn
*SN: 3070207
*Date: April, 2016
******************************************************************************/

#include "PriorityQueue.h"
#include <iostream>

void deleteMin(PriorityQueue<int> &queue)			//deletes minimum value
{
	try
	{
		queue.deleteMin();							//delete value if possible
	}
	catch (QueueEmpty& err)							//show error if not
	{
		std::cout << "Exception: " << err.getMessage()	
			<< std::endl << std::endl;
	}
}

void minQueue(PriorityQueue<int> &queue)			//print out the min value
{
	try
	{												//print value if possible
		std::cout << "The minimum value is: "		
			<< queue.min() << std::endl << std::endl;
	}
	catch (QueueEmpty& err)						//show error if not
	{
		std::cout << "Exception: " << err.getMessage()
			<< std::endl << std::endl;
	}
}

void sizeQueue(PriorityQueue<int> &queue)			//print out the queue size
{
	std::cout << "The size of the queue is: "
		<< queue.size() << std::endl << std::endl;
}

void printQueue(PriorityQueue<int> &queue)			//print out current list
{
	std::cout << "The current queue is: ";
	queue.print();									//print out list
	std::cout << std::endl << std::endl;
}

void testCase(int &test)							//prints test case value
{
	std::cout << "Test Case: " << test
		<< std::endl;
	test++;
}

int main(void)
{
	PriorityQueue<int> queue;						//create queue
	int test = 1;									//assign test case value
	
	testCase(test);									//print out test case no.
	queue.add(19);									//add items to queue
	queue.add(7);
	queue.add(1);
	queue.add(5);
	queue.add(3);
	queue.add(20);
	queue.add(15);
	queue.add(5);
	printQueue(queue);								//print queue
	
	testCase(test);
	sizeQueue(queue);								//queue size

	testCase(test);
	minQueue(queue);

	testCase(test);
	while (!queue.empty())
	{
		deleteMin(queue);							//delete minimum element
		printQueue(queue);							//print queue
	}

	testCase(test);
	sizeQueue(queue);								//queue size

	testCase(test);
	minQueue(queue);

	testCase(test);
	deleteMin(queue);
	return EXIT_SUCCESS;							//exit success
}