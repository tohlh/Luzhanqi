#ifndef CHESSGRID_H
#define CHESSGRID_H

#include <QWidget>
#include <QRandomGenerator>
#include <QDateTime>
#include <QStack>
#include "chesspiece.h"
#include "chessrules.h"
#include "grid.h"

struct actionStruct {
    int id; // -1 for grids as they do not have ID
    int xCoord;
    int yCoord;
};

namespace Ui {
class ChessGrid;
}

class ChessGrid : public QWidget
{
    Q_OBJECT

public:
    explicit ChessGrid(QWidget *parent = nullptr);
    ~ChessGrid();
    void moveChess(int id, int x, int y);

private slots:
    void appendAction(int id, int xCoord, int yCoord);

private:
    void arrangeChess(QList <ChessPiece*> chesspieces);
    chessPieceTypedef getChessTypeFromID(int ID);
    QStack <actionStruct> actionStack;

    ChessPiece *chesspiece = new ChessPiece();
    Grid *grid = new Grid();
    Ui::ChessGrid *ui;

    QList <Grid*> grids;
    QList <ChessPiece*> chesspieces;
    QList <int> xCoord = {0, 8, 108, 208, 308, 408};
    QList <int> yCoord = {0, 8, 60, 112, 164, 216, 268, 438, 490, 542, 594, 646, 698};
};

#endif // CHESSGRID_H
