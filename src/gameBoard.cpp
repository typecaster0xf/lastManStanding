#include <cassert>
#include <cmath>
#include <cstring>
#include "gameBoard.h"

using namespace std;

GameBoard::GameBoard() :
board(const_cast<const GameBoard::BoardSpace**>(
		makeInitialSetup())),
possibleMoves(determinePossibleMoves(this->board))
{}

GameBoard::~GameBoard()
{
	for(unsigned int j = 0; j < boardLength; j++)
		delete [] board[j];
	delete [] board;
}

//===============================================

unsigned int GameBoard::getPossibleNumberOfMoves()
{
	return possibleMoves.size();
}

bool GameBoard::isGameWon()
{
	unsigned int numberOfOccupiedSpaces = 0;
	
	for(unsigned int j = 0; j < boardLength; j++)
		for(unsigned int k = 0; k < boardLength; k++)
			if(board[j][k] == OCCUPIED)
				numberOfOccupiedSpaces++;
	
	assert(numberOfOccupiedSpaces > 0);
	
	return numberOfOccupiedSpaces == 1;
}

GameBoard GameBoard::makeMove(unsigned int moveNumber)
{
	assert(moveNumber < possibleMoves.size());
	return GameBoard(makeMove(board,
			possibleMoves[moveNumber]));
}

ostream& operator<<(ostream& sout, const GameBoard gameBoard)
{
	for(unsigned int j = 0; j < GameBoard::boardLength; j++)
		for(unsigned int k = 0; k < GameBoard::boardLength; k++)
		{
			switch(gameBoard.board[j][k])
			{
			case GameBoard::DOES_NOT_EXIST:
				sout << ' ';
				break;
			case GameBoard::EMPTY:
				sout << '_';
				break;
			case GameBoard::OCCUPIED:
				sout << '0';
				break;
			default:
				assert(false);
			}
			
			sout << '\n';
		}
		/*switch(j)
		{
		case 0:
		case 6:
			GameBoard::printRow(sout, gameBoard.board[j], 3);
			break;
		case 1:
		case 5:
			GameBoard::printRow(sout, gameBoard.board[j], 5);
			break;
		default:
			GameBoard::printRow(sout, gameBoard.board[j], 7);
		}*/
	
	return sout;
}

//===============================================

GameBoard::GameBoard(GameBoard::BoardSpace** board) :
board(const_cast<const GameBoard::BoardSpace**>(board)),
possibleMoves(determinePossibleMoves(this->board))
{}

GameBoard::BoardSpace** GameBoard::makeInitialSetup()
{
	const BoardSpace r3[boardLength] =
	{
		DOES_NOT_EXIST,
		DOES_NOT_EXIST,
		OCCUPIED,
		OCCUPIED,
		OCCUPIED,
		DOES_NOT_EXIST,
		DOES_NOT_EXIST
	};
	const BoardSpace r5[boardLength] =
	{
		DOES_NOT_EXIST,
		OCCUPIED,
		OCCUPIED,
		OCCUPIED,
		OCCUPIED,
		OCCUPIED,
		DOES_NOT_EXIST
	};
	const BoardSpace r7[boardLength] =
	{
		OCCUPIED,
		OCCUPIED,
		OCCUPIED,
		OCCUPIED,
		OCCUPIED,
		OCCUPIED,
		OCCUPIED
	};
	const BoardSpace rCenter[boardLength] =
	{
		OCCUPIED,
		OCCUPIED,
		OCCUPIED,
		EMPTY,
		OCCUPIED,
		OCCUPIED,
		OCCUPIED
	};
	
	BoardSpace **board = new BoardSpace*[boardLength];
	
	for(unsigned int j = 0; j < boardLength; j++)
	{
		board[j] = new BoardSpace[boardLength];
		
		switch(j)
		{
		case 0:
		case 6:
			memcpy(board[j], &r3,
					sizeof(BoardSpace) * boardLength);
			break;
		case 1:
		case 5:
			memcpy(board[j], &r5,
					sizeof(BoardSpace) * boardLength);
			break;
		case 2:
		case 4:
			memcpy(board[j], &r7,
					sizeof(BoardSpace) * boardLength);
			break;
		case 3:
			memcpy(board[j], &rCenter,
					sizeof(BoardSpace) * boardLength);
			break;
		default:
			assert(0);
		}
	}
	
	return board;
}

vector<GameBoard::Move> GameBoard::determinePossibleMoves(
		const GameBoard::BoardSpace** board)
{
	vector<Move> moves;
	
	for(unsigned int x = 0; x < boardLength; x++)
		for(unsigned int y = 0; y < boardLength; y++)
			if(board[x][y] == OCCUPIED)
			{
				/*Move marble left.*/
				if((x >= 2) && (board[x - 1][y] == OCCUPIED)
						&& (board[x - 2][y] == EMPTY))
					moves.push_back({x, y, x - 2, y});
				
				/*Move marble right.*/
				if((x + 2 < boardLength)
						&& (board[x + 1][y] == OCCUPIED)
						&& (board[x + 2][y] == EMPTY))
					moves.push_back({x, y, x + 2, y});
				
				/*Move marble down.*/
				if((y >= 2) && (board[x][y - 1] == OCCUPIED)
						&& (board[x][y - 2] == EMPTY))
					moves.push_back({x, y, x, y - 2});
				
				/*Move marble up.*/
				if((y + 2 < boardLength)
						&& (board[x][y + 1] == OCCUPIED)
						&& (board[x][y + 2] == EMPTY))
					moves.push_back({x, y, x, y + 2});
			}
	
	return moves;
}

GameBoard::BoardSpace** GameBoard::makeMove(
		const GameBoard::BoardSpace** startingPositions,
		const GameBoard::Move move)
{
	BoardSpace** board = new BoardSpace*[boardLength];
	for(unsigned int j = 0; j < boardLength; j++)
	{
		board[j] = new BoardSpace[boardLength];
		memcpy(board[j], startingPositions[j],
				sizeof(BoardSpace) * boardLength);
	}
	
	assert(move.xFrom < boardLength);
	assert(move.yFrom < boardLength);
	assert(move.xTo   < boardLength);
	assert(move.yTo   < boardLength);
	
	assert(board[move.xFrom][move.yFrom] == OCCUPIED);
	board[move.xFrom][move.yFrom] = EMPTY;
	
	assert(board[move.xTo][move.yTo] == EMPTY);
	board[move.xTo][move.yTo] = OCCUPIED;
	
	assert((move.xFrom == move.xTo)
			|| (move.yFrom == move.yTo));
	if(move.xFrom == move.xTo)
	{
		const unsigned int low =
				min(move.yFrom, move.yTo);
		const unsigned int high =
				max(move.yFrom, move.yTo);
		
		assert(low + 2 == high);
		
		assert(board[move.xFrom][low + 1] == OCCUPIED);
		board[move.xFrom][low + 1] = EMPTY;
	}else
	{
		assert(move.yFrom == move.yTo);
		
		const unsigned int low =
				min(move.xFrom, move.xTo);
		const unsigned int high =
				max(move.xFrom, move.xTo);
		
		assert(low + 2 == high);
		
		assert(board[low + 1][move.yFrom] == OCCUPIED);
		board[low + 1][move.yFrom] = EMPTY;
	}
	
	return board;
}

void GameBoard::printRow(ostream& sout,
		const GameBoard::BoardSpace* row,
		const unsigned int rowLength)
{
	assert((rowLength == 3) || (rowLength == 5)
			|| (rowLength == 7));
	
	//for(unsigned int j = 0; j < boardLength
}
