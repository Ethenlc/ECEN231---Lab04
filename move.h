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

    Move(const Move& rhs) : promote(SPACE), capture(SPACE), isWhite(true), moveType(MOVE)
    {
        *this = rhs;
    }
    Move(const char* s, bool isW = true) : promote(SPACE), capture(SPACE), isWhite(isW), moveType(MOVE)
    {
        *this = s;
    }

    // getters
    string getText() const;
    const Position& getDes() const { return dest; }
    const Position& getSrc() const { return source; }
    PieceType getPromotion() const { return promote; }
    PieceType getCapture() const { return capture; }
    bool getEnPassant() const { return moveType == ENPASSANT; }
    bool getCastleK() const { return moveType == CASTLE_KING; }
    bool getCastleQ() const { return moveType == CASTLE_QUEEN; }
    bool getWhiteMove() const { return isWhite; }
    Move::MoveType getMoveType() const { return moveType; }
    bool operator == (const Move & rhs) const;
    bool operator == (const string& rhs) const { return getText() == rhs; }
    bool operator != (const string& rhs) const { return getText() != rhs; }
    bool operator != (const Move& rhs) const { return !(*this == rhs); }
    bool operator < (const Move& rhs) const { return dest.getLocation() < rhs.getDes().getLocation(); }

    // setters
    void update() { text = getText(); }
    void setCapture(PieceType pt) { capture = pt; update(); }
    void setWhiteMove(bool f) { isWhite = f; update(); }
    void setSrc(const Position& src) { source = src; update(); }
    void setDes(const Position& des) { dest = des; update(); }
    void setEnPassant() { moveType = ENPASSANT; update(); }
    void setPromote(PieceType pt) { promote = pt; update(); }
    void setCastle(bool isKing) { moveType = (isKing ? CASTLE_KING : CASTLE_QUEEN); update(); }

    // for file I/O though only file input is currently implemented
    friend ostream& operator << (ostream& out, Move& rhs);
    friend istream& operator >> (istream& in, Move& rhs);

    const Move& operator = (const Move& rhs);
    const Move& operator = (const string& s) { read(s); return *this; }
    const Move& operator = (const char* s) { read(string(s)); return *this; }

private:
    void read(const std::string& s);
    char letterFromPieceType(PieceType pt) const;
    PieceType pieceTypeFromLetter(char letter) const;

    Position source;
    Position dest;
    PieceType promote;
    PieceType capture;
    MoveType moveType;
    bool isWhite;
    string text;
};
