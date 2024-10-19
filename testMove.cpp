/***********************************************************************
 * Header File:
 *    TEST MOVE
 * Author:
 *    Ethen Campbell & Joseph Gyman
 * Summary:
 *    test the Move class
 ************************************************************************/


#include "testMove.h"
#include "move.h"
#include <cassert>

 /*************************************
  * Constructor : default
  * Input:
  * Output: source=INVALID
  *         dest  =INVALID
  **************************************/
void TestMove::constructor_default()
{
	Move move;
	assertUnit(move.source.isInvalid());
	assertUnit(move.dest.isInvalid());
}

/*************************************
 * CONSTRUCTOR : standard string move
 * Input:  e5e6
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::constructString_simple()
{
	Move move("e5e6");
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 4);
	assertUnit(move.dest.getCol() == 4);
	assertUnit(move.dest.getRow() == 5);
	assertUnit(move.moveType == Move::MOVE);
}

/*************************************
 * READ simple move
 * Input:  e5e6
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::read_simple()
{
	Move move("e5e6");
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 4);
	assertUnit(move.dest.getCol() == 4);
	assertUnit(move.dest.getRow() == 5);
	assertUnit(move.moveType == Move::MOVE);
}

/*************************************
 * READ capture move
 * Input:  e5d6r
 * Output: source=4,4
 *         dest  =3,5
 *         type  =MOVE
 *         capture=ROOK
 **************************************/
void TestMove::read_capture()
{
	Move move("e5d6r");
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 4);
	assertUnit(move.dest.getCol() == 3);
	assertUnit(move.dest.getRow() == 5);
	assertUnit(move.capture == ROOK);
}

/*************************************
 * READ enpassant move
 * Input:  e5f6E
 * Output: source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 **************************************/
void TestMove::read_enpassant()
{
	Move move("e5f6E");
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 4);
	assertUnit(move.dest.getCol() == 5);
	assertUnit(move.dest.getRow() == 5);
	assertUnit(move.moveType == Move::ENPASSANT);
}

/*************************************
 * READ king side castle
 * Input:  e1g1c
 * Output: source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 **************************************/
void TestMove::read_castleKing()
{
	Move move("e1g1c");
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 0);
	assertUnit(move.dest.getCol() == 6);
	assertUnit(move.dest.getRow() == 0);
	assertUnit(move.moveType == Move::CASTLE_KING);
}

/*************************************
 * READ queen side castle
 * Input:  e1c1C
 * Output: source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 **************************************/
void TestMove::read_castleQueen()
{
	Move move("e1c1C");
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 0);
	assertUnit(move.dest.getCol() == 2);
	assertUnit(move.dest.getRow() == 0);
	assertUnit(move.moveType == Move::CASTLE_QUEEN);
}

/*************************************
 * ASSIGN simple move
 * Input:  e5e6
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::assign_simple()
{
	Move move1;
	move1.setSrc(Position(4, 4));
	move1.setDes(Position(4, 5));

	Move move2;
	move2 = move1;

	assertUnit(move2.source.getCol() == move1.source.getCol());
	assertUnit(move2.source.getRow() == move1.source.getRow());
	assertUnit(move2.dest.getCol() == move1.dest.getCol());
	assertUnit(move2.dest.getRow() == move1.dest.getRow());
	assertUnit(move2.moveType == move1.moveType);
}

/*************************************
 * ASSIGN capture move
 * Input:  e5d6r
 * Output: source=4,4
 *         dest  =3,5
 *         type  =MOVE
 *         capture=ROOK
 **************************************/
void TestMove::assign_capture()
{
	Move move1;
	move1.setSrc(Position(4, 4)); // 'e5'
	move1.setDes(Position(3, 5)); // 'd6'
	move1.setCapture(ROOK); // Capturing a rook

	Move move2;
	move2 = move1;

	assertUnit(move2.source.getCol() == move1.source.getCol());
	assertUnit(move2.source.getRow() == move1.source.getRow());
	assertUnit(move2.dest.getCol() == move1.dest.getCol());
	assertUnit(move2.dest.getRow() == move1.dest.getRow());
	assertUnit(move2.moveType == move1.moveType);
	assertUnit(move2.capture == move1.capture);
}

/*************************************
 * ASSIGN enpassant move
 * Input:  e5f6E
 * Output: source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 **************************************/
void TestMove::assign_enpassant()
{
	Move move1;
	move1.setSrc(Position(4, 4)); // 'e5'
	move1.setDes(Position(5, 5)); // 'f6'
	move1.setEnPassant(); // Sets the move type to ENPASSANT

	Move move2;
	move2 = move1;

	assertUnit(move2.source.getCol() == move1.source.getCol());
	assertUnit(move2.source.getRow() == move1.source.getRow());
	assertUnit(move2.dest.getCol() == move1.dest.getCol());
	assertUnit(move2.dest.getRow() == move1.dest.getRow());
	assertUnit(move2.moveType == move1.moveType);
}

