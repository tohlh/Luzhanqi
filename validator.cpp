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

    if ((abs(x - currX) == 1 && abs(y - currY) == 0) || (abs(x - currX) == 0 && abs(y - currY) == 1)) { // strictly vertical/horizontal
        return true;
    } else if ((abs(x - currX) == 1 && abs(y - currY) == 1)) { // one step diagonals
        return checkOneStepDiagonal(currX, currY, x, y);
    } else { // multisteps
        bool c1 = currY == 2 || currY == 6 || currY == 7 || currY == 11;
        bool c2 = (currX == 1 || currX == 5) && (currY != 1 && currY != 12);
        bool c3 = currX == 3 && (currY == 6 || currY == 7);
        if (!(c1 || c2 || c3)) return false; // sendiri not on track

        bool c4 = y == 2 || y == 6 || y == 7 || y == 11;
        bool c5 = (x == 1 || x == 5) && (y != 1 && y != 12);
        bool c6 = x == 3 && (y == 6 || y == 7);
        if (!(c4 || c5 || c6)) return false; // destination not on track

        bool c7 = (currX == x) || (currY == y);
        if (c7) {
            return checkMultistepStraights(currX, currY, x, y);
        } else {
            return checkMultistepFree(currX, currY, x, y);
        }
    }
    return false;
}

int Validator::checkAttack(ChessPiece* chess1, ChessPiece* chess2)
{

}

bool Validator::checkOneStepDiagonal(int currX, int currY, int x, int y)
{
    bool c1 = junying.contains({currX, currY});

    bool c2 = (currX == 1 && currY == 2) && (x == 2 && y == 3);
    bool c3 = (currX == 3 && currY == 2) && (x == 2 && y == 3);
    bool c4 = (currX == 3 && currY == 2) && (x == 4 && y == 3);
    bool c5 = (currX == 5 && currY == 2) && (x == 4 && y == 3);
    bool c6 = (currX == 1 && currY == 4) && (x == 2 && y == 3);
    bool c7 = (currX == 1 && currY == 4) && (x == 2 && y == 5);
    bool c8 = (currX == 5 && currY == 4) && (x == 4 && y == 3);
    bool c9 = (currX == 5 && currY == 4) && (x == 4 && y == 5);
    bool c10 = (currX == 1 && currY == 6) && (x == 2 && y == 5);
    bool c11 = (currX == 3 && currY == 6) && (x == 2 && y == 5);
    bool c12 = (currX == 3 && currY == 6) && (x == 4 && y == 5);
    bool c13 = (currX == 5 && currY == 6) && (x == 4 && y == 5);

    bool c14 = (currX == 1 && currY == 7) && (x == 2 && y == 8);
    bool c15 = (currX == 3 && currY == 7) && (x == 2 && y == 8);
    bool c16 = (currX == 3 && currY == 7) && (x == 4 && y == 8);
    bool c17 = (currX == 5 && currY == 7) && (x == 4 && y == 8);
    bool c18 = (currX == 1 && currY == 9) && (x == 2 && y == 8);
    bool c19 = (currX == 1 && currY == 9) && (x == 2 && y == 10);
    bool c20 = (currX == 5 && currY == 9) && (x == 4 && y == 8);
    bool c21 = (currX == 5 && currY == 9) && (x == 4 && y == 10);
    bool c22 = (currX == 1 && currY == 11) && (x == 2 && y == 10);
    bool c23 = (currX == 3 && currY == 11) && (x == 2 && y == 10);
    bool c24 = (currX == 3 && currY == 11) && (x == 4 && y == 10);
    bool c25 = (currX == 5 && currY == 11) && (x == 4 && y == 10);

    return (c1 || c2 || c3 || c4 || c5 ||
            c6 || c7 || c8 || c9 || c10 ||
            c11 || c12 || c13 || c14 || c15 ||
            c16 || c17 || c18 || c19 || c20 ||
            c21 || c22 || c23 || c24 || c25);
}

bool Validator::checkMultistepStraights(int currX, int currY, int x, int y)
{
    if (currX == x) {
        int smallY = y < currY ? y : currY;
        int bigY = y > currY ? y : currY;
        for (int i = smallY; i < bigY; i++) {
            if (i != smallY && i != bigY && grids[i - 1][currX - 1]->getOccupied()) {
                return false;
            }
        }
    } else if (currY == y) {
        int smallX = x < currX ? x : currX;
        int bigX = x > currX ? x : currX;
        for (int i = smallX; i < bigX; i++) {
            if (i != smallX && i != bigX && grids[currY - 1][i - 1]->getOccupied()) {
                return false;
            }
        }
    }

    return true;
}

bool Validator::checkMultistepFree(int currX, int currY, int x, int y)
{

    return false;
}
