#include <cassert>
#include <cmath>
#include <cstring>
#include "gameBoard.h"

//#ifdef UNITTEST
#include <iostream>
//#endif

using namespace std;

GameBoard::GameBoard() :
board(makeInitialSetup()),
possibleMoves(determinePossibleMoves(this->board))
{}

/*GameBoard::GameBoard(const GameBoard &gameBoard) :
board(const_cast<const GameBoard::BoardSpace**>(
		copyBoard(gameBoard.board))),
possibleMoves(gameBoard.possibleMoves)
{
cout << "Copy Constructor: " << board << endl;
}

GameBoard::~GameBoard()
{
cout << "Destructor: " << board << endl;
	for(unsigned int j = 0; j < boardLength; j++)
		delete [] board[j];
	delete [] board;
}*/

//===============================================

unsigned int GameBoard::getPossibleNumberOfMoves()
{
	return possibleMoves.size();
}

bool GameBoard::isGameWon()
{
	unsigned int numberOfOccupiedSpaces = 0;
	
	for(unsigned int j = 0; j < board.size(); j++)
		for(unsigned int k = 0; k < board[j].size(); k++)
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

/*GameBoard& GameBoard::operator=(const GameBoard &gameBoard)
{
	BoardSpace **clonerBoard = const_cast<BoardSpace**>(board);
	
	for(unsigned int j = 0; j < boardLength; j++)
		memcpy(clonerBoard[j], gameBoard.board[j],
				sizeof(BoardSpace) * boardLength);
	
	possibleMoves = determinePossibleMoves(board);
	
	return *this;
}*/

ostream& operator<<(ostream &sout, const GameBoard gameBoard)
{
cout << "Aardvark" << endl;
	for(unsigned int y = 0; y < gameBoard.board.size(); y++)
	{
		for(unsigned int x = 0; x < gameBoard.board[y].size(); x++)
		{
			switch(gameBoard.board[x][y])
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

bool playGame(GameBoard gameBoard, ostream &sout)
{
cout << "Play Game" << endl;
	if(gameBoard.isGameWon())
		return true;
	
cout << 1 << endl;
	const unsigned int numberOfMoves =
			gameBoard.getPossibleNumberOfMoves();
	
cout << 2 << endl;
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
{
cout << "Specifying Constructor: " << endl;
}

GameBoard::BoardMatrix GameBoard::makeInitialSetup()
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
	
	BoardMatrix board;
	
	board.resize(boardLength);
	for(unsigned int j = 0; j < board.size(); j++)
	{
		board[j].resize(boardLength);
		
		for(unsigned int k = 0; k < board[j].size(); k++)
			switch(j)
			{
			case 0:
			case 6:
				board[j][k] = r3[k];
				break;
			case 1:
			case 5:
				board[j][k] = r5[k];
				break;
			case 2:
			case 4:
				board[j][k] = r7[k];
				break;
			case 3:
				board[j][k] = rCenter[k];
				break;
			default:
				assert(0);
			}
	}
	
	return board;
}

/*GameBoard::BoardMatrix GameBoard::copyBoard(
		const BoardMatrix board)
{
	BoardSpace **newBoard = new BoardSpace*[boardLength];
	
	for(unsigned int j = 0; j < boardLength; j++)
	{
		newBoard[j] = new BoardSpace[boardLength];
		memcpy(newBoard[j], board[j],
				sizeof(BoardSpace) * boardLength);
	}
	
	return newBoard;
}*/

vector<GameBoard::Move> GameBoard::determinePossibleMoves(
		const GameBoard::BoardMatrix board)
{
//cout << "Come and feed us" << endl;
	vector<Move> moves;
	
	for(unsigned int y = 0; y < board.size(); y++)
		for(unsigned int x = 0; x < board[y].size(); x++)
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
	
//cout << "Never going to bring me down" << endl;
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
cout << "Laura" << endl;
	GameBoard::BoardMatrix board =
			GameBoard::makeInitialSetup();
	
cout << "Wendy" << endl;
	for(unsigned int j = 0; j < GameBoard::boardLength; j++)
		for(unsigned int k = 0; k < GameBoard::boardLength; k++)
			if(board[j][k] == GameBoard::OCCUPIED)
				board[j][k] = GameBoard::EMPTY;
	
	board[2][0] = GameBoard::OCCUPIED;
	board[2][1] = GameBoard::OCCUPIED;
	board[3][2] = GameBoard::OCCUPIED;
	
cout << "Delphinium" << endl;
	GameBoard gameBoard(board);
cout << "Alexa" << endl;
	
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
