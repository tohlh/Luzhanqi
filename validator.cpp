#include "validator.h"

Validator::Validator(QList < QList <Grid*> > &g)
{
    grids = g;
    junying = {{2, 3}, {4, 3}, {3, 4}, {2, 5}, {4, 5}, {2, 8}, {4, 8}, {3, 9}, {2, 10}, {4, 10}};
}

bool Validator::checkLose(QList <ChessPiece*> chesspieces)
{
    for (int i = 0; i < chesspieces.size(); i++) { // not flipped means still got chance
        if (!chesspieces[i]->getChessFlipped()) {
            return false;
        }
    }

    for (int i = 0; i < chesspieces.size(); i++) {
        for (int j = 0; j < grids.size(); j++) {
            for (int k = 0; k < grids[j].size(); k++) {
                if (grids[j][k]->getOccupied()) {
                    ChessPiece* chesspiece2 = grids[j][k]->getChess();
                    int stat = checkAttack(chesspieces[i], chesspiece2);
                    if (stat != -2) {
                        return false;
                    }
                } else {
                    int x = grids[j][k]->getXCoord();
                    int y = grids[j][k]->getYCoord();
                    bool stat = checkMove(chesspieces[i], x, y);
                    if (stat) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

bool Validator::checkMove(ChessPiece* chess, int x, int y)
{
    if (chess == nullptr) return false; //failsafe

    if (chess->getChessType() == dilei || chess->getChessType() == junqi) {
        return false;
    }

    int currX = chess->getXCoord();
    int currY = chess->getYCoord();

    if (((abs(x - currX) == 1 && abs(y - currY) == 0) || (abs(x - currX) == 0 && abs(y - currY) == 1)) &&
         ((currY <= 6 && y <= 6) || (currY >= 7 && y >= 7))) { // strictly vertical/horizontal, only applies on one side
        return true;
    } else if (((abs(x - currX) == 1 && abs(y - currY) == 1)) &&
               ((currY <= 6 && y <= 6) || (currY >= 7 && y >= 7))) { // one step diagonals, only applies on one side
        return checkOneStepDiagonal(currX, currY, x, y);
    } else if (((currY == 6 && y == 7) || (currY == 7 && y == 6)) && currX == x) {
        return (x == 1 || x == 3 || x == 5);
    } else { // multisteps
        bool c1 = currY == 2 || currY == 6 || currY == 7 || currY == 11;
        bool c2 = (currX == 1 || currX == 5) && (currY != 1 && currY != 12);
        bool c3 = currX == 3 && (currY == 6 || currY == 7);
        if (!(c1 || c2 || c3)) return false; // sendiri not on track

        bool c4 = y == 2 || y == 6 || y == 7 || y == 11;
        bool c5 = (x == 1 || x == 5) && (y != 1 && y != 12);
        bool c6 = x == 3 && (y == 6 || y == 7);
        if (!(c4 || c5 || c6)) return false; // destination not on track

        bool c7 = chess->getChessType() == gongbing;
        if (c7) {
            return checkMultistepFree(currX, currY, x, y);
        } else {
            if (((currX == x) && (currX == 1 || currX == 5)) ||
                ((currY == y) && (currY == 2 || currY == 6 || currY == 7 || currY == 11)))
            {
                return checkMultistepStraights(currX, currY, x, y);
            } else {
                return false;
            }
        }
    }
    return false;
}

int Validator::checkAttack(ChessPiece* chess1, ChessPiece* chess2) // 0 chess1 destroyed, 1 chess2 destroyed, -1 both destroyed, -2 invalid move
{
    if (chess1->getChessColor() == chess2->getChessColor()) { // kill own teammate lol?
        return -2;
    }

    int x2 = chess2->getXCoord();
    int y2 = chess2->getYCoord();

    if (!checkMove(chess1, x2, y2)) { // out of reach or chess1 cannot move
        return -2;
    }

    if (junying.contains({x2, y2})) { // chess2 is protected
        return -2;
    }

    if (chess2->getChessType() == junqi) {
        for (int i = 0; i < grids.size(); i++) {
            for (int j = 0; j < grids[i].size(); j++) {
                if (grids[i][j]->getOccupied()) {
                    ChessPiece* currChess = grids[i][j]->getChess();
                    if (currChess->getChessColor() == chess2->getChessColor() && currChess->getChessType() == dilei) {
                        return -2;
                    }
                }
            }
        }
        return 2;
    }

    if (chess1->getChessType() == gongbing && chess2->getChessType() == dilei) {
        return 1;
    }

    if (chess1->getChessType() >= gongbing && chess1->getChessType() <= siling &&
        chess2->getChessType() >= gongbing && chess2->getChessType() <= siling) {
        if (chess1->getChessType() > chess2->getChessType()) {
            return 1;
        } else if (chess1->getChessType() == chess2->getChessType()) {
            return -1;
        }
    }

    if (chess1->getChessType() == zhadan) {
        return -1;
    }

    return -2;
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
    bool c1 = currY == 6;
    bool c2 = currY == 7;
    bool c3 = y == 6;
    bool c4 = y == 7;
    bool c5 = currX == 1 || currX == 3 || currX == 5;

    if (((c1 && c4) || (c2 && c3)) && (c5)) {
        return true;
    }

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
    QList < QPair <int, int> > vis;
    vis.append({currX, currY});

    bool c1 = searchUtil(vis, currX + 1, currY, x, y);
    bool c2 = searchUtil(vis, currX - 1, currY, x, y);
    bool c3 = searchUtil(vis, currX, currY + 1, x, y);
    bool c4 = searchUtil(vis, currX, currY - 1, x, y);

    return (c1 || c2 || c3 || c4);
}

bool Validator::searchUtil(QList < QPair <int, int> > &vis, int currX, int currY, int x, int y)
{
    if (currX == x && currY == y) {
        return true;
    }

    if (currX > 5 || currX < 1 || currY > 12 || currY < 1) {
        return false;
    }

    bool c1 = currY == 2 || currY == 6 || currY == 7 || currY == 11;
    bool c2 = (currX == 1 || currX == 5) && (currY != 1 && currY != 12);
    bool c3 = currX == 3 && (currY == 6 || currY == 7);
    if (!(c1 || c2 || c3)) {
        return false;
    }

    if (vis.contains({currX, currY})) {
        return false;
    }
    vis.append({currX, currY});

    if (grids[currY - 1][currX - 1]->getOccupied()) {
        return false;
    }

    bool c5 = searchUtil(vis, currX + 1, currY, x, y);
    bool c6 = searchUtil(vis, currX - 1, currY, x, y);
    bool c7 = searchUtil(vis, currX, currY + 1, x, y);
    bool c8 = searchUtil(vis, currX, currY - 1, x, y);

    return (c5 || c6 || c7 || c8);
}
