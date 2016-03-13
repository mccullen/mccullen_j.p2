/**
UPDATE
Name: Jeff McCullen and Emma Elliott
Date: February 10, 2016
Description: 
*/

#include <iostream>
#include <string>
#include "LCExceptions.h"
#include "Board.h"
using namespace std;

// methods
Board::Board() : pieces_(initPieces()), nMoves_(0)
{
}

// [jrm] can you do this statically? will it go out of scope?
Board::Piece** Board::initPieces()
{
	Board::Piece** pieces = new Board::Piece*[Board::MAX_ROWS];
	for (size_t row = 0; row < Board::MAX_ROWS; ++row)
	{
		pieces[row] = new Board::Piece[Board::MAX_COLUMNS];
		for (size_t column = 0; column < Board::MAX_COLUMNS;
			++column)
		{
			pieces[row][column] = Board::NONE;
		}
	}
	return pieces;
}

Board::Board(const Board& original) : 
	pieces_(allocateAndCopy(original.pieces_)),
	nMoves_(original.nMoves_)
{
}

Board& Board::operator=(const Board& rhs)
{
	if (this != &rhs)
	{
		destroyBoard();

		nMoves_ = rhs.nMoves_;	
		pieces_ = allocateAndCopy(rhs.pieces_);
	}
	return *this;
}

Board::Piece** Board::allocateAndCopy(Piece** pieces) const
{
	Piece** copy = new Board::Piece*[Board::MAX_ROWS];
	for (size_t row = 0; row < Board::MAX_ROWS; ++row)
	{
		copy[row] = new Board::Piece[Board::MAX_COLUMNS];
		for (size_t column = 0; column < MAX_COLUMNS;
			++column)
		{
			copy[row][column] = pieces[row][column];
		}
	}
	return copy;
}

bool Board::operator==(const Board& rhs) const
{

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (checkPiece(i,j) != rhs.checkPiece(i,j))
			{
				return false;
			}
		}
	}
	return true;
	/*
	size_t row = 0;
	size_t column = 0;
	while (row < Board::MAX_ROWS && 
		pieces_[row][column] == rhs.pieces_[row][column])
	{
		while (column < Board::MAX_COLUMNS &&
			pieces_[row][column] == rhs.pieces_[row][column])
		{
			++column;
		}
		++row;
	}
	return row == Board::MAX_ROWS;
	*/
}

bool Board::operator!=(const Board& rhs) const
{
	return !(*this == rhs);
}


// places the given piece in the given position
// throws an IllegalMoveException if the move is not legal
void Board::playPiece(int row, int column, Piece piece)
	throw (IllegalMoveException)
{
  if(checkPiece(row, column) != Board::NONE) throw IllegalMoveException();
  
	pieces_[row][column] = piece;
	nMoves_++;
}

/*
returns the piece found on the board at this location
X for Xs
O for Os
NONE if there is no piece at this location
*/
Board::Piece Board::checkPiece(int row, int column) const
{
  return pieces_[row][column];
}


/*
Returns an enumeration, based on the state of the board.
XWINS: if X wins
OWINS: if O wins
DRAW: if its a draw
INCOMPLETE: if the game is not yet finished
*/
Board::State Board::gameState() const
{
	bool winnerCheck = false;
	State state = Board::INCOMPLETE;

	// Check for horizontal winner
	winnerCheck = horizontalWin(state);
	// If there is not a horizontal winner
	if (!winnerCheck)
	{
		// Check for vertical winner
		winnerCheck = verticalWin(state);

		// If there is not a vertical winner,
		// check for diagonal winner.
		if (!winnerCheck)
		{
			winnerCheck = diagonalWin(state);
		}
	}

	// Check for draw.
	if (nMoves_ == MAX_NUM_OF_MOVES && !winnerCheck)
	{
		state = Board::DRAW;
	}
	return state;
}

/*
Computes a hash code for the board.
*/
size_t Board::hash() const
{
	/*
	- Treat board as a base 3 number
	  - NONE is 0
	  - X is 1
	  - O is 2
	- Convert to an int
	*/
	size_t hashCode = 0;

	for (size_t row = 0; row < Board::MAX_ROWS; ++row)
	{
		for (size_t column = 0; column < Board::MAX_COLUMNS;
			++column)
		{
			const int BASE = 10;
			hashCode = hashCode * BASE;
			if (pieces_[row][column] == Board::NONE)
			{
				hashCode += 0;
			}
			else if (pieces_[row][column] == Board::X)
			{
				hashCode += 1;
			}
			else
			{
				hashCode += 2;
			}

		}
		
	}

	return hashCode;
}

