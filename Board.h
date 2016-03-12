/**
Name: Jeff McCullen and Emma Elliott
Date: February 10, 2016
Description: 
*/

#ifndef BOARD_H
#define BOARD_H

#include "LCExceptions.h"

class Board
{
public:
	// member variables
	enum Piece{X=0, O, NONE};
	enum {MAX_ROWS = 3};
	enum {MAX_COLUMNS = 3};
	enum {PIECES = 3};
	enum State{XWINS, OWINS, DRAW, INCOMPLETE};

	// methods
	Board();
	Board(const Board& original);

	Board& operator=(const Board& rhs);
	bool operator==(const Board& rhs) const;
	bool operator!=(const Board& rhs) const;

	// places the given piece in the given position
	// throws an IllegalMoveException if the move is not legal
	void playPiece(int row, int column, Piece piece)
		throw (IllegalMoveException);

	// [jrm] throw exception!!!!
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

	virtual ~Board();

private:
	//Piece Pieces_[MAX_ROWS][MAX_COLUMNS];
	Piece** pieces_;
	virtual Piece** initPieces();

	size_t nMoves_;
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

	virtual Piece** allocateAndCopy(Piece** pieces) const;
	virtual void destroyBoard() const;


};

#endif //BOARD_H
