
#include <iostream>
#include <string>

#include "game.h"

// code =====================================================

int main(int argc, char *argv[])
{
    game theGame;
    
    theGame.printMenu();
    theGame.printBoard();
    
    while (!theGame.ended())
    {
	   theGame.nextMove();
    }
    theGame.printWinner();
    
    return 0;
}
