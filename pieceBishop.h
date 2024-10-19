/***********************************************************************
 * Header File:
 *    BISHOP
 * Author:
 *    <your name here>
 * Summary:
 *    The BISHOP class
 ************************************************************************/

#pragma once
#include "piece.h"

class Bishop : public Piece
{
public:
    Bishop(const Position& pos, bool isWhite) : Piece(pos, isWhite) { }
    Bishop(int c, int r, bool isWhite) : Piece(c, r, isWhite) { }
    ~Bishop() { }
    PieceType getType() const override { return BISHOP; }
    void getMoves(set<Move>& moves, const Board& board) const override;
    void display(ogstream* pgout) const override;

private:
    set<Move> getMovesSlide(const Board& board, const Delta deltas[], int numDelta) const;
};