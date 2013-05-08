#ifndef _BOARD_H
#define _BOARD_H

#include "piece.h"
#include "move.h"

// maximum size of board side
const int MAXWIDTH = 6;
const int MAXHEIGHT = 4;
        
class board
{
    // the board object manages the board. 
    // Particularly, which pieces are on each square

    private:
        
        // the array that hold the board square and which pieces are on it
        piece* squares[MAXHEIGHT][MAXWIDTH];
        
        void setupBoard();
        void clear();
        
		// private methods for printing sections of the board
        void printRow(int y);        
        void printMiddleLine();      
        void printOuterLine();      
        void printBottomLine();
        
        piece* getPiece(int x, int y);
        bool connectsToPiece(int px, int py, int cx, int cy);
        bool threePlusPlayerConnect(Player player, int x, int y);
        
        int getBestMoveForSquare(Player player, int px, int py, move &bestMove, int playDepth);
        
    public:

        board();
        board(const board &other);
        ~board();
		
        void printBoard();
        void printScore();
		
        bool placePiece(Player player, move theMove);
        static bool insideBoardBoundaries(int x, int y);
        bool legalMove(move theMove);
        bool checkForCapture(Player player, int x, int y);
        
        Player getPiecePlayer(int x, int y);
        bool squareEmpty(int x, int y);
        PieceType getPieceType(int x, int y);
    
        int player1Score();
        int player2Score();
        int playerScore(Player player);
        int currentScore(Player player);
        
        int numEmptySquares();
        
        int evaluateNextMove(Player player, move &nextMove, int playDepth);
        
        board& operator = (const board &other);
};

#endif

