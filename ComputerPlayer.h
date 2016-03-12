/**
Name: Jeff McCullen and Emma Elliott
Date: February 10, 2016
Description: 
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

	virtual AIMove findCompMove(Board& board);
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

	virtual bool immediateWin(Board& board, Board::Piece player,
		AIMove& bestMove);

	class BoardHash
	{
	public:
		virtual size_t operator()(const Board& board) const;
	};

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
