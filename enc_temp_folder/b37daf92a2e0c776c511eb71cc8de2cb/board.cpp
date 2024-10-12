/***********************************************************************
 * Source File:
 *    BOARD 
 * Author:
 *    <your name here>
 * Summary:
 *    A collection of pieces and a small amount of game state
 ************************************************************************/

#include "board.h"
#include "uiDraw.h"
#include "position.h"
#include "piece.h"
#include "pieceSpace.h"
#include "pieceKnight.h"
#include <cassert>
#include <stdexcept>

using namespace std;


/***********************************************
 * BOARD : RESET
 *         Just fill the board with the known pieces
 *   +---a-b-c-d-e-f-g-h---+
 *   |                     |
 *   8     N         N     8
 *   7                     7
 *   6                     6
 *   5                     5
 *   4                     4
 *   3                     3
 *   2                     2
 *   1     n         n     1
 *   |                     |
 *   +---a-b-c-d-e-f-g-h---+
 ***********************************************/
void Board::reset(bool fFree)
{
    // Free all existing pieces and set squares to nullptr
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
        {
            if (fFree && board[c][r])
                delete board[c][r];
            board[c][r] = nullptr;
        }

    // Initialize Knights
    board[1][0] = new Knight(Position(1, 0), true);  // White knight
    board[6][0] = new Knight(Position(6, 0), true);  // White knight
    board[1][7] = new Knight(Position(1, 7), false); // Black knight
    board[6][7] = new Knight(Position(6, 7), false); // Black knight
}

// we really REALLY need to delete this.
Space space(0,0);

/***********************************************
* BOARD : GET (const)
* Get a piece from a given position.
***********************************************/
const Piece& Board::operator[](const Position& pos) const
{
    // Check if the position is valid
    if (!isPositionValid(pos))
        return *pSpace;  // Return the default space piece for invalid positions

    // Return the piece at the given position, or a space if it's nullptr
    return board[pos.getCol()][pos.getRow()] ? *board[pos.getCol()][pos.getRow()] : *pSpace;
}

/***********************************************
 * BOARD : GET (non-const)
 * Get a piece from a given position (non-const version)
 ***********************************************/
Piece& Board::operator[](const Position& pos)
{
    // Check if the position is valid
    if (!isPositionValid(pos))
        throw std::out_of_range("Invalid board position");

    // If the position is empty, create a new Space piece
    if (!board[pos.getCol()][pos.getRow()])
        board[pos.getCol()][pos.getRow()] = new Space(pos.getCol(), pos.getRow());

    return *board[pos.getCol()][pos.getRow()];
}

 /***********************************************
 * BOARD : DISPLAY
 *         Display the board
 ***********************************************/
void Board::display(const Position & posHover, const Position & posSelect) const
{
   
}


/************************************************
 * BOARD : CONSTRUCT
 *         Free up all the allocated memory
 ************************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0)
{
    pSpace = new Space(0, 0);  // Initialize the default space piece
    if (!noreset)
        reset();
}


/************************************************
 * BOARD : FREE
 *         Free up all the allocated memory
 ************************************************/
void Board::free()
{
    // Free all pieces on the board
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (board[c][r])
            {
                delete board[c][r];
                board[c][r] = nullptr;
            }

    // Free the default space piece
    delete pSpace;
    pSpace = nullptr;
}


/**********************************************
 * BOARD : ASSERT BOARD
 *         Verify the board is well-formed
 *********************************************/
void Board::assertBoard()
{

}




/**********************************************
 * BOARD : MOVE
 *         Execute a move according to the contained instructions
 *   INPUT move The instructions of the move
 *********************************************/
void Board::move(const Move & move)
{  

}

/**********************************************
 * BOARD : IS POSITION VALID
 * Check if a given position is valid on the board
 *********************************************/
bool Board::isPositionValid(const Position& pos) const {
    return (pos.getCol() >= 0 && pos.getCol() < 8 && pos.getRow() >= 0 && pos.getRow() < 8);
}

/**********************************************
 * BOARD EMPTY
 * The game board that is completely empty.
 * It does not even have spaces though each non-filled
 * spot will report it has a space. This is for unit testing
 *********************************************/
BoardEmpty::BoardEmpty() : BoardDummy(), pSpace(nullptr), moveNumber(0)
{
   pSpace = new Space(0, 0);
}
BoardEmpty::~BoardEmpty() 
{
   delete pSpace;
}

/**********************************************
 * BOARD : SET PIECE
 * Set a piece at a specific position on the board
 *********************************************/
void Board::setPiece(const Position& pos, Piece* piece)
{
    if (isPositionValid(pos))
    {
        if (board[pos.getCol()][pos.getRow()])
            delete board[pos.getCol()][pos.getRow()];
        board[pos.getCol()][pos.getRow()] = piece;
    }
    else
    {
        throw std::out_of_range("Invalid board position for setting piece");
    }
}