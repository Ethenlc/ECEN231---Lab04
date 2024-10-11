/***********************************************************************
 * Source File:
 *    PIECE 
 * Author:
 *    Ethen Campbell & Joseph Gyman
 * Summary:
 *    The Piece base class and all the derived classes:
 *       SPACE, KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN
 ************************************************************************/

#include "position.h"  // for POSITION
#include "piece.h"     // for all the PIECE class definitions
#include "pieceSpace.h"
#include "pieceKnight.h"
#include "board.h"     // for BOARD
#include "uiDraw.h"    // for draw*()
#include <cassert>     // because we are paranoid
using namespace std;


/************************************************
 * PIECE : ASSIGN
 ***********************************************/
const Piece & Piece::operator = (const Piece & rhs)
{
	if (this != &rhs)
	{
		this->position = rhs.position;  // Copy the position.
		this->fWhite = rhs.fWhite;		// Copy the color.
		this->nMoves = rhs.nMoves;		// Copy the move count.
		this->lastMove = rhs.lastMove;  // Copy the last move.
	}
	return *this;
}

/************************************************
 * PIECE : GET MOVES
 * Iterate through the moves decorator to allow a piece to move
 ***********************************************/
void Piece::getMoves(set <Move> & movesSet, const Board & board) const
{

}

