#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include "chessrules.h"

class ChessPiece : public QLabel
{
    Q_OBJECT

public:
    ChessPiece(QWidget *parent = nullptr);
    ~ChessPiece();
    void setChess(int color, chessPieceTypedef face);

    void setCoord(int x, int y);
    int getXCoord();
    int getYCoord();

    int x, y;

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    void flipChess();

    int xCoord, yCoord;
    bool isFlipped = false;
    int chessColor; //1 red, 2 blue
    chessPieceTypedef chessType;
    QPixmap realFace;
};

#endif // CHESSPIECE_H
