#include "chessboard.h"
#include "ui_chessboard.h"

Chessboard::Chessboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chessboard)
{
    ui->setupUi(this);

    //grid->setVisible(false);
    //layout->addWidget(grid);
    this->setLayout(layout);
}

Chessboard::~Chessboard()
{
    delete ui;
}

void Chessboard::setBlankChessboard()
{
    QPixmap blankChessboard(":/images/棋盘.png");
    ui->chessboard->setPixmap(blankChessboard);

    //grid->setVisible(false);
    this->setLayout(layout);
}

void Chessboard::setNewChessboard()
{
    QPixmap blankChessboard(":/images/棋盘背景.jpg");
    ui->chessboard->setPixmap(blankChessboard);

    //grid->setVisible(true);
    this->setLayout(layout);
}

void Chessboard::arrangeChess() {
    ChessPiece *piece = new ChessPiece(1, gongbing);
    layout->addWidget(piece, 0, 0);
    this->setLayout(layout);
}
