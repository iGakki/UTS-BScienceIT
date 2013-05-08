#include <iostream>
#include <time.h>
#include <stdlib.h>

#include "board.h"
#include "piece.h"
#include "point.h"

using namespace std;

// print functions ========================================

void board::printRow(int y)
{
    // print a row in board showing pieces at each square
    // also print row numbers
    char row = '0' + y;
    
    cout << row << " |";
    for (int x=0; x<MAXWIDTH; x++)
    {
       cout << squares[y][x]->getPieceChar() << "|";
    }
    cout << "\n";
}

void board::printMiddleLine()
{
    // print a ---+--- etc line
    cout << "  |-";
    for (int x=0; x<MAXWIDTH-1; x++)
    {
       cout << "--+-";
    }
    cout << "--|\n";
}

void board::printOuterLine()
{
    // print the top and bottom line of board
    cout << "   -";
    for (int x=0; x<MAXWIDTH-1; x++)
    {
       cout << "----";
    }
    cout << "--\n";
}

void board::printBottomLine()
{
    // bottom part of board with column letters
    cout << "    ";
    for (int x=0; x<MAXWIDTH; x++)
    {
       char digit = 'a' + x;
       cout << digit << "   ";
    }
    cout << "\n";
}
    
void board::printBoard()
{
    // print entire board
    printOuterLine();
    for (int y=0; y<MAXHEIGHT; y++)
    {
        printRow(y);
        if (y < MAXHEIGHT-1) printMiddleLine();
    }
    printOuterLine();
    printBottomLine();
}

void board::printScore()
{
    // print the scores of Player 1 and Player 2
    cout << "Player 1 score = " << player1Score() << " : Player 2 score = " << player2Score() << "\n";
}

   
// board constructors and destructor =============================================   

board::board()
{
    for (int y=0; y<MAXHEIGHT; y++)
    {
        for (int x=0; x<MAXWIDTH; x++)
        {
            squares[y][x] = NULL;
        }
    }
    setupBoard();
}

board::board(const board &other)
{
    // copy constructor
   
    for (int y=0; y<MAXHEIGHT; y++)
    {
        for (int x=0; x<MAXWIDTH; x++)
        {
            squares[y][x] = other.squares[y][x]->clone();
        }
    }
}

board::~board()
{
    // set the entire board to NULL
    clear();
}

board& board::operator = (const board &other)
{
   for (int y=0; y<MAXHEIGHT; y++)
    {
        for (int x=0; x<MAXWIDTH; x++)
        {
            if (squares[y][x] != NULL) delete(squares[y][x]);
            squares[y][x] = other.squares[y][x]->clone();
        }
    }
    
    return *this;
}

void board::setupBoard()
{
    // clean up previous board set up
    clear();
    
    // set middle rows to have no pieces
    for (int y=1; y<MAXHEIGHT-1; y++)
    {
        for (int x=0; x<MAXWIDTH; x++)
        {
            squares[y][x] = new noPiece();
        }
    }
    
    // set up middle of top and bottom rows 
    // (excepting corners of board)
    for (int x=1; x<MAXWIDTH-1; x++) 
    {
       squares[0][x] = new noPiece();
       squares[MAXHEIGHT-1][x] = new noPiece();
    }
    
    // setup Player 1 and Player 2 starting positions
    squares[0][0] = new plusPiece(PLAYER1);
    squares[0][MAXWIDTH-1] = new crossPiece(PLAYER2);
    squares[MAXHEIGHT-1][0] = new plusPiece(PLAYER2);
    squares[MAXHEIGHT-1][MAXWIDTH-1] = new crossPiece(PLAYER1);
}

void board::clear()
{
    // delete all former pieces and set board to NULL
    for (int y=0; y<MAXHEIGHT; y++)
    {
        for (int x=0; x<MAXWIDTH; x++)
        {
            if (squares[y][x] != NULL) delete(squares[y][x]);
            squares[y][x] = NULL;
        }
    }
}

// get functions ====================================================

Player board::getPiecePlayer(int x, int y)
{
    // return player of piece at square x, y
    return squares[y][x]->getPiecePlayer();
}

bool board::squareEmpty(int x, int y)
{
    return (getPiecePlayer(x, y) == NOPLAYER);
}

PieceType board::getPieceType(int x, int y)
{
    // return type of piece at square x, y
    return squares[y][x]->getPieceType();
}

piece* board::getPiece(int x, int y)
{
    return squares[y][x];
}

// move functions ===================================================

bool board::insideBoardBoundaries(int x, int y)
{
    // determine if (x,y) is properly inside the board area
    if (x < 0 || x >= MAXWIDTH) return false;
    if (y < 0 || y >= MAXHEIGHT) return false;
    return true;
}
        
bool board::legalMove(move theMove)
{
    // ckeck that the square to be filled is within the board boundaries
    if (!insideBoardBoundaries(theMove.x, theMove.y)) return false;
    
    // confirm the square to be filled is empty
    return squareEmpty(theMove.x, theMove.y);
}

bool board::placePiece(Player player, move theMove)
{
    // return true if piece is successfully placed
    
    // check for the legality of the move
    if (!legalMove(theMove)) return false;
    
    // remove the current non-piece from the square
    delete squares[theMove.y][theMove.x];
    
    // place the piece in the square
    if (theMove.pieceType == CROSS) 
        squares[theMove.y][theMove.x] = new crossPiece(player);
    else
        squares[theMove.y][theMove.x] = new plusPiece(player);
    
    // see if we have captured an opponents piece
    // keep doing this till no more pieces are captured
    while (checkForCapture(player, theMove.x, theMove.y));
    
    return true;
}

