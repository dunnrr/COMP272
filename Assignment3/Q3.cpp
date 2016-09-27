/******************************************************************************
* Test program and implementation of comparing two sequences for   
* COMP 272 assignment 3 question 3.
*
* Modified from Sources: Open Data Structures an Introduction, by Pat Morin,
* 						AU Press, © 2013
*
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

vector<int> createRandomSequence(int size)			//create random sequence
{
	vector<int> S;									//declare vector
	for (int i = 0; i < size; i++)					//cycle through indices
		S.push_back(rand() % size);					//insert random value
	return S;										//return vector
}

vector<int> createDifferentSequence(const 			
	vector<int> &S1)								//create different sequence
{
	vector<int> S;									//declare vector
	S.push_back(S1.size()+1);						//insert value not in S1
	for (int i = 1; i < S1.size(); i++)				//cycle through indices
		S.push_back(rand() % S1.size());			//insert random value 
	return S;										//return vector
}

vector<int> createSameSequence(const 
	vector<int> &S1)								//create same sequence
{
	vector<int> choices;							//create vector of choices
	vector<int> S;									//declare vector
	bool choice;									//choice variable
	for(int i = 0; i < S1.size(); i++)				//cycle through S1
	{
		choice = true;								//set choice to true
		for(int j = 0; j < choices.size(); j++)		//cycle through choices
		{
			if (choices[j] == S1[i])				//is S1[i] in choices?
				choice = false;						//set choice to false
		}
		if (choice)									//is this a choice?
			choices.push_back(S1[i]);				//add S1[i] to choices
	}
	for(int i : choices)							//cycle through choices
		S.push_back(i);								//add all of choices to S
	for (int i = choices.size(); i < S1.size(); i++)//cycle through remaining S
		S.push_back(
			choices[rand() % choices.size()]);		//insert random value
	return S;										//return S
}

void printSequence(const vector<int> &S)			//print out position list
{
	cout << "{";									
	int i=1;
	for(int n : S)									//cycle through sequence
	{
		cout << n;
		if (i < S.size())
			cout << ", ";
		i++;
	}
	cout << "}";
}

void printSequences(const vector<int> &S1,
	const vector<int> &S2)							//print out both trees
{
	cout << "Sequence S1: ";
	printSequence(S1);
	cout << endl << endl;
	cout << "Sequence S2: ";
	printSequence(S2);
	cout << endl << endl;
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

void compare(vector<int>& S1, vector<int>& S2)		//conpare S1 and S2
{
	mergeSort(S1);									//sort S1
	mergeSort(S2);									//sort S2
	
	int i = 0;										//initialize counter
	int j = 0;										//initialize counter
	
	while ( i < S1.size() && j < S2.size())			//while counters not at max
	{
		while (S1[i] == S1[i+1])					//skip duplicates in S1
			i++;
		while (S2[j] == S2[j+1])					//skip duplicates in S2
			j++;
		if (S1[i] != S2[j])							//is S1[i] != S2[j]?
		{
			cout << "The sequences do not contain "
				<< "the same set." << endl << endl;	//sequences not equal
			return;									//return
		}
		i++;										//increase i
		j++;										//increase j
	}
	
	cout << "The sequences contain the same set."
		<< endl << endl;							//sequences are equal
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
	vector<int> S1 = createRandomSequence(9);		//create random sequence	
	vector<int> S2 = createDifferentSequence(S1);	//create different sequence	
	printSequences(S1,S2);							//print sequences
	compare(S1,S2);
	
	testCase(test);									//print out test case no.	
	S1.clear();										//clear S1
	S2.clear();										//clear S2
	S1 = createRandomSequence(9);					//create random sequence
	S2 = createSameSequence(S1);					//create same sequence	
	printSequences(S1,S2);							//print sequences
	compare(S1,S2);
	
	return EXIT_SUCCESS;							//exit success
}