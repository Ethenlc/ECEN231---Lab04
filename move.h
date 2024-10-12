/***********************************************************************
 * Header File:
 *    MOVE
 * Author:
 *    Ethen Campbell & Joseph Gyman
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#pragma once

#include <string>
#include "position.h"  // Every move has two Positions as attributes
#include "pieceType.h" // A piece type

class TestMove; // Forward declaration for test classes
class TestBoard; // Forward declaration for test classes

/***************************************************
 * MOVE
 * Class representing a single move across the chess board.
 ***************************************************/
class Move
{
public:
    enum MoveType { MOVE, ENPASSANT, CASTLE_KING, CASTLE_QUEEN, MOVE_ERROR }; // Different types of moves

    // Friend declarations for test classes
    friend TestMove;
    friend TestBoard;

    // Default constructor
    Move();

    // Constructor to initialize from source and destination Positions and a PieceType.
    Move(const Position& source, const Position& dest, PieceType type)
        : source(source), dest(dest), promote(type), moveType(MOVE), isWhite(true), capture(SPACE) {}

    // Constructor to initialize from a string representation of a move.
    Move(const std::string& moveText);

    // Equality operator for comparing two moves.
    bool operator==(const Move& rhs) const;

    // Less than operator for ordering moves.
    bool operator<(const Move& rhs) const;

    // Convert PieceType to its character representation.
    char letterFromPieceType(PieceType pt) const;

    // Convert character to PieceType.
    PieceType pieceTypeFromLetter(char letter) const;

    // Read a move from a string and initialize its attributes.
    void readFromString(const std::string& moveText);

    // Get the textual representation of the move.
    std::string getText() const;

    // Setters for private members
    void setSource(const Position& pos) { source = pos; }
    void setDest(const Position& pos) { dest = pos; }
    void setIsWhite(bool white) { isWhite = white; }
    void setCapture(PieceType cap) { capture = cap; }

private:
    Position  source;    // Where the move originated from
    Position  dest;      // Where the move finished
    PieceType promote;   // Piece to be promoted to
    PieceType capture;   // Piece captured in this move, if any
    MoveType  moveType;  // The type of move (e.g., normal, en passant, castling)
    bool      isWhite;   // True if it's white's turn, false otherwise
    std::string text;    // Textual representation of the move (for debugging)
};
