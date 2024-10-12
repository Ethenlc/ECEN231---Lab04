/***********************************************************************
 * Source File:
 *    KNIGHT
 * Author:
 *    <your name here>
 * Summary:
 *    The Knight class implementation
 ************************************************************************/

#include "pieceKnight.h"
#include "board.h"
#include "uiDraw.h"    // For drawing functions
#include <vector>

 /***************************************************
  * KNIGHT : DISPLAY
  * Draws the knight piece on the board.
  ***************************************************/
void Knight::display(ogstream* pgout) const
{
    // Code to draw the knight piece can be implemented here.
    // Placeholder for knight's graphical representation
}

/**********************************************
 * KNIGHT : GET MOVES
 * Calculates all possible moves for the knight piece.
 *****************************************************/
void Knight::getMoves(set<Move>& moves, const Board& board) const {
    Position currentPosition = this->getPosition();

    // Debugging output to verify the position
    std::cout << "Knight's Current Position: " << currentPosition.getCol() << ", " << currentPosition.getRow() << std::endl;

    if (!board.isPositionValid(currentPosition)) {
        std::cout << "Current Position is invalid, exiting." << std::endl;
        return; // Exit early if the current position is invalid
    }

    // Define knight moves
    static const Delta knightMoves[] = {
        { 2, 1 }, { 2, -1 }, { -2, 1 }, { -2, -1 },
        { 1, 2 }, { 1, -2 }, { -1, 2 }, { -1, -2 }
    };

    for (const auto& move : knightMoves) {
        Position newPos = currentPosition + move;

        // Debugging output
        std::cout << "Attempting move to: " << newPos.getCol() << ", " << newPos.getRow() << std::endl;

        if (!board.isPositionValid(newPos)) {
            std::cout << "New position is invalid, continuing to next move." << std::endl;
            continue;
        }

        // Try to access the piece at the new position
        std::cout << "Attempting to access piece at position: "
            << newPos.getCol() << ", " << newPos.getRow() << std::endl;

        try {
            const Piece& pieceAtDest = board[newPos]; // Access the piece
            std::cout << "Piece at destination: " << pieceAtDest.getType() << std::endl;

            // Existing move logic
            if (pieceAtDest.getType() == SPACE || pieceAtDest.isWhite() != this->isWhite()) {
                Move possibleMove(currentPosition, newPos, this->getType());
                if (pieceAtDest.getType() != SPACE) {
                    possibleMove.setCapture(pieceAtDest.getType());
                }
                moves.insert(possibleMove);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }
        catch (...) {
            std::cerr << "Unknown exception caught!" << std::endl;
        }
    }
}
