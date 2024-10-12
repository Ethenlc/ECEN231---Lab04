/***********************************************************************
 * Header File:
 *    KNIGHT
 * Author:
 *    <your name here>
 * Summary:
 *    The KNIGHT class representing the knight piece in chess
 ************************************************************************/

#pragma once

#include "piece.h"

/***************************************************
 * KNIGHT
 * The knight piece, also known as the "Horse".
 ***************************************************/
class Knight : public Piece
{
public:
    // Constructor initializing the knight with a given position and color.
    Knight(const Position& pos, bool isWhite) 
        : Piece(pos, isWhite) { } // Initialize with arbitrary values for movement

    // Constructor initializing the knight with coordinates and color.
    Knight(int c, int r, bool isWhite) 
        : Piece(c, r, isWhite) { } // Initialize with arbitrary values for movement

    // Destructor
    ~Knight() { }

    // Returns the type of the piece as KNIGHT
    PieceType getType() const { return KNIGHT; }

    // Generates possible moves for the knight and adds them to the set
    void getMoves(set<Move>& moves, const Board& board) const;

    // Displays the knight on the board
    void display(ogstream* pgout) const;
};