/*************************************
 * ASSIGN king side castle
 * Input:  e1g1c
 * Output: source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 **************************************/
void TestMove::assign_castleKing()
{
	Move move1;
	move1.setSrc(Position(4, 0)); // 'e1'
	move1.setDes(Position(6, 0)); // 'g1'
	move1.setCastle(true); // Set for king-side castling (c)


	Move move2;
	move2 = move1;

	assertUnit(move2.source.getCol() == move1.source.getCol());
	assertUnit(move2.source.getRow() == move1.source.getRow());
	assertUnit(move2.dest.getCol() == move1.dest.getCol());
	assertUnit(move2.dest.getRow() == move1.dest.getRow());
	assertUnit(move2.moveType == move1.moveType);
}

/*************************************
 * ASSIGN queen side castle
 * Input:  e1c1C
 * Output: source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 **************************************/
void TestMove::assign_castleQueen()
{
	Move move1;
	move1.setSrc(Position(4, 0)); // 'e1'
	move1.setDes(Position(2, 0)); // 'c1'
	move1.setCastle(false); // Set for queen-side castling (C)

	Move move2;
	move2 = move1;

	assertUnit(move2.source.getCol() == move1.source.getCol());
	assertUnit(move2.source.getRow() == move1.source.getRow());
	assertUnit(move2.dest.getCol() == move1.dest.getCol());
	assertUnit(move2.dest.getRow() == move1.dest.getRow());
	assertUnit(move2.moveType == move1.moveType);
}

/*************************************
 * GET TEXT simple move
 * Input : source=4,4
 *         dest  =4,5
 *         type  =MOVE
 * Output:  e5e6
 **************************************/
void TestMove::getText_simple()
{
	Move move;
	move.source.set(4, 4);
	move.dest.set(4, 5);
	move.moveType = Move::MOVE;
	assertUnit(move.getText() == "e5e6");
}

/*************************************
 * GET TEXT capture
 * Input : source=4,4
 *         dest  =4,5
 *         type  =MOVE
 *         capture=ROOK
 * Output:  e5e6r
 **************************************/
void TestMove::getText_capture()
{
	Move move;
	move.source.set(4, 4);
	move.dest.set(3, 5);
	move.capture = ROOK;
	assertUnit(move.getText() == "e5d6r");
}

/*************************************
 * GET TEXT en passant
 * Input : source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 *         capture=PAWN
 * Output:  e5f6E
 **************************************/
void TestMove::getText_enpassant()
{
	Move move;
	move.source.set(4, 4);
	move.dest.set(5, 5);
	move.moveType = Move::ENPASSANT;
	move.capture = PAWN;
	assertUnit(move.getText() == "e5f6E");
}

/*************************************
 * GET TEXT king side castle
 * Input : source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 * Output:  e1g1c
 **************************************/
void TestMove::getText_castleKing()
{
	Move move;
	move.source.set(4, 0);
	move.dest.set(6, 0);
	move.moveType = Move::CASTLE_KING;
	assertUnit(move.getText() == "e1g1c");
}

/*************************************
 * GET TEXT queen side castle
 * Input : source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 * Output:  e1c1C
 **************************************/
void TestMove::getText_castleQueen()
{
	Move move;
	move.source.set(4, 0);
	move.dest.set(2, 0);
	move.moveType = Move::CASTLE_QUEEN;
	assertUnit(move.getText() == "e1c1C");
}

/*************************************
 * LETTER FROM PIECE TYPE space
 * Input :  SPACE
 * Output:  ' '
 **************************************/
void TestMove::letterFromPieceType_space()
{
	Move move;
	assertUnit(move.letterFromPieceType(SPACE) == ' ');
}

/*************************************
 * LETTER FROM PIECE TYPE pawn
 * Input : PAWN
 * Output:  'p'
 **************************************/
void TestMove::letterFromPieceType_pawn()
{
	Move move;
	assertUnit(move.letterFromPieceType(PAWN) == 'p');
}

/*************************************
 * LETTER FROM PIECE TYPE bishop
 * Input : BISHOP
 * Output:  'b'
 **************************************/
void TestMove::letterFromPieceType_bishop()
{
	Move move;
	assertUnit(move.letterFromPieceType(BISHOP) == 'b');
}

/*************************************
 * LETTER FROM PIECE TYPE knight
 * Input : KNIGHT
 * Output:  'n'
 **************************************/
