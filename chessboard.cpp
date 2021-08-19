#include "chessboard.h"
#include "ui_chessboard.h"

Chessboard::Chessboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chessboard)
{
    ui->setupUi(this);
    this->setLayout(layout);
}

Chessboard::~Chessboard()
{
    delete ui;
}

void Chessboard::setBlankChessboard()
{
    QPixmap chessboard(":/images/棋盘.png");
    ui->chessboardBackground->setPixmap(chessboard);

    if (chessgrid) {
        layout->removeWidget(chessgrid);
        delete (chessgrid);
    }
    this->setLayout(layout);
}

void Chessboard::setNewChessboard()
{
    QPixmap chessboard(":/images/空棋盘.png");
    ui->chessboardBackground->setPixmap(chessboard);

    chessgrid = new ChessGrid();
    layout->addWidget(chessgrid, 0, 0);
    this->setLayout(layout);
}
