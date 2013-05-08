#include <string.h>
#include <iostream>

#include "game.h"
#include "math.h"

using namespace std;

game::game()
{
    currentPlayer = PLAYER1;
    
    numMoves = 0;
    entryString = new char[ENTRYMAX];
    
    srand(time(NULL));
}

game::game(const game &other)
{
    gameBoard = other.gameBoard;
    currentPlayer = other.currentPlayer;
    numMoves = other.numMoves;
    entryString = new char[ENTRYMAX];
    strcpy(entryString, other.entryString);
}

game::~game()
{
   delete entryString;
}

game& game::operator = (const game &other)
{
    gameBoard = other.gameBoard;
    strcpy(entryString, other.entryString);
    currentPlayer = other.currentPlayer;
    numMoves = other.numMoves;
    
    return *this;
}
        
bool game::splitUpMove(char *entry, move &theMove)
{
    // the user has entered a move - eg a1x
    // split this up and update the move object
    // return true/false if well formed move or not

    if (entry == NULL) return false;
    if (strlen(entry) != 3) return false;
    
    theMove.x = entry[0] - 'a';
    theMove.y = entry[1] - '0';
    if (!gameBoard.insideBoardBoundaries(theMove.x, theMove.y)) return false;   
    
    if (entry[2] == 'x') theMove.pieceType = CROSS;
    else if (entry[2] == '+') theMove.pieceType = PLUS;
    else return false;
    
    return true;
}

char* game::getMove()
{
    // ask the user to enter a move
    if (currentPlayer == PLAYER1)
        cout << "\n" << numMoves << ". Next move, Player 1 () to play : ";
    else
        cout << "\n" << numMoves << ". Next move, Player 2 <> to play : ";
      
    cin.getline(entryString, ENTRYMAX);
    
    return entryString;
}
    
void game::printMenu()
{
    cout << "\nINSTRUCTIONS\n";
    cout << "m   : print this menu\n";
    cout << "q   : quit\n";
    cout << "a2+ : add a plus piece to location a2\n";
    cout << "\n";
}

void game::printBoard()
{
    gameBoard.printBoard();
}

void game::printWinner()
{
    // print the results of the game
    int scorePlayer1 = gameBoard.player1Score();
    int scorePlayer2 = gameBoard.player2Score();
    
    if (scorePlayer1 > scorePlayer2)
    {
        cout << "\nPlayer 1 has won with a score of " 
            << scorePlayer1 << " to " << scorePlayer2 << "\n";
    }
    else if (scorePlayer2 > scorePlayer1)
    {
        cout << "\nPlayer 2 has won with a score of " 
            << scorePlayer2 << " to " << scorePlayer1<< "\n";
    }
    else
    {
        cout << "\nIt's a draw with a score of " 
            << scorePlayer1 << " each\n";
    }
}

void game::nextMove()
{
    // ask the user to enter a move, validate the move and, if valid, run it
    bool validMove = true;
    move theMove;
    
    char* entry = getMove();

    if (entry[0] == 'q' && entry[1] == '\0') 
    {
        // the player has entered the quit commmand
        exit(0);
    }
    else if (entry[0] == 'm' && entry[1] == '\0')
    {
        // the player has entered the print menu command
        printMenu();
    }
    else 
    {
        // the player has possibly entered a move instruction
        validMove = splitUpMove(entry, theMove);
    
        if (validMove)
        {
            // a properly formated move instruction has been entered
            // now try and run it
            validMove = gameBoard.placePiece(currentPlayer, theMove);
        }
        
        if (validMove)
        {
            // a properly formated, legal move was entered
            gameBoard.printBoard();
            gameBoard.printScore();
            
            // swap the current player and update moves
            currentPlayer.swapPlayer();
            numMoves++;
        }
        else
        {
            cout << "Invalid move entered\n";
        }
    }
}

bool game::ended()
{
    return gameBoard.numEmptySquares() == 0;
}
