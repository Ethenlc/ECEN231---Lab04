/***********************************************************************
 * Source File:
 *    POSITION
 * Author:
 *    Ethen Campbell & Joseph Gyman
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#include "position.h"
#include <iostream>
#include <cstring>

 /******************************************
  * POSITION INSERTION OPERATOR
  ******************************************/
ostream& operator << (ostream& out, const Position& pos)
{
    if (pos.isInvalid())
        out << "error";
    else
    {
        char col = 'a' + pos.getCol(); // Convert column to 'a'-'h'
        char row = '1' + pos.getRow(); // Convert row to '1'-'8'
        out << col << row;             // Output chess notation
    }
    return out;
}

/*************************************
 * POSITION EXTRACTION OPERATOR
 **************************************/
istream& operator >> (istream& in, Position& pos)
{
    string input;
    in >> input;
    pos = input.c_str();  // Use the assignment operator to set position
    return in;
}

/******************************************
 * POSITION ASSIGNMENT OPERATOR (const char*)
 ******************************************/
const Position& Position::operator=(const char* rhs)
{
    if (rhs && strlen(rhs) == 2)
    {
        char col = rhs[0];
        char row = rhs[1];

        // Convert 'a'-'h' to 0-7 (columns) and '1'-'8' to 0-7 (rows)
        int colValue = col - 'a';
        int rowValue = row - '1';

        // Only assign if column and row are valid
        if (colValue >= 0 && colValue <= 7 && rowValue >= 0 && rowValue <= 7)
            colRow = (colValue << 4) | (rowValue & 0x0F);
        else
            colRow = 0xFF; // Invalid value
    }
    else
    {
        colRow = 0xFF; // Invalid value
    }

    return *this;
}

/******************************************
 * GET X
 * Get the x-coordinate for screen rendering
 ******************************************/
int Position::getX() const
{
    return OFFSET_BOARD + getCol() * (int)getSquareWidth();
}

/******************************************
 * GET Y
 * Get the y-coordinate for screen rendering
 ******************************************/
int Position::getY() const
{
    return OFFSET_BOARD + getRow() * (int)getSquareHeight();
}

/******************************************
 * SET X AND Y
 * Set the position based on screen coordinates
 ******************************************/
void Position::setXY(double x, double y)
{
    int col = (int)((x - OFFSET_BOARD) / getSquareWidth());
    int row = (int)((y - OFFSET_BOARD) / getSquareHeight());
    set(col, row);
}

/******************************************
 * POSITION SET COLUMN METHOD
 ******************************************/
void Position::setCol(int c) {
    colRow = (uint8_t)((colRow & 0x0F) | (c << 4)); // Clear the column bits and set the new column
}

/******************************************
 * POSITION SET ROW METHOD
 ******************************************/
void Position::setRow(int r) {
    colRow = (uint8_t)((colRow & 0xF0) | (r & 0x0F)); // Clear the row bits and set the new row
}

/******************************************
 * POSITION SET METHOD
 ******************************************/
void Position::set(int c, int r) {
    colRow = (uint8_t)((c << 4) | (r & 0x0F)); // Set both row and column
}

/******************************************
 * GET LOCATION
 * Convert row/column to a single location (0-63)
 ******************************************/
int Position::getLocation() const
{
    if (isInvalid())
        return -1;
    return getRow() * 8 + getCol();
}

/******************************************
 * SET LOCATION
 * Convert a single location (0-63) into row/column
 ******************************************/
void Position::setLocation(int location)
{
    if (location < 0 || location >= 64)
    {
        setInvalid();
    }
    else
    {
        int col = location % 8;
        int row = location / 8;
        set(col, row);
    }
}

/******************************************
 * GET COLUMN
 * Get the column (0-7) from colRow
 ******************************************/
int Position::getCol() const
{
    if (isInvalid())
        return -1;
    return (colRow & 0xF0) >> 4;
}

/******************************************
 * GET ROW
 * Get the row (0-7) from colRow
 ******************************************/
int Position::getRow() const
{
    if (isInvalid())
        return -1;
    return colRow & 0x0F;
}

/******************************************
 * ADJUST ROW
 * Adjust the row with boundary checks
 ******************************************/
void Position::adjustRow(int dRow)
{
    int newRow = getRow() + dRow;
    if (newRow >= 0 && newRow <= 7)
        setRow(newRow);
    else
        setInvalid();
}

/******************************************
 * ADJUST COL
 * Adjust the column with boundary checks
 ******************************************/
void Position::adjustCol(int dCol)
{
    int newCol = getCol() + dCol;
    if (newCol >= 0 && newCol <= 7)
        setCol(newCol);
    else
        setInvalid();
}

/******************************************
 * OPERATOR +=
 * Add a delta to a position
 ******************************************/
const Position& Position::operator += (const Delta& rhs)
{
    adjustRow(rhs.dRow);
    adjustCol(rhs.dCol);
    return *this;
}

/******************************************
 * OPERATOR +
 * Return a new position with added delta
 ******************************************/
Position Position::operator + (const Delta& rhs) const
{
    Position result = *this;
    result += rhs;
    return result;
}

