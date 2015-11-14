#pragma once

#include <ostream>
#include <vector>

class GameBoard
{
public:
	
	GameBoard();
	~GameBoard();
	
	//======
	
	unsigned int getPossibleNumberOfMoves();
	
	bool isGameWon();
	
	GameBoard makeMove(unsigned int moveNumber);
	
	friend
	std::ostream& operator<<(std::ostream& sout,
			const GameBoard gameBoard);
	
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
	
	static const unsigned int boardLength = 7;
	
	const BoardSpace **board;
	
	const std::vector<Move> possibleMoves;
	
	//======
	
	GameBoard(BoardSpace** board);
	
	static
	BoardSpace** makeInitialSetup();
	
	static
	std::vector<Move> determinePossibleMoves(
			const BoardSpace** board);
	
	static
	BoardSpace** makeMove(const BoardSpace** startingPositions,
			const Move move);
	
	//======
	
	static
	void printRow(std::ostream& sout, const BoardSpace* row,
			const unsigned int rowLength);
};
