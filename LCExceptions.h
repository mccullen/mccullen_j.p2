/*
Name: Jeff McCullen and Emma Elliott
Date: September 27, 2015
Description: This class contains the .h file prototypes for a number
of exception classes.
*/
#ifndef LC_EXCEPTIONS_H
#define LC_EXCEPTIONS_H

// Define all exceptions here.
#include <string>
#include <stdexcept>

/*
Runtime error: should be detected at runtime
Logic error: Should be detected at compile time.

c++ will catch and exit program if you do not catch it.
*/

/**
The OutOfBoundsException will be thrown whenever an invalid access
occurs such as attempting to index into an array at a negative location
or a location greater than or equal to the size of the array.
*/
class OutOfBoundsException : public std::runtime_error
{
public:
	/**
	Print a default out of bounds exception error message.
	*/
	OutOfBoundsException();

	/**
	Print the out of bounds message according to the string passed in.

	@param message The error message to print.
	*/
	OutOfBoundsException(const std::string& message);
};

/**
The ItemNotFoundException will be thrown whenever an item is not found in
a list. This may occur when a remove attempt is tried but the item to 
remove is not found in the list.
*/
class ItemNotFoundException : public std::runtime_error
{
public:
	/**
	Print a default item not found exception error message.
	*/
	ItemNotFoundException();

	/**
	Print the item not found message according to the string passed in.

	@param message The error message to print.
	*/
	ItemNotFoundException(const std::string& message);
};

/**
The EmptyStackException will be thrown whenever someone tries to do
something invalid with an empty stack such as top or pop.
*/
class EmptyStackException : public std::runtime_error
{
public:
	/**
	Print a default empty stack exception error message.
	*/
	EmptyStackException();

	/**
	Print the empty stack message according to the string passed in.

	@param message The error message to print.
	*/
	EmptyStackException(const std::string& message);
};
/**
The EmptyQueueException will be thrown whenever someone tries to do
something invalid with an empty stack such as top or pop.
*/
class EmptyQueueException : public std::runtime_error
{
public:
	/**
	Print a default empty queue exception error message.
	*/
	EmptyQueueException();

	/**
	Print the empty queue message according to the string passed in.

	@param message The error message to print.
	*/
	EmptyQueueException(const std::string& message);
};

/**
The NoPlayersException will be thrown whenever someone tries to
deal cards to an empty vector of players.
*/
class NoPlayersException : public std::runtime_error
{
public:
	/**
	Print a default no players exception error message.
	*/
	NoPlayersException();

	/**
	Print the no players message according to the string passed in.

	@param message The error message to print.
	*/
	NoPlayersException(const std::string& message);
};

/**
The EmptyDeckException will be thrown whenever someone tries to
deal cards to an empty vector of players.
*/
class EmptyDeckException : public std::runtime_error
{
public:
	/**
	Print a default EmptyDeckException exception error message.
	*/
	EmptyDeckException();

	/**
	Print the EmptyDeckException  message according to the 
	string passed in.

	@param message The error message to print.
	*/
	EmptyDeckException(const std::string& message);
};
/**
The EmptyHandException will be thrown whenever someone tries to
deal cards to an empty vector of players.
*/
class EmptyHandException : public std::runtime_error
{
public:
	/**
	Print a default EmptyHandException exception error message.
	*/
	EmptyHandException();

	/**
	Print the EmptyHandException  message according to the 
	string passed in.

	@param message The error message to print.
	*/
	EmptyHandException(const std::string& message);
};

/**
The KeyInMapException will be thrown whenever someone tries to 
insert a key into a map that is already in the map.
*/
class KeyInMapException : public std::runtime_error
{
public:
	/**
	Print a default KeyInMapException exception error message.
	*/
	KeyInMapException();

	/**
	Print the KeyInMapException  message according to the 
	string passed in.

	@param message The error message to print.
	*/
	KeyInMapException(const std::string& message);
};

/**
The IllegalMoveException will be thrown whenever someone tries to 
insert a key into a map that is already in the map.
*/
class IllegalMoveException : public std::runtime_error
{
public:
	/**
	Print a default IllegalMoveException exception error message.
	*/
	IllegalMoveException();

	/**
	Print the IllegalMoveException  message according to the 
	string passed in.

	@param message The error message to print.
	*/
	IllegalMoveException(const std::string& message);
};
#endif //LC_EXCEPTIONS_H
