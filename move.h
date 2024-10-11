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


class TestMove;
class TestBoard;

/***************************************************
 * MOVE
 * One move across the board
 ***************************************************/
class Move
{
public:
	enum MoveType { MOVE, ENPASSANT, CASTLE_KING, CASTLE_QUEEN, MOVE_ERROR };

	friend TestMove;
	friend TestBoard;

	// Default constructor
	Move();

	// Equality operator
	bool operator==(const Move& rhs) const;

	// Less than operator for comparison
	bool operator<(const Move& rhs) const;

	// Convert PieceType to char
	char letterFromPieceType(PieceType pt) const;

	// Convert char to PieceType
	PieceType pieceTypeFromLetter(char letter) const;

	// Read a move rom a text string
	void readFromString(const std::string& moveText);

	// Get the text of a move
	std::string getText() const;

private:
	Position  source;    // where the move originated from
	Position  dest;      // where the move finished
	PieceType promote;   // piece to be promoted to
	PieceType capture;   // did a capture happen this move?
	MoveType  moveType;  // what type of move is this?
	bool      isWhite;   // whose turn is it anyway?
	std::string text;    // what is the textual version of the move?
};