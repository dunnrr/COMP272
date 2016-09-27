/******************************************************************************
* Test program and implementation of merge sort and quick sort for   
* COMP 272 assignment 3 question 4.
* 
* Modified from Sources: Open Data Structures an Introduction, by Pat Morin,
* 						AU Press, © 2013
*
* Author: Robert Ryan Dunn
* SN: 3070207
* Date: 19 September, 2016
******************************************************************************/

#include <vector>
#include <iostream>
#include <random>
#include <time.h>

using std::cout;
using std::endl;
using std::vector;

int sequence[11] = {3,1,4,1,5,9,2,6,5,3,5}; 

vector<int> createSequence()						//create sequence
{
	vector<int> S;									//declare vector
	for (int i : sequence)							//cycle through indices
		S.push_back(i);								//insert value
	return S;										//return vector
}


void printSequence(const vector<int> &S)			//print out position list
{
	cout << "Sequence: ";
	cout << "{";									
	int i=1;
	for(int n : S)									//cycle through sequence
	{
		cout << n;
		if (i < S.size())
			cout << ", ";
		i++;
	}
	cout << "}" << endl << endl;
}

void merge(vector<int>& Sn, vector<int>& Sm, 
	vector<int>& S)									//merge vectors
{
	int n = 0;										//initialize counters
	int m = 0;
	for (int i = 0; i < S.size(); i++)				//cycle through S
	{
		if (n == Sn.size())							//has Sn reached end?
			S[i] = Sm[m++];							//add Sm[m] to S; m++
		else if (m == Sm.size())					//has Sm reached end?
			S[i] = Sn[n++];							//add Sn[n] to S; n++
		else if (Sn[n] < Sm[m])						//is Sn[n] less than Sm[m]?
			S[i] = Sn[n++];							//add Sn[n] to S; n++
		else										//else
			S[i] = Sm[m++];							//add Sm[m] to S; m++
	}
}

void mergeSort(vector<int>& S)						//merge sort
{
	if (S.size() <= 1)								//is size is <= 1?
		return;										//return
	vector<int> Sn;									//initialize Sn
	vector<int> Sm;									//initialize Sm
	for(int i = 0; i < S.size()/2; i++)				//assign half of S to Sn 
		Sn.push_back(S[i]);
	for(int i = S.size()/2; i < S.size(); i++)		//assign remaining S to Sm
		Sm.push_back(S[i]);
	mergeSort(Sn);									//merge sort Sn
	mergeSort(Sm);									//merge sort Sm
	merge(Sn,Sm,S);									//merge Sn and Sm into S
}

void quickSort(vector<int>& S, int left, int right) {
	if (left >= right) return;
	// 0 or 1 left? done
	int pivot = S[right];
	// select last as pivot
	int l = left;
	// left edge
	int r = right - 1;
	// right edge
	while (l <= r) {
		while (l <= r && pivot >= S[l]) l++;
		// scan right till larger
		while (r >= l && S[r] >= pivot) r--;
		// scan left till smaller
		if (l < r)
			// both elements found
			std::swap(S[l], S[r]);
	}
	// until indices cross
	std::swap(S[l], S[right]);
	// store pivot at l
	// recur on both sides
	quickSort(S, left, l-1);
	quickSort(S, l+1, right);
}



/*
void quickSort(vector<int>& S, int left, int right)	//quick sort
{
	if ( left >= right )							//is left >= right?
		return;										//return
	int index = left + rand() % (right - left + 1);	//choose pivot index
	int pivot = S[index];							//assign pivot element
	int l = left;									//left edge
	int r = right;									//right edge
	
	while ( left < r || l < right )
	{
		while ( l <= r && S[l] < pivot )
			l++;
		while ( l <= r && S[r] > pivot )
			r--;
			
		if ( l<= r )
		{
			std::swap(S[l],S[r]);
			l++;
			r--;
		}
		else
		{
			if(left<=r)
				quickSort(S,left,r);
			if(l<right)
				quickSort(S,l,right);
			return;
		}
	}
}
*/

void quickSort(vector<int>& S)						//quick sort
{
	quickSort(S,0,S.size()-1);						//quick sort
}

void testCase(int &test)							//prints test case value
{
	cout << endl << "Test Case: " << test
		<< endl << endl;
	test++;
}

int main(void)
{
	srand(time(NULL));								//set random seed
	int test = 1;									//assign test case value
	
	testCase(test);									//print out test case no.
	vector<int> S = createSequence();				//create sequence	
	printSequence(S);								//print sequence
	mergeSort(S);									//merge sort sequence
	printSequence(S);								//print sequence
	
	testCase(test);									//print out test case no.	
	S.clear();										//clear S
	S = createSequence();							//create sequence
	printSequence(S);								//print sequence
	quickSort(S);									//quick sort sequence
	printSequence(S);								//print sequence
	
	return EXIT_SUCCESS;							//exit success
}