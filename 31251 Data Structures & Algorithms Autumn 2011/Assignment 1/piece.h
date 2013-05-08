#ifndef _PIECE_H
#define _PIECE_H

// enumerated cosntants for pieces, including NOPIECE for noPiece type
enum PieceType 
{ 
    NOPIECE = 0,
    CROSS = 1, 
    PLUS = 2
};

#include "move.h"
#include "point.h"
#include "player.h"

/*********************************************************\
   WARNING
    This code makes use of polymorphism and inheritance.
    Do NOT use such concepts in assignments 2 and 3.
   WARNING
\*********************************************************/
   
// these objects manage the base piece class and the derived pieces of 
// cross and plus

class piece
{
   // you cannot create a piece. Instead, you create derived objects such as crosses, etc
   // which are pieces.

   protected:
      Player player;
      
   public:
      piece();
      piece(Player p);
      virtual ~piece();
      
      // pure virtual functions
      virtual PieceType getPieceType() = 0;      
      virtual const char* getPieceChar() = 0;
      virtual piece* clone() = 0;
      virtual void getConnectPoints(int x, int y, point pts[]) = 0;
      virtual bool connectsToPiece(int px, int py, int cx, int cy) = 0;
      
      Player getPiecePlayer() { return player; }
      void setPiecePlayer(Player p);
      
      // questions about the type of piece
      bool isCross() { return getPieceType() == CROSS; } 
      bool isPlus() { return getPieceType() == PLUS; } 
      bool isNoPiece() { return getPieceType() == NOPIECE; }
};

class crossPiece : public piece //------------------------------
{
   public :
      crossPiece(Player p) : piece (p)
      {
      }
        
      inline PieceType getPieceType()
      {
         return CROSS;
      }
		
      const char* getPieceChar();
      void getConnectPoints(int x, int y, point pts[]);
      bool connectsToPiece(int px, int py, int cx, int cy);

      piece* clone()
      {
         return new crossPiece(player);
      }
};

class plusPiece : public piece //------------------------------
{
   public:
      plusPiece(Player player) : piece (player)
      {
      }
      
      const char* getPieceChar();
      void getConnectPoints(int x, int y, point pts[]);
      bool connectsToPiece(int px, int py, int cx, int cy);
      
      inline PieceType getPieceType()
      {
         return PLUS;
      }

      piece* clone()
      {
         return new plusPiece(player);
      }
};

class noPiece : public piece //------------------------------
{
   // The piece you are having when you are not having a piece. 
   // This is a pattern object that simplifies some of our code
   
   public:
      noPiece() : piece(NOPLAYER)
      {
      }
      
      inline const char* getPieceChar()
      {
         return "   ";
      }   
      
      inline PieceType getPieceType()
      {
         return NOPIECE;
      } 

      piece* clone()
      {
         return new noPiece();
      }
      
      void getConnectPoints(int x, int y, point pts[]);
      bool connectsToPiece(int px, int py, int cx, int cy)
      {
         return false;
      }
};

#endif

