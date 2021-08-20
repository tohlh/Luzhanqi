#include "validator.h"

Validator::Validator(QList < QList <Grid*> > &g)
{
    grids = g;
    junying = {{2, 3}, {4, 3}, {3, 4}, {2, 5}, {4, 5}, {2, 8}, {4, 8}, {3, 9}, {2, 10}, {4, 10}};
}

bool Validator::checkMove(ChessPiece* chess, int x, int y)
{
    if (chess == nullptr) return false; //failsafe

    if (chess->getChessType() == dilei || chess->getChessType() == junqi) {
        return false;
    }

    int currX = chess->getXCoord();
    int currY = chess->getYCoord();

    if ((abs(x - currX) == 1 && abs(y - currY) == 0) ||
        (abs(x - currX) == 0 && abs(y - currY) == 1)) { // strictly vertical/horizontal
        if (!grids[y - 1][x - 1]->getOccupied()) {
            return true;
        }
    } else if ((abs(x - currX) == 1 || abs(y - currY) == 1)) { // diagonals
        bool c1 = !grids[y - 1][x - 1]->getOccupied();
        bool c2 = junying.contains({currX, currY});
        if (c1 && c2) return true;

        bool c3 = (currX == 1 && currY == 2) && (x == 2 && y == 3);
        bool c4 = (currX == 3 && currY == 2) && (x == 2 && y == 3);
        bool c5 = (currX == 3 && currY == 2) && (x == 4 && y == 3);
        bool c6 = (currX == 5 && currY == 2) && (x == 4 && y == 3);
        bool c7 = (currX == 1 && currY == 4) && (x == 2 && y == 3);
        bool c8 = (currX == 1 && currY == 4) && (x == 2 && y == 5);
        bool c9 = (currX == 5 && currY == 4) && (x == 4 && y == 3);
        bool c10 = (currX == 5 && currY == 4) && (x == 4 && y == 5);
        bool c11 = (currX == 1 && currY == 6) && (x == 2 && y == 5);
        bool c12 = (currX == 3 && currY == 6) && (x == 2 && y == 5);
        bool c13 = (currX == 3 && currY == 6) && (x == 4 && y == 5);
        bool c14 = (currX == 5 && currY == 6) && (x == 4 && y == 5);

        bool c15 = (currX == 1 && currY == 7) && (x == 2 && y == 8);
        bool c16 = (currX == 3 && currY == 7) && (x == 2 && y == 8);
        bool c17 = (currX == 3 && currY == 7) && (x == 4 && y == 8);
        bool c18 = (currX == 5 && currY == 7) && (x == 4 && y == 8);
        bool c19 = (currX == 1 && currY == 9) && (x == 2 && y == 8);
        bool c20 = (currX == 1 && currY == 9) && (x == 2 && y == 10);
        bool c21 = (currX == 5 && currY == 9) && (x == 4 && y == 8);
        bool c22 = (currX == 5 && currY == 9) && (x == 4 && y == 10);
        bool c23 = (currX == 1 && currY == 11) && (x == 2 && y == 10);
        bool c24 = (currX == 3 && currY == 11) && (x == 2 && y == 10);
        bool c25 = (currX == 3 && currY == 11) && (x == 4 && y == 10);
        bool c26 = (currX == 5 && currY == 11) && (x == 4 && y == 10);

        return (c1 && (c3 || c4 || c5 || c6 || c7 || c8 || c9 || c10 || c11 || c12 || c13 || c14 || c15 || c16 || c17 || c18 || c19 || c20 || c21 || c22 || c23 || c24 || c25 || c26));
    }
    return false;
}

int Validator::checkAttack(ChessPiece* chess1, ChessPiece* chess2)
{

}
