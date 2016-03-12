/**
Name: Jeff McCullen and Emma Elliott
Date: February 10, 2016
Description: 
*/

#ifndef CONSOLE_INTERFACE_H
#define CONSOLE_INTERFACE_H

class ConsoleInterface
{
public:
	/**
	Construct a console interface
	*/
	ConsoleInterface();

	/**
	Take control of the game from main.
	*/
	virtual void start();

	/**
	Destruct the console interface.
	*/
	virtual ~ConsoleInterface();
private:
	// Store the options that the user can play in the game
	// of tic tac toe.
	static const int HUMAN_VS_HUMAN = 1;
	static const int COMP_VS_HUMAN = 2;

	static const char AFFIRMATIVE = 'y';
	static const char NEGATIVE = 'n';

	/**
	Get the option from the user.

	@return The option the user chose.
	*/
	virtual int getOption() const;

	/**
	Play a single game of human vs. human tic tac toe.
	*/
	virtual void playHumanVsHuman() const;

	/**
	Play a single game of computer vs. human tic tac toe.
	*/
	virtual void playCompVsHuman() const;

	/**
	Determine wheather or not the option the user chose is valid.
	Valid options are human vs. human and comp. vs. human.

	@param The option the user entered
	@return True if the option is valid.
	*/
	virtual bool isValidOption(int option) const;

	/**
	Determine wheather the row and column the user chose is valid
	or not.

	@return True if the option is valid.
	*/
	virtual bool isValidRowAndColumn(int row, int column) const;

	/**
	Get the row and column from the user

	@param row The variable to store the row in.
	@param column The variable to store the column in.
	*/
	virtual void getRowAndColumnFromUser(int& row, int& column) const;

	/**
	Determine which player goes first in COMP_VS_HUMAN game.
	*/
	virtual char getFirstPlayer() const;

	/**
	Play a game where the human goes first.
	*/
	virtual void playHumanFirst() const;

	/**
	Play a game where the computer goes first.
	*/
	virtual void playComputerFirst() const;
};

#endif // CONSOLE_INTERFACE_H
