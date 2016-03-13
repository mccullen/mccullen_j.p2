/**
Name: Jeff McCullen and Emma Elliott
Date: February 10, 2016
Description: Board prototype for a game of 3x3 tic tac toe.
*/

#ifndef BOARD_H
#define BOARD_H

#include "LCExceptions.h"

class Board
{
public:
	// A tic tac toe piece is that which fills a square on the board
	// and can be either X, O, or nothing.
	enum Piece{X=0, O, NONE};

	// A tic tac toe board has 3 rows and 3 columns.
	enum {MAX_ROWS = 3};
	enum {MAX_COLUMNS = 3};

	// There are three kinds of tic tac toe pieces (X, O, and NONE).
	enum {PIECES = 3};

	// The possible states of a tic tac toe board are
	//  - X won the game
	//  - O won the game
	//  - Draw
	//  - The game has not finished yet.
	enum State{XWINS, OWINS, DRAW, INCOMPLETE};

	/**
	Construct a default board.
	*/
	Board();

	/**
	Construct a board given another board.

	@param original The board to copy.
	*/
	Board(const Board& original);

	/**
	Assign the board on the rhs to the board on the lhs.
	This will make a deep copy.

	@param rhs The board on the rhs that you are assigning.
	@return This board after the assignment.
	*/
	Board& operator=(const Board& rhs);

	/**
	Determine wheather two boards are equivalent. They are equivalent
	if each square has the same piece.

	@param rhs The board on the right hand side.
	@return True if the lhs and rhs board have the same piece in every
	square.
	*/
	bool operator==(const Board& rhs) const;

	/**
	Determine wheather two boards are not equivalent. They are 
	not equivalent if any of the squares have a different piece.

	@param rhs The board on the right hand side.
	@return True if the lhs and rhs board do not have the same 
	piece in every square.
	*/
	bool operator!=(const Board& rhs) const;

	// places the given piece in the given position
	// throws an IllegalMoveException if the move is not legal
	void playPiece(int row, int column, Piece piece)
		throw (IllegalMoveException);

	/**
	Set the square at the given row and column to NONE.

	@param row The row of the board.
	@param column The column of the board.
	*/
	virtual void unplacePiece(int row, int column);

	/*
	returns the piece found on the board at this location
	X for Xs
	O for Os
	NONE if there is no piece at this location
	*/
	Piece checkPiece(int row, int column) const;

	/*
	Returns an enumeration, based on the state of the board.
	XWINS: if X wins
	OWINS: if O wins
	DRAW: if its a draw
	INCOMPLETE: if the game is not yet finished
	*/
	State gameState() const;
	
	/*
	Computes a hash code for the board.
	*/
	size_t hash() const;

	/**
	Print the board to the output stream.
	*/
	virtual void drawBoard(std::ostream& out) const;

	/**
	Destruct the board.
	*/
	virtual ~Board();

private:
	// Note: You could do this if you did not want to use
	// dynamic memory allocation.
	// Piece Pieces_[MAX_ROWS][MAX_COLUMNS];

	// Field to store the piece in each square.
	Piece** pieces_;

	/**
	Initialize every square in the pieces_ field to NONE.
	*/
	virtual Piece** initPieces();

	// Keep track of the number of moves. Note that unplacing a piece
	// will decrement this unless the user tried to unplace a piece
	// on a square which was already set to NONE, in which case
	// it will stay the same.
	size_t nMoves_;

	// The maximum number of moves in a tic tac toe game.
	static const size_t MAX_NUM_OF_MOVES = 9;

	/**
	Determine wheather someone won horizontally.

	@param state Set to the winner if there is a win.
	*/
	virtual bool horizontalWin(Board::State& state) const;

	/**
	Determine wheather someone won vertically.

	@param state Set to the winner if there is a win.
	*/
	virtual bool verticalWin(Board::State& state) const;

	/**
	Determine wheather someone won diagonally.

	@param state Set to the winner if there is a win.
	*/
	virtual bool diagonalWin(Board::State& state) const;

	/**
	Get an allocated copy of the pieces.

	@param pieces The pieces to copy.
	@return The allocated copy of pieces.
	*/
	virtual Piece** allocateAndCopy(Piece** pieces) const;

	/**
	Destroy a board, freeing up any allocated memory.
	*/
	virtual void destroyBoard() const;
};

#endif //BOARD_H
