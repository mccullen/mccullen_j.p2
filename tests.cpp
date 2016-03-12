/**
Name: Jeff McCullen
Date: March 6, 2016
Description: Tests for LCHashMap
*/

#include <iostream>
#include "LCHashMap.h"
#include "Board.h"
#include <assert.h>
#include "ComputerPlayer.h"

using namespace std;


class BoardEquator
{
public:
	virtual bool operator()(const Board& lhs, const Board& rhs) const
	{
		return lhs == rhs;
	}
};
class BoardHash
{
public:
	virtual size_t operator()(const Board& board) const
	{
		return board.hash();
	}
};
class IntHash
{
public:
	virtual size_t operator()(int myInt) const
	{
		return myInt;
	}
};
class IntEquator
{
public:
	virtual bool operator()(int lhs, int rhs) const
	{
		return lhs == rhs;
	}

};

void testInsert();
void testDefaultConstructor();
void testErase();
void testIn();
void testBracketOperator();
void testRehash();
void testResize();

int main(int argc, char** argv)
{
	testDefaultConstructor();
	testInsert();
	testErase();
	testIn();
	testBracketOperator();
	testRehash();
	//testResize();

	return 0;
}

void testResize()
{
	LCHashMap<int, char, IntHash, IntEquator> intToChar;
	int tsize = intToChar.tsize();
	for (int i = 0; i < 1000000; ++i)
	{
		intToChar.insert(i,'a');
		if (tsize != intToChar.tsize())
		{
			//cout << i << " : " << intToChar.tsize() << endl;
			tsize = intToChar.tsize();
		}
	}
}

void testRehash()
{
	LCHashMap<Board, ComputerPlayer::Evaluation, BoardHash, BoardEquator> boardToEval;

	Board b1;

	Board::Piece piece = Board::X;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			b1.playPiece(i,j,piece);
			boardToEval.insert(b1, ComputerPlayer::DRAW);
			//piece = (piece == Board::X) ? Board::O : Board::X;
			b1.unplacePiece(i,j);
		}
	}


	b1.playPiece(2,2,piece);
	assert(boardToEval[b1] == ComputerPlayer::DRAW);







	LCHashMap<int, char, IntHash, IntEquator> intToChar;

	// Insert enough to cause rehash
	assert(intToChar.insert(1,'a'));
	assert(intToChar.tsize() == 5);
	assert(intToChar.insert(2,'b'));
	assert(intToChar.tsize() == 5);
	assert(intToChar.insert(3,'c'));
	assert(intToChar.tsize() == 5);
	assert(intToChar.insert(4,'d'));
	assert(intToChar.tsize() == 5);
	assert(intToChar.insert(5,'e'));
	assert(intToChar.tsize() == 5);
	assert(intToChar.insert(6,'f')); // should cause rehash
	assert(intToChar.tsize() == 11); 

	// Test to make sure everything is still right.
	assert(intToChar.size() == 6);
	assert(intToChar[1] == 'a');
	assert(intToChar[2] == 'b');
	assert(intToChar[3] == 'c');
	assert(intToChar[4] == 'd');
	assert(intToChar[5] == 'e');
	assert(intToChar[6] == 'f');
	assert(intToChar.in(1));
	assert(intToChar.in(2));
	assert(intToChar.in(3));
	assert(intToChar.in(4));
	assert(intToChar.in(5));
	assert(intToChar.in(6));

	assert(intToChar.insert(7,'g'));
	assert(intToChar.size() == 7);
	assert(intToChar[7] == 'g');
	assert(intToChar.in(7));
	assert(intToChar.insert(8,'h'));
	assert(intToChar.insert(9,'i'));
	assert(intToChar.insert(10,'j'));
	assert(intToChar.insert(11,'k'));
	assert(intToChar.insert(12,'l'));

	assert(intToChar.size() == 12);
	assert(intToChar[1] == 'a');
	assert(intToChar[2] == 'b');
	assert(intToChar[3] == 'c');
	assert(intToChar[4] == 'd');
	assert(intToChar[5] == 'e');
	assert(intToChar[6] == 'f');
	assert(intToChar[7] == 'g');
	assert(intToChar[8] == 'h');
	assert(intToChar[9] == 'i');
	assert(intToChar[10] == 'j');
	assert(intToChar[11] == 'k');
	assert(intToChar[12] == 'l');

	assert(intToChar.in(1));
	assert(intToChar.in(2));
	assert(intToChar.in(3));
	assert(intToChar.in(4));
	assert(intToChar.in(5));
	assert(intToChar.in(6));
	assert(intToChar.in(7));
	assert(intToChar.in(8));
	assert(intToChar.in(9));
	assert(intToChar.in(10));
	assert(intToChar.in(11));
	assert(intToChar.in(12));
	
	assert(intToChar.insert(13,'a'));
	assert(intToChar.insert(14,'b'));
	assert(intToChar.insert(15,'c'));

	assert(intToChar.in(13));
	assert(intToChar.in(14));
	assert(intToChar.in(15));
	assert(intToChar[13] == 'a');
	assert(intToChar[14] == 'b');
	assert(intToChar[15] == 'c');
	assert(intToChar[1] == 'a');
	assert(intToChar[2] == 'b');
	assert(intToChar[3] == 'c');

}

void testBracketOperator()
{
	// Try insertint an item into the map.
	LCHashMap<int, char, IntHash, IntEquator> intToChar;
	intToChar[5] = 'a';
	assert(intToChar[5] == 'a');
	assert(intToChar.size() == 1);

	// Try changing the value of an already inserted item.
	intToChar[5] = 'b';
	assert(intToChar[5] == 'b');
	assert(intToChar.size() == 1);
}

void testErase()
{
	// Test erase on an empty map
	LCHashMap<int, char, IntHash, IntEquator> intToChar;
	assert(!intToChar.erase(5));
	assert(intToChar.size() == 0);
	assert(intToChar.empty());

	// Test erase on a map with one item.
	assert(intToChar.insert(5,'a'));
	assert(intToChar.size() == 1);
	assert(!intToChar.empty());
	assert(intToChar.in(5));
	assert(intToChar.erase(5));
	assert(!intToChar.in(5));
	assert(intToChar.size() == 0);
	assert(intToChar.empty());

	// Try eraseing an item that has already been erased.
	assert(!intToChar.erase(5));
	assert(intToChar.size() == 0);
	assert(intToChar.empty());
	assert(!intToChar.in(5));
}

void testIn()
{
	// Test in on an empty map.
	LCHashMap<int, char, IntHash, IntEquator> intToChar;
	assert(!intToChar.in(0));
}

void testDefaultConstructor()
{
	// Make sure the default constructor worked.
	LCHashMap<int, char, IntHash, IntEquator> intToChar;
	assert(intToChar.size() == 0);
	assert(intToChar.empty());
}

void testInsert()
{
	// Create hash map and test default constructor.
	LCHashMap<int, char, IntHash, IntEquator> intToChar;
	assert(intToChar.size() == 0);
	assert(intToChar.empty());

	// Insert vlaue into hash map.
	assert(intToChar.insert(5, 'a'));
	assert(intToChar.size() == 1);
	assert(!intToChar.empty());
	assert(intToChar.in(5));

	// Try it again with another value.
	assert(intToChar.insert(6,'b'));
	assert(intToChar.size() == 2);
	assert(!intToChar.empty());
	assert(intToChar.in(6));

	// Try it with a key already in the map
	assert(!intToChar.insert(5,'c'));
	assert(intToChar.size() == 2);
	assert(!intToChar.empty());
	assert(intToChar.in(5));
}
