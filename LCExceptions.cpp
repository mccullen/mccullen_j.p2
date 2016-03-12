/*
Name: Jeff McCullen and Emma Elliott
Date: September 27, 2015
Description: This class contains the implementation for a number
of exception classes.
*/
#include <string>
#include "LCExceptions.h"

/**
Print a default out of bounds exception error message.
*/
OutOfBoundsException::OutOfBoundsException() : 
	std::runtime_error("Error: Out of bounds.")
{
}

/**
Print the out of bounds message according to the string passed in.

@param message The error message to print.
*/
OutOfBoundsException::OutOfBoundsException(const std::string& message) : 
	std::runtime_error(message)
{
}

/**
Print a default item not found exception error message.
*/
ItemNotFoundException::ItemNotFoundException() : 
	std::runtime_error("Error: Item not found.")
{
}

/**
Print the item not found message according to the string passed in.

@param message The error message to print.
*/
ItemNotFoundException::ItemNotFoundException(const std::string& message) :
	std::runtime_error(message)
{
}

/**
Print a default empty stack exception error message.
*/
EmptyStackException::EmptyStackException() : 
	std::runtime_error("Error: Stack is empty.")
{
}

/**
Print the empty stack message according to the string passed in.

@param message The error message to print.
*/
EmptyStackException::EmptyStackException(const std::string& message) : 
	std::runtime_error(message)
{
}
/**
Print a default empty stack exception error message.
*/
EmptyQueueException::EmptyQueueException() : 
	std::runtime_error("Error: Queue is empty.")
{
}

/**
Print the empty stack message according to the string passed in.

@param message The error message to print.
*/
EmptyQueueException::EmptyQueueException(const std::string& message) : 
	std::runtime_error(message)
{
}
/**
Print a default NoPlayersException error message.
*/
NoPlayersException::NoPlayersException() : 
	std::runtime_error("Error: No players to deal cards to.")
{
}

/**
Print the NoPlayersException message according to the string passed in.

@param message The error message to print.
*/
NoPlayersException::NoPlayersException(const std::string& message) : 
	std::runtime_error(message)
{
}
/**
Print a default EmptyDeckException error message.
*/
EmptyDeckException::EmptyDeckException() : 
	std::runtime_error("Error: No more cards in deck.")
{
}

/**
Print the EmptyDeckException message according to the string passed in.

@param message The error message to print.
*/
EmptyDeckException::EmptyDeckException(const std::string& message) : 
	std::runtime_error(message)
{
}
/**
Print a default EmptyHandException error message.
*/
EmptyHandException::EmptyHandException() : 
	std::runtime_error("Error: Hand is empty.")
{
}

/**
Print the EmptyHandException message according to the string passed in.

@param message The error message to print.
*/
EmptyHandException::EmptyHandException(const std::string& message) : 
	std::runtime_error(message)
{
}

/**
Print a default KeyInMapException error message.
*/
KeyInMapException::KeyInMapException() : 
	std::runtime_error("Error: Key is already in map.")
{
}

/**
Print the KeyInMapException message according to the string passed in.

@param message The error message to print.
*/
KeyInMapException::KeyInMapException(const std::string& message) : 
	std::runtime_error(message)
{
}

/**
Print a default IllegalMoveException error message.
*/
IllegalMoveException::IllegalMoveException() : 
	std::runtime_error("Error: Illegal move.")
{
}

/**
Print the IllegalMoveException message according to the string passed in.

@param message The error message to print.
*/
IllegalMoveException::IllegalMoveException(const std::string& message) : 
	std::runtime_error(message)
{
}
