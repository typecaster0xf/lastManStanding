#include <ostream>
#include <vector>

class GameBoard
{
	GameBoard();
	
	//======
	
	unsigned int getPossibleMoves();
	
	bool isGameWon();
	
	GameBoard makeMove(unsigned int moveNumber);
	
	friend
	std::ostream& operator<<(ostream&, const GameBoard gameBoard);
	
protected:
	
	enum BoardSpace
	{
		DOES_NOT_EXIST,
		OCCUPIED,
		EMPTY
	};
	
	struct Move
	{
		const unsigned int xFrom, yFrom;
		const unsigned int xTo,   yTo;
	};
	
	//======
	
	GameBoard(BoardSpace **board);
	
	const BoardSpace **board;
	
	const std::vector<Move> possibleMoves;
};
