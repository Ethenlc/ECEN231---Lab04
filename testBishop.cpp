/***********************************************************************
 * Source File:
 *    TEST BISHOP
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for a bishop
 ************************************************************************/

#include "testBishop.h"
#include "pieceBishop.h"
#include "board.h"
#include "uiDraw.h"
#include <cassert>
#include <memory>
#include <typeinfo>
#include <iostream>

 /*************************************
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6                     6
  * 5                     5
  * 4                     4
  * 3     p   p           3
  * 2      (b)            2
  * 1     p   p           1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestBishop::getMoves_blocked()
{
    // SETUP
    BoardEmpty board;
    Bishop bishop(1, 1, false /*white*/);
    bishop.fWhite = true;
    White white1, white2;
    board.board[3][3] = &white1; // Blocking piece
    board.board[4][4] = &white2; // Another blocking piece
    set<Move> moves;

    // EXERCISE
    bishop.getMoves(moves, board);

    // VERIFY
    assertUnit(moves.size() == 0);  // No possible moves due to blocking pieces
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 .   7
 * 6               .     6
 * 5             .       5
 * 4   .       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     .   .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToEnd()
{
    // SETUP
    BoardEmpty board;
    Bishop bishop(1, 1, false /*white*/);
    bishop.fWhite = true;
    set<Move> moves;

    // EXERCISE
    bishop.getMoves(moves, board);

    // VERIFY
    assertUnit(moves.size() == 7);  // 7 possible diagonal moves to the end of the board
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 p   7
 * 6               .     6
 * 5             .       5
 * 4   p       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     p   p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToBlock()
{
    // SETUP
    BoardEmpty board;
    Bishop bishop(1, 1, false /*white*/);
    bishop.fWhite = true;
    board.board[3][3] = new Black(PAWN); // Blocking piece
    set<Move> moves;

    // EXERCISE
    bishop.getMoves(moves, board);

    // VERIFY
    assertUnit(moves.size() == 3);  // 3 possible moves until the blocking piece

    // TEARDOWN
    delete board.board[3][3];  // Clean up
    board.board[3][3] = nullptr; // Ensure the board is clean
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 P   7
 * 6               .     6
 * 5             .       5
 * 4   P       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     P   P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToCapture()
{
    // SETUP
    BoardEmpty board;
    Bishop bishop(1, 1, false /*white*/);
    bishop.fWhite = true;
    board.board[3][3] = new Black(PAWN); // Capturable piece
    set<Move> moves;

    // EXERCISE
    bishop.getMoves(moves, board);

    // VERIFY
    assertUnit(moves.size() == 1);  // 1 capturing move

    // TEARDOWN
    delete board.board[3][3];  // Clean up
    board.board[3][3] = nullptr; // Ensure the board is clean
}

/*************************************
 * GET TYPE : bishop
 * Input:
 * Output: BISHOP
 **************************************/
void TestBishop::getType()
{
    // SETUP
    Bishop bishop(1, 1, false /*white*/);

    // EXERCISE & VERIFY
    assertUnit(bishop.getType() == BISHOP); // Verify type is BISHOP
}