void TestMove::letterFromPieceType_knight()
{
	Move move;
	assertUnit(move.letterFromPieceType(KNIGHT) == 'n');
}

/*************************************
 * LETTER FROM PIECE TYPE rook
 * Input : ROOK
 * Output:  'r'
 **************************************/
void TestMove::letterFromPieceType_rook()
{
	Move move;
	assertUnit(move.letterFromPieceType(ROOK) == 'r');
}

/*************************************
 * LETTER FROM PIECE TYPE queen
 * Input : QUEEN
 * Output:  'q'
 **************************************/
void TestMove::letterFromPieceType_queen()
{
	Move move;
	assertUnit(move.letterFromPieceType(QUEEN) == 'q');
}

/*************************************
 * LETTER FROM PIECE TYPE king
 * Input : KING
 * Output:  'k'
 **************************************/
void TestMove::letterFromPieceType_king()
{
	Move move;
	assertUnit(move.letterFromPieceType(KING) == 'k');
}

/*************************************
 * PIECE TYPE FROM LETTER pawn
 * Input : 'p'
 * Output:  PAWN
 **************************************/
void TestMove::pieceTypeFromLetter_pawn()
{
	Move move;
	assertUnit(move.pieceTypeFromLetter('p') == PAWN);
}

/*************************************
 * PIECE TYPE FROM LETTER bishop
 * Input : 'b'
 * Output:  BISHOP
 **************************************/
void TestMove::pieceTypeFromLetter_bishop()
{
	Move move;
	assertUnit(move.pieceTypeFromLetter('b') == BISHOP);
}

/*************************************
 * PIECE TYPE FROM LETTER knight
 * Input : 'n'
 * Output:  KNIGHT
 **************************************/
void TestMove::pieceTypeFromLetter_knight()
{
	Move move;
	assertUnit(move.pieceTypeFromLetter('n') == KNIGHT);
}

/*************************************
 * PIECE TYPE FROM LETTER rook
 * Input : 'r'
 * Output:  ROOK
 **************************************/
void TestMove::pieceTypeFromLetter_rook()
{
	Move move;
	assertUnit(move.pieceTypeFromLetter('r') == ROOK);
}

/*************************************
 * PIECE TYPE FROM LETTER queen
 * Input : 'q'
 * Output:  QUEEN
 **************************************/
void TestMove::pieceTypeFromLetter_queen()
{
	Move move;
	assertUnit(move.pieceTypeFromLetter('q') == QUEEN);
}

/*************************************
 * PIECE TYPE FROM LETTER king
 * Input : 'k'
 * Output:  KING
 **************************************/
void TestMove::pieceTypeFromLetter_king()
{
	Move move;
	assertUnit(move.pieceTypeFromLetter('k') == KING);
}


/*************************************
 * EQUAL - NOT
 * Input : b2b4 == b2b5
 * Output: false
 **************************************/
void TestMove::equal_not()
{
	bool response;
	Move move1, move2;
	move1.source = Position("b2");
	move1.dest = Position("b4");
	move2.source = Position("b2");
	move2.dest = Position("b5");

	response = (move1 == move2);
	assertUnit(response == false);
}

/*************************************
 * EQUAL - EQUALS
 * Input : b2b4 == b2b4
 * Output: false
 **************************************/
void TestMove::equal_equals()
{
	Move move1, move2;
	move1.source = Position("b2");
	move1.dest = Position("b4");
	move2.source = Position("b2");
	move2.dest = Position("b4");
	assertUnit(move1 == move2);
}

/*************************************
 * LESS THAN - LESS THAN
 * Input : b2b2 < b2b4
 * Output: false
 **************************************/
void TestMove::lessthan_lessthan()
{
	Move move1, move2;
	move1.source = Position("b2");
	move1.dest = Position("b2");
	move2.source = Position("b2");
	move2.dest = Position("b4");
	assertUnit(move1 < move2);
}

/*************************************
 * LESS THAN - EQUALS
 * Input : b2b4 < b2b4
 * Output: false
 **************************************/
void TestMove::lessthan_equals()
{
	bool response;
	Move move1, move2;
	move1.source = Position("b2");
	move1.dest = Position("b4");
	move2.source = Position("b2");
	move2.dest = Position("b4");

	response = (move1 < move2);
	assertUnit(response == false);
}

/*************************************
 * LESS THAN - GREATAER THAN
 * Input : b2b4 < b2b2
 * Output: false
 **************************************/
void TestMove::lessthan_greaterthan()
{
	Move move1, move2;
	move1.source = Position("b2");
	move1.dest = Position("b4");
	move2.source = Position("b2");
	move2.dest = Position("b2");
	assertUnit(!(move1 < move2));
}