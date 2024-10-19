#include "pieceBishop.h"
#include "board.h"
#include "uiDraw.h"

void Bishop::display(ogstream* pgout) const
{
    pgout->drawBishop(position, !isWhite());
}

set<Move> Bishop::getMovesSlide(const Board& board, const Delta deltas[], int numDelta) const
{
    set<Move> moves;
    for (int i = 0; i < numDelta; i++)
    {
        for (int j = 1; j < 8; j++)
        {
            Position posMove(position, deltas[i] * j);
            if (!posMove.isValid())
                break;

            if (board[posMove] == SPACE)
            {
                Move move;
                move.setSrc(getPosition());
                move.setDes(posMove);
                move.setWhiteMove(isWhite());
                moves.insert(move);
            }
            else
            {
                if (board[posMove].isWhite() != isWhite())
                {
                    Move move;
                    move.setSrc(getPosition());
                    move.setDes(posMove);
                    move.setWhiteMove(isWhite());
                    move.setCapture(board[posMove].getType());
                    moves.insert(move);
                }
                break;
            }
        }
    }
    return moves;
}

void Bishop::getMoves(set<Move>& moves, const Board& board) const
{
    const Delta delta[] =
    {
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };
    moves = getMovesSlide(board, delta, sizeof(delta) / sizeof(delta[0]));
}