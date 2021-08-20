#include "validator.h"

Validator::Validator(QList < QList <Grid*> > &g)
{
    grids = g;
}

bool Validator::checkMove(ChessPiece* chess, int x, int y)
{
    if (chess == nullptr) return false; //failsafe

    if (chess->getChessType() == dilei || chess->getChessType() == junqi) {
        return false;
    }

    int currX = chess->getXCoord();
    int currY = chess->getYCoord();

    if ( (abs(x - currX) == 1 && abs(y - currY) == 0) ||
         (abs(x - currX) == 0 && abs(y - currY) == 1) )
    { // strictly vertical/horizontal
        if (!grids[y - 1][x - 1]->getOccupied()) return true;
    }

    return false;
}

int Validator::checkAttack(ChessPiece* chess1, ChessPiece* chess2)
{

}
