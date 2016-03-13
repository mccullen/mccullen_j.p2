/**
Name: Jeff McCullen and Emma Elliott
Date: February 10, 2016
Description: Implementation for the ComputerPlayer class. This class
is a computer player for tic tac toe and uses a hash table to 
store the states of the game in order to always make the best move.
If the state of the game is not known, meaning it is not yet stored
in the table, it is recursively figured out using the minimax
algorithm and then stored in the table.
*/
#include "Board.h"
#include "ComputerPlayer.h"
#include <vector>

/**
Construct a computer player using the given piece.

@param piece The piece to make the computer player (X or O)
*/
ComputerPlayer::ComputerPlayer(Board::Piece piece) : 
	compPiece_(piece)
{
	// The human piece is whatever the computer piece is not.
	humanPiece_ = (compPiece_ == Board::X) ? Board::O : Board::X;
}

/**
Make the best move on the board.

@param The board to make the best move on.
*/
void ComputerPlayer::makeNextMove(Board& board)
{
	// Find the best move for the computer and then make that move.
	AIMove bestMove = findCompMove(board);
	board.playPiece(bestMove.row_, bestMove.column_, compPiece_);
}

/**
Find the best move for the computer given a board.

@param board The board to find the best move for.
@return The best move (a structure containing the row, column, and 
evaluation of the move). The evaluation determines who will win
if the other player plays optimally or may be a draw.
*/
ComputerPlayer::AIMove ComputerPlayer::findCompMove(Board& board)
{
	// Variable for the bestMove the computer can make given the
	// board.
	AIMove bestMove;

	// Variable for the evaluation of the human player assuming
	// he plays optimally.
	Evaluation responseValue;

	// If the game is a draw, the score (evaluation) of the move is
	// a draw.
	if (board.gameState() == Board::DRAW)
	{
		bestMove.score_ = ComputerPlayer::DRAW;
	}
	// Else, if the computer player can make a move to win the game,
	//  - set the bestMove row and column to that move (happens inside
	//    immediateWin()) and set the score to COMP_WIN
	else if (immediateWin(board, compPiece_, bestMove))
	/*
	else if ((board.gameState() == Board::XWINS && compPiece_ == Board::X) ||
		(board.gameState() == Board::OWINS && compPiece_ == Board::O))
	*/
	{
		bestMove.score_ = COMP_WIN;
	}
	// Else, the board has not yet reached a terminal state so
	// figure out the bestMove by looking it up in the table or 
	// using minimax.
	else
	{
		// Set the score to assume the worst (COMP_LOSS)
		bestMove.score_ = COMP_LOSS;
		// Set the row and column to the first
		bestMove.row_ = 0;
		bestMove.column_ = 0;

		// Check every square on the board

		for (size_t row = 0; row < Board::MAX_ROWS; ++row)
		{
			for (size_t column = 0; column < Board::MAX_COLUMNS;
				++column)
			{
				// If the square is empty, play there and see what the
				// evaluation of the board is.
				if (board.checkPiece(row, column) == Board::NONE)
				{
					board.playPiece(row, column, compPiece_);

					// If the board is in the table, return the score
					if (boardToEvaluation_.in(board))
					{
						responseValue = boardToEvaluation_[board];
					}
					// Else, evaluate the score using minimax recurisvely
					// and then store it in the table.
					else
					{
						responseValue = findHumanMove(board).score_;
						boardToEvaluation_.insert(board, responseValue);
					}

					board.unplacePiece(row, column);

					// If the evaluation of the board after making the move
					// is better than the score of the bestMove seen so far,
					// update the bestMove.
					if (responseValue > bestMove.score_)
					{
						bestMove.score_ = responseValue;
						bestMove.row_ = row;
						bestMove.column_ = column;
					}
				}
			}
		}

	}

	return bestMove;
}

