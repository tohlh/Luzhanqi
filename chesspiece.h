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
    explicit ChessPiece(QWidget *parent = nullptr);
    ~ChessPiece();
    void setChess(int color, chessPieceTypedef face);

public slots:
    void flipChess();

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    bool isFlipped = false;
    int chessColor; //1 red, 2 blue
    chessPieceTypedef chessType;
    QPixmap realFace;
};

#endif // CHESSPIECE_H
