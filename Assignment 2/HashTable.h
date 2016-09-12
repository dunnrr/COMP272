/******************************************************************************
* Implementation of a hash table for Assignment 2 of COMP 272
*
* Modified from Sources: Open Data Structures an Introduction, by Pat Morin,
* 						AU Press, © 2013
* 
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		9 September, 2016
******************************************************************************/

#ifndef _HASHTABLE_H_							//if not defined
#define _HASHTABLE_H_							//define HashTable

#include <math.h>
#include "RuntimeException.h"

enum state {UNUSED,INUSE,FREE};

template <typename E>
class HashItem
{
public:
	E entry;									//entry
	state status;								//status
	HashItem<E>(): entry(), status(UNUSED) {} 	//constructor

};

template <typename E>
class HashTable
{
public:
	HashTable<E> (int capacity = 100);			//constructor
	~HashTable<E> ();							//destructor
	int size();									//# of INUSE entries
	void add(E entry);							//add an entry
	HashItem<E>* find(E entry);					//find an entry
	void remove(E entry);						//remove an entry
protected:
	int hash(E entry);							//hash function
	HashItem<E>* finder(E entry);				//find an entry utility
	void resize();								//resize utility
private:
	int nonNull;								//number of non-null entries
	int length;									//max number of entries
	int n;										//size
	HashItem<E>* hashArray;						//array of HashItems
	int HASHMODULUS = 13;						//hash modulus
};		

template <typename E>
HashTable<E>::HashTable(int capacity)			//constructor
{
	length = capacity;							//save the max size
	hashArray = new HashItem<E>[capacity];		//allocate array storage
	n = 0;										//initialize hash size
	nonNull = 0;								//initialize nonNull entries
}

template<typename E>
HashTable<E>::~HashTable()						// destructor
{
	delete[] hashArray;							//delete hashArray
}

template <typename E>
int HashTable<E>::size()						//# of INUSE entries
{
	return n;
}

template <typename E>
void HashTable<E>::add(E entry)					//add an entry to the table
{
	if ( finder(entry)->status == INUSE )		//does entry exist?
		throw EntryExists(
			"Entry already exists!");			//entry exists, can't add
	if ( ( 2*(nonNull + 1) > length ) ||		//greater than 50% occupancy? 
		( length <= HASHMODULUS ) )				//or smaller than hash modulus?
		resize();								//resize table
	int key = hash(entry);						//get the key
	while ( hashArray[key].status == INUSE )	//search for an empty spot
		key = ( key >= length-1 ) ? 0 : key+1;	//increment key
	if ( hashArray[key].status == UNUSED )		//is spot a null spot?
		nonNull++;								//increment nonNull
	n++;										//increment size
	hashArray[key].entry = entry;				//add entry
	hashArray[key].status = INUSE;				//reset entry to INUSE
}

template <typename E>
HashItem<E>* HashTable<E>::find(E entry)		//find an entry
{
	HashItem<E>* result = finder(entry);
	if ( result->status == UNUSED )
		throw NonexistentEntry(
			"Entry does not exist!");			//entry not found
	return result;
}

template <typename E>
void HashTable<E>::remove(E entry)				//remove an entry
{
	HashItem<E>* temp = finder(entry);
	if ( temp->status == UNUSED )
		throw NonexistentEntry(
			"Entry does not exist!");			//entry not found	
	temp->status = FREE;						//set status to free
	n--;										//reduce size counter
	if ( 8*n < length ) 						//min 12.5% occupancy
		resize();								//resize	
}


template <typename E>
int HashTable<E>::hash(E entry)					//hash function
{
	return int(entry % HASHMODULUS);			//return key
}

template <typename E>
HashItem<E>* HashTable<E>::finder(E entry)		//find an entry
{
	int key = hash(entry);						//get the starting index
	if ( key >= length )						//ensure key will be in array
		key = key % length;						//adjust key for small array
	while ( hashArray[key].status != UNUSED )	//cycle through hash table
	{
		if ( (hashArray[key].status == INUSE) && 
			(hashArray[key].entry == entry) )	//matched in use entry?
			return &hashArray[key];				//return entry
		key = ( key >= length-1 ) ? 0 : key+1;	//increment key
	}
	return &hashArray[key];						//return null key if not found
}

template<typename E>
void HashTable<E>::resize()						//double the size of the array
{

	int l = 2;									//assign a temp length
	while ( (l < 3*n) || (l <= HASHMODULUS) )	//find a good starting point
		l = l*2;								//increment l by a power of 2
	HashItem<E>* temp = new HashItem<E>[l];		//create a temp array
	nonNull = n;								//reset nonNull
	for (int i = 0; i < length; i++)
	{
		if ( hashArray[i].status == INUSE )		//look for INUSE
		{
			int key = hash(hashArray[i].entry);	//get key
			while ( temp[key].status != UNUSED )//find an empty space
				key = (key >= l-1) ? 0 : key+1;	//increment key
			temp[key].entry = 
				hashArray[i].entry;
			temp[key].status = INUSE;
		}
	}
	delete[] hashArray;							//delete hashArray
	length = l;									//reset length
	hashArray = temp;							//reassign array to temp

}

#endif