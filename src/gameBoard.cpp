#include <cassert>
#include <cmath>
#include <cstring>
#include "gameBoard.h"

#ifdef UNITTEST
#include <iostream>
#endif

using namespace std;

GameBoard::GameBoard() :
board(makeInitialSetup()),
possibleMoves(determinePossibleMoves(this->board))
{}

//===============================================

unsigned int GameBoard::getPossibleNumberOfMoves()
{
	return possibleMoves.size();
}

bool GameBoard::isGameWon()
{
	unsigned int numberOfOccupiedSpaces = 0;
	
	for(auto& row; board)
		for(auto& cell; row)
			if(cell == BoardSpace::OCCUPIED)
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

ostream& operator<<(ostream &sout, const GameBoard gameBoard)
{
	for(unsigned int y = 0; y < gameBoard.board.size(); y++)
	{
		for(unsigned int x = 0; x < gameBoard.board[y].size(); x++)
		{
			switch(gameBoard.board[x][y])
			{
			case GameBoard::BoardSpace::DOES_NOT_EXIST:
				sout << ' ';
				break;
			case GameBoard::BoardSpace::EMPTY:
				sout << '_';
				break;
			case GameBoard::BoardSpace::OCCUPIED:
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

bool playGame(GameBoard gameBoard, ostream &sout)
{
	if(gameBoard.isGameWon())
	{
		sout << gameBoard <<
				"=========================================\n";
		return true;
	}
	
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

GameBoard::GameBoard(GameBoard::BoardMatrix board) :
board(board),
possibleMoves(determinePossibleMoves(this->board))
{}

GameBoard::BoardMatrix GameBoard::makeInitialSetup()
{
	BoardMatrix board;
	
	board.resize(boardLength);
	for(unsigned int j = 0; j < board.size(); j++)
	{
		switch(j)
		{
		case 0:
		case 6:
			board[j] =
			{
				BoardSpace::DOES_NOT_EXIST,
				BoardSpace::DOES_NOT_EXIST,
				BoardSpace::OCCUPIED,
				BoardSpace::OCCUPIED,
				BoardSpace::OCCUPIED,
				BoardSpace::DOES_NOT_EXIST,
				BoardSpace::DOES_NOT_EXIST
			};
			break;
		case 1:
		case 5:
			board[j] =
			{
				BoardSpace::DOES_NOT_EXIST,
				BoardSpace::OCCUPIED,
				BoardSpace::OCCUPIED,
				BoardSpace::OCCUPIED,
				BoardSpace::OCCUPIED,
				BoardSpace::OCCUPIED,
				BoardSpace::DOES_NOT_EXIST
			};
			break;
		case 2:
		case 4:
			board[j] =
			{
				BoardSpace::OCCUPIED,
				BoardSpace::OCCUPIED,
				BoardSpace::OCCUPIED,
				BoardSpace::OCCUPIED,
				BoardSpace::OCCUPIED,
				BoardSpace::OCCUPIED,
				BoardSpace::OCCUPIED
			};
			break;
		case 3:
			board[j] =
			{
				BoardSpace::OCCUPIED,
				BoardSpace::OCCUPIED,
				BoardSpace::OCCUPIED,
				BoardSpace::EMPTY,
				BoardSpace::OCCUPIED,
				BoardSpace::OCCUPIED,
				BoardSpace::OCCUPIED
			};
			break;
		default:
			assert(0);
		}
	}
	
	return board;
}//GameBoard::makeInitialSetup()

vector<GameBoard::Move> GameBoard::determinePossibleMoves(
		const GameBoard::BoardMatrix board)
{
	vector<Move> moves;
	
	for(unsigned int y = 0; y < board.size(); y++)
		for(unsigned int x = 0; x < board[y].size(); x++)
			if(board[x][y] == BoardSpace::OCCUPIED)
			{
				/*Move marble left.*/
				if((x >= 2)
						&& (board[x - 1][y] == BoardSpace::OCCUPIED)
						&& (board[x - 2][y] == BoardSpace::EMPTY))
					moves.push_back({x, y, x - 2, y});
				
				/*Move marble right.*/
				if((x + 2 < boardLength)
						&& (board[x + 1][y] == BoardSpace::OCCUPIED)
						&& (board[x + 2][y] == BoardSpace::EMPTY))
					moves.push_back({x, y, x + 2, y});
				
				/*Move marble down.*/
				if((y >= 2)
						&& (board[x][y - 1] == BoardSpace::OCCUPIED)
						&& (board[x][y - 2] == BoardSpace::EMPTY))
					moves.push_back({x, y, x, y - 2});
				
				/*Move marble up.*/
				if((y + 2 < boardLength)
						&& (board[x][y + 1] == BoardSpace::OCCUPIED)
						&& (board[x][y + 2] == BoardSpace::EMPTY))
					moves.push_back({x, y, x, y + 2});
			}
	
	return moves;
}

GameBoard::BoardMatrix GameBoard::makeMove(
		const GameBoard::BoardMatrix startingPositions,
		const GameBoard::Move move)
{
	BoardMatrix board(startingPositions);
	
	assert(move.xFrom < boardLength);
	assert(move.yFrom < boardLength);
	assert(move.xTo   < boardLength);
	assert(move.yTo   < boardLength);
	
	assert(board[move.xFrom][move.yFrom] == BoardSpace::OCCUPIED);
	board[move.xFrom][move.yFrom] = BoardSpace::EMPTY;
	
	assert(board[move.xTo][move.yTo] == BoardSpace::EMPTY);
	board[move.xTo][move.yTo] = BoardSpace::OCCUPIED;
	
	assert((move.xFrom == move.xTo)
			|| (move.yFrom == move.yTo));
	if(move.xFrom == move.xTo)
	{
		const unsigned int midPoint =
				min(move.yFrom, move.yTo) + 1;
		
		assert(midPoint + 1 == max(move.yFrom, move.yTo));
		assert(board[move.xFrom][midPoint] == BoardSpace::OCCUPIED);
		
		board[move.xFrom][midPoint] = BoardSpace::EMPTY;
	}else
	{
		assert(move.yFrom == move.yTo);
		
		const unsigned int midPoint =
				min(move.xFrom, move.xTo) + 1;
		
		assert(midPoint + 1 == max(move.xFrom, move.xTo));
		assert(board[midPoint][move.yFrom] == BoardSpace::OCCUPIED);
		
		board[midPoint][move.yFrom] = BoardSpace::EMPTY;
	}
	
	return board;
}//GameBoard::makeMove

#ifdef UNITTEST
GameBoard makeUnitTestBoard()
{
	GameBoard::BoardMatrix board =
			GameBoard::makeInitialSetup();
	
	for(unsigned int j = 0; j < GameBoard::boardLength; j++)
		for(unsigned int k = 0; k < GameBoard::boardLength; k++)
			if(board[j][k] == GameBoard::BoardSpace::OCCUPIED)
				board[j][k] = GameBoard::BoardSpace::EMPTY;
	
	board[2][0] = GameBoard::BoardSpace::OCCUPIED;
	board[2][1] = GameBoard::BoardSpace::OCCUPIED;
	board[3][2] = GameBoard::BoardSpace::OCCUPIED;
	
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
