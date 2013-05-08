#include <iostream>
#include <string.h>

#include "piece.h"
       
// piece constructors and destructors
       
piece::piece() : player(NOPLAYER)
{
}
        
piece::piece(Player p) : player(p)
{
}

piece::~piece()
{
}

void piece::setPiecePlayer(Player p) 
{ 
    player = p; 
}

// cross functions ===========================================
		
const char* crossPiece::getPieceChar()
{
    if (player.getPlayer() == PLAYER1) return "(x)"; else return "<x>";
}   

void crossPiece::getConnectPoints(int x, int y, point pts[])
{
   pts[0].y = y-1;
   pts[0].x = x-1;
   pts[1].y = y-1;
   pts[1].x = x+1;
   pts[2].y = y+1;
   pts[2].x = x-1;
   pts[3].y = y+1;
   pts[3].x = x+1;
}

bool crossPiece::connectsToPiece(int px, int py, int cx, int cy)
{
    // if the piece is at (px, py) is it connected to (cx, cy)
    
    int ydif = py - cy;
    int xdif = px - cx;
    
    return ((ydif * ydif) * (xdif * xdif) == 1);
}

// plus functions ===========================================
		
const char* plusPiece::getPieceChar()
{
    if (player == PLAYER1) return "(+)"; else return "<+>";
}   

void plusPiece::getConnectPoints(int x, int y, point pts[])
{
   pts[0].y = y;
   pts[0].x = x-1;
   pts[1].y = y-1;
   pts[1].x = x;
   pts[2].y = y;
   pts[2].x = x+1;
   pts[3].y = y+1;
   pts[3].x = x;
}

bool plusPiece::connectsToPiece(int px, int py, int cx, int cy)
{
    // if the piece is at (px, py) is it connected to (cx, cy)
    
    int ydif = py - cy;
    int xdif = px - cx;
    
    return ((ydif * ydif) + (xdif * xdif) == 1);
}

// noPiece functions ===========================================

void noPiece::getConnectPoints(int x, int y, point pts[])
{
   // set connect points to outside the board
   pts[0].y = -1;
   pts[0].x = -1;
   pts[1].y = -1;
   pts[1].x = -1;
   pts[2].y = -1;
   pts[2].x = -1;
   pts[3].y = -1;
   pts[3].x = -1;
}

