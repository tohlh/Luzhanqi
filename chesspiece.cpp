#include "chesspiece.h"

ChessPiece::ChessPiece(QWidget *parent) : QLabel(parent)
{

}

ChessPiece::~ChessPiece()
{

}

void ChessPiece::setChess(int color, chessPieceTypedef face)
{
    chessColor = color;
    chessType = face;
    switch(face) {
        case junqi:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/junqi_red.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/junqi_blue.png");
            }
            break;
        }
        case gongbing:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/gongbing_red.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/gongbing_blue.png");
            }
            break;
        }
        case paizhang:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/paizhang_red.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/paizhang_blue.png");
            }
            break;
        }
        case lianzhang:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/lianzhang_red.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/lianzhang_blue.png");
            }
            break;
        }
        case yingzhang:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/yingzhang_red.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/yingzhang_blue.png");
            }
            break;
        }
        case tuanzhang:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/tuanzhang_red.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/tuanzhang_blue.png");
            }
            break;
        }
        case lvzhang:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/lvzhang_red.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/lvzhang_blue.png");
            }
            break;
        }
        case shizhang:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/shizhang_red.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/shizhang_blue.png");
            }
            break;
        }
        case junzhang:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/junzhang_red.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/junzhang_blue.png");
            }
            break;
        }
        case siling:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/siling_red.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/siling_blue.png");
            }
            break;
        }
        case dilei:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/dilei_red.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/dilei_blue.png");
            }
            break;
        }
        case zhadan:
        {
            if (chessColor == 1) {
                realFace = QPixmap(":/images/zhadan_red.png");
            } else if (chessColor == 0) {
                realFace = QPixmap(":/images/zhadan_blue.png");
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

int ChessPiece::getChessColor()
{
    return chessColor;
}

chessPieceTypedef ChessPiece::getChessType()
{
    return chessType;
}

void ChessPiece::selectChess(bool yourself)
{
    QPixmap currFace = realFace;
    QPixmap selBorder;
    if (yourself) {
        selBorder = QPixmap(":/images/bg_light_chess_green.png");
    } else {
        selBorder = QPixmap(":/images/bg_light_chess_red.png");
    }
    QPainter paint(&currFace);
    //paint.drawPixmap(0, 0, 360, 185, selBorder);
    paint.drawPixmap(0, 0, 100, 55, selBorder);
    this->setPixmap(currFace);
}

void ChessPiece::deselectChess()
{
    this->setPixmap(realFace);
}

bool ChessPiece::getChessFlipped()
{
    return isFlipped;
}

void ChessPiece::flipChess()
{
    isFlipped = true;
    this->setPixmap(realFace);
}

void ChessPiece::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit sendAction(0, ID, xCoord, yCoord);
    } else {
        ChessPiece::mousePressEvent(event);
    }
}
