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

void Chessboard::setNewChessboard()
{
    QPixmap chessboard(":/images/emptyChessboard.png");
    ui->chessboardBackground->setPixmap(chessboard);

    if (chessgrid != nullptr) {
        delete chessgrid;
    }

    chessgrid = new ChessGrid(this);
    layout->addWidget(chessgrid, 0, 0);
    this->setLayout(layout);
}
