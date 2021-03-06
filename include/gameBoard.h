#pragma once

#include <cstdint>
#include <ostream>
#include <vector>

class GameBoard
{
public:
	
	GameBoard();
	
	//======
	
	unsigned int getPossibleNumberOfMoves();
	
	bool isGameWon();
	
	GameBoard makeMove(unsigned int moveNumber);
	
	//======
	
	friend
	std::ostream& operator<<(std::ostream &sout,
			const GameBoard gameBoard);
	
protected:
	
	enum class BoardSpace : uint8_t
	{
		DOES_NOT_EXIST,
		OCCUPIED,
		EMPTY
	};
	
	typedef std::vector< std::vector<BoardSpace> > BoardMatrix;
	
	struct Move
	{
		const unsigned int xFrom, yFrom;
		const unsigned int xTo,   yTo;
	};
	
	//======
	
	static const unsigned int boardLength = 7;
	
	const BoardMatrix board;
	
	const std::vector<Move> possibleMoves;
	
	//======
	
	GameBoard(const BoardMatrix board);
	
	static
	BoardMatrix makeInitialSetup();
	
	static
	std::vector<Move> determinePossibleMoves(
			const BoardMatrix board);
	
	static
	BoardMatrix makeMove(const BoardMatrix startingPositions,
			const Move move);
	
	//======
	
public:
	
	#ifdef UNITTEST
	friend
	GameBoard makeUnitTestBoard();
	#endif
};

/**
Recursively tries all possible moves until a
winning set of moves is on the stack.  When the
stack is collapsed, it will print out the winning
strategy (in reverse) to the console.

Params:
gameBoard= A GameBoard set to whatever positions
will be evaluated in this recursive iteration.
This will either be the return from the default
constructor or from the makeMove function.

Returns: 'true' if a winning strategy has
occurred, 'false' if all recursive possibilities
were tried and no winning strategy was stumbled
upon.
*/
bool playGame(GameBoard gameBoard, std::ostream &sout);
