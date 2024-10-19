/***********************************************************************
 * Source File:
 *    BOARD
 * Author:
 *    <your name here>
 * Summary:
 *    A collection of pieces and a small amount of game state
 ************************************************************************/

#include "board.h"
#include "move.h"
#include "uiDraw.h"
#include "position.h"
#include "piece.h"
#include "pieceSpace.h"
#include "pieceKnight.h"
#include <cassert>
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
	// free everything
	if (fFree)
		free();

	for (int r = 0; r < 8; r++)
		for (int c = 0; c < 8; c++)
			board[c][r] = nullptr;

	board[1][0] = new Knight(1, 0, true);
	board[6][0] = new Knight(6, 0, true);
	board[1][7] = new Knight(1, 7, false);
	board[6][7] = new Knight(6, 7, false);

	for (int r = 0; r < 8; r++)
		for (int c = 0; c < 8; c++)
			if (nullptr == board[c][r])
				board[c][r] = new Space(c, r);

	numMoves = 0;
	assertBoard();
}

// we really REALLY need to delete this.
Space space(0, 0);

/***********************************************
* BOARD : GET
* Get a piece from a given position.
***********************************************/
const Piece& Board::operator [] (const Position& pos) const
{
    assert(0 <= pos.getCol() && pos.getCol() < 8);
    assert(0 <= pos.getRow() && pos.getRow() < 8);
    assert(nullptr != board[pos.getCol()][pos.getRow()]);
    return *board[pos.getCol()][pos.getRow()];
}
Piece& Board::operator [] (const Position& pos)
{
    assert(0 <= pos.getCol() && pos.getCol() < 8);
    assert(0 <= pos.getRow() && pos.getRow() < 8);
    assert(nullptr != board[pos.getCol()][pos.getRow()]);
    return *board[pos.getCol()][pos.getRow()];
}

/***********************************************
* BOARD : DISPLAY
*         Display the board
***********************************************/
void Board::display(const Position& posHover, const Position& posSelect) const
{

}


/************************************************
 * BOARD : CONSTRUCT
 *         Free up all the allocated memory
 ************************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0) {
	// Optionally initialize your board positions
	for (int r = 0; r < 8; r++)
		for (int c = 0; c < 8; c++)
			board[c][r] = nullptr;  // Initialize each square to nullptr
}

/************************************************
 * BOARD : FREE
 *         Free up all the allocated memory
 ************************************************/
void Board::free() {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			delete board[c][r]; // Delete each piece, if it exists
			board[c][r] = nullptr; // Set the pointer to nullptr after deletion
		}
	}
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
void Board::move(const Move& move) {
	Position src = move.getSrc();
	Position dest = move.getDes();

	if (src.isValid() && dest.isValid()) {
		// Capture logic: delete the piece at the destination if it's not a SPACE
		if (board[dest.getCol()][dest.getRow()] &&
			board[dest.getCol()][dest.getRow()]->getType() != SPACE) {
			delete board[dest.getCol()][dest.getRow()]; // Delete the captured piece
		}

		// Move the knight from src to dest
		board[dest.getCol()][dest.getRow()] = board[src.getCol()][src.getRow()];
		board[src.getCol()][src.getRow()] = new Space(src.getCol(), src.getRow()); // Create a space where the piece was

		// Update move count
		numMoves++;
	}
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

// Board Destructor
Board::~Board() {
	free();
}