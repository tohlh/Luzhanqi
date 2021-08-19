#ifndef CHESSGRID_H
#define CHESSGRID_H

#include <QWidget>
#include <QRandomGenerator>
#include <QDateTime>
#include "chesspiece.h"

namespace Ui {
class ChessGrid;
}

class ChessGrid : public QWidget
{
    Q_OBJECT

public:
    explicit ChessGrid(QWidget *parent = nullptr);
    ~ChessGrid();

    void arrangeChess(QList <ChessPiece*> chesspieces);
    void moveChess(ChessPiece* chess, int x, int y);

private:
    chessPieceTypedef getChessTypeFromID(int ID);
    Ui::ChessGrid *ui;
};

#endif // CHESSGRID_H
