#include "chesspiece.h"
#include "ui_chesspiece.h"

ChessPiece::ChessPiece(QWidget *parent) : QLabel(parent)
{

}

ChessPiece::~ChessPiece()
{

}

void ChessPiece::setChess(int color, chessPieceTypedef face)
{
    chessColor = color;
    switch(face) {
        case junqi:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/军旗_红.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/军旗_蓝.png");
            }
            break;
        }
        case gongbing:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/工兵_红.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/工兵_蓝.png");
            }
            break;
        }
        case paizhang:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/排长_红.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/排长_蓝.png");
            }
            break;
        }
        case lianzhang:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/连长_红.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/连长_蓝.png");
            }
            break;
        }
        case yingzhang:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/营长_红.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/营长_蓝.png");
            }
            break;
        }
        case tuanzhang:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/团长_红.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/团长_蓝.png");
            }
            break;
        }
        case lvzhang:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/旅长_红.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/旅长_蓝.png");
            }
            break;
        }
        case shizhang:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/师长_红.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/师长_蓝.png");
            }
            break;
        }
        case junzhang:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/军长_红.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/军长_蓝.png");
            }
            break;
        }
        case siling:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/司令_红.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/司令_蓝.png");
            }
            break;
        }
        case dilei:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/地雷_红.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/地雷_蓝.png");
            }
            break;
        }
        case zhadan:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/炸弹_红.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/炸弹_蓝.png");
            }
            break;
        }
    }
}

void ChessPiece::setID(int i)
{
    ID = i;
}

int ChessPiece::getID()
{
    return ID;
}

void ChessPiece::setCoord(int x, int y)
{
    xCoord = x;
    yCoord = y;
}

int ChessPiece::getXCoord()
{
    return xCoord;
}

int ChessPiece::getYCoord()
{
    return yCoord;
}


void ChessPiece::flipChess()
{
    isFlipped = true;
    this->setPixmap(realFace);
}

void ChessPiece::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        if (!isFlipped) {
            flipChess();
        }
    } else {
        ChessPiece::mousePressEvent(event);
    }
}
