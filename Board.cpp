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

/**
Construct a default board.
*/
Board::Board() : pieces_(initPieces()), nMoves_(0)
{
}

/**
Initialize every square in the pieces_ field to NONE.
*/
Board::Piece** Board::initPieces()
{
	// Allocate memory for the pieces's rows
	Board::Piece** pieces = new Board::Piece*[Board::MAX_ROWS];

	// For every row
	for (size_t row = 0; row < Board::MAX_ROWS; ++row)
	{
		// allocate memory for the pieces columns
		pieces[row] = new Board::Piece[Board::MAX_COLUMNS];
		// for every column in the row
		for (size_t column = 0; column < Board::MAX_COLUMNS;
			++column)
		{
			// set its inital value to NONE.
			pieces[row][column] = Board::NONE;
		}
	}
	return pieces;
}

/**
Construct a board given another board.

@param original The board to copy.
*/
Board::Board(const Board& original) : 
	pieces_(allocateAndCopy(original.pieces_)),
	nMoves_(original.nMoves_)
{
}

/**
Assign the board on the rhs to the board on the lhs.
This will make a deep copy.

@param rhs The board on the rhs that you are assigning.
@return This board after the assignment.
*/
Board& Board::operator=(const Board& rhs)
{
	// If not self assignment
	if (this != &rhs)
	{
		// destroy any allocated memory
		destroyBoard();

		// assign and allocate new values.
		nMoves_ = rhs.nMoves_;
		pieces_ = allocateAndCopy(rhs.pieces_);
	}
	return *this;
}

/**
Get an allocated copy of the pieces.

@param pieces The pieces to copy.
@return The allocated copy of pieces.
*/
Board::Piece** Board::allocateAndCopy(Piece** pieces) const
{
	// Allocate memory for the copy's rows
	Piece** copy = new Board::Piece*[Board::MAX_ROWS];
	// For every row in the copy
	for (size_t row = 0; row < Board::MAX_ROWS; ++row)
	{
		// allocate memory for the copy's columns
		copy[row] = new Board::Piece[Board::MAX_COLUMNS];
		// for every column in the row
		for (size_t column = 0; column < MAX_COLUMNS;
			++column)
		{
			// assign the pieces value to the copy.
			copy[row][column] = pieces[row][column];
		}
	}
	return copy;
}

/**
Determine wheather two boards are equivalent. They are equivalent
if each square has the same piece.

@param rhs The board on the right hand side.
@return True if the lhs and rhs board have the same piece in every
square.
*/
bool Board::operator==(const Board& rhs) const
{

	bool retVal = true;
	// For every row
	for (int i = 0; i < Board::MAX_ROWS && retVal; ++i)
	{
		// For every column in that row
		for (int j = 0; j < Board::MAX_COLUMNS && retVal; ++j)
		{
			// if the piece at that square is different,
			// return false.
			if (checkPiece(i,j) != rhs.checkPiece(i,j))
			{
				retVal = false;
			}
		}
	}
	return retVal;
}

/**
Determine wheather two boards are not equivalent. They are 
not equivalent if any of the squares have a different piece.

@param rhs The board on the right hand side.
@return True if the lhs and rhs board do not have the same 
piece in every square.
*/
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
	const size_t X_VAL = 1;
	const size_t O_VAL = 2;
	const size_t NONE_VAL = 0;

	// For every row
	for (size_t row = 0; row < Board::MAX_ROWS; ++row)
	{
		// For every column in the row
		for (size_t column = 0; column < Board::MAX_COLUMNS;
			++column)
		{
			const int BASE = 10;

			// Multiply the hase code by the BASE
			// to shift everything over.
			hashCode = hashCode * BASE;

			// If the piece at this square is NONE,
			// add 0.
			if (pieces_[row][column] == Board::NONE)
			{
				hashCode += NONE_VAL;
			}
			// Else, if it is X, add 1
			else if (pieces_[row][column] == Board::X)
			{
				hashCode += X_VAL;
			}
			// Else, it is O so add 2.
			else
			{
				hashCode += O_VAL;
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

	// For every row
	for (size_t row = 0; row < Board::MAX_ROWS; ++row)
	{
		// output the spacing
		out << spacing << endl;
		// For every column in the row
		for (size_t column = 0; column < Board::MAX_COLUMNS; ++column)
		{
			// output the piece
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
			// If not at the end of a column, print a bar.
			if (column < Board::MAX_COLUMNS - 1)
			{
				out << "|";
			}
		}
		// end the line and output spacing
		out << endl;
		out << spacing << endl;
		// If not at the end of the row, output more spacing.
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
	// If there is something to unplace, decrement the
	// number of moves.
	if (pieces_[row][column] != Board::NONE)
	{
		--nMoves_;
	}
	// Set the row and column to none.
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

/**
Destroy a board, freeing up any allocated memory.
*/
void Board::destroyBoard() const
{
	// For every row allocated in pieces_
	for (size_t row = 0; row < Board::MAX_ROWS; ++row)
	{
		// delete everything it points to
		delete [] pieces_[row];
	}
	// delete everything pieces_ points to.
	delete [] pieces_;
}

/**
Destory the board, freeing up all allocated memory.
*/
Board::~Board()
{
	destroyBoard();
}
