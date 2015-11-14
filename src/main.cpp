#include <iostream>
#include "gameBoard.h"

using namespace std;

bool playGame(GameBoard gameBoard);

int main()
{
	playGame(GameBoard());
	return 0;
}

bool playGame(GameBoard gameBoard)
{
	if(gameBoard.isGameWon())
		return true;
	
	const unsigned int numberOfMoves =
			gameBoard.getPossibleNumberOfMoves();
	
	if(numberOfMoves == 0)
		return false;
	
	for(unsigned int j = 0; j < numberOfMoves; j++)
		if(playGame(gameBoard.makeMove(j)))
		{
			cout << gameBoard <<
					"=========================================\n";
			return true;
		}
	
	return false;
}
