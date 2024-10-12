/***********************************************************************
 * Source File:
 *    TEST KNIGHT
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the knight
 ************************************************************************/

#include "testKnight.h"
#include "pieceKnight.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      

 /*************************************
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6                     6
  * 5                     5
  * 4                     4
  * 3             p   .   3
  * 2           P         2
  * 1              (n)    1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestKnight::getMoves_end()
{
   // SETUP
   BoardEmpty board;
   Knight knight(7, 7, false /*white*/);
   knight.fWhite = true;
   knight.position.set(6, 0);
   board.board[6][0] = &knight;
   Black black(PAWN);
   board.board[4][1] = &black;
   White white(PAWN);
   board.board[5][2] = &white;
   set <Move> moves;

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // many possible moves
   assertUnit(moves.find(Move("g1e2p")) != moves.end());
   assertUnit(moves.find(Move("g1h3")) != moves.end());

   // TEARDOWN
   board.board[6][0] = nullptr; // white knight
   board.board[4][1] = nullptr; // black pawn
   board.board[5][2] = nullptr; // white pawn
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       p   p         7
 * 6     p       p       6
 * 5        (n)          5
 * 4     p       p       4
 * 3       p   p         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_blocked()
{
   // SETUP
	BoardEmpty board;
	Knight knight(4, 5, false); // White night at e5
	board.board[4][5] = &knight;

	// Block all possible moves
	board.board[3][3] = new Black(PAWN); // c4
	board.board[3][5] = new Black(PAWN); // e4
	board.board[5][3] = new Black(PAWN); // c6
	board.board[5][5] = new Black(PAWN); // e6
	set<Move> moves;

	// EXERCISE
	knight.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.empty()); // No moves should be possible

	// TEARDOWN
	board.board[4][5] = nullptr; // Knight
	board.board[3][3] = nullptr; // Blocked piece
	board.board[3][5] = nullptr; // Blocked piece
	board.board[5][3] = nullptr; // Blocked piece
	board.board[5][5] = nullptr; // Blocked piece
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       p   p         7
 * 6     p       p       6
 * 5        (n)          5
 * 4     p       p       4
 * 3       p   p         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_capture()
{
   // SETUP
	BoardEmpty board;
	Knight knight(4, 5, false); // White knight at e5
	board.board[4][5] = &knight;
	board.board[3][3] = new Black(PAWN); // Capturable pawn at c4
	board.board[5][3] = new White(PAWN); // Not capturable pawn
	set<Move> moves;

	// EXERCISE
	knight.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 1); // Should only have one capturing move
	assertUnit(moves.find(Move("e5c4p")) != moves.end()); // Expect capture move

	// TEARDOWN
	board.board[4][5] = nullptr; // Knight
	board.board[3][3] = nullptr; // Captured piece
	board.board[5][3] = nullptr; // Non-captured piece
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       .   .         7
 * 6     .       .       6
 * 5        (n)          5
 * 4     .       .       4
 * 3       .   .         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_free()
{
   // SETUP
	BoardEmpty board;
	Knight knight(4, 5, false); // White knight at e5
	board.board[4][5] = &knight;
	set<Move> moves;

	// EXERCISE
	knight.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 8); // Should have all possibilities available

	// TEARDOWN
	board.board[4][5] = nullptr; // Knight
}



/*************************************
 * GET TYPE : knight
 * Input:
 * Output: KNIGHT
 **************************************/
void TestKnight::getType()
{
	// SETUP
	Knight knight(0, 0, true); // Black knight at a1

	// EXERCISE
	PieceType type = knight.getType();

	// VERIFY
	assertUnit(type == KNIGHT); // Expect type to be Knight

	// TEARDOWN
}