#include <cassert>
#include <cmath>
#include <cstring>
#include "gameBoard.h"

#ifdef UNITTEST
#include <iostream>
#endif

using namespace std;

GameBoard::GameBoard() :
board(const_cast<const GameBoard::BoardSpace**>(
		makeInitialSetup())),
possibleMoves(determinePossibleMoves(this->board))
{}

GameBoard::GameBoard(const GameBoard &gameBoard) :
board(const_cast<const GameBoard::BoardSpace**>(
		copyBoard(gameBoard.board))),
possibleMoves(gameBoard.possibleMoves)
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
	{
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
			
			sout << ' ';
		}
			
		sout << '\n';
	}
	
	return sout;
}

bool playGame(GameBoard gameBoard, ostream& sout)
{
	if(gameBoard.isGameWon())
		return true;
	
	const unsigned int numberOfMoves =
			gameBoard.getPossibleNumberOfMoves();
	
	for(unsigned int j = 0; j < numberOfMoves; j++)
		if(playGame(gameBoard.makeMove(j), sout))
		{/*Print put the game board at this level
		in the stack to represent this move to
		the user.*/
			
			sout << gameBoard <<
					"=========================================\n";
			return true;
		}
	
	return false;
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

GameBoard::BoardSpace** GameBoard::copyBoard(
		const BoardSpace** board)
{
	BoardSpace **newBoard = new BoardSpace*[boardLength];
	
	for(unsigned int j = 0; j < boardLength; j++)
	{
		newBoard[j] = new BoardSpace[boardLength];
		memcpy(newBoard[j], board[j],
				sizeof(BoardSpace) * boardLength);
	}
	
	return newBoard;
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
		const unsigned int midPoint =
				min(move.yFrom, move.yTo) + 1;
		
		assert(midPoint + 1 == max(move.yFrom, move.yTo));
		assert(board[move.xFrom][midPoint] == OCCUPIED);
		
		board[move.xFrom][midPoint] = EMPTY;
	}else
	{
		assert(move.yFrom == move.yTo);
		
		const unsigned int midPoint =
				min(move.xFrom, move.xTo) + 1;
		
		assert(midPoint + 1 == max(move.xFrom, move.xTo));
		assert(board[midPoint][move.yFrom] == OCCUPIED);
		
		board[midPoint][move.yFrom] = EMPTY;
	}
	
	return board;
}//GameBoard::makeMove

#ifdef UNITTEST
GameBoard makeUnitTestBoard()
{
	GameBoard::BoardSpace **board =
			GameBoard::makeInitialSetup();
	
	for(unsigned int j = 0; j < GameBoard::boardLength; j++)
		for(unsigned int k = 0; k < GameBoard::boardLength; k++)
			if(board[j][k] == GameBoard::OCCUPIED)
				board[j][k] = GameBoard::EMPTY;
	
	board[2][0] = GameBoard::OCCUPIED;
	board[2][1] = GameBoard::OCCUPIED;
	board[3][2] = GameBoard::OCCUPIED;
	
	GameBoard gameBoard(board);
	
	cout << "Initial board setup:\n" << gameBoard
			<< "\n\n\n\n";
	
	return GameBoard(board);
}
#endif

//===============================================

#ifdef UNITTEST
int main()
{
	const bool endValue = playGame(makeUnitTestBoard(), cout);
	
	cout << "Ending value: " << endValue << endl;
	
	return 0;
}
#endif
