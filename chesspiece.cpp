#include "chesspiece.h"
#include "ui_chesspiece.h"

ChessPiece::ChessPiece(int color, chessPieceTypedef type, QWidget *parent) :
    QWidget(parent),
    chessColor(color),
    chessType(type),
    ui(new Ui::ChessPiece)
{
    ui->setupUi(this);

    switch(type) {
        case junqi:
        {
            if (color == 1) {
                realFace = QPixmap(":/images/军旗_红.png");
            } else if (color == 2) {
                realFace = QPixmap(":/images/军长_蓝.png");
            }
            break;
        }
        case gongbing:
        {
            if (color == 1) {
                realFace = QPixmap(":/images/工兵_红.png");
            } else if (color == 2) {
                realFace = QPixmap(":/images/工兵_蓝.png");
            }
            break;
        }
        case paizhang:
        {
            if (color == 1) {
                realFace = QPixmap(":/images/排长_红.png");
            } else if (color == 2) {
                realFace = QPixmap(":/images/排长_蓝.png");
            }
            break;
        }
        case lianzhang:
        {
            if (color == 1) {
                realFace = QPixmap(":/images/连长_红.png");
            } else if (color == 2) {
                realFace = QPixmap(":/images/连长_蓝.png");
            }
            break;
        }
        case yingzhang:
        {
            if (color == 1) {
                realFace = QPixmap(":/images/营长_红.png");
            } else if (color == 2) {
                realFace = QPixmap(":/images/营长_蓝.png");
            }
            break;
        }
        case tuanzhang:
        {
            if (color == 1) {
                realFace = QPixmap(":/images/团长_红.png");
            } else if (color == 2) {
                realFace = QPixmap(":/images/团长_蓝.png");
            }
            break;
        }
        case lvzhang:
        {
            if (color == 1) {
                realFace = QPixmap(":/images/旅长_红.png");
            } else if (color == 2) {
                realFace = QPixmap(":/images/旅长_蓝.png");
            }
            break;
        }
        case shizhang:
        {
            if (color == 1) {
                realFace = QPixmap(":/images/师长_红.png");
            } else if (color == 2) {
                realFace = QPixmap(":/images/师长_蓝.png");
            }
            break;
        }
        case junzhang:
        {
            if (color == 1) {
                realFace = QPixmap(":/images/军长_红.png");
            } else if (color == 2) {
                realFace = QPixmap(":/images/军长_蓝.png");
            }
            break;
        }
        case siling:
        {
            if (color == 1) {
                realFace = QPixmap(":/images/司令_红.png");
            } else if (color == 2) {
                realFace = QPixmap(":/images/司令_蓝.png");
            }
            break;
        }
        case dilei:
        {
            if (color == 1) {
                realFace = QPixmap(":/images/地雷_红.png");
            } else if (color == 2) {
                realFace = QPixmap(":/images/地雷_蓝.png");
            }
            break;
        }
        case zhadan:
        {
            if (color == 1) {
                realFace = QPixmap(":/images/炸弹_红.png");
            } else if (color == 2) {
                realFace = QPixmap(":/images/炸弹_蓝.png");
            }
            break;
        }
    }
}

ChessPiece::~ChessPiece()
{
    delete ui;
}

void ChessPiece::flipChess()
{
    isFlipped = true;
    ui->chessFace->setPixmap(realFace);
}

void ChessPiece::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        if (!isFlipped) {
            flipChess();
        } else {
            // todo
        }
    } else {
        ChessPiece::mousePressEvent(event);
    }
}
