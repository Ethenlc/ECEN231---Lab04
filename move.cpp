/***********************************************************************
 * Source File:
 *    MOVE
 * Author:
 *    Ethen Campbell & Joseph Gyman
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#include "move.h"
#include "pieceType.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

/***************************************************
 * MOVE : DEFAULT CONSTRUCTOR
 ***************************************************/
Move::Move()
{
    source.setInvalid();
    dest.setInvalid();
    promote = SPACE;      // Default piece type is SPACE
    capture = SPACE;      // Default capture is no capture (SPACE)
    moveType = MOVE;      // Default move type
    isWhite = true;       // Default isWhite to true
}

/***************************************************
 * MOVE : EQUALITY OPERATOR
 ***************************************************/
bool Move::operator==(const Move& rhs) const
{
    return (this->source == rhs.source &&
        this->dest == rhs.dest &&
        this->promote == rhs.promote &&
        this->capture == rhs.capture &&
        this->moveType == rhs.moveType &&
        this->isWhite == rhs.isWhite);
}

/***************************************************
 * MOVE : LESS THAN OPERATOR FOR COMPARISON
 ***************************************************/
bool Move::operator<(const Move& rhs) const
{
    if (this->source != rhs.source)
        return this->source < rhs.source;
    if (this->dest != rhs.dest)
        return this->dest < rhs.dest;
    // Optionally include other fields like promote, capture, etc.
    return false; // If all are equal, return false
}

/***************************************************
 * MOVE : CONVERT PieceType TO CHAR
 ***************************************************/
char Move::letterFromPieceType(PieceType pt) const
{
    switch (pt)
    {
    case PAWN:   return 'p';
    case BISHOP: return 'b';
    case KNIGHT: return 'n';
    case ROOK:   return 'r';
    case QUEEN:  return 'q';
    case KING:   return 'k';
    case SPACE:  return ' '; // Empty space or no piece
    default:     return '?'; // Error case
    }
}

/***************************************************
 * MOVE : CONVERT CHAR TO PieceType
 ***************************************************/
PieceType Move::pieceTypeFromLetter(char letter) const
{
    switch (letter)
    {
    case 'p': return PAWN;
    case 'b': return BISHOP;
    case 'n': return KNIGHT;
    case 'r': return ROOK;
    case 'q': return QUEEN;
    case 'k': return KING;
    case ' ': return SPACE; // Empty space
    default:  return SPACE;  // Default to SPACE for unrecognized input
    }
}

/***************************************************
 * MOVE : READ FROM STRING
 ***************************************************/
void Move::readFromString(const std::string& moveText)
{
    // Source position ('xx')
    source.set(moveText[0] - 'a', moveText[1] - '1');

    // Destination position ('xx')
    dest.set(moveText[2] - 'a', moveText[3] - '1');

    // Default move type;
    moveType = MOVE;

    // If there is a 5th character, it indicates capture, promotion, or other move
    if (moveText.size() > 4)
    {
        char special = moveText[4];
        switch (special)
        {
        case 'r': // Capture a rook
            capture = ROOK;
            break;
        case 'n': // Capture a knight
            capture = KNIGHT;
            break;
        case 'E': // En passant
            moveType = ENPASSANT;
            break;
        case 'c': // Castling kingside
            moveType = CASTLE_KING;
            break;
        case 'C': // Castling queenside
            moveType = CASTLE_QUEEN;
            break;
        default:
            promote = pieceTypeFromLetter(special);
        }
    }
}

/***************************************************
 * MOVE : GET TEXT OF A MOVE
 ***************************************************/
string Move::getText() const
{
    stringstream ss;

    // Insert source position
    ss << source;

    // Insert destination position
    ss << dest;

    // Handle special cases (capture, en passant, castling, etc.)
    if (moveType == ENPASSANT)
        ss << 'E';
    else if (moveType == CASTLE_KING)
        ss << 'c';  // King-side castling
    else if (moveType == CASTLE_QUEEN)
        ss << 'C';  // Queen-side castling
    else if (capture != SPACE)
        ss << letterFromPieceType(capture);  // Capture piece type

    return ss.str();
}