/**
Find the best move for the human given a board.

@param board The board to find the best move for.
@return The best move (a structure containing the row, column, and 
evaluation of the move). The evaluation determines who will win
if the other player plays optimally or may be a draw.
*/
ComputerPlayer::AIMove ComputerPlayer::findHumanMove(Board& board)
{
	// Variable for the bestMove the computer can make given the
	// board.
	AIMove bestMove;

	// Variable for the evaluation of the human player assuming
	// he plays optimally.
	Evaluation responseValue;

	// If the game is a draw, the score (evaluation) of the move is
	// a draw.
	if (board.gameState() == Board::DRAW)
	{
		bestMove.score_ = ComputerPlayer::DRAW;
	}
	// Else, if the computer player can make a move to win the game,
	//  - set the bestMove row and column to that move (happens inside
	//    immediateWin()) and set the score to COMP_WIN
	else if (immediateWin(board, humanPiece_, bestMove))
	/*
	else if ((board.gameState() == Board::XWINS && humanPiece_ == Board::X) ||
		(board.gameState() == Board::OWINS && humanPiece_ == Board::O))
	*/
	{
		bestMove.score_ = COMP_LOSS;
	}
	// Else, the board has not yet reached a terminal state so
	// figure out the bestMove by looking it up in the table or 
	// using minimax.
	else
	{
		// Set the score to assume the worst (COMP_LOSS)
		bestMove.score_ = COMP_WIN;
		// Set the row and column to the first
		bestMove.row_ = 0;
		bestMove.column_ = 0;

		// Check every square on the board

		for (size_t row = 0; row < Board::MAX_ROWS; ++row)
		{
			for (size_t column = 0; column < Board::MAX_COLUMNS;
				++column)
			{
				// If the square is empty, play there and see what the
				// evaluation of the board is.
				if (board.checkPiece(row, column) == Board::NONE)
				{
					board.playPiece(row, column, humanPiece_);

					// If the board is in the table, return the score
					if (boardToEvaluation_.in(board))
					{
						responseValue = boardToEvaluation_[board];
					}
					// Else, evaluate the score using minimax recurisvely
					// and then store it in the table.
					else
					{
						responseValue = findCompMove(board).score_;
						boardToEvaluation_.insert(board, responseValue);
					}
					board.unplacePiece(row, column);

					// If the evaluation of the board after making the move
					// is better than the score of the bestMove seen so far,
					// update the bestMove.
					if (responseValue < bestMove.score_)
					{
						bestMove.score_ = responseValue;
						bestMove.row_ = row;
						bestMove.column_ = column;
					}
				}
			}
		}

	}

	return bestMove;
}
/**
Determine if the player can make a move to win the game on the
board. If he can, set the best move to that move. 

@param board The board to check if there is an immediate win.
@param player The player to check if they can win.
@param bestMove The move to update if there is an immediate win
@return True if the player can win on the board.
*/
bool ComputerPlayer::immediateWin(Board& board, Board::Piece player,
	AIMove& bestMove)
{
	bool retVal = false;
	// For every row
	for (int i = 0; i < Board::MAX_ROWS &&
		!retVal; ++i)
	{
		// For every column
		for (int j = 0; j < Board::MAX_COLUMNS &&
			!retVal; ++j)
		{
			// if the square is empty
			if (board.checkPiece(i,j) == Board::NONE)
			{
				// play the piece
				board.playPiece(i,j,player);

				// If there is an immediate win
				if (board.gameState() == Board::XWINS ||
					board.gameState() == Board::OWINS)
				{
					// set the bestMove and return true.
					bestMove.row_ = i;
					bestMove.column_ = j;
					retVal = true;
				}
				board.unplacePiece(i,j);

			}
		}
	}
	return retVal;
}


/**
Functor which returns the hash code of the board.

@param The board to hash.
@return The hash code of the board.
*/
size_t ComputerPlayer::BoardHash::operator()(const Board& board) const
{
	return board.hash();
}

/**
Functor which determines wheather two boards are equal.

@param lhs The board on the left hand side.
@param rhs The board on the right hand side.
@return True if the boards are equalivant. 
*/
bool ComputerPlayer::BoardEquator::operator()(const Board& lhs,
	const Board& rhs) const
{
	return lhs == rhs;
}

/**
Destruct the ComputerPlayer.
*/
ComputerPlayer::~ComputerPlayer()
{
}
