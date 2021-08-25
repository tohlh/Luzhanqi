#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include "global.h"
#include "chessrules.h"

class ChessPiece : public QLabel
{
    Q_OBJECT

public:
    ChessPiece(QWidget *parent = nullptr);
    ~ChessPiece();

    void setChess(int color, chessPieceTypedef type);
    void setID(int i);
    int getID();
    void setCoord(int x, int y);
    int getXCoord();
    int getYCoord();
    int getChessColor();
    chessPieceTypedef getChessType();

    void selectChess(bool yourself);
    void deselectChess();
    bool getChessFlipped();
    void flipChess();

signals:
    void sendAction(int type, int id, int xCoord, int yCoord);

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    int ID, xCoord, yCoord;
    bool isFlipped = false;
    int chessColor; //1 red, 2 blue
    chessPieceTypedef chessType;
    QPixmap realFace;
};

#endif // CHESSPIECE_H
