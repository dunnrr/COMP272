// Main File

#include <iostream>
#include "SLinkedList.h"

void swapConsecutive(SNode<int>* &head, int index)
{
	if (index < 0)																			//check if index is below 0
	{
		std::cout << "Index is out of bounds.  Index must be 0 or greater." << std::endl;
		return;																				//exit function with error
	}
	if (head == nullptr || head->next == nullptr)											//ensure list is big enough to swap
	{
		std::cout << "The list is empty or too small." << std::endl;
		return;
	}

	
	
	if (index == 0)
	{
		SNode<int>* current = head;																//assign a pointer equal to head
		SNode<int>* swap = current->next;
		current->next = swap->next;
		swap->next = current;
		head = swap;
	}
	else
	{
		SNode<int>* prev = head;																//create a pointer to head
		SNode<int>* current = prev->next;														//create a pointer to current location
		SNode<int>* swap = current->next;														//create a pointer to the swap location
		int counter = 1;																		//create a counter
		
		while (counter != index)																//increment the pointer in the list to specified index
		{
			counter++;																			//increment the counter
			if (swap->next != nullptr)															//check to ensure end of list is not occuring
			{
				current = current->next;														//increment the list pointer
				prev = prev->next;																//increment the prev pointer
				swap = swap->next;																//increment the swap pointer
			}
			else
			{
				std::cout << "Index is out of bounds.  End of list occurred." << std::endl;		//exit function with error
				return;
			}
		}

		prev->next = swap;
		current->next = swap->next;
		swap->next = current;
	}
}

void createList(SLinkedList<int> &list)
{
	for (int i = 0; i < 5; i++)
	{
		list.addFront(i);
	}
}

void printList(SLinkedList<int> &list)
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
	SLinkedList<int> list;
	createList(list);
	printList(list);
	createList(list);
	swapConsecutive(list.head, -1);
	swapConsecutive(list.head, 4);
	swapConsecutive(list.head, 2);
	printList(list);
	createList(list);
	swapConsecutive(list.head, 3);
	swapConsecutive(list.head, 0);
	printList(list);
	return EXIT_SUCCESS;
}