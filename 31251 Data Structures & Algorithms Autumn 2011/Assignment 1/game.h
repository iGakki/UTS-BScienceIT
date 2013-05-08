#ifndef _GAME_H
#define _GAME_H

// forward declarations
class board;
class piece;

#include <time.h>

#include "move.h"
#include "piece.h"
#include "player.h"
#include "board.h"

// maximum number of chars player can enter at keyboard
const int ENTRYMAX = 4;

class game
{
    // the game object manages the game of connections.
    // the moves, who wins/loses, etc

    private:
        board gameBoard;
        Player currentPlayer;
        int numMoves;
        char* entryString;
        
        bool splitUpMove(char *entry, move &theMove);
        char* getMove();
        
    public:
        game();
        game(const game &other);
        ~game();
        
        void printBoard();
        
        void printWinner();
        
        void printMenu();
        
        void nextMove();
        
        bool ended();
        
        game& operator = (const game &other);
};

#endif
