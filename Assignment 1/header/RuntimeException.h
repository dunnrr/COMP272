/******************************************************************************
* Implementation of generic Runtime Exceptions
*
* Modified from Source: Data Structures and Algorithms in C++, 2nd Edition,
*						by Michael T. Goodrich, Roberto Tamassia, David M.
*						Mount, Wiley publisher, February 2011, © 2011
*
* Author:	Robert Ryan Dunn
* Stu. No.:	3070207
* Date:		5 June, 2016
******************************************************************************/

#ifndef _RUNTIMEEXCEPTION_H_
#define _RUNTIMEEXCEPTION_H_

#include <string>

//generic RuntimeException
class RuntimeException : public std::exception	
{
private:
	std::string errorMsg;
public:
	RuntimeException(const std::string& err) { errorMsg = err; }
	std::string getMessage() const { return errorMsg; }
};

//Exception thrown due to empty queue
class QueueEmpty : public RuntimeException
{
public:
	QueueEmpty(const std::string& err) : RuntimeException(err) {}
};

//Exception thrown due to empty list
class ListEmpty : public RuntimeException
{
public:
	ListEmpty(const std::string& err) : RuntimeException(err) {}
};

//Exception thrown due to empty stack
class StackEmpty : public RuntimeException
{
public:
	StackEmpty(const std::string& err) : RuntimeException(err) {}
};

//Exception thrown when index out of bounds
class IndexOutOfBounds : public RuntimeException
{
public:
	IndexOutOfBounds(const std::string& err): RuntimeException(err) {}
};
#endif