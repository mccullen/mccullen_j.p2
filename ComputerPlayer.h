/**
Name: Jeff McCullen and Emma Elliott
Date: February 10, 2016
Description: Prototype for the ComputerPlayer class. This class
is a computer player for tic tac toe and uses a hash table to 
store the states of the game in order to always make the best move.
If the state of the game is not known, meaning it is not yet stored
in the table, it is recursively figured out using the minimax
algorithm and then stored in the table.
*/
#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "Board.h"
#include <vector>
#include <map>
#include "LCHashMap.h"


class ComputerPlayer
{
public:
	/**
	Construct a computer player using the given piece.

	@param piece The piece to make the computer player (X or O)
	*/
	ComputerPlayer(Board::Piece piece);

	/**
	Make the best move on the board.

	@param The board to make the best move on.
	*/
	void makeNextMove(Board& board);

	/**
	Destruct the ComputerPlayer.
	*/
	virtual ~ComputerPlayer();

	enum Evaluation {COMP_LOSS = -1, DRAW = 0, COMP_WIN = 1};
private:
	// Store the evaluation of each game state. The computer
	// is the "MAX" so he wins with the board evaluation of 1.
	// change this back to private by uncommenting![jrm]
	//enum Evaluation {COMP_LOSS = -1, DRAW = 0, COMP_WIN = 1};

	// An AIMove is used as a container for the best row and 
	// column for the player to play.
	struct AIMove
	{
		AIMove() {};
		AIMove(Evaluation score) : score_(score) {}
		int row_;
		int column_;
		Evaluation score_;
	};

	//enum {O_WINS = -1, DRAW = 0, X_WINS = 1};


	// Store the piece of each player.
	Board::Piece compPiece_;
	Board::Piece humanPiece_;

	/**
	Find the best move for the computer given a board.

	@param board The board to find the best move for.
	@return The best move (a structure containing the row, column, and 
	evaluation of the move). The evaluation determines who will win
	if the other player plays optimally or may be a draw.
	*/
	virtual AIMove findCompMove(Board& board);

	/**
	Find the best move for the human given a board.

	@param board The board to find the best move for.
	@return The best move (a structure containing the row, column, and 
	evaluation of the move). The evaluation determines who will win
	if the other player plays optimally or may be a draw.
	*/
	virtual AIMove findHumanMove(Board& board);

	/** 
	Get the best move for the given player for the given board.

	@param board The board to play
	@param player The player whose turn it is.
	*/
	AIMove getBestMove(Board& board, Board::Piece player);

	/**
	Helper functio for getBestMove
	*/
	AIMove getBestMoveAux(Board& board, Board::Piece player);

	/**
	Get the moves and their scores for the player on the given board.

	@param board The board to get the moves for.
	@param player The player to get the moves for.
	@param moves The vector of moves.
	*/
	void getMoves(Board& board, Board::Piece player,
		std::vector<AIMove>& moves);

	/**
	Determine if the player can make a move to win the game on the
	board. If he can, set the best move to that move. 

	@param board The board to check if there is an immediate win.
	@param player The player to check if they can win.
	@param bestMove The move to update if there is an immediate win
	@return True if the player can win on the board.
	*/
	virtual bool immediateWin(Board& board, Board::Piece player,
		AIMove& bestMove);

	/**
	Functor which returns the hash code of the board.

	@param The board to hash.
	@return The hash code of the board.
	*/
	class BoardHash
	{
	public:
		virtual size_t operator()(const Board& board) const;
	};

	/**
	Functor which determines wheather two boards are equal.

	@param lhs The board on the left hand side.
	@param rhs The board on the right hand side.
	@return True if the boards are equalivant. 
	*/
	class BoardEquator
	{
	public:
		virtual bool operator()(const Board& lhs,
			const Board& rhs) const;
	};

	// Maintain hash table of previously encountered boards.
	LCHashMap<Board, Evaluation, BoardHash, BoardEquator> 
		boardToEvaluation_;
};

#endif // COMPUTER_PLAYER_H
