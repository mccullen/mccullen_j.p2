/**
Name: Jeff McCullen and Emma Elliott
Date: February 10, 2016
Description: 

[jrm] - check for playing piece in place already taken
      - 
*/
#include <iostream>
#include "ConsoleInterface.h"
#include "Board.h"
#include "ComputerPlayer.h"
using namespace std;

/**
Construct a console interface
*/
ConsoleInterface::ConsoleInterface()
{
}

/**
Take control of the game from main.
*/
void ConsoleInterface::start()
{
  char input = AFFIRMATIVE;
  do
  {
	  int option = getOption();
  
  	switch (option)
	  {
	  case HUMAN_VS_HUMAN:
	  	playHumanVsHuman();
		  break;
	  case COMP_VS_HUMAN:
	  	playCompVsHuman();
	  	break;
	  default:
	  	break;
	  }
     
     cout << "Play again?(y/n): ";
     cin >> input;
     
   }while(input == AFFIRMATIVE);
}

/**
Play a single game of human vs. human tic tac toe.
*/
void ConsoleInterface::playHumanVsHuman() const
{
	// Create board
	Board board;

	// X is the starting piece. 
	Board::Piece piece = Board::X;

	// While the game is not finished
	while (board.gameState() == Board::INCOMPLETE)
	{
		// draw the board.
		board.drawBoard(cout);

		// prompt the user for a row and column to place his or 
		// her piece.
		int row;
		int column;
		getRowAndColumnFromUser(row, column);

		// play the piece.
		try
		{
			board.playPiece(row, column, piece);

			// Toggle the player
			(piece == Board::X) ? piece = Board::O : 
				piece = Board::X;
		}
		catch(IllegalMoveException e)
		{
			// Print out error and tell them to try again
			cout << "Error: Illegal Move. Try again.\n";
		}
		cout << endl;
	}

	board.drawBoard(cout);
  
	if(board.gameState() == Board::XWINS)
	{
		cout << "X wins!\n";
	}
	else if(board.gameState() == Board::OWINS)
	{
		cout << "O wins!\n";
	}
	else
	{
		cout << "Draw.\n"; 
	}
}


/**
Get the row and column from the user

@param row The variable to store the row in.
@param column The variable to store the column in.
*/
void ConsoleInterface::getRowAndColumnFromUser(int& row, int& column) const
{
	do
	{
		cout << "Select row: ";
		cin >> row;
		cout << "Select column: ";
		cin >> column;

		if (!isValidRowAndColumn(row, column))
		{
			cout << "Error: Invalid row or column.\n";
		}
	} while (!isValidRowAndColumn(row, column));
}

/**
Determine wheather the row and column the user chose is valid
or not.

@return True if the option is valid.
*/
bool ConsoleInterface::isValidRowAndColumn(int row, int column) const
{
	return row >= 0 && column >= 0 &&
		row < Board::MAX_ROWS && column < Board::MAX_COLUMNS;
}

/**
Play a single game of computer vs. human tic tac toe.
*/
void ConsoleInterface::playCompVsHuman() const
{
	// Ask the human if they want to go first
	char firstPlayer = getFirstPlayer();

	// If the human wants to go first
	if(firstPlayer == AFFIRMATIVE)
	{
		playHumanFirst();
	}
	// Else if the human does not want to go first
	else if(firstPlayer == NEGATIVE)
	{
		playComputerFirst();  
	}

}

