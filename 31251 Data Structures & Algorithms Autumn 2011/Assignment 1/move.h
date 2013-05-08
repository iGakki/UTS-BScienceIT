#ifndef _MOVE_H
#define _MOVE_H

#include <stdlib.h>

#include "piece.h"
#include "point.h"

struct move : public point
{
    // struct to store coordinates for moving a piece into a square
    
    PieceType pieceType;
    
    move() : point(-1, -1), pieceType(NOPIECE)
    {
    }
    
    move(int xx, int yy, PieceType pt) 
        : point(xx, yy), pieceType(pt)
    {
        
    }
    
    void setMove(int xx, int yy, PieceType pt)
    {
        x = xx;
        y = yy;
        pieceType = pt;
    }
    
    char* getString(char *theMove)
    {
        // given the char array theMove, add the typed move to it and then return it
        theMove[0] = 'a' + x;
        theMove[1] = '0' + y;
        if (pieceType == CROSS) theMove[2] = 'x';
        else theMove[2] = '+';
        theMove[3] = '\0';
        
        return theMove;
    }
};

#endif
