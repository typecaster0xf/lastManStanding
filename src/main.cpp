#include <iostream>
#include "gameBoard.h"

using namespace std;

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
bool playGame(GameBoard gameBoard);

//===============================================

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
	
	for(unsigned int j = 0; j < numberOfMoves; j++)
		if(playGame(gameBoard.makeMove(j)))
		{/*Print put the game board at this level
		in the stack to represent this move to
		the user.*/
			
			cout << gameBoard <<
					"=========================================\n";
			return true;
		}
	
	return false;
}