/**
Determine which player goes first in COMP_VS_HUMAN game.
*/
char ConsoleInterface::getFirstPlayer() const
{
	char input;
	do
	{ 
		cout << "Do you want to go first?(y/n): ";
		cin >> input;
		if(input != AFFIRMATIVE && input != NEGATIVE)
		{
			cout << "Error! Did not enter a valid character! Try again!/n";
		}
	} while (input != AFFIRMATIVE && input != NEGATIVE);

	return input;
}
/**
Play a game where the human goes first.
*/
void ConsoleInterface::playHumanFirst() const
{
	// Human is the first play
	bool humanPlayerTurn = true;

	Board::Piece humanPiece = Board::X;
	Board::Piece cpuPiece = Board::O;

	// Create  computer player
	ComputerPlayer computerPlayer(cpuPiece);

	// Create the board
	Board board;

	// While the game is not finished
	while (board.gameState() == Board::INCOMPLETE)
	{
		// draw the board.
		board.drawBoard(cout);

		if(humanPlayerTurn)
		{
			// prompt the user for a row and column to place his or 
			// her piece.
			int row;
			int column;
			getRowAndColumnFromUser(row, column);
			  
			// play the piece.
			try
			{
				board.playPiece(row, column, humanPiece);

				// Toggle the player
				humanPlayerTurn = false;
			}
			catch(IllegalMoveException e)
			{
				// Print out error and tell them to try again
				cout << "Error: Illegal Move. Try again.\n";
			} 
		}
		else
		{
			// Computer Player makes their move
			computerPlayer.makeNextMove(board);
			// Toggle the player
			humanPlayerTurn = true;
		}
		cout << endl;
	}
	board.drawBoard(cout);

	if(board.gameState() == Board::XWINS)
	{
		cout << "X wins!\n";
	}
	else if(board.gameState() == Board::OWINS)
	{
		cout << "O wins!\n";
	}
	else if(board.gameState() == Board::DRAW)
	{
		cout << "Draw.\n"; 
	}
}

/**
Play a game where the computer goes first.
*/
void ConsoleInterface::playComputerFirst() const
{
	// Computer is the first to play
	bool humanPlayerTurn = false;

	Board::Piece humanPiece = Board::O;
	Board::Piece cpuPiece = Board::X;

	//Create  computer player
	ComputerPlayer computerPlayer(cpuPiece);

	//Create the board
	Board board;

	// While the game is not finished
	while (board.gameState() == Board::INCOMPLETE)
	{
		// draw the board.
		board.drawBoard(cout);

		if(humanPlayerTurn)
		{
			// prompt the user for a row and column to place his or 
			// her piece.
			int row;
			int column;
			getRowAndColumnFromUser(row, column);
			  
			// play the piece.
			try
			{
				board.playPiece(row, column, humanPiece);

				// Toggle the player
				humanPlayerTurn = false;
			}
			catch(IllegalMoveException e)
			{
				// Print out error and tell them to try again
				cout << "Error: Illegal Move. Try again.\n";
			} 
		}
		else
		{
			// Computer Player makes their move
			computerPlayer.makeNextMove(board);
			// Toggle the player
			humanPlayerTurn = true;
		}
		cout << endl;
	}
	board.drawBoard(cout);

	if(board.gameState() == Board::XWINS)
	{
		cout << "X wins!\n";
	}
	else if(board.gameState() == Board::OWINS)
	{
		cout << "O wins!\n";
	}
	else if(board.gameState() == Board::DRAW)
	{
		cout << "Draw.\n"; 
	}
}

/**
Get the option from the user.

@return The option the user chose.
*/
int ConsoleInterface::getOption() const
{
	int option;

	// While the user has not entered a valid option
	do
	{
		// keep prompting them for a valid option
		cout << "1. Human vs. Human\n"
		     << "2. Computer vs. Human\n"
		     << "Please select one of the above options: ";
		cin >> option;
		if (!isValidOption(option))
		{
			cout << "Error: Invalid option.\n";
		}
	} while (!isValidOption(option));

	return option;
}
/**
Determine wheather or not the option the user chose is valid.
Valid options are human vs. human and comp. vs. human.

@param The option the user entered
@return True if the option is valid.
*/
bool ConsoleInterface::isValidOption(int option) const
{
	return option == HUMAN_VS_HUMAN || option == COMP_VS_HUMAN;
}

/**
Destruct the console interface.
*/
ConsoleInterface::~ConsoleInterface()
{
}