bool board::checkForCapture(Player player, int x, int y)
{
    // determine if the piece placed by the player at (x,y) allows
    // the player to capture any opponents pieces
    // return true if we capture any pieces
    
    int row, col;
    bool captured = false;
    
    // check all the squares surrounding (x,y)
    for (row=y-1; row<=y+1; row++)
    {
        for (col=x-1; col<=x+1; col++)
        {
            if (insideBoardBoundaries(col, row) && 
                getPiecePlayer(col, row) == player.otherPlayer(player))
            {
                // we have a square on the board at (col, row) containing an opponents piece
                if (threePlusPlayerConnect(player, col, row))
                {
                    // the player has at least 3 pieces connecting to the opponents piece
                    // capture the piece
                    getPiece(col, row)->setPiecePlayer(player);
                    captured = true;
                    
                    // see if capturing the piece allows for any more captures
                    // continue doing this till no more pieces are captured
                    while (checkForCapture(player, col, row));
                }
            }
        }
    }
    
    return captured;
}

bool board::connectsToPiece(int px, int py, int cx, int cy)
{
    // does the piece at (px, py) connect to point (cx, cy)
    
    return getPiece(px, py)->connectsToPiece(px, py, cx, cy);
}

bool board::threePlusPlayerConnect(Player player, int x, int y)
{
    // determine if the player has three or more pieces connecting to the square at (x,y)
    
    int row, col, connect=0;
    
    // check all the squares surrounding (x, y)
    for (row=y-1; row<=y+1; row++)
    {
        for (col=x-1; col<=x+1; col++)
        {
            if (insideBoardBoundaries(col, row) &&
                getPiecePlayer(col, row) == player && 
                connectsToPiece(col, row, x, y))
            {
                // the player has a piece at (col, row) and it connects to (x,y)
                connect++;
            }
        }
    }
    
    return (connect >= 3);    
}

// scoring functions ===========================================

int board::player1Score()
{
    // add up the values and connections of all player1 pieces
   return playerScore(PLAYER1);
}

int board::player2Score()
{ 
    // add up the values and connections of all player2 pieces
   return playerScore(PLAYER2);
}

int board::playerScore(Player player)
{
    // add up the values and connections of all player pieces
    int score = 0;
    
    for (int y=0; y<MAXHEIGHT; y++)
    {
        for (int x=0; x<MAXWIDTH; x++) 
        {
            if (getPiecePlayer(x, y) == player) 
            {
               // increment score for the piece
               score++;
               
               // increment score with all connections the piece has
               point pts[4];
               getPiece(x, y)->getConnectPoints(x, y, pts);
               
               for (int p=0; p<4; p++)
               {
                  if (insideBoardBoundaries(pts[p].x, pts[p].y))
                  {
                      if (getPiecePlayer(pts[p].x, pts[p].y) == player) score++;
                  }
               }
               
            }
        }
    }
    return score;
}

int board::currentScore(Player player)
{
    // subtract the opponents score from the players score
	// a +'ve score for the player means they are ahead, other wise they are behind
   return playerScore(player) - playerScore(player.otherPlayer(player)); 
}

int board::numEmptySquares()
{
    // return the number of empty squares
    int num = 0;
        
    for (int y=0; y<MAXHEIGHT; y++)
    {
        for (int x=0; x<MAXWIDTH; x++) 
        {
            if (getPiecePlayer(x, y) == NOPLAYER) num++;
        }
    }
    return num;
}

// game ai ========================================================

int board::evaluateNextMove(Player player, move &nextMove, int playDepth)
{   
    int valueOfMove;
    int bestMoveValue = -1000000000; // any move is going to produce a better value than this
    move goodMove;
    
    for (int y=0; y<MAXHEIGHT; y++)
    {
        for (int x=0; x<MAXWIDTH; x++) 
        {
            if (squareEmpty(x, y))
            {
                valueOfMove = getBestMoveForSquare(player, x, y, goodMove, playDepth);
                if (valueOfMove > bestMoveValue || (valueOfMove == bestMoveValue && rand() % 3 == 0))
                {
                    // we have a better move or randomly pick an equivalent move
                    bestMoveValue = valueOfMove;
                    nextMove = goodMove;
                }
            }
        }
    }
    
    return bestMoveValue;
}

int board::getBestMoveForSquare(Player player, int x, int y, move &theMove, int playDepth)
{   
    // make a copy of the board
    board *boardCopy = new board(*this);
    
    // try placing a CROSS piece at the location
    theMove.setMove(x, y, CROSS);
    boardCopy->placePiece(player, theMove);
    int crossScore = boardCopy->currentScore(player);
    if (playDepth > 0)
    {
        // deduct the opponents counter move
        crossScore -= boardCopy->evaluateNextMove(player.otherPlayer(), theMove, playDepth-1);
    }
    
    // delete board and reset to test PLUS piece
    delete boardCopy;
    boardCopy = new board(*this);
    
    // try placing a PLUS piece at the location
    theMove.setMove(x, y, PLUS);
    boardCopy->placePiece(player, theMove);
    int plusScore = boardCopy->currentScore(player);
    if (playDepth > 0)
    {
        plusScore -= boardCopy->evaluateNextMove(player.otherPlayer(), theMove, playDepth-1);
    }
    
    // clean up copy of board
    delete boardCopy;
    
    // decide which is the better move
    if (crossScore > plusScore || (crossScore == plusScore && rand() % 2 == 0)) 
    {
        theMove.setMove(x, y, CROSS);
        return crossScore;
    }
    else
    {
        theMove.setMove(x, y, PLUS);
        return plusScore;
    }
    
}

