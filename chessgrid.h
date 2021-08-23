#ifndef CHESSGRID_H
#define CHESSGRID_H

#include <QWidget>
#include <QRandomGenerator>
#include <QDateTime>
#include "chesspiece.h"
#include "grid.h"
#include "validator.h"
#include "global.h"
#include "chessrules.h"

struct actionStruct {
    int id; // -1 for grids as they do not have ID, -2 for null
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
    void removeChess(int id);

private slots:
    void appendAction(int type, int id, int xCoord, int yCoord);
    void appendActionNetwork(int from, int id, int xCoord, int yCoord);
    void receivedSeq(QList<int> seq);

private:
    void shuffleChess();
    void arrangeChess(QList <ChessPiece*> chesspieces);
    void sendChessSeq();
    chessPieceTypedef getChessTypeFromID(int ID);

    void selectChess(int id);
    void deselectChess(int id);

    Grid* getGrid(int x, int y);
    bool isGridOccupied(int x, int y);
    void setGridOccupied(int x, int y, bool a);
    void setGridChess(int x, int y, ChessPiece* chess);
    void clearGridChess(int x, int y);
    ChessPiece* getGridChess(int x, int y);

    ChessPiece* getChessByID(int id);

    QList <int> chessSeq;
    QList < QList <Grid*> > grids;
    QList <ChessPiece*> chesspieces;

    QList <ChessPiece*> blueChess;
    QList <ChessPiece*> redChess;
    QList <int> xCoord = {0, 8, 108, 208, 308, 408};
    QList <int> yCoord = {0, 8, 60, 112, 164, 216, 268, 438, 490, 542, 594, 646, 698};
    actionStruct currAction = {-2, -2, -2};

    Ui::ChessGrid *ui;
    Validator *validate;
};

#endif // CHESSGRID_H
