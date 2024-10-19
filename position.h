/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    Ethen Campbell & Joseph Gyman
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#pragma once

#include <string>
#include <cstdint>
#include <iostream> // Move iostream include here for ostream and istream
using std::string;
using std::ostream;
using std::istream;

const int SIZE_SQUARE = 32;   // number of pixels in a square by default
const int OFFSET_BOARD = 50;   // boarder between the board and the edge of screen

/***********************************************
 * DELTA
 * Movement in a direction (dRow and dCol)
 **********************************************/
struct Delta
{
    int dRow;
    int dCol;

    // Operator overload for multiplying Delta by an integer
    Delta operator*(int scalar) const {
        return Delta{ dRow * scalar, dCol * scalar };
    }
};

const Delta ADD_R = { 1,  0 };
const Delta ADD_C = { 0,  1 };
const Delta SUB_R = { -1,  0 };
const Delta SUB_C = { 0, -1 };

class PositionTest;

/***************************************************
 * POSITION
 * The location of a piece on the board
 ***************************************************/
class Position
{
    friend class PositionTest;
public:
    Position() : colRow(0x99) {}
    Position(int c, int r) : colRow((uint8_t)((c << 4) | (r & 0x0F))) {}
    Position(int location) { setLocation(location); }
    Position(const Position& rhs) { this->colRow = rhs.colRow; }
    Position(const char* s) { *this = s; }

    bool isInvalid() const { return (colRow & 0x88) != 0; }
    bool isValid()   const { return (colRow & 0x88) == 0; }
    void setValid() { colRow &= ~0x88; }
    void setInvalid() { colRow = 0xFF; }

    bool operator <  (const Position& rhs) const { return colRow < rhs.colRow; }
    bool operator == (const Position& rhs) const { return colRow == rhs.colRow; }
    bool operator != (const Position& rhs) const { return !(*this == rhs); }
    const Position& operator = (const Position& rhs) { this->colRow = rhs.colRow; return *this; }
    const Position& operator = (const char* rhs);
    const Position& operator = (const string& rhs) { return *this = rhs.c_str(); }

    int getLocation() const;
    void setLocation(int location);

    virtual int getCol() const;
    virtual int getRow() const;
    void setCol(int c);
    void setRow(int r);
    void set(int c, int r);

    // Pixels:    The Position class can work with screen coordinates,
    //            a.k.a. Pixels, these are X and Y coordinates. Note that
    //            we need to scale them according to the size of the board.
    int getX()   const;
    int getY()   const;
    void setXY(double x, double y);
    double getSquareWidth()  const { return 99; }
    double getSquareHeight() const { return 99; }
    void setSquareWidth(double width) {  }
    void setSquareHeight(double height) {  }

    // Delta:    The Position class can work with deltas, which are
    //           offsets from a given location. This helps pieces move
    //           on the chess board.
    Position::Position(const Position& rhs, const Delta& delta) {
        int newCol = rhs.getCol() + delta.dCol;
        int newRow = rhs.getRow() + delta.dRow;
        if (newCol >= 0 && newCol <= 7 && newRow >= 0 && newRow <= 7) {
            colRow = (uint8_t)((newCol << 4) | (newRow & 0x0F));
        }
        else {
            setInvalid();
        }
    }

    void adjustRow(int dRow);
    void adjustCol(int dCol);

    const Position& operator += (const Delta& rhs);
    Position operator + (const Delta& rhs) const;

private:
    uint8_t colRow;
    static double squareWidth;
    static double squareHeight;

    void set(uint8_t colRowNew) { colRow = colRowNew; }
};

// Overload stream operators
ostream& operator << (ostream& out, const Position& pos);
istream& operator >> (istream& in, Position& pos);

