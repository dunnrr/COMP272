// Main File

#include <iostream>
#include "DLinkedList.h"

void swapConsecutive(DLinkedList<int> &list, int index)
{
	if (index < 0)																			//check if index is below 0
	{
		std::cout << "Index is out of bounds.  Index must be 0 or greater." << std::endl;
		return;																				//exit function with error
	}
	if (list.empty() || list.header->next == list.trailer->prev)							//ensure list is big enough to swap
	{
		std::cout << "The list is empty or too small." << std::endl;
		return;
	}

	DNode<int>* current = list.header->next;												//assign a pointer equal to header->next
	DNode<int>* swap = current->next;																
	int counter = 0;																		//create a counter
	
	while (counter != index)																//increment the pointer in the list to specified index
	{
		counter++;																			//increment the counter
		if (swap->next != list.trailer)														//check to ensure end of list is not occuring
		{
			current = current->next;														//increment the list pointer
			swap = swap->next;																//increment the swap pointer
		}
		else
		{
			std::cout << "Index is out of bounds.  End of list occurred." << std::endl;		//exit function with error
			return;
		}
	}

	swap->prev = current->prev;
	current->prev = swap;
	current->next = swap->next;
	swap->next = current;
	swap->prev->next = swap;
	current->next->prev = current;
}


void createList(DLinkedList<int> &list)
{
	for (int i = 0; i < 5; i++)
	{
		list.addFront(i);
	}
}

void printList(DLinkedList<int> &list)
{
	std::cout << "The list values are: " << std::endl;
	while (!list.empty())
	{
		std::cout << list.front() << " ";
		list.removeFront();
	}
	std::cout << std::endl;
}

int main()
{
	DLinkedList<int> list;
	createList(list);
	printList(list);
	createList(list);
	swapConsecutive(list, -1);
	swapConsecutive(list, 4);
	swapConsecutive(list, 2);
	printList(list);
	createList(list);
	swapConsecutive(list, 3);
	swapConsecutive(list, 0);
	printList(list);
	swapConsecutive(list, 0);
	printList(list);
	list.addFront(1);
	swapConsecutive(list, 0);
	printList(list);
	return EXIT_SUCCESS;
}