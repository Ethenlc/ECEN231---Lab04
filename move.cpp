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
 * Initializes a move with invalid positions, default piece types,
 * move type, and sets isWhite to true.
 ***************************************************/
Move::Move()
    : source(), dest(), promote(SPACE), capture(SPACE), moveType(MOVE), isWhite(true)
{
    source.setInvalid(); // Set the source position as invalid
    dest.setInvalid();   // Set the destination position as invalid
}

/***************************************************
 * MOVE : INITIALIZE FROM STRING
 * Constructor that initializes a move based on a string representation.
 ***************************************************/
Move::Move(const std::string& moveText) {
    readFromString(moveText); // Parse the string to initialize the move
}

/***************************************************
 * MOVE : EQUALITY OPERATOR
 * Checks if two moves are equal based on their attributes.
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
 * Compares two moves based on their source and destination positions.
 ***************************************************/
bool Move::operator<(const Move& rhs) const
{
    if (this->source != rhs.source)
        return this->source < rhs.source;
    return this->dest < rhs.dest; // Compare destination if sources are equal
}

/***************************************************
 * MOVE : CONVERT PieceType TO CHAR
 * Converts a PieceType enum to its corresponding character representation.
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
    case SPACE:  return ' '; // Represents empty space or no piece
    default:     return '?'; // Error case for unrecognized PieceType
    }
}

/***************************************************
 * MOVE : CONVERT CHAR TO PieceType
 * Converts a character representation back to its corresponding PieceType.
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
    case ' ': return SPACE; // Represents empty space
    default:  return SPACE;  // Default to SPACE for unrecognized input
    }
}

/***************************************************
 * MOVE : READ FROM STRING
 * Parses a string representation of a move and initializes the move's
 * attributes accordingly.
 ***************************************************/
void Move::readFromString(const std::string& moveText)
{
    // Set the source position from the first two characters of moveText
    source.set(moveText[0] - 'a', moveText[1] - '1');

    // Set the destination position from the next two characters
    dest.set(moveText[2] - 'a', moveText[3] - '1');

    // Default move type is a regular move
    moveType = MOVE;

    // If there is a 5th character, process it for special move types
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
        case 'E': // En passant move
            moveType = ENPASSANT;
            break;
        case 'c': // Kingside castling
            moveType = CASTLE_KING;
            break;
        case 'C': // Queenside castling
            moveType = CASTLE_QUEEN;
            break;
        default:
            promote = pieceTypeFromLetter(special); // Promotion type
        }
    }
}

/***************************************************
 * MOVE : GET TEXT OF A MOVE
 * Generates the string representation of the move.
 ***************************************************/
string Move::getText() const
{
    stringstream ss;

    // Insert source and destination positions into the string stream
    ss << source;
    ss << dest;

    // Append special move type if applicable
    if (moveType == ENPASSANT)
        ss << 'E';
    else if (moveType == CASTLE_KING)
        ss << 'c'; // King-side castling
    else if (moveType == CASTLE_QUEEN)
        ss << 'C'; // Queen-side castling
    else if (capture != SPACE)
        ss << letterFromPieceType(capture); // Capture piece type

    return ss.str(); // Return the complete string representation of the move
}
