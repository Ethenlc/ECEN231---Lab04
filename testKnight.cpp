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
    knight.position.set(0, 0);
    Black black(PAWN);
    set<Move> moves;

    // EXERCISE
    knight.getMoves(moves, board);

    // VERIFY
    assertUnit(moves.size() == 2);  // many possible moves
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
    Knight knight(7, 7, false /*white*/);
    White white;
    knight.fWhite = true;
    knight.position.set(3, 4);
    board.board[2][6] = board.board[4][6] = &white;
    board.board[1][5] = board.board[5][5] = &white;
    board.board[1][3] = board.board[5][3] = &white;
    board.board[2][2] = board.board[4][2] = &white;
    set<Move> moves;

    // EXERCISE
    knight.getMoves(moves, board);

    // VERIFY
    assertUnit(moves.size() == 0);  // no possible moves

    // TEARDOWN
    board.board[2][6] = board.board[4][6] = nullptr;
    board.board[1][5] = board.board[5][5] = nullptr;
    board.board[1][3] = board.board[5][3] = nullptr;
    board.board[2][2] = board.board[4][2] = nullptr;
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
    Knight knight(7, 7, false /*white*/);
    knight.fWhite = true;
    knight.position.set(3, 4);
    Black black(PAWN);
    board.board[2][6] = board.board[4][6] = &black;
    board.board[1][5] = board.board[5][5] = &black;
    board.board[1][3] = board.board[5][3] = &black;
    board.board[2][2] = board.board[4][2] = &black;
    set<Move> moves;

    // EXERCISE
    knight.getMoves(moves, board);

    // VERIFY
    assertUnit(moves.size() == 8);  // all possible moves

    // TEARDOWN
    board.board[2][6] = board.board[4][6] = nullptr;
    board.board[1][5] = board.board[5][5] = nullptr;
    board.board[1][3] = board.board[5][3] = nullptr;
    board.board[2][2] = board.board[4][2] = nullptr;
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
    Knight knight(7, 7, false /*white*/);
    knight.fWhite = true;
    knight.position.set(3, 4);
    board.board[3][4] = &knight;
    set<Move> moves;

    // EXERCISE
    knight.getMoves(moves, board);

    // VERIFY
    assertUnit(moves.size() == 8);  // many possible moves

    // TEARDOWN
    board.board[3][4] = nullptr; // white knight
}

/*************************************
 * GET TYPE : knight
 * Input:
 * Output: KNIGHT
 **************************************/
void TestKnight::getType()
{
    // SETUP
    BoardEmpty board;
    Knight knight(7, 7, false /*white*/);
    knight.fWhite = true;
    knight.position.set(3, 4);
    board.board[3][4] = &knight;

    // EXERCISE

    // VERIFY
    assertUnit(knight.getType() == KNIGHT);

    // TEARDOWN
    board.board[3][4] = nullptr; // white knight
}