/**
Print the board to the output stream.
*/
void Board::drawBoard(std::ostream& out) const
{
	std::string spacing = "   |   |   ";
	std::string outline = "---+---+---";

	for (size_t row = 0; row < Board::MAX_ROWS; ++row)
	{
		cout << spacing << endl;
		for (size_t column = 0; column < Board::MAX_COLUMNS; ++column)
		{
			switch (pieces_[row][column])
			{
			case X:
				out << " X ";
				break;
			case O:
				out << " O ";
				break;
			case NONE:
				out << "   ";
				break;
			default:
				break;
			}
			if (column < Board::MAX_COLUMNS - 1)
			{
				out << "|";
			}
		}
		out << endl;
		out << spacing << endl;
		if (row < Board::MAX_ROWS - 1)
		{
			out << outline << endl;
		}
	}

}

/**
Set the square at the given row and column to NONE.

@param row The row of the board.
@param column The column of the board.
*/
void Board::unplacePiece(int row, int column)
{
	if (pieces_[row][column] != Board::NONE)
	{
		--nMoves_;
	}
	pieces_[row][column] = Board::NONE;
}


/**
Determine wheather someone won horizontally.

@param state Set to the winner if there is a win.
*/
bool Board::horizontalWin(Board::State& state) const
{
	bool winnerCheck = false;
	// For every row
	for (int row = 0; row < Board::MAX_ROWS && !winnerCheck; ++row)
	{
		// store the number of Xs or Os in a row.
		int numberOfXs = 0;
		int numberOfOs = 0;

		// For every column
		for (int column = 0; column < Board::MAX_COLUMNS;
			++column)
		{
			// If the piece is an X, add it to the numberOfXs
			if (pieces_[row][column] == Board::X)
			{
				++numberOfXs;
			}
			// If the piece is an O, add it to the numberOfOs
			if (pieces_[row][column] == Board::O)
			{
				++numberOfOs;
			}
		}
		// If X won, set the state and the winnerCheck.
		if (numberOfXs == Board::MAX_COLUMNS)
		{
			state = Board::XWINS;
			winnerCheck = true;
		}
		// If O won, set the state and the winnerCheck.
		else if(numberOfOs == Board::MAX_COLUMNS)
		{
			state = Board::OWINS;
			winnerCheck = true;
		}
	}
	return winnerCheck;
}

/**
Determine wheather someone won vertically.

@param state Set to the winner if there is a win.
*/
bool Board::verticalWin(Board::State& state) const
{
	bool winnerCheck = false;
	// For every column
	for (int column = 0; column < Board::MAX_COLUMNS && !winnerCheck; ++column)
	{
		// Store the numberOfXs and Os for that column
		int numberOfXs = 0;
		int numberOfOs = 0;

		// For every row
		for (int row = 0; row < Board::MAX_ROWS; ++row)
		{
			// If the piece is X, increment the numberOfXs
			if (pieces_[row][column] == Board::X)
			{
				++numberOfXs;
			}
			// If the piece is O, increment the numberOfOs
			if (pieces_[row][column] == Board::O)
			{
				++numberOfOs;
			}
		}
		// If x won along a column, set winnerCheck and state
		if (numberOfXs == Board::MAX_ROWS)
		{
			state = Board::XWINS;
			winnerCheck = true;
		}
		// else if o won along a colmn, set winnerCheck and state.
		else if(numberOfOs == Board::MAX_ROWS)
		{
			state = Board::OWINS;
			winnerCheck = true;
		}
	}
	return winnerCheck;
}

/**
Determine wheather someone won diagonally.

@param state Set to the winner if there is a win.
*/
bool Board::diagonalWin(Board::State& state) const
{
	bool winnerCheck = false;
	// [jrm] get rid of constants
	// Check diagnal
	if (pieces_[0][0] == Board::X &&
		pieces_[1][1] == Board::X &&
		pieces_[2][2] == Board::X)
	{
		state = Board::XWINS;
		winnerCheck = true;
	}
	if (pieces_[0][0] == Board::O &&
		pieces_[1][1] == Board::O &&
		pieces_[2][2] == Board::O)
	{
		state = Board::OWINS;
		winnerCheck = true;
	}


	// Check diagnal
	if (pieces_[0][2] == Board::X &&
		pieces_[1][1] == Board::X &&
		pieces_[2][0] == Board::X)
	{
		state = Board::XWINS;
		winnerCheck = true;
	}
	if (pieces_[0][2] == Board::O &&
		pieces_[1][1] == Board::O &&
		pieces_[2][0] == Board::O)
	{
		state = Board::OWINS;
		winnerCheck = true;
	}

	return winnerCheck;
}
void Board::destroyBoard() const
{
	for (size_t row = 0; row < Board::MAX_ROWS; ++row)
	{
		delete [] pieces_[row];
	}
	delete [] pieces_;
}

Board::~Board()
{
	destroyBoard();
}
