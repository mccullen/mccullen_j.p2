/**
Name: Jeff McCullen and Emma Elliott
Date: February 10, 2016
Description: 
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
	humanPiece_ = (compPiece_ == Board::X) ? Board::O : Board::X;
}

/**
Make the best move on the board.

@param The board to make the best move on.
*/
void ComputerPlayer::makeNextMove(Board& board)
{
	/*
	 - If board is in table
	   - return the score
	 - Else
	   - evaluate the score using minimax recursively
	   - store it in the table.
	*/

	AIMove bestMove = findCompMove(board);
	board.playPiece(bestMove.row_, bestMove.column_, compPiece_);
}

ComputerPlayer::AIMove ComputerPlayer::findCompMove(Board& board)
{
	AIMove bestMove;

	Evaluation responseValue;

	if (board.gameState() == Board::DRAW)
	{
		bestMove.score_ = ComputerPlayer::DRAW;
	}
	else if (immediateWin(board, compPiece_, bestMove))
	/*
	else if ((board.gameState() == Board::XWINS && compPiece_ == Board::X) ||
		(board.gameState() == Board::OWINS && compPiece_ == Board::O))
	*/
	{
		bestMove.score_ = COMP_WIN;
	}
	else
	{
		bestMove.score_ = COMP_LOSS;
		bestMove.row_ = 0;
		bestMove.column_ = 0;

		for (size_t row = 0; row < Board::MAX_ROWS; ++row)
		{
			for (size_t column = 0; column < Board::MAX_COLUMNS;
				++column)
			{
				if (board.checkPiece(row, column) == Board::NONE)
				{
					board.playPiece(row, column, compPiece_);
					/*
					 - If board is in table
					   - return the score
					 - Else
					   - evaluate the score using minimax recursively
					   - store it in the table.
					*/
					if (boardToEvaluation_.in(board))
					{
						responseValue = boardToEvaluation_[board];
					}
					else
					{
						responseValue = findHumanMove(board).score_;
						boardToEvaluation_.insert(board, responseValue);
					}
					board.unplacePiece(row, column);

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

ComputerPlayer::AIMove ComputerPlayer::findHumanMove(Board& board)
{
	AIMove bestMove;

	Evaluation responseValue;

	if (board.gameState() == Board::DRAW)
	{
		bestMove.score_ = ComputerPlayer::DRAW;
	}
	else if (immediateWin(board, humanPiece_, bestMove))
	/*
	else if ((board.gameState() == Board::XWINS && humanPiece_ == Board::X) ||
		(board.gameState() == Board::OWINS && humanPiece_ == Board::O))
	*/
	{
		bestMove.score_ = COMP_LOSS;
	}
	else
	{
		bestMove.score_ = COMP_WIN;
		bestMove.row_ = 0;
		bestMove.column_ = 0;

		for (size_t row = 0; row < Board::MAX_ROWS; ++row)
		{
			for (size_t column = 0; column < Board::MAX_COLUMNS;
				++column)
			{
				if (board.checkPiece(row, column) == Board::NONE)
				{
					board.playPiece(row, column, humanPiece_);
					/*
					 - If board is in table
					   - return the score
					 - Else
					   - evaluate the score using minimax recursively
					   - store it in the table.
					*/
					if (boardToEvaluation_.in(board))
					{
						responseValue = boardToEvaluation_[board];
					}
					else
					{
						responseValue = findCompMove(board).score_;
						boardToEvaluation_.insert(board, responseValue);
					}
					board.unplacePiece(row, column);

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
Get the best move for the given player for the given board.

@param board The board to play
@param player The player whose turn it is.
*/
ComputerPlayer::AIMove ComputerPlayer::getBestMove(
	Board& board, Board::Piece player)
{
	// Get the state of the board (incomplete, someone won, or draw)
	Board::State state = board.gameState();

	// Store the best move for the player.
	AIMove bestMove;

	// Base Cases: Someone won or there is a draw.

	/*
	// If the computer won
	if ((state == Board::XWINS && compPiece_ == Board::X) ||
		(state == Board::OWINS && compPiece_ == Board::O))
	{
		bestMove = AIMove(ComputerPlayer::COMP_WIN);
	}
	// Else, if the computer lost
	else if ((state == Board::XWINS && humanPiece_ == Board::X) ||
		(state == Board::OWINS && humanPiece_ == Board::O))
	{
		bestMove = AIMove(ComputerPlayer::COMP_LOSS);
	}
	*/
	/*
	if (immediateWin(board, player))
	{
		bestMove = (player == compPiece_) ? COMP_WIN : COMP_LOSS;
	}
	// Else, if draw
	else if (state == Board::DRAW)
	{
		bestMove = AIMove(ComputerPlayer::DRAW);
	}

	// Recursive case: Board incomplete
	// Else, the board is incomplete so recurse.
	else
	{
		bestMove = getBestMoveAux(board, player);

	}
	return bestMove;
	*/

}
// [jrm] this could be more efficient with a break when 
// retVal becomes true.
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
Helper functio for getBestMove
*/
ComputerPlayer::AIMove ComputerPlayer::getBestMoveAux(
	Board& board, Board::Piece player)
{
	// Store the best move
	AIMove bestMove;

	// Get moves and their scores (evaluation).
	//getHash(board, player, moves);

	// Why do you need to do this here? [jrm]
	if (player == compPiece_)
	{
		bestMove.score_ = COMP_LOSS;
	}
	else
	{
		bestMove.score_ = COMP_WIN;
	}
	for (int row = 0; row < Board::MAX_ROWS; ++row)
	{
		for (int column = 0; column < Board::MAX_COLUMNS;
			++column)
		{
			if (board.checkPiece(row, column) ==
				Board::NONE)
			{
				AIMove move;
				move.row_ = row;
				move.column_ = column;

				board.playPiece(row, column, player);
				Evaluation responseValue;
				// If the board is in the hash map
				if (boardToEvaluation_.in(board))
				{
					//move.score_ = boardToEvaluation_[board];
					responseValue = boardToEvaluation_[board];
				}
				else
				{
					if (player == compPiece_)
					{
						//move.score_ = getBestMove(board, humanPiece_).score_;
						responseValue = getBestMove(board, humanPiece_).score_;
					}
					else
					{
						//move.score_ = getBestMove(board, compPiece_).score_;
						responseValue = getBestMove(board, compPiece_).score_;
					}
					//boardToEvaluation_.insert(board, move.score_);
					boardToEvaluation_.insert(board, responseValue);
				}
				board.unplacePiece(row, column);
				if (player == compPiece_)
				{
					// Why can't you set the best score here??
					if (responseValue > bestMove.score_)
					{
						bestMove.score_ = responseValue;
						bestMove.row_ = move.row_;
						bestMove.column_ = move.column_;
					}
				}
				else
				{
					if (responseValue < bestMove.score_)
					{
						bestMove.score_ = responseValue;
						bestMove.row_ = move.row_;
						bestMove.column_ = move.column_;
					}
				}
			}
		}
	}

	return bestMove;

/*
	// Store the best move
	AIMove bestMove;

	// Get moves and their scores (evaluation).
	std::vector<AIMove> moves;
	getMoves(board, player, moves);


	int bestMoveIndex = 0;

	// [jrm] why doesn't the other approach work all the time??
	// If the player is a computer, the maximum score is the best.
	if (player == compPiece_)
	{
		int bestScore = ComputerPlayer::COMP_LOSS;
		for (int i = 0; i < moves.size(); ++i)
		{
			if (moves[i].score_ > bestScore)
			{
				bestMoveIndex = i;
				bestScore = moves[i].score_;
				//bestMove = moves[i];
			}
		}
	}
	// If the player is human, the minimum score is the best.
	else
	{
		int bestScore = ComputerPlayer::COMP_WIN;
		for (int i = 0; i < moves.size(); ++i)
		{
			if (moves[i].score_ < bestScore)
			{
				bestMoveIndex = i;
				bestScore = moves[i].score_;
				//bestMove = moves[i];
			}
		}
		
	
	}

	bestMove = moves[bestMoveIndex];

	return bestMove;

*/
}

/**
[jrm] recursive function takes in a single board and returns back
its value.

Get the moves and their scores for the player on the given board.

@param board The board to get the moves for.
@param player The player to get the moves for.
@param moves The vector of moves.
*/
void ComputerPlayer::getMoves(
	Board& board, Board::Piece player, std::vector<AIMove>& moves)
{
	for (int row = 0; row < Board::MAX_ROWS; ++row)
	{
		for (int column = 0; column < Board::MAX_COLUMNS;
			++column)
		{
			if (board.checkPiece(row, column) ==
				Board::NONE)
			{
				AIMove move;
				move.row_ = row;
				move.column_ = column;

				board.playPiece(row, column, player);

				if (player == compPiece_)
				{
					move.score_ = getBestMove(board, humanPiece_).score_;
				}
				else
				{
					move.score_ = getBestMove(board, compPiece_).score_;
				}
				

				moves.push_back(move);
				board.unplacePiece(row, column);
			}
		}
	}

}

size_t ComputerPlayer::BoardHash::operator()(const Board& board) const
{
	return board.hash();
}
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
