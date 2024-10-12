/***********************************************************************
 * Header File:
 *    SPACE
 * Author:
 *    Ethen Campbell & Joseph Gyman
 * Summary:
 *    The space
 ************************************************************************/

#pragma once

#include "piece.h"
#include "position.h"

class TestSpace;

 /***************************************************
  * SPACES
  * A space is a trivial piece
  ***************************************************/
class Space : public Piece
{
   friend TestSpace;
public:
   Space(int c, int r) : Piece(9, 9), position(c, r) { }
   ~Space()                            {               }
   PieceType getType()           const { return SPACE; }
   void display(ogstream* pgout) const {               }
   Position position;
};