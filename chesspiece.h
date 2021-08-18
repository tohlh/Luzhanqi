#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QWidget>
#include <QMouseEvent>
#include "chessrules.h"

namespace Ui {
class ChessPiece;
}

class ChessPiece : public QWidget
{
    Q_OBJECT

public:
    explicit ChessPiece(int color, chessPieceTypedef type, QWidget *parent = nullptr);
    ~ChessPiece();

    int chessColor; //1 red, 2 blue
    chessPieceTypedef chessType;
    QPixmap realFace;

public slots:
    void flipChess();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    Ui::ChessPiece *ui;
    bool isFlipped = false;
};

#endif // CHESSPIECE_H
