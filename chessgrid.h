#ifndef CHESSGRID_H
#define CHESSGRID_H

#include <QWidget>
#include <QRandomGenerator>
#include <QDateTime>
#include "chesspiece.h"
#include "grid.h"

namespace Ui {
class ChessGrid;
}

class ChessGrid : public QWidget
{
    Q_OBJECT

public:
    explicit ChessGrid(QWidget *parent = nullptr);
    ~ChessGrid();
    void moveChess(ChessPiece* chess, int x, int y);

private:
    void arrangeChess(QList <ChessPiece*> chesspieces);
    chessPieceTypedef getChessTypeFromID(int ID);

    ChessPiece *chesspiece = new ChessPiece();
    Grid *grid = new Grid();
    Ui::ChessGrid *ui;
};

#endif // CHESSGRID_H
