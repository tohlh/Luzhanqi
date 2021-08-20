#ifndef CHESSGRID_H
#define CHESSGRID_H

#include <QWidget>
#include <QRandomGenerator>
#include <QDateTime>
#include "chesspiece.h"
#include "chessrules.h"
#include "grid.h"

struct actionStruct {
    int id; // -1 for grids as they do not have ID, -2 for null
    int color;
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
    void moveChess(int id, int color, int x, int y);
    void removeChess(int id, int color);

private slots:
    void appendAction(int id, int color, int xCoord, int yCoord);

private:
    void arrangeChess(QList <ChessPiece*> chesspieces);

    Grid* getGrid(int x, int y);
    bool isGridOccupied(int x, int y);
    void setGridOccupied(int x, int y, bool a);
    void setGridChess(int x, int y, ChessPiece* chess);
    void clearGridChess(int x, int y);
    ChessPiece* getGridChess(int x, int y);

    chessPieceTypedef getChessTypeFromID(int ID);
    actionStruct currAction = {-2, -2, -2, -2};

    ChessPiece *chesspiece = new ChessPiece();
    Grid *grid = new Grid();
    Ui::ChessGrid *ui;

    QList < QList <Grid*> > grids;
    QList <ChessPiece*> chesspieces;

    QList <ChessPiece*> blueChess;
    QList <ChessPiece*> redChess;
    QList <int> xCoord = {0, 8, 108, 208, 308, 408};
    QList <int> yCoord = {0, 8, 60, 112, 164, 216, 268, 438, 490, 542, 594, 646, 698};
};

#endif // CHESSGRID_H
