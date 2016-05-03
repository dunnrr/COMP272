/******************************************************************************
* Implementation of generic Runtime Exceptions
*
* Source: Data Structures and Algorithms in C++, 2nd Edition,
*         by Michael T. Goodrich, Roberto Tamassia, David M. Mount,
*         Wiley publisher, February 2011, © 2011
******************************************************************************/

#pragma once
#include <string>

class RuntimeException : public std::exception	//generic run-time exception
{
private:
	std::string errorMsg;
public:
	RuntimeException(const std::string& err) { errorMsg = err; }
	std::string getMessage() const { return errorMsg; }
};